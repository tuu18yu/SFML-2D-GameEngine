#pragma once

#include "Scene.h"
#include <map>
#include <memory>

#include "EntityManager.h"

class GameEngine;

class SceneTest : public Scene
{

protected:

	int m_playerID = 0;


public:
	SceneTest(GameEngine* gameEngine);

	void sRender();
	void update();

	void sDoAction(const Action& action);
	void sMovement();
	void sAnimation();
};