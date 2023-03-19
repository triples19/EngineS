#include "GraphicsAPI/Buffer.hpp"

namespace EngineS {

Buffer::Buffer(std::size_t size, BufferType type, BufferUsage usage) : _size(size), _type(type), _usage(usage) {}

} // namespace EngineS
