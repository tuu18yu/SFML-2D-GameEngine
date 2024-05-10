#pragma once

#include "Action.h"
#include "EntityManager.h"

#include <memory>

class GameEngine;

typedef std::map<int, std::string> ActionMap;

class Scene
{
protected:

	GameEngine*		m_game = nullptr;
	EntityManager	m_entityManager;
	ActionMap		m_actionMap;
	bool			m_paused = false;
	bool			m_hasEnded = false;
	size_t			m_currentFrame = 0;
	Vec2			m_size = { 1200, 90 };

public:
	Scene();
	Scene(GameEngine* gameEngine);

	virtual void update() = 0;
	virtual void init() = 0;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender() = 0;

	virtual void doAction(const Action& action);
	// void simulate(const size_t frames);
	void registerAction(int inputKey, const std::string& actionName);

	//size_t width() { return m_size.x; };
	//size_t height()  { return m_size.y; };
	size_t currentFrame() const { return m_currentFrame; }

	bool hasEnded() const { return m_hasEnded; };
	const ActionMap& getActionMap() const { return m_actionMap; }
	void clearEntityManager() { m_entityManager.clear(); }
	// void drawLine(const Vec2& p1, const Vec2& p2);
};