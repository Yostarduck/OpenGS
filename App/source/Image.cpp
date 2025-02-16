#include "Image.h"

#include <gsMath.h>
#include <fstream>

namespace opengs
{

#pragma region CONSTRUCTORS

Image::Image()
 : m_width(0), m_height(0), m_pixels(nullptr) {
}

Image::Image(const Image& image) {
  m_width = image.m_width;
  m_height = image.m_height;

  if (m_width * m_height <= 0)
    return;

  m_pixels = new Color[m_width * m_height];

  for (uint32 i = 0; i < m_width * m_height; i++) {
    m_pixels[i] = image.m_pixels[i];
  }
}

Image::Image(const uint32 width,
             const uint32 height,
             const Color& color) {
  m_width = width;
  m_height = height;

  if (m_width * m_height <= 0)
    return;

  m_pixels = new Color[m_width * m_height];

  for (uint32 i = 0; i < m_width * m_height; i++)
    m_pixels[i] = color;
}

Image::~Image() {
  if (m_pixels != nullptr)
    delete[] m_pixels;
}

#pragma endregion

#pragma region OPERATORS

Image&
Image::operator=(const Image& image) {
  m_width = image.m_width;
  m_height = image.m_height;

  if (m_pixels != nullptr)
    delete[] m_pixels;

  if (m_width * m_height <= 0)
    return *this;

  m_pixels = new Color[m_width * m_height];

  for (uint32 i = 0; i < m_width * m_height; i++)
    m_pixels[i] = image.m_pixels[i];

  return *this;
}

#pragma endregion

#pragma region METHODS

void
Image::clear(const Color& color) {
  for (uint32 i = 0; i < m_width * m_height; i++)
    m_pixels[i] = color;
}

Color
Image::getPixel(const uint32 x, const uint32 y) const {
  if (x >= m_width || y >= m_height)
    return Color::BLACK;

  return m_pixels[(y * m_width) + x];
}

void
Image::setPixel(const uint32 x,
                const uint32 y,
                const Color& color) {
  if (x >= m_width || y >= m_height)
    return;

  m_pixels[(y * m_width) + x] = color;
}

#pragma endregion

#pragma region GETTERS

uint32
Image::getWidth() const {
  return m_width;
}

uint32
Image::getHeight() const {
  return m_height;
}

Color*
Image::getPixels() const {
  return m_pixels;
}

int32
Image::load(const char* filename) {
  if (filename == nullptr)
    return -1;

  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open())
    return -2;

  BMPHeader header;
  file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
  
  BMPInfo info;
  file.read(reinterpret_cast<char*>(&info), sizeof(BMPInfo));
  
  if (header.type != (uint16)0x4D42) {
    file.close();
    return -3;
  }

  if (info.bitCount != 24) {
    file.close();
    return -4;
  }
  
  if (m_pixels != nullptr)
  delete[] m_pixels;
  
  const uint32 bitsPerPixel = info.bitCount;
  const uint32 bytesPerPixel = bitsPerPixel / 8;
  const uint32 size = m_width * m_height;
  
  m_width = info.width;
  m_height = info.height;
  m_pixels = new Color[size];
  
  uint32 columns = ((m_width * bytesPerPixel) + 3) & ~3;
  uint32 rows = m_height;
  
  uint8 b, g, r;
  uint8* rowData = new uint8[columns];
  
  file.seekg(header.dataOffset, std::ios::beg);

  for (uint32 row = 0; row < rows; row++) {
    file.read(reinterpret_cast<char*>(rowData), columns);

    for (uint32 column = 0; column < columns; column += bytesPerPixel) {
      b = rowData[column + 0];
      g = rowData[column + 1];
      r = rowData[column + 2];
      
      m_pixels[(row * m_width) + column] = Color(r / 255.0f,
                                                 g / 255.0f,
                                                 b / 255.0f);
    }
  }

  file.close();

  return 0;
}

bool
Image::save(const char* filename) const {
  return false;
}

#pragma endregion

}