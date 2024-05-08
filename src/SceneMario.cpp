#include "SceneMario.h"
#include "Physics.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"

#include <iostream>

SceneMario::SceneMario(GameEngine* gameEngine)
	:Scene(gameEngine)
{
	init();
}

void SceneMario::init()
{
	m_camera.reset(0 * m_scale.x, 100.f, Vec2(1200.f, 900.f));
	m_camera.setDX(2.f);

	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");

	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::Right, "RIGHT");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::Left, "LEFT");

	registerAction(sf::Keyboard::Space, "JUMP");


	m_background.setTexture((m_game->assets()).getTexture("background"));
	m_background.setScale(m_scale.x, m_scale.y);
	m_background.setTextureRect(sf::IntRect(0, 0, 13504, 1920));

	m_playerID = m_entityManager.addEntity("PLAYER");
	m_entityManager.getComponentVector<CInput>()[m_playerID].has = true;

	m_entityManager.getComponentVector<CAnimation>()[m_playerID].has = true;

	m_entityManager.getComponentVector<CTransform>()[m_playerID].has = true;
	m_entityManager.getComponentVector<CTransform>()[m_playerID].prevPos = Vec2{ 10 * m_scale.x, (208.f * m_scale.y) - (31.f * 3.f) };
	m_entityManager.getComponentVector<CTransform>()[m_playerID].pos = Vec2{ 10 * m_scale.x, (208.f * m_scale.y) - (31.f * 3.f) };
	m_entityManager.getComponentVector<CTransform>()[m_playerID].velocity = Vec2{ 2, 3 };

	m_entityManager.getComponentVector<CGravity>()[m_playerID].has = true;
	m_entityManager.getComponentVector<CGravity>()[m_playerID].gravity = 0.15f;
	m_entityManager.getComponentVector<CGravity>()[m_playerID].speed = 6.5f;
	m_entityManager.getComponentVector<CGravity>()[m_playerID].threshold = 68.f * m_scale.y;

	m_entityManager.getComponentVector<CState>()[m_playerID].has = true;
	m_entityManager.getComponentVector<CState>()[m_playerID].state = "STAND_RIGHT";

	m_entityManager.getComponentVector<CBoundingBox>()[m_playerID].has = true;
	m_entityManager.getComponentVector<CBoundingBox>()[m_playerID].size = Vec2(16.f*3, 31.f*3);

	buildPipe(Vec2(27.f, 31.f), Vec2(450.f, 176.f));
	buildPipe(Vec2(27.f, 47.f), Vec2(610.f, 160.f));
	buildPipe(Vec2(27.f, 63.f), Vec2(738.f, 144.f));
	buildPipe(Vec2(27.f, 63.f), Vec2(914.f, 144.f));
	buildPipe(Vec2(27.f, 31.f), Vec2(2610.f, 176.f));
	buildPipe(Vec2(27.f, 31.f), Vec2(2868.f, 176.f));

	m_steppingOn = buildFloor(Vec2(1103.f, 31.f), Vec2(0.f, 208.f));
	buildFloor(Vec2(239.f, 31.f), Vec2(1136.f, 208.f));
	buildFloor(Vec2(1023.f, 31.f), Vec2(1424.f, 208.f));
	buildFloor(Vec2(895.f, 31.f), Vec2(2480.f, 208.f));

	buildStairs(Vec2(15.f, 15.f), Vec2(2144.f, 192.f), 4, true, 1);
	buildStairs(Vec2(15.f, 15.f), Vec2(2240.f, 144.f), 4, false, 1);
	buildStairs(Vec2(15.f, 15.f), Vec2(2368.f, 192.f), 4, true, 2);
	buildStairs(Vec2(15.f, 15.f), Vec2(2480.f, 144.f), 4, false, 1);
	buildStairs(Vec2(15.f, 15.f), Vec2(2896.f, 192.f), 8, true, 1);

	int item = m_entityManager.addEntity("ITEM_BLOCK");
	m_entityManager.getComponentVector<CAnimation>()[item].has = true;
	m_entityManager.getComponentVector<CAnimation>()[item].animation = (m_game->assets()).getAnimation("ITEM_BLOCK");

	m_entityManager.getComponentVector<CTransform>()[item].has = true;
	m_entityManager.getComponentVector<CTransform>()[item].pos = Vec2(256.f * m_scale.y, 144.f * m_scale.x);

	m_entityManager.getComponentVector<CBoundingBox>()[item].has = true;
	m_entityManager.getComponentVector<CBoundingBox>()[item].size = Vec2(15.f * m_scale.x, 15.f * m_scale.y);
}

