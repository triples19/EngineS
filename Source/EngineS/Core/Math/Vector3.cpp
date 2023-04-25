#include "Vector3.hpp"
#include "Vector2.hpp"

#include "fmt/format.h"

namespace EngineS {

const Vector3 Vector3::Back {0, 0, -1};
const Vector3 Vector3::Down {0, -1, 0};
const Vector3 Vector3::Forward {0, 0, 1};
const Vector3 Vector3::Left {-1, 0, 0};
const Vector3 Vector3::NegativeInfinity {Math::NegInfinity};
const Vector3 Vector3::One {1, 1, 1};
const Vector3 Vector3::PositiveInfinity {Math::PosInfinity};
const Vector3 Vector3::Right {1, 0, 0};
const Vector3 Vector3::Up {0, 1, 0};
const Vector3 Vector3::Zero {0, 0, 0};

Vector3::operator Vector2() const {
    return {x, y};
}

std::string Vector3::ToString() const {
    return fmt::format("Vector3({}, {}, {})", x, y, z);
}

} // namespace EngineS