#include "gsMath.h"

#include <limits>

namespace opengs
{

//////////////////////////////
// Constants
//////////////////////////////

const float Math::PI          = std::acosf(-1.0f);
const float Math::HALF_PI     = std::acosf(-1.0f) * 0.5f;
const float Math::QUARTER_PI  = std::acosf(-1.0f) * 0.25f;
const float Math::ONE_OVER_PI = 1.0f / std::acosf(-1.0f);

const float Math::TAU           = std::acosf(-1.0f) * 2.0f;
const float Math::HALF_TAU      = std::acosf(-1.0f);
const float Math::QUARTER_TAU   = std::acosf(-1.0f) * 0.5f;
const float Math::ONE_OVER_TAU  = 1.0f / (std::acosf(-1.0f) * 2.0f);

const float Math::EULER             = std::expf(1.0f);
const float Math::DEGREE_TO_RADIAN  = std::acosf(-1.0f) / 180.0f;
const float Math::RADIAN_TO_DEGREE  = 180 / std::acosf(-1.0f);

const float Math::EPSILON       = 0.0001f;
const float Math::SMALL_NUMBER  = std::numeric_limits<float>::min();

//////////////////////////////
// Limits
//////////////////////////////

const float Math::MAX_FLOAT           = std::numeric_limits<float>::max();
const float Math::MIN_FLOAT           = std::numeric_limits<float>::lowest();
const float Math::MIN_POSITIVE_FLOAT  = std::numeric_limits<float>::min();

const int64 Math::MAX_INT64 = std::numeric_limits<int64>::max();
const int64 Math::MIN_INT64 = std::numeric_limits<int64>::lowest();
const int32 Math::MAX_INT32 = std::numeric_limits<int32>::max();
const int32 Math::MIN_INT32 = std::numeric_limits<int32>::lowest();
const int16 Math::MAX_INT16 = std::numeric_limits<int16>::max();
const int16 Math::MIN_INT16 = std::numeric_limits<int16>::lowest();
const int8  Math::MAX_INT8  = std::numeric_limits<int8>::max();
const int8  Math::MIN_INT8  = std::numeric_limits<int8>::lowest();

const uint64  Math::MAX_UINT64  = std::numeric_limits<uint64>::max();
const uint32  Math::MAX_UINT32  = std::numeric_limits<uint32>::max();
const uint16  Math::MAX_UINT16  = std::numeric_limits<uint16>::max();
const uint8   Math::MAX_UINT8   = std::numeric_limits<uint8>::max();

}