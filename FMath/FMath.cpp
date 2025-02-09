#include "FMath.h"

#if MATH_IMPLEMENTATION == USE_CUSTOM_MATH

float
FMath::sqrt(float n) {
  long i;
  float x, y;

  n = 1.0f / n;
  
  x = n * 0.5f;
  y = n;
  i = *(long *)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float *)&i;
  y = y * (1.5f - (x * y * y));

  return y;
}

#elif MATH_IMPLEMENTATION == USE_STD_MATH

float
FMath::sqrt(float n) {
  return std::sqrt(n);
}

#endif