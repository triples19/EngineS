#include "GraphicsAPI/OpenGL/BufferOpenGL.hpp"
#include "GraphicsAPI/OpenGL/UtilsOpenGL.hpp"

namespace EngineS {

BufferOpenGL::BufferOpenGL(std::size_t size, BufferType type, BufferUsage usage) :
    Buffer(size, type, usage), _size(size), _type(UtilsOpenGL::ConvertBufferType(type)),
    _usage(UtilsOpenGL::ConvertBufferUsage(usage)) {
    glGenBuffers(1, &_buffer);
}

BufferOpenGL::~BufferOpenGL() {
    if (_buffer) {
        glDeleteBuffers(1, &_buffer);
    }
}

void BufferOpenGL::UpdateData(const byte* data) {
    glBindBuffer(_type, _buffer);
    glBufferData(_type, _size, data, _usage);

    UtilsOpenGL::CheckError();

    glBindBuffer(_type, 0);
}

} // namespace EngineS
