#pragma once

#include "Utility.h"

class Object;

class Component {

public:
	Object* object = nullptr;

	virtual void Render(SDL_Renderer* renderer) {}
	virtual void Process(Uint64 deltaTime) {}
	virtual void Construct() {}
};