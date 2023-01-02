#include "Render/SpriteBatch.hpp"
#include "Function/Camera.hpp"
#include "Function/Scene.hpp"
#include "Function/SceneManager.hpp"
#include "Function/Transform2D.hpp"
#include "Render/Material2D.hpp"
#include "Render/Program.hpp"
#include "Render/Texture2D.hpp"

namespace EngineS {

// SpriteBatch::SpriteBatch(std::shared_ptr<Texture2D> texture, std::shared_ptr<Program> program) :
//     _texture {texture}, _program {program} {
//     glGenVertexArrays(1, &_vao);
//     glGenBuffers(1, &_vbo);
// }

// SpriteBatch::SpriteBatch(std::shared_ptr<Material2D> material) :
//     SpriteBatch(material->GetTexture(), material->GetProgram()) {}

void SpriteBatch::Draw() {
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _triangles.size() * sizeof(Triangle), _triangles.data(), GL_STREAM_DRAW);

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
    _texture->Bind();

    _program->Use();

    glDrawArrays(GL_TRIANGLES, 0, 3 * _triangles.size());
}

void SpriteBatch::Add(const Matrix4x4& modelMat, const Vector2& anchor, const Color4F& color) {
    auto camera = SceneManager::Instance()->GetCurrentScene()->GetMainCamera();
    auto proj   = camera->GetProjectionMatrix();
    auto view   = camera->GetViewMatrix();

    V2F_C4F_T2F_Quad quad;

    quad.tl.vertices = {0.0f, 1.0f};
    quad.tr.vertices = {1.0f, 1.0f};
    quad.bl.vertices = {0.0f, 0.0f};
    quad.br.vertices = {1.0f, 0.0f};

    quad.tl.colors = color;
    quad.tr.colors = color;
    quad.bl.colors = color;
    quad.br.colors = color;

    auto doVertexTransform = [&](Vector2& vert) {
        Vector2 vertTransformed = (vert - anchor) * Vector2(_texture->GetWidth(), _texture->GetHeight());
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

    _triangles.push_back({quad.tl, quad.br, quad.bl});
    _triangles.push_back({quad.tl, quad.tr, quad.br});
}

} // namespace EngineS