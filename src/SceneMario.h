#pragma once

#include "Scene.h"
#include <map>
#include <memory>

#include "EntityManager.h"
#include "CameraMario.h"

class SceneMario : public Scene
{
protected:

	int						m_playerID;
	bool					m_drawCollision = true;
	int						m_steppingOn = -1;

	const Vec2				m_scale = { 4.0, 4.0 };
	sf::Sprite				m_background;
	CameraMario				m_camera;


	int buildPipe(Vec2 size, Vec2 pos);
	int buildFloor(Vec2 size, Vec2 pos);
	int buildStairs(Vec2 size, Vec2 pos, int floors, bool isUp, int lastWidth);

public:
	SceneMario(GameEngine* gameEngine);
	void init() override;
	void sRender() override;
	void update() override;
	
	void sDoAction(const Action& action) override;
	void sMovement();
	void sAnimation();
	void sCollision();
};