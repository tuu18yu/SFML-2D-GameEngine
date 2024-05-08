#pragma once

#include "Camera.h"

class CameraMario : public Camera
{
	float m_dx = 0;
	float m_dy = 0;

public:
	CameraMario() {}
	CameraMario(Vec2 center, Vec2 size);
	CameraMario(float leftX, float topY, Vec2 size);
	
	void setDX(float x) { m_dx = x; }
	void setDY(float y) { m_dy = y; }
	void horizontalMove(float xPos);
};