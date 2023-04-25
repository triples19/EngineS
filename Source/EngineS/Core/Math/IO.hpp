#pragma once

#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include <ostream>

namespace EngineS {

inline std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << v.ToString();
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << v.ToString();
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Vector4& v) {
    os << v.ToString();
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Matrix3x3& v) {
    os << v.ToString();
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Matrix4x4& v) {
    os << v.ToString();
    return os;
}

} // namespace EngineS

// for fmt's std::ostream support
#include "fmt/ostream.h"
template<>
struct fmt::formatter<EngineS::Vector2> : fmt::ostream_formatter {};
template<>
struct fmt::formatter<EngineS::Vector3> : fmt::ostream_formatter {};
template<>
struct fmt::formatter<EngineS::Vector4> : fmt::ostream_formatter {};
template<>
struct fmt::formatter<EngineS::Matrix3x3> : fmt::ostream_formatter {};
template<>
struct fmt::formatter<EngineS::Matrix4x4> : fmt::ostream_formatter {};