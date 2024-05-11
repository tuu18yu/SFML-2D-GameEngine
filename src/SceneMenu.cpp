#include "SceneMenu.h"
#include "GameEngine.h"

#include <iostream>


SceneMenu::SceneMenu(GameEngine* gameEngine)
	:Scene(gameEngine)
{
	//init();
}

void SceneMenu::init()
{
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::Up, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::Down, "DOWN");
	registerAction(sf::Keyboard::Enter, "ENTER");

	m_title = sf::Text{ "SELECT", m_game->assets().getFont("BASE") };
	m_title.setCharacterSize(150);
	m_title.setStyle(sf::Text::Bold);
	m_title.setFillColor(sf::Color::White);
	m_title.setPosition(460, 10);

	addMenuIndex(Vec2{ 110, 210 }, Vec2{ 300, 210 }, "SUPER MARIO TEST");
	addMenuIndex(Vec2{ 110, 400 }, Vec2{ 360, 400 }, "GEOMETRY WAR");

	sf::RectangleShape selectBox;
	selectBox.setSize(sf::Vector2f(1040, 166));
	selectBox.setOutlineColor(sf::Color::Cyan);
	selectBox.setOutlineThickness(10);
	selectBox.setFillColor(sf::Color::Transparent);

	int ID = m_entityManager.addEntity("SELECT_MENU");
	m_entityManager.getComponentVector<CInput>()[ID].has = true;
	m_entityManager.getComponentVector<CShape>()[ID].has = true;
	m_entityManager.getComponentVector<CState>()[ID].has = true;
	m_entityManager.getComponentVector<CTransform>()[ID].has = true;

	m_entityManager.getComponentVector<CState>()[ID].state = "0";
	m_entityManager.getComponentVector<CShape>()[ID].shape = selectBox;
	m_entityManager.getComponentVector<CTransform>()[ID].pos = Vec2{ 90, 190 };
	m_entityManager.getComponentVector<CTransform>()[ID].velocity.y = 190;
	m_entityManager.getComponentVector<CShape>()[ID].shape.setPosition(90, 190);

	m_menu = ID;
	m_total_menu = 2;
	// m_entityManager.getComponentVector<CShape>()[ID].shape.setPosition(90, 380);
}

void SceneMenu::addMenuIndex(Vec2 boxPos, Vec2 textPos, std::string name)
{
	sf::RectangleShape menuBox;
	menuBox.setSize(sf::Vector2f(1000, 126));
	menuBox.setOutlineColor(sf::Color::White);
	menuBox.setOutlineThickness(15);
	menuBox.setFillColor(sf::Color::Transparent);

	int ID = m_entityManager.addEntity("MENU_INDEX");
	m_entityManager.getComponentVector<CInput>()[ID].has = true;
	m_entityManager.getComponentVector<CShape>()[ID].has = true;
	m_entityManager.getComponentVector<CShape>()[ID].shape = menuBox;
	m_entityManager.getComponentVector<CShape>()[ID].shape.setPosition(boxPos.x, boxPos.y);

	sf::Text menu_text;
	menu_text = sf::Text{ name, m_game->assets().getFont("BASE") };
	menu_text.setCharacterSize(100);
	menu_text.setStyle(sf::Text::Bold);
	menu_text.setFillColor(sf::Color::White);
	menu_text.setPosition(textPos.x, textPos.y);

	m_menuText.push_back(menu_text);
}

void SceneMenu::sRender()
{
	m_game->window().draw(m_title);

	for (auto& t : m_menuText)
	{
		m_game->window().draw(t);
	}

	for (int i = 0; i < 10; i++)
	{
		CShape shape = m_entityManager.getComponentVector<CShape>()[i];
		if (shape.has)
		{
			CTransform trans = m_entityManager.getComponentVector<CTransform>()[i];
			if (trans.has)
			{
				shape.shape.setPosition(trans.pos.x, trans.pos.y);
			}

			m_game->window().draw(shape.shape);

		}

	}
}

void SceneMenu::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{

		if (action.name() == "UP")
		{
			m_entityManager.getComponentVector<CInput>()[m_menu].up = true;
			std::cout << "UP PRESSED\n";
		}
		else if (action.name() == "DOWN")
		{
			m_entityManager.getComponentVector<CInput>()[m_menu].down = true;
			std::cout << "DOWN PRESSED\n";
		}
	}

	else
	{
		if (action.name() == "UP")
		{
			m_entityManager.getComponentVector<CInput>()[m_menu].up = false;
			std::cout << "UP RELEASED\n";
		}
		else if (action.name() == "DOWN")
		{
			m_entityManager.getComponentVector<CInput>()[m_menu].down = false;
			std::cout << "DOWN RELEASED\n";
		}
		else if (action.name() == "ENTER")
		{
			int curr = std::stoi(m_entityManager.getComponentVector<CState>()[m_menu].state);
			m_game->changeScene(curr + 1);
		}
	}
}

void SceneMenu::sMovement()
{
	int curr = std::stoi(m_entityManager.getComponentVector<CState>()[m_menu].state);
	if (m_entityManager.getComponentVector<CInput>()[m_menu].up && curr != 0)
	{
		m_entityManager.getComponentVector<CState>()[m_menu].state = std::to_string(curr - 1);
		m_entityManager.getComponentVector<CTransform>()[m_menu].pos.y -= m_entityManager.getComponentVector<CTransform>()[m_menu].velocity.y;

	}
	else if (m_entityManager.getComponentVector<CInput>()[m_menu].down && curr != m_total_menu - 1)
	{
		m_entityManager.getComponentVector<CState>()[m_menu].state = std::to_string(curr + 1);
		m_entityManager.getComponentVector<CTransform>()[m_menu].pos.y += m_entityManager.getComponentVector<CTransform>()[m_menu].velocity.y;
	}
}

void SceneMenu::update()
{
	m_currentFrame++;

	sMovement();
	sRender();
}