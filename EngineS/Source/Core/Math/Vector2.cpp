#include "Vector2.hpp"
#include "Vector3.hpp"

namespace EngineS {

const Vector2 Vector2::Down {0, -1};
const Vector2 Vector2::Left {-1, 0};
const Vector2 Vector2::NegativeInfinity {Math::NegInfinity};
const Vector2 Vector2::One {1, 1};
const Vector2 Vector2::PositiveInfinity {Math::PosInfinity};
const Vector2 Vector2::Right {1, 0};
const Vector2 Vector2::Up {0, 1};
const Vector2 Vector2::Zero {0, 0};

Vector2::operator Vector3() const {
	return {x, y, 0};
}

} // namespace EngineS