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

}