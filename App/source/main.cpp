#define SDL_MAIN_USE_CALLBACKS 1
#define WINDDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include <iostream>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_main.h>

#include <gsMath.h>
#include <gsTriangle.h>

#include "AppConfig.h"

#include "Image.h"

static SDL_Window*    window    = nullptr;
static SDL_Renderer*  renderer  = nullptr;
static SDL_Texture*   texture   = nullptr;

static opengs::Image* screenImage = nullptr;

static opengs::Image* CubeFaceFront   = nullptr;
static opengs::Image* CubeFaceLeft    = nullptr;
static opengs::Image* CubeFaceTop     = nullptr;
static opengs::Image* CubeFaceBack    = nullptr;
static opengs::Image* CubeFaceRight   = nullptr;
static opengs::Image* CubeFaceBottom  = nullptr;

static std::vector<opengs::Triangle> triangles;
static std::vector<opengs::Vertex>   vertices;

#pragma region FORWARD_DECLARATIONS

void
DrawTriangle(opengs::Triangle* triangle, opengs::Image* image);

#pragma endregion

#pragma region SDL_FORWARD_DECLARATIONS

SDL_AppResult
SDL_AppInit(void **appstate, int argc, char *argv[]);

SDL_AppResult
SDL_AppEvent(void *appstate, SDL_Event *event);

SDL_AppResult
SDL_AppIterate(void *appstate);

void
SDL_AppQuit(void *appstate, SDL_AppResult result);

#pragma endregion

#pragma region FUNCTIONS

void
DrawTriangle(const opengs::Triangle* triangle, opengs::Image* image) {
  using namespace opengs;

  if (triangle == nullptr || image == nullptr)
    return;
    
  const Vector3 normal = triangle->getNormal();
  
  const float dot = normal.dot(Vector3::Forward);
  
  if (dot > 0.0f)
    return;
  
  const Vertex* v1 = triangle->getVertex1();
  const Vertex* v2 = triangle->getVertex2();
  const Vertex* v3 = triangle->getVertex3();
  
  int32 v1y = round(v1->y);
  int32 v2y = round(v2->y);
  int32 v3y = round(v3->y);

  int32 v1x = round(v1->x);
  int32 v2x = round(v2->x);
  int32 v3x = round(v3->x);

  int32 minY = 0;
  int32 maxY = 0;
  {
    minY = Math::min(Math::min(v1y, v2y), v3y);
    maxY = Math::max(Math::max(v1y, v2y), v3y);
  }

  uint32 verticalPixels = (maxY - minY) + 1;

  std::vector<Vertex> leftPixels(verticalPixels);
  std::vector<Vertex> rightPixels(verticalPixels);

  for (uint32 i = 0; i < verticalPixels; i++) {
    leftPixels[i]   = Vertex(Math::MAX_FLOAT, 0.0f, 0.0f, 0.0f, 0.0f);
    rightPixels[i]  = Vertex(Math::MIN_FLOAT, 0.0f, 0.0f, 0.0f, 0.0f);
  }
  
  auto generatePixels = [&](const Vertex* a, const Vertex* b)
  {
    const int32 ax = round(a->x);
    const int32 bx = round(b->x);
    
    const int32 ay = round(a->y);
    const int32 by = round(b->y);

    const uint32 width  = Math::max(bx, ax) - Math::min(bx, ax);
    const uint32 height = Math::max(by, ay) - Math::min(by, ay);
    const uint32 steps  = Math::max(width, height);

    const float edgeLenght = (b->vector - a->vector).length();

    for (uint32 i = 0; i < steps; i++) {
      const float t = (float)i / (float)steps;
      
      const Vertex v = Math::lerp(*a, *b, t);
      
      const int32 y = round(v.y);
      
      if (y >= minY && y <= maxY) {
        const uint32 index = y - minY;
        
        if (v.x < leftPixels[index].x)
          leftPixels[index] = v;
        
        if (v.x > rightPixels[index].x)
          rightPixels[index] = v;
      }
    }
  };

  generatePixels(v1, v2);
  generatePixels(v2, v3);
  generatePixels(v3, v1);

  for (uint32 y = minY; y <= maxY; y++) {
    const uint32 index = y - minY;
    
    const Vertex& left = leftPixels[index];
    const Vertex& right = rightPixels[index];
    
    const uint32 xStart = round(left.x);
    const uint32 xEnd = round(right.x);
    
    for (uint32 x = xStart; x <= xEnd; x++) {
      const float t = (float)(x - xStart) / (float)(xEnd - xStart);
      const Vertex v = Math::lerp(left, right, t);

      image->setPixel(x, y, Color(v.u, v.v, 0.0f));
    }
  }
}

#pragma endregion

#pragma region SDL_FUNCTIONS