int SceneMario::buildPipe(Vec2 size, Vec2 pos)
{
	int pipe = m_entityManager.addEntity("PIPE");
	m_entityManager.getComponentVector<CBoundingBox>()[pipe].has = true;
	m_entityManager.getComponentVector<CBoundingBox>()[pipe].size = Vec2(size.x * m_scale.x, size.y * m_scale.y);

	m_entityManager.getComponentVector<CTransform>()[pipe].has = true;
	m_entityManager.getComponentVector<CTransform>()[pipe].pos = Vec2{ pos.x * m_scale.x, pos.y * m_scale.y };

	return pipe;
}

int SceneMario::buildFloor(Vec2 size, Vec2 pos)
{
	int floor = m_entityManager.addEntity("FLOOR");
	m_entityManager.getComponentVector<CBoundingBox>()[floor].has = true;
	m_entityManager.getComponentVector<CBoundingBox>()[floor].size = Vec2(size.x * m_scale.x, size.y * m_scale.y);

	m_entityManager.getComponentVector<CTransform>()[floor].has = true;
	m_entityManager.getComponentVector<CTransform>()[floor].pos = Vec2{ pos.x * m_scale.x, pos.y * m_scale.y };

	return floor;
}

int SceneMario::buildStairs(Vec2 size, Vec2 pos, int floors, bool isUp, int lastWidth)
{
	int stair = -1;

	for (int i = 0; i < floors; i++)
	{
		stair = m_entityManager.addEntity("STAIR");
		CBoundingBox &BB = m_entityManager.getComponentVector<CBoundingBox>()[stair];
		CTransform &trans = m_entityManager.getComponentVector<CTransform>()[stair];

		BB.has = true;
		trans.has = true;

		if (isUp)
		{
			BB.size = (i == floors - 1 
							? Vec2((size.x + 1) * m_scale.x * lastWidth, (size.y + 1) * m_scale.y * (i + 1)) 
							: Vec2((size.x + 1) * m_scale.x, (size.y + 1) * m_scale.y * (i + 1))
						);
			
			trans.pos = Vec2{ (pos.x + ((size.x + 1) * i)) * m_scale.x, (pos.y - ((size.y + 1) * i)) * m_scale.y };
		}
		else
		{
			BB.size = (i == floors - 1
				? Vec2((size.x + 1) * m_scale.x * lastWidth, (size.y + 1) * m_scale.y * (floors - i))
				: Vec2((size.x + 1) * m_scale.x, (size.y + 1) * m_scale.y * (floors - i))
				);

			trans.pos = Vec2{ (pos.x + ((size.x + 1) * i)) * m_scale.x, (pos.y + ((size.y + 1) * i)) * m_scale.y };
		}
	}

	return stair;
}


void SceneMario::sRender()
{
	m_game->window().draw(m_background);

	for (int i = 0; i < 100; i++)
	{
		CAnimation anim = m_entityManager.getComponentVector<CAnimation>()[i];
		if (anim.has)
		{
			//std::cout << i << "\n";
			Vec2 pos = m_entityManager.getComponentVector<CTransform>()[i].pos;
			anim.animation.update(m_currentFrame);
			anim.animation.getSprite().setPosition(pos.x, pos.y);
			m_game->window().draw(anim.animation.getSprite());
		}

		CBoundingBox BB = m_entityManager.getComponentVector<CBoundingBox>()[i];
		if (m_drawCollision)
		{
			Vec2 pos = m_entityManager.getComponentVector<CTransform>()[i].pos;
			sf::RectangleShape box;
			box.setSize(sf::Vector2f(BB.size.x, BB.size.y));
			box.setOutlineColor(sf::Color::Blue);
			box.setOutlineThickness(5);
			box.setFillColor(sf::Color::Transparent);
			if (i == m_playerID)
			{
				box.setPosition(pos.x - BB.size.x / 2, pos.y - BB.size.y / 2);
			}
			else
			{
				box.setPosition(pos.x, pos.y);
			}
			m_game->window().draw(box);
		}
	}
}

