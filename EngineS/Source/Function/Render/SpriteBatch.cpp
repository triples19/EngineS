#include "Function/Render/SpriteBatch.hpp"

#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Camera.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Render/Material2D.hpp"
#include "Function/Render/Program.hpp"
#include "Function/Render/Texture2D.hpp"
#include "Function/Scene/SceneManager.hpp"

namespace EngineS {

SpriteBatch::SpriteBatch(std::shared_ptr<Texture2D> texture, std::shared_ptr<Program> program) :
	_texture {texture}, _program {program} {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
}

SpriteBatch::SpriteBatch(std::shared_ptr<Material2D> material) :
	SpriteBatch(material->GetTexture(), material->GetProgram()) {}

void SpriteBatch::Add(const Vector2& position, float rotation, const Vector2& scale) {
	auto			 camera = SceneManager::Instance()->GetCurrentScene()->GetMainCamera();
	V2F_C4F_T2F_Quad quad;
	Vector2			 up, right;

	right = {_texture->width / 2.0f * scale.x, 0};
	up	  = {0, _texture->height / 2.0f * scale.y};
	up	  = Vector2::Rotate(up, rotation);
	right = Vector2::Rotate(right, rotation);

	Vector2 ortho {camera->width / 2.0f, camera->height / 2.0f};

	quad.tl.vertices = (position + up - right) / ortho;
	quad.tr.vertices = (position + up + right) / ortho;
	quad.bl.vertices = (position - up - right) / ortho;
	quad.br.vertices = (position - up + right) / ortho;

	quad.tl.texCoords = {0.0f, 1.0f};
	quad.tr.texCoords = {1.0f, 1.0f};
	quad.bl.texCoords = {0.0f, 0.0f};
	quad.br.texCoords = {1.0f, 0.0f};

	_triangles.push_back({quad.tl, quad.br, quad.bl});
	_triangles.push_back({quad.tl, quad.tr, quad.br});
}

void SpriteBatch::Draw() {
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _triangles.size() * sizeof(Triangle), _triangles.data(), GL_STREAM_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4F_T2F), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,
						  4,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(V2F_C4F_T2F),
						  reinterpret_cast<const void*>(sizeof(Vector2)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2,
						  2,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(V2F_C4F_T2F),
						  reinterpret_cast<const void*>(sizeof(Vector2) + sizeof(Color4F)));
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	_texture->Bind();

	_program->Use();

	glDrawArrays(GL_TRIANGLES, 0, 3 * _triangles.size());
}

void SpriteBatch::Add(const Transform2D* transform) {
	Add(transform->position, transform->rotation, transform->scale);
}

} // namespace EngineS