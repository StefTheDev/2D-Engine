#pragma once

#include "Component.h"

class TransformComponent : public Component
{
public:

	void Process(Uint64 deltaTime) override {

		//TODO: position based on deltatime

		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	void SetSpeed(float speed) {
		this->speed = speed;
	}

	void SetPosition(Vector2 position) {
		this->position = position;
	}

	void SetVelocity(Vector2 velocity) {
		this->velocity = velocity;
	}

	float GetSpeed() {
		return speed;
	}

	Vector2 GetPosition() {
		return position;
	}

	Vector2 GetVelocity() {
		return velocity;
	}

private:
	float speed = 0.0f;
	Vector2 position = { 0.0f, 0.0f }, velocity = { 0.0f, 0.0f };
};