#include "Render/SpriteRenderer.hpp"
#include "Function/Camera.hpp"
#include "Function/GameObject.hpp"
#include "Function/Scene.hpp"
#include "Function/SceneManager.hpp"
#include "Function/Transform2D.hpp"
#include "Math/Math.hpp"
#include "Render/Material2D.hpp"
#include "Render/Program.hpp"
#include "Render/RenderSystem.hpp"
#include "Render/Texture2D.hpp"

namespace EngineS {

SpriteRenderer::SpriteRenderer() {
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
}

void SpriteRenderer::Render(const Matrix4x4& modelMat) {
    if (!_material) {
        return;
    }
    auto camera = SceneManager::Instance()->GetCurrentScene()->GetMainCamera();
    auto proj   = camera->GetProjectionMatrix();
    auto view   = camera->GetViewMatrix();

    V2F_C4F_T2F_Quad quad;

    quad.tl.vertices = {0.0f, 1.0f};
    quad.tr.vertices = {1.0f, 1.0f};
    quad.bl.vertices = {0.0f, 0.0f};
    quad.br.vertices = {1.0f, 0.0f};

    quad.tl.colors = _color;
    quad.tr.colors = _color;
    quad.bl.colors = _color;
    quad.br.colors = _color;

    auto doVertexTransform = [&](Vector2& vert) {
        auto    texture         = _material->GetTexture();
        Vector2 vertTransformed = (vert - _anchor) * Vector2(texture->GetWidth(), texture->GetHeight());
        Vector4 vertHomo {vertTransformed.x, vertTransformed.y, 0.0f, 1.0f};
        vertHomo = proj * view * modelMat * vertHomo;
        vert     = {vertHomo.x, vertHomo.y};
    };

    doVertexTransform(quad.tl.vertices);
    doVertexTransform(quad.tr.vertices);
    doVertexTransform(quad.bl.vertices);
    doVertexTransform(quad.br.vertices);

    quad.tl.texCoords = {0.0f, 1.0f};
    quad.tr.texCoords = {1.0f, 1.0f};
    quad.bl.texCoords = {0.0f, 0.0f};
    quad.br.texCoords = {1.0f, 0.0f};

    std::array<V2F_C4F_T2F, 6> buffer = {quad.tl, quad.br, quad.bl, quad.tl, quad.tr, quad.br};

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(V2F_C4F_T2F), buffer.data(), GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4F_T2F), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(V2F_C4F_T2F),
        reinterpret_cast<const void*>(sizeof(Vector2))
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(V2F_C4F_T2F),
        reinterpret_cast<const void*>(sizeof(Vector2) + sizeof(Color4F))
    );
    glEnableVertexAttribArray(2);

    glActiveTexture(GL_TEXTURE0);
    _material->GetTexture()->Bind();
    _material->GetProgram()->Use();

    glDrawArrays(GL_TRIANGLES, 0, buffer.size());
}

void SpriteRenderer::Initialize(GameObject* parent) {
    Renderer::Initialize(parent);
}

} // namespace EngineS