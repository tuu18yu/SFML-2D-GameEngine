#pragma once

#include <SFML/Graphics/View.hpp>
#include "Vec2.h"

class Camera
{
protected:

	sf::View m_view;

public:
	Camera() {};
	Camera(Vec2 center, Vec2 size);
	Camera(float leftX, float topY, Vec2 size);

	void reset(float leftX, float topY, Vec2 size);
	sf::View view() { return m_view; }
};