#include "CameraMario.h"


CameraMario::CameraMario(Vec2 center, Vec2 size)
	:Camera(center, size)
{

}

CameraMario::CameraMario(float leftX, float topY, Vec2 size)
	:Camera(leftX, topY, size)
{

}

void CameraMario::horizontalMove(float xPos)
{
	if (m_view.getCenter().x <= xPos)
	{
		m_view.move(m_dx, m_dy);
	}
}