#pragma once

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <limits>

#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace EngineS {

class Math {
  public:
	static constexpr float PosInfinity	 = std::numeric_limits<float>::infinity();
	static constexpr float NegInfinity	 = -std::numeric_limits<float>::infinity();
	static constexpr float Pi			 = 3.14159265358979323846264338327950288f;
	static constexpr float OneOverPi	 = 1.0f / Pi;
	static constexpr float TwoPi		 = 2.0f * Pi;
	static constexpr float HalfPi		 = 0.5f * Pi;
	static constexpr float Deg2Rad		 = Pi / 180.0f;
	static constexpr float Rad2Deg		 = 180.0f / Pi;
	static constexpr float Log2			 = 0.30102999566f;
	static constexpr float Epsilon		 = 1e-6f;
	static constexpr float FloatEpsilon	 = FLT_EPSILON;
	static constexpr float DoubleEpsilon = DBL_EPSILON;

	static float Sin(float value) { return std::sin(value); }
	static float Cos(float value) { return std::cos(value); }
	static float Tan(float value) { return std::tan(value); }
	static float Acos(float value) { return std::acos(value); }
	static float Asin(float value) { return std::asin(value); }
	static float Atan(float value) { return std::atan(value); }

	static float Abs(float value) { return std::fabs(value); }
	static bool	 IsNaN(float f) { return std::isnan(f); }
	static float Sqr(float value) { return value * value; }
	static float Sqrt(float fValue) { return std::sqrt(fValue); }
	static float InvSqrt(float value) { return 1.f / Sqrt(value); }
	static bool	 RealEqual(float a, float b, float tolerance = std::numeric_limits<float>::epsilon()) {
		 return std::fabs(b - a) <= tolerance;
	}
	static float Clamp(float v, float min, float max) { return std::clamp(v, min, max); }

	template<class T>
	static constexpr T Max(const T a, const T b) {
		return std::max(a, b);
	}

	template<class T>
	static constexpr T Min(const T a, const T b) {
		return std::min(a, b);
	}
};

} // namespace EngineS
