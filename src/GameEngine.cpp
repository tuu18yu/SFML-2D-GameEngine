#include "GameEngine.h"

GameEngine::GameEngine(const std::string& path)
{
	init(path);
}

void GameEngine::init(const std::string& path)
{
	m_assets.loadFromFile(path);
	m_windows.create(sf::VideoMode(1280, 960), "Game Engine");
	m_windows.setFramerateLimit(100);
	
	std::shared_ptr<Scene> p;

	p = std::make_shared<SceneMenu>(this);
	m_sceneMap[0] = p;
	m_assetsMap[0] = "../data/main_menu/assets.txt";

	p = std::make_shared<SceneMario>(this);
	m_sceneMap[1] = p;
	m_assetsMap[1] = "../data/super_mario_bros/SuperMarioBros.txt";

	p = std::make_shared<SceneGeometryWar>(this);
	m_sceneMap[2] = p;
	m_assetsMap[2] = "../data/geometry_war/assets.txt";

	m_currentScene = 2;
	m_assets.loadFromFile(m_assetsMap[m_currentScene]);
}

void GameEngine::update()
{
	
	sKeyboardInput();
	currentScene()->update();
}

void GameEngine::sKeyboardInput()
{
	sf::Event event;
	while (m_windows.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
			m_windows.close();
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) { continue; }
			const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
			currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
		}

		if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
		{
			if (currentScene()->getActionMap().find(event.mouseButton.button) == currentScene()->getActionMap().end()) { continue; }
			const std::string actionType = (event.type == sf::Event::MouseButtonPressed) ? "START" : "END";
			currentScene()->doAction(Action(currentScene()->getActionMap().at(event.mouseButton.button), actionType));
		}

	}
}

Vec2 GameEngine::getMousePosition()
{
	Vec2 mousePos;
	float x = (float)sf::Mouse::getPosition(m_windows).x;
	float y = (float)sf::Mouse::getPosition(m_windows).y;
	mousePos = Vec2(x, y);

	return mousePos;
}

void GameEngine::run()
{
	while (m_windows.isOpen())
	{
		m_windows.clear();
		update();
		m_windows.display();

	}
}

void GameEngine::quit()
{
	m_windows.close();
}

void GameEngine::changeScene(const int sceneName)
{
	currentScene()->clearEntityManager();
	m_currentScene = sceneName;
	m_assets.clear();
	m_assets.loadFromFile(m_assetsMap[sceneName]);
	currentScene()->init();

}