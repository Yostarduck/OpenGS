#include <iostream>

#include "AppConfig.h"
#include "FMath.h"

#include "SDL.h"

int
main(int args, char **argv) {
  std::cout << argv[0] << " version: " << APP_VERSION_MAJOR << "." << APP_VERSION_MINOR << std::endl;
  
  SDL_Log("SDL version: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);
  
  std::cout << "sqrt(2) = " << FMath::sqrt(2) << std::endl;

  return 0;
}