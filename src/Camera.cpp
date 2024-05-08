#include "Camera.h"

Camera::Camera(Vec2 center, Vec2 size)
{
	m_view = sf::View(sf::Vector2f(center.x, center.y), sf::Vector2f(size.x, size.y));
}

Camera::Camera(float leftX, float topY, Vec2 size)
{
	m_view = sf::View(sf::FloatRect(leftX, topY, size.x, size.y));
}

void Camera::reset(float leftX, float topY, Vec2 size)
{
	m_view.reset(sf::FloatRect(leftX, topY, size.x, size.y));
}