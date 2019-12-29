#pragma once

#include "Component.h"

class Object
{
public:
	Object(std::type_index index) : index(index) {}

	~Object()
	{
		for (auto& component : components) delete component.second;
	}

	void Process(Uint64 deltaTime)
	{
		for (auto& component : components) component.second->Process(deltaTime);
	}

	void Render(SDL_Renderer* renderer) 
	{
		for (auto& component : components) component.second->Render(renderer);
	}

	template <typename T, typename... A> void AddComponent(A&& ... a)
	{
		T* component = new T(std::forward<A>(a)...);
		component->object = this;
		component->Link();

		components.insert(std::pair<std::type_index, Component*>(
			std::type_index(typeid(T)),
			std::move(component)
		));
	}

	template <typename T> T& GetComponent()
	{
		return *dynamic_cast<T*>(components[std::type_index(typeid(T))]);
	}

	std::type_index GetIndex() {
		return index;
	}

private:
	std::type_index index;
	std::map<std::type_index, Component*> components;
};

