#pragma once

#include "Core/Macros.hpp"
#include "Graphics/API/Buffer.hpp"
#include "Graphics/API/RenderTypes.hpp"

#include "glad/glad.h"

namespace EngineS {

class BufferOpenGL : public Buffer {
    ES_OBJECT
  public:
    BufferOpenGL(std::size_t size, BufferType type, BufferUsage usage);
    ~BufferOpenGL();

    void UpdateData(const byte* data) override;

    GLuint GetHandler() const { return _buffer; }

  private:
    GLuint _buffer;
    size_t _size;
    GLenum _type;
    GLenum _usage;
};

} // namespace EngineS
