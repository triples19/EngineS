#pragma once

#include "Core/Math/MathHeaders.hpp"

#include <cstdint>

namespace EngineS {

struct Color3B {
	uint8_t r {0}, g {0}, b {0};

	Color3B() = default;
	Color3B(uint8_t _r, uint8_t _g, uint8_t _b) : r {_r}, g {_g}, b {_b} {}
};

struct Color4B {
	uint8_t r {0}, g {0}, b {0}, a {0};

	Color4B() = default;
	Color4B(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r {_r}, g {_g}, b {_b}, a {_a} {}
};

struct Color4F {
	float r {.0f}, g {.0f}, b {.0f}, a {.0f};

	Color4F() = default;
	Color4F(float _r, float _g, float _b, float _a) : r {_r}, g {_g}, b {_b}, a {_a} {}
};

struct Tex2F {
	float u {.0f}, v {.0f};

	Tex2F() = default;
	Tex2F(float _u, float _v) : u {_u}, v {_v} {}
};

struct V2F_C4F_T2F {
	Vector2 vertices;
	Color4F colors;
	Tex2F	texCoords;
};

struct V2F_C4F_T2F_Quad {
	V2F_C4F_T2F bl;
	V2F_C4F_T2F br;
	V2F_C4F_T2F tl;
	V2F_C4F_T2F tr;
};

} // namespace EngineS