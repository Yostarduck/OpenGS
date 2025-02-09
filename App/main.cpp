#include <iostream>

#include "AppConfig.h"
#include "FMath.h"

int
main(int args, char **argv) {
  std::cout << argv[0] << " version: " << APP_VERSION_MAJOR << "." << APP_VERSION_MINOR << std::endl;
  std::cout << "sqrt(2) = " << FMath::sqrt(2) << std::endl;
  
  return 0;
}