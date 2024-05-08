#include "SceneTest.h"
#include "GameEngine.h"
#include <iostream>


SceneTest::SceneTest(GameEngine* gameEngine)
	:Scene(gameEngine)
{
	//init();
}

void SceneTest::init()
{
	registerAction(sf::Keyboard::D, "RIGHT");
	m_playerID = m_entityManager.addEntity("PLAYER");
	m_entityManager.getComponentVector<CInput>()[m_playerID].has = true;
	m_entityManager.getComponentVector<CAnimation>()[m_playerID].has = true;
	m_entityManager.getComponentVector<CTransform>()[m_playerID].has = true;

	m_entityManager.getComponentVector<CTransform>()[m_playerID].pos = Vec2{ 0, 100 };
	m_entityManager.getComponentVector<CTransform>()[m_playerID].velocity = Vec2{ 1, 1 };


	int test = m_entityManager.addEntity("PLAYER");
	m_entityManager.getComponentVector<CAnimation>()[test].has = true;
	m_entityManager.getComponentVector<CTransform>()[test].has = true;
	m_entityManager.getComponentVector<CTransform>()[test].pos = Vec2{ 100, 300 };
	m_entityManager.getComponentVector<CAnimation>()[test].animation = (m_game->assets()).getAnimation("STAND");

}



void SceneTest::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		// m_game->assets Note: this causes an error bc gameEngine is declare but not defined, including the header file
		// will create cirucular dependency
		// Find a differen way to trigger animation

		if (action.name() == "RIGHT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].right = true;
			
		}
	}

	else
	{
		if (action.name() == "RIGHT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].right = false;
		}
	}
}

void SceneTest::sMovement()
{
	if (m_entityManager.getComponentVector<CInput>()[m_playerID].right)
	{
		m_entityManager.getComponentVector<CState>()[m_playerID].state = "RIGHT";
		m_entityManager.getComponentVector<CTransform>()[m_playerID].pos.x += m_entityManager.getComponentVector<CTransform>()[m_playerID].velocity.x;
	}
	else
	{
		m_entityManager.getComponentVector<CState>()[m_playerID].state = "STAND";
	}
}

void SceneTest::sAnimation()
{
	if (m_entityManager.getComponentVector<CState>()[m_playerID].state == "RIGHT")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("RIGHT");
	}

	else if (m_entityManager.getComponentVector<CState>()[m_playerID].state == "STAND")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("STAND");
	}
}


void SceneTest::sRender()
{
	for (int i = 0; i < 10; i++)
	{
		CAnimation anim = m_entityManager.getComponentVector<CAnimation>()[i];
		if (anim.has)
		{
			Vec2 pos = m_entityManager.getComponentVector<CTransform>()[i].pos;
			anim.animation.update(m_currentFrame);
			anim.animation.getSprite().setPosition(pos.x, pos.y);
			m_game->window().draw(anim.animation.getSprite());
		}
	}
}

void SceneTest::update()
{
	m_currentFrame++;

	if (m_currentFrame == 1000)
	{
		m_entityManager.destoryEntity(2);
	}
	sMovement();
	sAnimation();
	sRender();
}