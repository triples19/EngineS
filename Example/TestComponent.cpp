#include "TestComponent.hpp"

void TestComponent::Update(float deltaTime) {
	transform->rotation += deltaTime * 30.0f;
}