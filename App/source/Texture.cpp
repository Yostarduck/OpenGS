#include "Texture.h"

#include <gsMath.h>

#include "Image.h"

namespace opengs
{

#pragma region CONSTRUCTORS

Texture::Texture()
 : m_image(nullptr) {
}

Texture::Texture(const Image* Image)
  : m_image(Image) {
}

Texture::~Texture() {
}

#pragma endregion

#pragma region METHODS

void
Texture::setImage(const Image* image) {
  m_image = image;
}

Color
Texture::sample(float u,
                float v,
                const ETextureMode& mode,
                const ESamplerFilter& sampler) {
  if (nullptr == m_image) {
    return Color::BLACK;
  }

  adjustUV(u, v, mode);

  if (ESamplerFilter::POINT == sampler){
    uint32 x = static_cast<uint32>(Math::round(u * (m_image->getWidth() - 1)));
    uint32 y = static_cast<uint32>(Math::round(v * (m_image->getHeight() - 1)));

    return m_image->getPixel(x, y);
  }
  else if (ESamplerFilter::BILINEAL == sampler) {
    uint32 imgWidth = m_image->getWidth() - 1u;
    uint32 imgHeight = m_image->getHeight() - 1u;

    float x = u * imgWidth;
    float y = v * imgHeight;

    uint32 x0 = Math::clamp(static_cast<uint32>(x), 0u, imgWidth);
    uint32 y0 = Math::clamp(static_cast<uint32>(y), 0u, imgHeight);

    uint32 x1 = Math::min(x0 + 1, imgWidth);
    uint32 y1 = Math::min(y0 + 1, imgHeight);

    float dx = x - x0;
    float dy = y - y0;

    Color c00(m_image->getPixel(x0, y0));
    Color c10(m_image->getPixel(x1, y0));
    Color c01(m_image->getPixel(x0, y1));
    Color c11(m_image->getPixel(x1, y1));

    Color c0 = Math::lerp(c00, c10, dx);
    Color c1 = Math::lerp(c01, c11, dx);
    
    return Math::lerp(c0, c1, dy);
  }
  else if (ESamplerFilter::TRILINEAL == sampler){
    // No mipmaps, no trilinear filtering. Default to bilinear.
    return sample(u, v, mode, ESamplerFilter::BILINEAL);
  }
  
  return Color::BLACK;
}

#pragma endregion

#pragma region PROTECTED_METHODS

void
Texture::adjustUV(float& u,
                  float& v,
                  const ETextureMode& mode) {
  if (ETextureMode::NONE == mode) {
    return; 
  }
  else if (ETextureMode::CLAMP == mode) {
    u = Math::clamp(u, 0.0f, 1.0f);
    v = Math::clamp(v, 0.0f, 1.0f);
  }
  else if (ETextureMode::MIRROR == mode) {
    float tu = Math::mod(Math::abs(u), 2.0f);
    u = (tu > 1.0f) ? (2.0f - tu) : tu;
    float tv = Math::mod(Math::abs(v), 2.0f);
    v = (tv > 1.0f) ? (2.0f - tv) : tv;
  }
  else if (ETextureMode::MIRROR_ONCE == mode) {
    u = Math::clamp(u, -1.0f, 2.0f);
    v = Math::clamp(v, -1.0f, 2.0f);
    adjustUV(u, v, ETextureMode::MIRROR);
  }
  else if (ETextureMode::WRAP == mode) {
    u = Math::mod(u, 1.0f);
    v = Math::mod(v, 1.0f);
  }
}

#pragma endregion
}