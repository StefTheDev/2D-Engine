#pragma once

//Forward Decleration
class Object;

class Component 
{
public:
	Object* object = nullptr;

	virtual void Render(SDL_Renderer) {}
	virtual void Process(float deltaTime) {}
};