SDL_AppResult
SDL_AppInit(void **appstate, int argc, char *argv[]) {
  std::cout << "Executing " << APP_NAME << " from path: " << argv[0] << std::endl;
  
  std::cout << APP_NAME << " version: " << APP_VERSION_MAJOR << "." << APP_VERSION_MINOR << std::endl;
  
  std::cout << "SDL version: "
            << SDL_MAJOR_VERSION << "."
            << SDL_MINOR_VERSION << "."
            << SDL_MICRO_VERSION << "."
            << std::endl;

  std::string appVersion = std::to_string(APP_VERSION_MAJOR) + "." + std::to_string(APP_VERSION_MINOR);
  SDL_SetAppMetadata(APP_NAME, appVersion.c_str(), "com.yostarduck.app");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer(APP_NAME, WINDDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
    std::cout << "Couldn't create window/renderer: " << SDL_GetError() << std::endl;
    return SDL_APP_FAILURE;
  }

  texture = SDL_CreateTexture(renderer,
                              SDL_PIXELFORMAT_RGBA128_FLOAT,
                              SDL_TEXTUREACCESS_STREAMING,
                              WINDDOW_WIDTH,
                              WINDOW_HEIGHT);

  screenImage   = new opengs::Image(WINDDOW_WIDTH, WINDOW_HEIGHT);
  CubeFaceFront = new opengs::Image();
  CubeFaceLeft  = new opengs::Image();
  CubeFaceTop   = new opengs::Image();

  opengs::uint32 result;

  result = CubeFaceFront->load("Assets/Textures/TitanCameraMan.bmp");
  if (result < 0)
    std::cout << "Couldn't load TitanCameraMan image error code: " << result << std::endl;
    
  result = CubeFaceLeft->load("Assets/Textures/TitanSpeakerMan.bmp");
  if (result < 0)
    std::cout << "Couldn't load TitanSpeakerMan image error code: " << result << std::endl;
    
  result = CubeFaceTop->load("Assets/Textures/TitanTVMan.bmp");
  if (result < 0)
    std::cout << "Couldn't load TitanTVMan image error code: " << result << std::endl;
  
  vertices.resize(4);
  // Front Face
  {  
    vertices[0] = opengs::Vertex( 590.0f, 310.0f, 50.0f, 0.0f, 0.0f); // Front Bottom Left
    vertices[1] = opengs::Vertex( 590.0f, 410.0f, 50.0f, 0.0f, 1.0f); // Front Top    Left
    vertices[2] = opengs::Vertex( 690.0f, 310.0f, 50.0f, 1.0f, 0.0f); // Front Bottom Right
    vertices[3] = opengs::Vertex( 690.0f, 410.0f, 50.0f, 1.0f, 1.0f); // Front Top    Right
  }

  triangles.resize(2);
  triangles[0] = opengs::Triangle(&vertices[0], &vertices[1], &vertices[2]); 
  triangles[1] = opengs::Triangle(&vertices[3], &vertices[2], &vertices[1]); 
  
  return SDL_APP_CONTINUE;
}

SDL_AppResult
SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult
SDL_AppIterate(void *appstate) {
  const double now = ((double)SDL_GetTicks()) / 1000.0;
  
  const float red   = (float) (0.5 + 0.5 * SDL_sin(now));
  const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
  const float blue  = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
  
  for (int y = 0; y < WINDOW_HEIGHT; y++) {
    for (int x = 0; x < WINDDOW_WIDTH; x++) {
      screenImage->setPixel(x, y, opengs::Color(red, green, blue));
    }
  }
  
  for (const opengs::Triangle& triangle : triangles) {
    DrawTriangle(&triangle, screenImage);
  }
  
  SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.0f, 0.0f, SDL_ALPHA_OPAQUE_FLOAT);
  SDL_RenderClear(renderer);

  SDL_Surface* imgSurface = SDL_CreateSurfaceFrom(screenImage->getWidth(),
                                                  screenImage->getHeight(),
                                                  SDL_PIXELFORMAT_RGBA128_FLOAT,
                                                  screenImage->getPixels(),
                                                  screenImage->getWidth() * sizeof(opengs::Color));

  SDL_Surface* surface = nullptr;
  if (SDL_LockTextureToSurface(texture, nullptr, &surface)) {
    SDL_BlitSurface(imgSurface, nullptr, surface, nullptr);
    
    SDL_UnlockTexture(texture);
  }

  SDL_DestroySurface(imgSurface);

  SDL_FRect dstRect = { 0, 0, WINDDOW_WIDTH, WINDOW_HEIGHT };
  SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
  
  SDL_RenderPresent(renderer);
  
  return SDL_APP_CONTINUE;
}

void
SDL_AppQuit(void *appstate, SDL_AppResult result) {
  // SDL will clean up the window/renderer for us.
  
  SDL_DestroyTexture(texture);
  
  if (screenImage != nullptr)
    delete screenImage;

  if (CubeFaceFront != nullptr)
    delete CubeFaceFront;
  if (CubeFaceLeft != nullptr)
    delete CubeFaceLeft;
  if (CubeFaceTop != nullptr)
    delete CubeFaceTop;
  if (CubeFaceBack != nullptr)
    delete CubeFaceBack;
  if (CubeFaceRight != nullptr)
    delete CubeFaceRight;
  if (CubeFaceBottom != nullptr)
    delete CubeFaceBottom;

  if (!triangles.empty())
    triangles.clear();
  if (!vertices.empty())
    vertices.clear();
}

#pragma endregion