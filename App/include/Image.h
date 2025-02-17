#pragma once

#include "AppConfig.h"

#include <vector>

#include <gsTypes.h>
#include <gsColor.h>

namespace opengs
{

/**
 * @brief BMP file headers
 * extradted from
 * https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
 * https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
 */

struct BMPHeader {
  uint16 type{ 0x4D42 };
  uint32 size{ 0 };
  uint16 reserved1{ 0 };
  uint16 reserved2{ 0 };
  uint32 dataOffset{ 54 };
};

struct BMPInfo {
  uint32  size{ 40 };
  int32   width{ 0 };
  int32   height{ 0 };
  uint16  planes{ 1 };
  uint16  bitCount{ 24 };
  uint32  compression{ 0 };
  uint32  sizeImage{ 0 };
  int32   xPixelsPerMeter{ 0 };
  int32   yPixelsPerMeter{ 0 };
  uint32  colorsUsed{ 0 };
  uint32  colorsImportant{ 0 };
};

class Image
{
 public:
#pragma region CONSTRUCTORS

  Image();

  Image(const Image& image);

  Image(const uint32 width,
        const uint32 height,
        const Color& color = Color::BLACK);

  ~Image();

#pragma endregion

#pragma region OPERATORS

  Image&
  operator=(const Image& image);

#pragma endregion

 public:

#pragma region METHODS

  void
	clear(const Color& color = Color::BLACK);
  
  Color
  getPixel(const uint32 x, const uint32 y) const;

  void
  setPixel(const uint32 x, const uint32 y, const Color& color);
  
  int32
  load(const char* filename);

  bool
  save(const char* filename) const;

#pragma endregion

#pragma region GETTERS

  uint32
  getWidth() const;

  uint32
  getHeight() const;

  const Color*
  getPixels() const;

#pragma endregion

 private:
  uint32 m_width;
  uint32 m_height;
  std::vector<Color> m_pixels;
};

}