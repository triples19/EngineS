#include "TestComponent.hpp"

void TestComponent::Update(float deltaTime) {
    GetTransform()->rotation += deltaTime * 30.0f;
}