void SceneMario::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		if (action.name() == "RIGHT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].right = true;
		}
		else if (action.name() == "LEFT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].left = true;
		}
		else if (action.name() == "JUMP")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].jump = true;
		}
		
	}

	else
	{
		if (action.name() == "RIGHT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].right = false;
		}
		else if (action.name() == "LEFT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].left = false;
		}
	}
}

void SceneMario::sMovement()
{
	std::string &state = m_entityManager.getComponentVector<CState>()[m_playerID].state;
	CTransform& trans = m_entityManager.getComponentVector<CTransform>()[m_playerID];
	Animation& anim = m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation;

	// std::cout << "state before: " << state << "\n";
	if (m_entityManager.getComponentVector<CInput>()[m_playerID].right)
	{
		if (state == "LEFT")
		{
			state = "SHIFT_LEFT";
		}
		else if (state == "STAND_LEFT")
		{
			state = "RIGHT";
			anim.getSprite().setOrigin(0, 0);
		}
		else
		{
			state = "RIGHT";
		}
		trans.prevPos.x = trans.pos.x;
		trans.pos.x += trans.velocity.x;
	}
	else if (m_entityManager.getComponentVector<CInput>()[m_playerID].left)
	{
		if (state == "RIGHT")
		{
			state = "SHIFT_RIGHT";
		}
		else
		{
			state = "LEFT";
		}
		trans.prevPos.x = trans.pos.x;
		trans.pos.x -= trans.velocity.x;
	}
	else
	{
		if (state == "RIGHT")
		{
			state = "STAND_RIGHT";
		}
		else if (state == "LEFT")
		{
			state = "STAND_LEFT";
		}
	}

	if (m_entityManager.getComponentVector<CInput>()[m_playerID].jump)
	{
		m_steppingOn = -1;

		if (state == "RIGHT" || state == "STAND_RIGHT")
		{
			state = "JUMP_RIGHT";
		}
		else if (state == "LEFT" || state == "STAND_LEFT")
		{
			state = "JUMP_LEFT";
		}

		CGravity &gravity = m_entityManager.getComponentVector<CGravity>()[m_playerID]; 

		if (!gravity.isFall)
		{

			trans.prevPos.y = trans.pos.y;
			trans.pos.y -= trans.velocity.y + gravity.speed;
			gravity.current += trans.velocity.y + gravity.speed;
			gravity.speed - gravity.gravity < 0 ? gravity.speed = 0 : gravity.speed -= gravity.gravity;

			if (gravity.current >= gravity.threshold)
			{
				gravity.isFall = true;
			}
		}
		else
		{
			trans.prevPos.y = trans.pos.y;
			trans.pos.y += trans.velocity.y + gravity.speed;
			gravity.current -= trans.velocity.y + gravity.speed;
			gravity.speed + gravity.gravity > 6.5f ? gravity.speed = 6.5f : gravity.speed += gravity.gravity;

		}
		
	}
	//std::cout << "state after: " + state + "\n";
}

void SceneMario::sAnimation()
{
	
	std::string state = m_entityManager.getComponentVector<CState>()[m_playerID].state;

	if (state == "RIGHT")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("RIGHT");
	}

	else if (state == "STAND_RIGHT")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("STAND_RIGHT");
	}

	else if (state == "LEFT")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("LEFT");
	}

	else if (state == "STAND_LEFT")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("STAND_LEFT");
	}

	else if (state == "JUMP_LEFT")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("JUMP_LEFT");
	}
	else if (state == "JUMP_RIGHT")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("JUMP_RIGHT");
	}
	else if (state == "SHIFT_LEFT")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("SHIFT_LEFT");
	}
	else if (state == "SHIFT_RIGHT")
	{
		m_entityManager.getComponentVector<CAnimation>()[m_playerID].animation = (m_game->assets()).getAnimation("SHIFT_RIGHT");
	}
}

