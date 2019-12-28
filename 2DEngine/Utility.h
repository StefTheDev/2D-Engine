#pragma once

//Native Includes
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>

//Library Includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern Uint64 DELTATIME;

struct Vector2
{
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {	}

	Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	Vector2& operator+=(const float& scalar) { x += scalar; y += scalar; return *this; }
	Vector2& operator-=(const float& scalar) { x -= scalar; y -= scalar; return *this; }

	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs) += rhs; }
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs) -= rhs; }

	float x, y;
};

template <typename M> void FreeClear(M& map) {
	for (auto& element : map) delete element.second;
}