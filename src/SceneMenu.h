#pragma once

#include "Scene.h"
#include <map>
#include <memory>
#include <deque>

#include "EntityManager.h"

class SceneMenu : public Scene
{
protected:
	sf::Text					m_title;
	std::vector<sf::Text>		m_menuText;
	int							m_menu;
	int							m_total_menu;

	//void onEnd();
	void addMenuIndex(Vec2 boxPos, Vec2 textPos, std::string name);

public:
	SceneMenu(GameEngine* gameEngine);
	void sRender() override;
	void update() override;
	void sDoAction(const Action& action) override;
	void sMovement();
	void init() override;
};