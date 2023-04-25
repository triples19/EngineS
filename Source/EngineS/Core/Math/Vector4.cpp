#include "Vector4.hpp"
#include "Vector3.hpp"

#include "fmt/format.h"

namespace EngineS {

const Vector4 Vector4::One {1, 1, 1, 1};
const Vector4 Vector4::Zero {0, 0, 0, 0};

Vector4::Vector4(const Vector3& v3, float w) : x {v3.x}, y {v3.y}, z {v3.z}, w {w} {}

std::string Vector4::ToString() const {
    return fmt::format("Vector4({}, {}, {}, {})", x, y, z, w);
}

} // namespace EngineS