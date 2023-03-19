#pragma once

#include "Base/Object.hpp"
#include "Base/SharedPtr.hpp"
#include "GraphicsAPI/Program.hpp"
#include "GraphicsAPI/Texture2D.hpp"

#include <memory>

namespace EngineS {

class Program;
class Texture2D;

class Material2D : public Object {
    ES_OBJECT
  public:
    Material2D(Program* program, Texture2D* texture);

    Program*   GetProgram() const { return _program.Get(); }
    Texture2D* GetTexture() const { return _texture.Get(); }

  private:
    SharedPtr<Program>   _program;
    SharedPtr<Texture2D> _texture;
};

} // namespace EngineS
