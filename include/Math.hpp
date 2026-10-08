/*
创建来储存我自己写的一些计算矩阵的公式
*/
#pragma once
#include "CS171.hpp"

namespace cs171 {

Mat4f<>::AsStorage rotate(float theta, Vec3f<>::AsStorage const &axis);

Mat4f<>::AsStorage scale(float s);

Mat4f<>::AsStorage translation(Vec3f<>::AsStorage pos, Vec3f<>::AsStorage center);

Mat4f<>::AsStorage
lookAt(Vec3f<>::AsStorage const &eye, Vec3f<>::AsStorage const &center, Vec3f<>::AsStorage const &up);

Mat4f<>::AsStorage perspective(float fovY, float aspect, float nearplane, float farplane);

float OnSphere(
    Vec3f<>::AsStorage const &eye, Vec3f<>::AsStorage const &direction, float R, Vec3f<>::AsStorage const &center
);
} // namespace cs171
