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
	// std::string				m_levelPath;
	// PlayerConfig			m_playerConfig;
	bool					m_drawTextures = true;
	bool					m_drawCollision = true;
	bool					m_drawGrid = false;
	int						m_steppingOn = -1;
	const Vec2				m_gridSize = { 64, 64 };
	const Vec2				m_scale = { 4.0, 4.0 };
	sf::Text				m_gridText;
	sf::Sprite				m_background;

	CameraMario				m_camera;


	// void loadLevel(const std::string & filename);

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