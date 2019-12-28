#pragma once

#include "Object.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

enum EngineState {
	RUNNING,
	STOP
};

class Engine
{
public:
	Engine(std::string name);
	~Engine() { }

	void Render();
	void Process();
	void Listen();
	void Clean();

	EngineState GetState() const;

private:
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	SDL_Event event;

	Uint64 currentFrame = 0;
	Uint64 lastFrame = 0;

	EngineState engineState = STOP;

	Object* object = nullptr;
};

