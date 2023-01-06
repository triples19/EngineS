#include "TestComponent.hpp"

void TestComponent::Update(float deltaTime) {
    GetComponent<Transform2D>()->rotation += deltaTime * 30.0f;
}