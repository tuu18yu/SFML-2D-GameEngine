#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "Scene.h"
#include "SceneMenu.h"
#include "SceneGeometryWar.h"
#include "SceneMario.h"
#include "Assets.h"
#include "MemoryPool.h"

#include <memory>

typedef std::map<int, std::shared_ptr<Scene>> SceneMap;
typedef std::map<int, std::string> AssetsMap;

class GameEngine
{
protected:
	sf::RenderWindow	m_windows;
	Assets				m_assets;
	int					m_currentScene;
	SceneMap			m_sceneMap;
	AssetsMap			m_assetsMap;
	size_t				m_simulationSpeed = 1;
	bool				m_running = true;

	void init();
	void update();

	void sKeyboardInput();

	std::shared_ptr<Scene> currentScene() { return m_sceneMap[m_currentScene]; }

public:
	GameEngine();
	void changeScene(const int sceneName);
	void quit();
	void run();

	Vec2 getMousePosition();
	
	sf::RenderWindow& window() { return m_windows; }
	Assets& assets() { return m_assets; };
	bool isRunning() { return m_running; }
};