#pragma once

#include "Object.h"
#include "TransformComponent.h"

class SpriteComponent : public Component 
{
public:
	SpriteComponent(SDL_Surface* surface, SDL_Renderer* renderer, std::string fileName)
	{
		texture = IMG_LoadTexture(renderer, fileName.c_str());
	}

	~SpriteComponent() 
	{
		SDL_DestroyTexture(texture);
	}

	void Construct() override 
	{
		transform = &object->GetComponent<TransformComponent>();

		source.x = source.y = 0;
		SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

		transform->SetSpeed(0.5f);
		transform->SetVelocity({ 1.0f, 0.0f });
	}

	void Render(SDL_Renderer* renderer) override 
	{
		destination = {
			static_cast<int>(transform->GetPosition().x),
			static_cast<int>(transform->GetPosition().y),
			source.w,
			source.h
		};

		SDL_RenderCopy(renderer, texture, &source, &destination);
	}

private:
	TransformComponent* transform = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect source = {}, destination = {};
};