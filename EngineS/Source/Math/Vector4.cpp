#include "Vector4.hpp"
#include "Vector3.hpp"

namespace EngineS {

const Vector4 Vector4::One {1, 1, 1, 1};
const Vector4 Vector4::Zero {0, 0, 0, 0};

Vector4::Vector4(const Vector3& v3, float w) : x {v3.x}, y {v3.y}, z {v3.z}, w {w} {}

} // namespace EngineS