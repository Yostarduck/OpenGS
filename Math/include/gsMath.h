#pragma once

#include "gsMathConfig.h"
#include "gsTypes.h"

#include <cmath>

#undef max
#undef min

namespace opengs
{

struct MATH_API Math
{

  //////////////////////////////
  // Constants
  //////////////////////////////

  static const float PI;
  static const float HALF_PI;
  static const float QUARTER_PI;
  static const float ONE_OVER_PI;

  static const float TAU;
  static const float HALF_TAU;
  static const float QUARTER_TAU;
  static const float ONE_OVER_TAU;

  static const float EULER;
  static const float DEGREE_TO_RADIAN;
  static const float RADIAN_TO_DEGREE;

  static const float EPSILON;
  static const float SMALL_NUMBER;

  //////////////////////////////
  // Limits
  //////////////////////////////

  static const float MAX_FLOAT;
  static const float MIN_FLOAT;
  static const float MIN_POSITIVE_FLOAT;

  static const int64  MAX_INT64;
  static const int64  MIN_INT64;
  static const int32  MAX_INT32;
  static const int32  MIN_INT32;
  static const int16  MAX_INT16;
  static const int16  MIN_INT16;
  static const int8   MAX_INT8;
  static const int8   MIN_INT8;

  static const uint64 MAX_UINT64;
  static const uint32 MAX_UINT32;
  static const uint16 MAX_UINT16;
  static const uint8  MAX_UINT8;

  //////////////////////////////
  // Math functions
  //////////////////////////////

  static float
  almostEqual(float a, float b) {
    return Math::abs(a - b) < Math::EPSILON;
  }

  static float
  cos(float value){
    return std::cosf(value);
  }

  static float
  aCos(float value) {
    return std::acosf(value);
  }

  static float
  sin(float value) {
    return std::sinf(value);
  }

  static float
  aSin(float value) {
    return std::asinf(value);
  }

  static float
  tan(float value) {
    return std::tanf(value);
  }

  static float
  aTan(float value) {
    return std::atanf(value);
  }

  static float
  aTan2(float y, float x) {
    return std::atan2f(y,x);
  }

  static float
  sqrt(float value) {
    return std::sqrtf(value);
  }

  static float
  pow(float a, float b) {
    return std::powf(a,b);
  }

  static float
  exp(float value) {
    return std::expf(value);
  }

  static int32
  truncate2Int(float value) {
    return static_cast<int32>(value);
  }

  static float
  truncate2Float(float value) {
    return static_cast<float>(truncate2Int(value));
  }

  static float
  ceil(float value) {
    return std::ceilf(value);
  }

  static float
  floor(float value) {
    return std::floorf(value);
  }

  static int32
  round(float value) {
    return truncate2Int(floor(value + 0.5f));
  }

  static float
  logE(float value) {
    return std::logf(value);
  }

  static float
  logX(float base,float value) {
    return logE(value) / logE(base);
  }
  
  //////////////////////////////
  // Math function templates
  //////////////////////////////
  
  template<class T>
  static T
  abs(const T A) {
    return (A >= static_cast<T>(0)) ? A : -A;
  }

  template<class T>
  static T
  mod(T value, T divisor) {
    return value % divisor;
  }
  
  template<class T>
  static T
  max(const T A, const T B) {
    return (A >= B) ? A : B;
  }
  
  template<class T>
  static T
  min(const T A, const T B) {
    return (A <= B) ? A : B;
  }
  
  template<class T>
  static T
  square(const T A) {
    return A * A;
  }
  
  template<class T>
  static T
  clamp(const T X, const T Min, const T Max) {
    return (X < Min) ? Min : ((X < Max) ? X : Max);
  }
  
  template<class T>
  static T
  lerp(const T a, const T b, const float proportion) {
    return (a * (1.0f - proportion)) + (b * proportion);
  }

  template<class T>
  static float
  invLerp(const T a, const T b, const T value) {
    return (value - a) / (b - a);
  }
  
  //////////////////////////////
  // Template specialization
  //////////////////////////////
  
  template<>
  static float
  abs<float>(float value) {
    return std::fabsf(value);
  }
  
  template<>
  static float
  mod(float value, float divisor) {
    return std::fmodf(value, divisor);
  }
};

}