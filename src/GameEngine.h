#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "Scene.h"
#include "SceneTest.h"
#include "Assets.h"
#include "MemoryPool.h"

#include <memory>

typedef std::map<int, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
protected:
	sf::RenderWindow	m_windows;
	Assets				m_assets;
	int					m_currentScene;
	SceneMap			m_sceneMap;
	size_t				m_simulationSpeed = 1;
	bool				m_running = true;

	void init(const std::string& path);
	void update();

	void sKeyboardInput();
	Vec2 sMouseInput();

	std::shared_ptr<Scene> currentScene() { return m_sceneMap[m_currentScene]; }

public:
	GameEngine(const std::string& path);
	// void changeScene(const int sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
	void quit();
	void run();
	
	sf::RenderWindow& window() { return m_windows; }
	Assets& assets() { return m_assets; };
	bool isRunning() { return m_running; }
};