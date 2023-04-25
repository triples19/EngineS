#pragma once

#include "Core/Math/Color.hpp"
#include "Core/Math/Vector2.hpp"

namespace EngineS {

struct Tex2F {
    float u {.0f}, v {.0f};

    Tex2F() = default;
    Tex2F(float _u, float _v) : u {_u}, v {_v} {}
};

struct V2F_C4F_T2F {
    Vector2 vertices;
    Color4F colors;
    Tex2F   texCoords;
};

struct V2F_C4F_T2F_Quad {
    V2F_C4F_T2F bl;
    V2F_C4F_T2F br;
    V2F_C4F_T2F tl;
    V2F_C4F_T2F tr;
};

} // namespace EngineS
