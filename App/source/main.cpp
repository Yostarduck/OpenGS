#define SDL_MAIN_USE_CALLBACKS 1

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_main.h>

#include <gsMath.h>

#include "AppConfig.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

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

#pragma region SDL_FUNCTIONS

SDL_AppResult
SDL_AppInit(void **appstate, int argc, char *argv[]) {
  std::cout << "Executing " << APP_NAME << " from path: " << argv[0] << std::endl;
  
  std::cout << APP_NAME << " version: " << APP_VERSION_MAJOR << "." << APP_VERSION_MINOR << std::endl;
  
  SDL_Log("SDL version: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);

  std::string appVersion = std::to_string(APP_VERSION_MAJOR) + "." + std::to_string(APP_VERSION_MINOR);
  SDL_SetAppMetadata(APP_NAME, appVersion.c_str(), "com.yostarduck.app");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer(APP_NAME, 640, 480, 0, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  
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
  
  const float red = (float) (0.5 + 0.5 * SDL_sin(now));
  const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
  const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
  
  SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
  
  SDL_RenderClear(renderer);
  
  SDL_RenderPresent(renderer);
  
  return SDL_APP_CONTINUE;
}

void
SDL_AppQuit(void *appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
}

#pragma endregion