void SceneMario::sCollision()
{
	
	CBoundingBox BB1 = m_entityManager.getComponentVector<CBoundingBox>()[m_playerID];
	CTransform &T1 = m_entityManager.getComponentVector<CTransform>()[m_playerID];
	CGravity &gravity = m_entityManager.getComponentVector<CGravity>()[m_playerID];
	std::string &state = m_entityManager.getComponentVector<CState>()[m_playerID].state;

	bool isOnFloor = false;

	for (int j = 0; j < 100; j++)
	{
		Vec2 overlap;
		CBoundingBox BB2 = m_entityManager.getComponentVector<CBoundingBox>()[j];
		CTransform T2 = m_entityManager.getComponentVector<CTransform>()[j];
		bool hitItem = false;


		if (j != m_playerID && BB2.has)
		{
			const std::string& entity_type = m_entityManager.getTag(j);
			Vec2 T2pos;
			entity_type != "MUSHROOM" || entity_type != "TURTLE" ? T2pos = T2.pos + BB2.size / 2 : T2pos = T2.pos;

			if (detectCollision(T1.pos, T2pos, BB1.size, BB2.size, overlap))
			{
				// std::cout << "mario: " << T1.pos.y << "\t"<< entity_type + ": " << T1.pos.y << "\n";
				// std::cout << "standing on: " << m_steppingOn << "\n";
				// coming from top
				// only resolute collision when stepping on it or not stepping on and coming from top and prev pos is higher than the entity stepping on
				if (j == m_steppingOn || (m_steppingOn == -1 && T1.prevPos.y < T1.pos.y && T1.prevPos.y < T2.pos.y))
				{
					
					std::cout << entity_type + " coming from top \n";
					isOnFloor = true;
					m_steppingOn = j;
					
					T1.pos.y -= overlap.y;

					gravity.isFall = false;
					gravity.current = 0;
					gravity.speed = 6.5f;
					m_entityManager.getComponentVector<CInput>()[m_playerID].jump = false;

					if (m_entityManager.getComponentVector<CState>()[m_playerID].state == "JUMP_RIGHT")
					{
						m_entityManager.getComponentVector<CState>()[m_playerID].state = "STAND_RIGHT";
					}
					else if (m_entityManager.getComponentVector<CState>()[m_playerID].state == "JUMP_LEFT")
					{
						m_entityManager.getComponentVector<CState>()[m_playerID].state = "STAND_LEFT";
					}

				}
				// coming from bottom
				else if (m_steppingOn == -1 && T1.prevPos.y > T1.pos.y)
				{
					std::cout << entity_type + " coming from bottom \n";
					T1.pos.y += overlap.y;
					hitItem = true;

					gravity.isFall = true;
				}

				// coming from right
				if (T1.prevPos.x < T1.pos.x && j != m_steppingOn && !hitItem)
				{
					std::cout << "mario: " << T1.pos.y << "\t" << entity_type + ": " << T1.pos.y << "\n";
					std::cout << entity_type + " coming from right \n";
					T1.pos.x -= overlap.x;

				}
				// coming from left
				else if (T1.prevPos.x > T1.pos.x && j != m_steppingOn && !hitItem)
				{
					std::cout << entity_type + " coming from left \n";
					T1.pos.x += overlap.x;
				}
			}
		}
	}

	if (!isOnFloor && !m_entityManager.getComponentVector<CInput>()[m_playerID].jump)
	{
		
		if (state == "RIGHT" || state == "STAND_RIGHT")
		{
			state = "JUMP_RIGHT";
		}
		else if (state == "LEFT" || state == "STAND_LEFT")
		{
			state = "JUMP_LEFT";
		}

		m_steppingOn = -1;
		m_entityManager.getComponentVector<CInput>()[m_playerID].jump = true;

		gravity.isFall = true;
		gravity.speed = 2.5f;

		CTransform& trans = m_entityManager.getComponentVector<CTransform>()[m_playerID];
		
		trans.prevPos.y = trans.pos.y;
		trans.pos.y += trans.velocity.y + gravity.speed;
		gravity.current -= trans.velocity.y + gravity.speed;
		gravity.speed + gravity.gravity > 6.5f ? gravity.speed = 6.5f : gravity.speed += gravity.gravity;

	}
	
	
}

void SceneMario::update()
{
	m_currentFrame++;
	sMovement();
	sCollision(); 
	sAnimation();
	m_camera.horizontalMove(m_entityManager.getComponentVector<CTransform>()[m_playerID].pos.x);
	m_game->window().setView(m_camera.view());
	sRender();
	//m_game->window().setView(m_camera.view());
}