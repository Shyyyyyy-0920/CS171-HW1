#pragma once
#include "CS171.hpp"
#include "stb_image.h"

#include <glad/gl.h>

namespace cs171 {
class Texture {
public:
  Texture(std::vector<std::string> const &paths);
  ~Texture() noexcept;
  void Bind();
  Texture(Texture const &) = delete;
  Texture &operator=(Texture const &) = delete;

private:
  unsigned int id_ = 0;
  int photoWidth = 0;
  int photoHeight = 0;
  int channels = 0;
  void Load(std::string const &path, GLenum target);
};
} // namespace cs171
