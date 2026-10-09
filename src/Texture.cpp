#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <stdexcept>

namespace cs171 {
Texture::Texture(std::vector<std::string> const &paths) {
  // 图片调取
  // glGenTextures(GLsizei count, GLuint *ids);
  // glBindTexture(GLenum target, GLuint id);
  if (paths.size() != 6)
    throw std::runtime_error("num is not equal to 6");
  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_CUBE_MAP, id_);
  Load(paths[0], GL_TEXTURE_CUBE_MAP_POSITIVE_X);
  Load(paths[1], GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
  Load(paths[2], GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
  Load(paths[3], GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
  Load(paths[4], GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
  Load(paths[5], GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
  // glTexParameteri()设置采样参数,三个参数分别是纹理类型、设置项、设置值
  // S是纹理的横向坐标T是纹理的纵向坐标GL_CLAMP_TO_EDGE表示采样超出边缘时沿用最近的边缘颜色，WRAP_R通常不会直接影响结果
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Texture::Load(std::string const &path, GLenum target) {
  auto pixels_ = stbi_load(path.c_str(), &photoWidth, &photoHeight, &channels, STBI_rgb);
  if (!pixels_) {
    std::cerr << path << stbi_failure_reason() << std::endl;
    stbi_image_free(pixels_);
    glDeleteTextures(1, &id_);
    throw std::runtime_error("Failed to load image: " + path);
  }
  // void glTexImage2D(
  //     GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format,
  //     GLenum type, void const *pixels);
  // target:要上传到哪个面，level：mipmap的层级，internalFormat：GPU保存像素的格式，border：边框参数，format：输入像素的通道排列，type：输入的每个分量是什么数据类型，pixels：输入像素的地址
  // 绑定纹理对象时使用GL_TEXTURE_CUBE_MAP，上传其中一个面时，使用该面的常量，比如GL_TEXTURE_CUBE_MAP_POSITIVE_X
  // GL_RGB8是告诉GPU用RGB格式保存，每个分量占8位，
  glTexImage2D(target, 0, GL_RGB8, photoWidth, photoHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels_);
  stbi_image_free(pixels_);
}

Texture::~Texture() { glDeleteTextures(1, &id_); }

void Texture::Bind() { glBindTexture(GL_TEXTURE_CUBE_MAP, id_); }
} // namespace cs171
