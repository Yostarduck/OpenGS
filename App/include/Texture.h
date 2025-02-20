#pragma once

#include <gsColor.h>
#include <gsTypes.h>

#include "AppConfig.h"

namespace opengs
{

enum class ESamplerFilter : uint32
{
  POINT = 0,
  BILINEAL,
  TRILINEAL,
  SIZE
};

enum class ETextureMode : uint32
{
  NONE = 0,
  CLAMP,
  MIRROR,
  MIRROR_ONCE,
  WRAP,
  SIZE
};

class Image;

class Texture
{
 public:
#pragma region CONSTRUCTORS

  Texture();

  Texture(const Image* Image);

  ~Texture();

#pragma endregion

 public:

#pragma region METHODS

  void
  setImage(const Image* image);

  Color
  sample(float u,
         float v,
         const ETextureMode& mode = ETextureMode::CLAMP,
         const ESamplerFilter& sampler = ESamplerFilter::POINT);

#pragma endregion

 protected:

#pragma region PROTECTED_METHODS

  void
  adjustUV(float& u,
           float& v,
           const ETextureMode& mode = ETextureMode::CLAMP);

#pragma endregion

 private:
  const Image* m_image;

};

}