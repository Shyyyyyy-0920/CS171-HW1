#include "Math.hpp"

#include <cmath>
#include <stdexcept>

namespace cs171 {

Mat4f<>::AsStorage rotate(float theta, Vec3f<>::AsStorage const &axis) {
  // 先把角度转换为弧度制
  auto rad = theta * pi<float> / 180.0f;
  constexpr float exp = 1e-12;
  Vec3f axis_ = axis;
  if (axis_.Norm() <= exp)
    throw std::invalid_argument("Cannot normalize a zero-length vector.");
  axis_ = axis_ / axis_.Norm();
  auto I = Mat3f<>::Identity();
  Mat A{Vec3f{0.0f, axis_(2), -axis_(1)}, Vec3f{-axis_(2), 0.0f, axis_(0)}, Vec3f{axis_(1), -axis_(0), 0.0f}};
  auto First = std::cos(rad) * I;
  auto Second = (1.0f - std::cos(rad)) * axis_ * axis_.Transpose();
  auto Third = std::sin(rad) * A;
  auto R = First + Second + Third;
  Mat4f<>::AsStorage M{Mat4f<>::Identity()};
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      M(i, j) = R(i, j);
  return M;
}

Mat4f<>::AsStorage scale(float s) {
  Mat4f<>::AsStorage S{Mat4f<>::Identity()};
  S(0, 0) = s;
  S(1, 1) = s;
  S(2, 2) = s;
  return S;
}

Mat4f<>::AsStorage translation(Vec3f<>::AsStorage pos, Vec3f<>::AsStorage center) {
  Mat4f<>::AsStorage T{Mat4f<>::Identity()};
  auto direction = center - pos;
  T(0, 3) = direction(0);
  T(1, 3) = direction(1);
  T(2, 3) = direction(2);
  return T;
}

Mat4f<>::AsStorage
lookAt(Vec3f<>::AsStorage const &eye, Vec3f<>::AsStorage const &center, Vec3f<>::AsStorage const &up) {
  constexpr float esp = 1e-12;
  auto f = center - eye;
  auto fn = f.Norm();
  if (fn <= esp)
    throw std::invalid_argument("Cannot normalize a zero-length vector.");
  f = f / fn;
  auto r = f.Cross(up);
  auto rn = r.Norm();
  if (rn <= esp)
    throw std::invalid_argument("Cannot normalize a zero-length vector.");
  r = r / rn;
  auto u = r.Cross(f);
  auto un = u.Norm();
  if (un <= esp)
    throw std::invalid_argument("Cannot normalize a zero-length vector.");
  u = u / un;
  Vec4f v1{r(0), u(0), -f(0), 0.0f};
  Vec4f v2{r(1), u(1), -f(1), 0.0f};
  Vec4f v3{r(2), u(2), -f(2), 0.0f};
  Vec4f v4{-r.Dot(eye), -u.Dot(eye), f.Dot(eye), 1.0f};
  Mat4f<>::AsStorage V{v1, v2, v3, v4};
  return V;
}

Mat4f<>::AsStorage perspective(float fovY, float aspect, float nearplane, float farplane) {
  constexpr float esp = 1e-12;
  if (fovY <= 0 || fovY >= 180 || farplane - nearplane <= esp || aspect <= 0 || nearplane <= 0)
    throw std::invalid_argument("Cannot normalize a zero.");
  auto rad = fovY * pi<float> / 180.0f;
  // 投影缩放系数
  auto s = 1 / std::tan(rad / 2);
  Vec4f v1{s / aspect, 0.0f, 0.0f, 0.0f};
  Vec4f v2{0.0f, s, 0.0f, 0.0f};
  Vec4f v3{0.0f, 0.0f, -(farplane + nearplane) / (farplane - nearplane), -1.0f};
  Vec4f v4{0.0f, 0.0f, -2 * farplane * nearplane / (farplane - nearplane), 0.0f};
  Mat4f<>::AsStorage P{v1, v2, v3, v4};
  return P;
}

float OnSphere(
    Vec3f<>::AsStorage const &eye, Vec3f<>::AsStorage const &direction, float R, Vec3f<>::AsStorage const &center
) {
  constexpr float esp = 1e-12;
  auto ldl = direction.Norm();
  if (ldl < esp)
    throw std::invalid_argument("Cannot normalize a zero.");
  auto d = direction / ldl;
  auto v = eye - center;
  auto lvl = v.Norm();
  if (lvl < esp)
    return R / ldl;
  v = v / lvl;
  // 设定一个容差，用于判断直线与球面相切的情况，给一定容错
  float const sigma = 8 * 1e-7 * std::max(R * R, lvl * lvl);
  float cosTheta = v.Dot(d);
  float delta = R * R - (1 - cosTheta * cosTheta) * lvl * lvl;
  if (delta < -sigma)
    return 0.0f;
  if (std::abs(delta) <= sigma)
    delta = 0.0f;
  auto t1 = (std::sqrt(delta) - lvl * cosTheta) / ldl;
  auto t2 = (-std::sqrt(delta) - lvl * cosTheta) / ldl;
  if (t1 > esp && t2 > esp)
    return std::min(t1, t2);
  if (t1 <= esp && t2 <= esp)
    return 0.0f;
  return t1;
}

float OnPlane(
    Vec3f<>::AsStorage const &eye,
    Vec3f<>::AsStorage const &direction,
    float R,
    Vec3f<>::AsStorage const &center,
    Vec3f<>::AsStorage const &normal
) {
  constexpr float esp = 1e-12;
  auto ldl = direction.Norm();
  if (ldl < esp)
    throw std::invalid_argument("Cannot normalize a zero.");
  auto d = direction / ldl;

  auto v = center - eye;

  auto lnl = normal.Norm();
  if (lnl < esp)
    throw std::invalid_argument("Cannot normalize a zero.");
  auto n = normal / lnl;

  auto low = d.Dot(n);
  auto up = v.Dot(n);
  // 这里用绝对值只是为了排除趋近于0也就是平行时的情况
  if (std::abs(low) < esp)
    return 0.0f;
  auto t = up / low;
  if (t <= esp)
    return 0.0f;
  // 交点P
  auto p = eye + t * d;
  if (std::abs(p(0) - center(0)) <= R && std::abs(p(1) - center(1)) <= R)
    return t / ldl;
  return 0.0f;
}

int nearestHitIndex(std::vector<float> const &distances) {
  auto infty = std::numeric_limits<float>::infinity();
  int n = -1;
  for (int i = 0; i < distances.size(); ++i) {
    float t = distances[i];
    if (t > 0 && t < infty) {
      infty = t;
      n = i;
    }
  }
  return n;
}

} // namespace cs171
