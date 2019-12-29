#pragma once

#include "SpriteComponent.h"

enum b2BodyShape {
	CIRCLE,
	POLYGON
};

class PhysicsBodyComponent : public Component 
{
public:
	PhysicsBodyComponent(b2World& world, b2BodyShape bodyShape, bool isStatic)
		: bodyShape(bodyShape), isStatic(isStatic)
	{	
		bodyDef.type = isStatic ? b2_staticBody : b2_dynamicBody;

		fixtureDef.density = isStatic ? 0.0f : 2.0f;
		fixtureDef.friction = 1.0f;
		fixtureDef.restitution = 0.45f;

		body = world.CreateBody(&bodyDef);
		body->SetAngularDamping(0.2f);
		body->SetLinearDamping(0.1f);
		body->CreateFixture(&fixtureDef);
	}

	void Link() override
	{
		spriteComponent = &object->GetComponent<SpriteComponent>();

		SDL_Rect rect = spriteComponent->GetDestination();

		switch (bodyShape)
		{
			case CIRCLE: {
				b2CircleShape circleShape;
				circleShape.m_p = b2Vec2(0.0f, 0.0f);
				circleShape.m_radius = (rect.w * PIXEL_TO_METER * 0.5f) - 0.01f;
				fixtureDef.shape = &circleShape;
			} break;
			case POLYGON: {
				b2PolygonShape boxShape;
				boxShape.SetAsBox((rect.w * PIXEL_TO_METER * 0.5f) - 0.01f, (rect.h * PIXEL_TO_METER * 0.5f) - 0.01f);
				fixtureDef.shape = &boxShape;
			} break;
		}

		bodyDef.position.Set((rect.x + rect.w / 2.0f) * PIXEL_TO_METER, (rect.y + rect.h / 2.0f) * PIXEL_TO_METER);
	}

	void Process(Uint64 deltaTime) override 
	{
		if (spriteComponent != nullptr) {
			SDL_Rect rect;
			SDL_Rect source = spriteComponent->GetSource();

			rect.x = body->GetPosition().x * METER_TO_PIXEL - source.w * 0.5f;
			rect.y = body->GetPosition().y * METER_TO_PIXEL - source.h * 0.5f;

			spriteComponent->SetDestination(rect);
			spriteComponent->SetAngle(body->GetAngle() * (1.0f / 0.01745329252f));
		}
	}

	b2Body* GetBody() const
	{
		return body;
	}

private:
	bool isStatic = false;
	b2Body* body = nullptr;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2BodyShape bodyShape = POLYGON;

	SpriteComponent* spriteComponent = nullptr;
};