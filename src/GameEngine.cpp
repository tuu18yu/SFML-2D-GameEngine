#include "GameEngine.h"

GameEngine::GameEngine(const std::string& path)
{
	init(path);
}

void GameEngine::init(const std::string& path)
{
	m_assets.loadFromFile(path);
	m_windows.create(sf::VideoMode(1000, 500), "Game Engine");
	m_windows.setFramerateLimit(100);
	
	auto p = std::make_shared<SceneTest>(this);
	m_sceneMap[0] = p;
	m_currentScene = 0;
}

void GameEngine::update()
{
	
	sKeyboardInput();
	//m_assets.getAnimation("STAND").getSprite().setPosition(50, 30);
	//m_assets.getAnimation("STAND").update(0);
	//m_windows.draw(m_assets.getAnimation("STAND").getSprite());
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

	}
}

Vec2 GameEngine::sMouseInput()
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

//void GameEngine::changeScene(const int sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false)
//{
//	
//}