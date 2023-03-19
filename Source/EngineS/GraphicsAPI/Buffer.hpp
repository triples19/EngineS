#pragma once

#include "Base/Macros.hpp"
#include "GraphicsAPI/RenderTypes.hpp"

namespace EngineS {

class Buffer : public Object {
    ES_OBJECT
  public:
    Buffer(std::size_t size, BufferType type, BufferUsage usage);
    virtual ~Buffer() = default;

    virtual void UpdateData(const byte* data) = 0;

  protected:
    std::size_t _size;
    BufferType  _type;
    BufferUsage _usage;
};

} // namespace EngineS
