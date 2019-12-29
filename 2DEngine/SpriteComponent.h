#pragma once

#include "Object.h"
#include "TransformComponent.h"

class SpriteComponent : public Component 
{
public:
	SpriteComponent(SDL_Surface* surface, SDL_Renderer* renderer, std::string fileName)
	{
		texture = IMG_LoadTexture(renderer, fileName.c_str());

		source.x = source.y = 0;
		SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
	}

	~SpriteComponent() 
	{
		SDL_DestroyTexture(texture);
	}

	void Link() override
	{
		transform = &object->GetComponent<TransformComponent>();

		if (transform != nullptr)
		{
			transform->SetSpeed(0.5f);
			transform->SetVelocity({ 1.0f, 0.0f });
		}
		else 
		{
			std::cout << "[Error] SpriteComponent needs the TransformComponent to function." << std::endl;
		}
	}

	void Render(SDL_Renderer* renderer) override 
	{
		if (transform != nullptr) {
			destination = {
				static_cast<int>(transform->GetPosition().x),
				static_cast<int>(transform->GetPosition().y),
				source.w,
				source.h
			};

			SDL_RenderCopyEx(renderer, texture, &source, &destination, angle, NULL, flip);
		}
	}

	SDL_Rect GetSource() const 
	{
		return source;
	};

	SDL_Rect GetDestination() const
	{ 
		return destination;
	};

	SDL_Texture* GetTexture() const
	{
		return texture; 
	}

	float GetAngle() const
	{
		return angle; 
	}

	void SetSource(SDL_Rect source)
	{
		this->source = source;
	}

	void SetDestination(SDL_Rect destination)
	{
		this->destination = destination;
	}

	void SetTexture(SDL_Texture* texture)
	{
		this->texture = texture;
	}
	void SetAngle(float angle)
	{
		this->angle = angle; 
	}

private:
	SDL_Texture* texture = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Rect source = {}, destination = {};

	TransformComponent* transform = nullptr;

	float angle = 0.0f;
};