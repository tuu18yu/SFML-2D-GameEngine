#include "SceneGeometryWar.h"
#include "GameEngine.h"
#include "Collision.h"
#include <iostream>
#include <fstream>


SceneGeometryWar::SceneGeometryWar(GameEngine* gameEngine)
	:Scene(gameEngine)
{
	init();
}

void SceneGeometryWar::init()
{
	loadConfig("../data/geometry_war/config.txt");
	spawnPlayer();

	registerAction(sf::Keyboard::E, "UP");
	registerAction(sf::Keyboard::S, "LEFT");
	registerAction(sf::Keyboard::D, "DOWN");
	registerAction(sf::Keyboard::F, "RIGHT");
	registerAction(sf::Mouse::Left, "SHOOT");

	registerAction(sf::Keyboard::B, "RETURN MENU");

}

void SceneGeometryWar::spawnPlayer()
{
	m_playerID = m_entityManager.addEntity("PLAYER");

	// Spawn player at the center of the window
	float centerX = m_game->window().getSize().x / 2.0f;
	float centerY = m_game->window().getSize().y / 2.0f;

	m_entityManager.getComponentVector<CTransform>()[m_playerID].has = true;
	m_entityManager.getComponentVector<CTransform>()[m_playerID].prevPos = Vec2{ centerX, centerY };
	m_entityManager.getComponentVector<CTransform>()[m_playerID].pos = Vec2{ centerX, centerY };
	m_entityManager.getComponentVector<CTransform>()[m_playerID].velocity = Vec2{(float)m_playerConfig.S, (float)m_playerConfig.S };

	// Set shape to the Player based on config file
	m_entityManager.getComponentVector<CShape>()[m_playerID].has = true;
	sf::CircleShape &circle = m_entityManager.getComponentVector<CShape>()[m_playerID].circle;
	sf::Color fColor(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB);
	sf::Color oColor(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB);

	circle.setRadius(m_playerConfig.SR);
	circle.setPointCount(m_playerConfig.V);
	circle.setFillColor(fColor);
	circle.setOutlineColor(oColor);
	circle.setOutlineThickness(m_playerConfig.OT);
	circle.setOrigin(m_playerConfig.SR, m_playerConfig.SR);

	// Add input component to the Player entity in order to recieve inputs from user
	m_entityManager.getComponentVector<CInput>()[m_playerID].has = true;

	// Add collision component to detect collision
	m_entityManager.getComponentVector<CBoundingBox>()[m_playerID].has = true;
	m_entityManager.getComponentVector<CBoundingBox>()[m_playerID].radius = m_playerConfig.SR + m_playerConfig.OT;
}

void SceneGeometryWar::spawnEnemy()
{
	std::cout << "big spawned\n";
	// add enemy to the EntityManager
	int enemy = m_entityManager.addEntity("ENEMY");

	// Enemy spawns in a random location within the [radius, window - radius]
	float ePosX = rand() % (m_game->window().getSize().x - (2 * m_enemyConfig.CR) + 1);
	ePosX += m_enemyConfig.CR;
	float ePosY = rand() % (m_game->window().getSize().y - (2 * m_enemyConfig.CR) + 1);
	ePosY += m_enemyConfig.CR;
	Vec2 ePos(ePosX, ePosY);

	// Enemy has random speed between SMIN and SMAX inclusive
	float speed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_enemyConfig.SMAX - m_enemyConfig.SMIN)));
	speed += m_enemyConfig.SMIN;

	// Initially enemy will move in a random angle
	int angle = rand() % 360;
	float velX = speed * cos((double) angle), velY = speed * sin((double) angle);
	Vec2 eVel(velX, velY);


	m_entityManager.getComponentVector<CTransform>()[enemy].has = true;
	m_entityManager.getComponentVector<CTransform>()[enemy].prevPos = ePos;
	m_entityManager.getComponentVector<CTransform>()[enemy].pos = ePos;
	m_entityManager.getComponentVector<CTransform>()[enemy].velocity = eVel;


	// Enemy has random verticies between VMIN and VMAX inclusive
	int verticies = rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1);
	verticies += m_enemyConfig.VMIN;

	// Enemy has random fill color and given outline color
	int R = rand() % 255, G = rand() % 255, B = rand() % 255;
	sf::Color fColor(R, G, B);
	sf::Color oColor(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB);

	m_entityManager.getComponentVector<CShape>()[enemy].has = true;
	sf::CircleShape &circle = m_entityManager.getComponentVector<CShape>()[enemy].circle;

	circle.setRadius(m_enemyConfig.SR);
	circle.setPointCount(verticies);
	circle.setFillColor(fColor);
	circle.setOutlineColor(oColor);
	circle.setOutlineThickness(m_enemyConfig.OT);
	circle.setOrigin(m_enemyConfig.SR, m_enemyConfig.SR);

	// Add collision component to detect collision
	m_entityManager.getComponentVector<CBoundingBox>()[enemy].has = true;
	m_entityManager.getComponentVector<CBoundingBox>()[enemy].radius = m_enemyConfig.SR + m_enemyConfig.OT;

	// record the most recent enemy spawn time
	m_lastEnemySpawnTime = m_currentFrame;
}
void SceneGeometryWar::spawnSmallEnemies(int parent)
{
	// Small enemies spawn in the middle of the parent enemy
	CTransform parentTrans = m_entityManager.getComponentVector<CTransform>()[parent];

	// Inherits shape from parent, but half the size
	sf::CircleShape circle = m_entityManager.getComponentVector<CShape>()[parent].circle;
	sf::Color fColor = circle.getFillColor();
	sf::Color oColor = circle.getOutlineColor();
	int OT = circle.getOutlineThickness();
	int radius = circle.getRadius() / 2;
	int nVerticies = circle.getPointCount();

	// Moves in different directions
	int currAngle = 0;
	int increaseAngle = 360 / nVerticies;

	// Create nVerticies of small enemies
	for (int i = 0; i < nVerticies; i++)
	{
		std::cout << "small spawned\n";
		int child = m_entityManager.addEntity("ENEMY");

		m_entityManager.getComponentVector<CShape>()[child].has = true;
		sf::CircleShape &circle = m_entityManager.getComponentVector<CShape>()[child].circle;
		circle.setRadius(radius);
		circle.setPointCount(nVerticies);
		circle.setFillColor(fColor);
		circle.setOutlineColor(oColor);
		circle.setOutlineThickness(OT);
		circle.setOrigin(radius, radius);

		m_entityManager.getComponentVector<CBoundingBox>()[child].has = true;
		m_entityManager.getComponentVector<CBoundingBox>()[child].radius = radius + OT;

		m_entityManager.getComponentVector<CLifeSpan>()[child].has = true;
		m_entityManager.getComponentVector<CLifeSpan>()[child].frameCreated = m_currentFrame;
		m_entityManager.getComponentVector<CLifeSpan>()[child].lifespan = m_enemyConfig.L;

		Vec2 sVel(parentTrans.velocity.x * cos(currAngle), parentTrans.velocity.y * sin(currAngle));

		m_entityManager.getComponentVector<CTransform>()[child].has = true;
		m_entityManager.getComponentVector<CTransform>()[child].pos = parentTrans.pos;
		m_entityManager.getComponentVector<CTransform>()[child].prevPos = parentTrans.pos;
		m_entityManager.getComponentVector<CTransform>()[child].velocity = sVel;
		
		currAngle += increaseAngle;
	}
}

void SceneGeometryWar::spawnBullet()
{
	std::cout << "bullet spawned\n";
	int bullet = m_entityManager.addEntity("BULLET");
	// Bullet spawns in middle of the given entity
	Vec2 bPos = m_entityManager.getComponentVector<CTransform>()[m_playerID].pos;
	// Bullet moves to the location of the mouse at given speed;
	Vec2 bVel = m_game->getMousePosition() - bPos;
	bVel.normalize();
	bVel *= m_bulletConfig.S;
	sf::Color fColor(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB);
	sf::Color oColor(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB);

	// add bullet to the EntityManager
	m_entityManager.getComponentVector<CShape>()[bullet].has = true;
	sf::CircleShape &circle = m_entityManager.getComponentVector<CShape>()[bullet].circle;
	circle.setRadius(m_bulletConfig.SR);
	circle.setPointCount(m_bulletConfig.V);
	circle.setFillColor(fColor);
	circle.setOutlineColor(oColor);
	circle.setOutlineThickness(m_bulletConfig.OT);
	circle.setOrigin(m_bulletConfig.SR, m_bulletConfig.SR);

	m_entityManager.getComponentVector<CBoundingBox>()[bullet].has = true;
	m_entityManager.getComponentVector<CBoundingBox>()[bullet].radius = m_bulletConfig.SR + m_bulletConfig.OT;

	m_entityManager.getComponentVector<CLifeSpan>()[bullet].has = true;
	m_entityManager.getComponentVector<CLifeSpan>()[bullet].frameCreated = m_currentFrame;
	m_entityManager.getComponentVector<CLifeSpan>()[bullet].lifespan = m_bulletConfig.L;

	m_entityManager.getComponentVector<CTransform>()[bullet].has = true;
	m_entityManager.getComponentVector<CTransform>()[bullet].pos = bPos;
	m_entityManager.getComponentVector<CTransform>()[bullet].prevPos = bPos;
	m_entityManager.getComponentVector<CTransform>()[bullet].velocity = bVel;

}

void SceneGeometryWar::loadConfig(std::string file)
{
	std::ifstream ifile(file);
	if (ifile.is_open())
	{
		std::string lineName;
		while (ifile >> lineName)
		{
			if (lineName == "Player")
			{
				ifile >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG
					>> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB
					>> m_playerConfig.OT >> m_playerConfig.V;
			}
			else if (lineName == "Enemy")
			{
				ifile >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR
					>> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX
					>> m_enemyConfig.L >> m_enemyConfig.SI;
			}
			else if (lineName == "Bullet")
			{
				ifile >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR
					>> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG
					>> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;
			}
		}
	}
	ifile.close();
}


void SceneGeometryWar::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		if (action.name() == "RIGHT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].right = true;
			
		}
		if (action.name() == "LEFT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].left = true;

		}
		if (action.name() == "UP")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].up = true;

		}
		if (action.name() == "DOWN")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].down = true;

		}
		if (action.name() == "SHOOT")
		{
			spawnBullet();
		}
		if (action.name() == "RETURN MENU")
		{
			m_game->changeScene(0);
		}
	}

	else
	{
		if (action.name() == "RIGHT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].right = false;

		}
		if (action.name() == "LEFT")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].left = false;

		}
		if (action.name() == "UP")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].up = false;

		}
		if (action.name() == "DOWN")
		{
			m_entityManager.getComponentVector<CInput>()[m_playerID].down = false;

		}
		if (action.name() == "SHOOT")
		{
		}
	}
}

void SceneGeometryWar::sMovement()
{
	CInput &input = m_entityManager.getComponentVector<CInput>()[m_playerID];
	CTransform &trans = m_entityManager.getComponentVector<CTransform>()[m_playerID];
	CBoundingBox& BB = m_entityManager.getComponentVector<CBoundingBox>()[m_playerID];

	if (input.right)
	{
		trans.pos.x += trans.velocity.x;
	}
	if (input.left)
	{
		trans.pos.x -= trans.velocity.x;
	}
	if (input.down)
	{
		trans.pos.y += trans.velocity.y;
	}
	if (input.up)
	{
		trans.pos.y -= trans.velocity.y;
	}

	// check if player hits the border
	Vec2 wSize(m_game->window().getSize().x, m_game->window().getSize().y);
	if (trans.pos.y - BB.radius < 0.0f)
	{
		trans.pos.y -= trans.pos.y - BB.radius;
	}
	
	else if (trans.pos.y + BB.radius > wSize.y)
	{
		trans.pos.y -= (trans.pos.y + BB.radius) - wSize.y;
	}
	if (trans.pos.x - BB.radius < 0.0f)
	{
		trans.pos.x -= trans.pos.x - BB.radius;
	}
	else if(trans.pos.x + BB.radius > wSize.x)
	{
		trans.pos.x -= (trans.pos.x + BB.radius) - wSize.x;
	}
	

	// for the rest
	for (int i = 0; i < 1000; i++)
	{
		CTransform& trans = m_entityManager.getComponentVector<CTransform>()[i];
		if (trans.has && i != m_playerID)
		{
			trans.prevPos = trans.pos;
			trans.pos += trans.velocity;
		}
	}
}

void SceneGeometryWar::sLifeSpan()
{
	for (int i = 0; i < 1000; i++)
	{
		CLifeSpan life = m_entityManager.getComponentVector<CLifeSpan>()[i];
		CShape &shape = m_entityManager.getComponentVector<CShape>()[i];

		if (life.has)
		{
			// if there is no remaining time remove the entity
			int remaining = life.lifespan - (m_currentFrame - life.frameCreated);
			if (remaining <= 0)
			{
				m_entityManager.destoryEntity(i);
			}

			// change transparency of entity depending on the remaining time
			float alphaRatio = (float)remaining / (float)life.lifespan;
			sf::Uint8 alpha = 255 * alphaRatio;
			sf::Color eColor = shape.circle.getFillColor();
			eColor.a = alpha;
			sf::Color oColor = shape.circle.getOutlineColor();
			oColor.a = alpha;
			shape.circle.setOutlineColor(oColor);
		}
	}
}


void SceneGeometryWar::sRender()
{

	for (int i=0; i < 1000; i++)
	{
		CShape &e = m_entityManager.getComponentVector<CShape>()[i];
		Vec2 pos = m_entityManager.getComponentVector<CTransform>()[i].pos;
		if (e.has)
		{
			// Set the position of the entities based on the transform component
			e.circle.setPosition(pos.x, pos.y);

			// Set the roatation of the entities based on the transform component
			e.circle.rotate(m_rotationAngle);

			// Draw the entities shape on the window
			m_game->window().draw(e.circle);
		}
	}
}

void SceneGeometryWar::sCollision()
{
	for (int i = 0; i < 1000; i++)
	{
		std::string tag = m_entityManager.getTag(i);
		CTransform& trans = m_entityManager.getComponentVector<CTransform>()[i];
		CBoundingBox& BB = m_entityManager.getComponentVector<CBoundingBox>()[i];

		// Enemy collision with border or enemy collides with player
		if (tag == "ENEMY")
		{
			Vec2 wSize(m_game->window().getSize().x, m_game->window().getSize().y);

			// if next move hits top of the window or the bottom of the window
			if (trans.pos.y - BB.radius + trans.velocity.y <= 0.0f 
				|| trans.pos.y + BB.radius + trans.velocity.y >= wSize.y)
			{
				trans.velocity.y *= -1.0f;
			}
			// if next move hits left of the window or right of the window
			if (trans.pos.x - BB.radius + trans.velocity.x <= 0.0f 
				|| trans.pos.x + BB.radius + trans.velocity.x >= wSize.x)
			{
				trans.velocity.x *= -1.0f;
			}

			// When enemy collides with player, player spawns back to the middle
			CTransform& trans2 = m_entityManager.getComponentVector<CTransform>()[m_playerID];
			CBoundingBox& BB2 = m_entityManager.getComponentVector<CBoundingBox>()[m_playerID];
			Vec2 overlap;
			if (detectCollision(trans.pos, trans2.pos, BB.radius, BB2.radius, overlap))
			{
				trans2.pos = wSize / 2.f;
			}
		}

		// Bullet collides with Enemies then destroy the bullet and the enemy
		if (tag == "BULLET")
		{
			for (int j = 0; j < 1000; j++)
			{
				std::string tag2 = m_entityManager.getTag(j);
				if (tag2 == "ENEMY")
				{
					CTransform& trans2 = m_entityManager.getComponentVector<CTransform>()[j];
					CBoundingBox& BB2 = m_entityManager.getComponentVector<CBoundingBox>()[j];
					Vec2 overlap;
					if (detectCollision(trans.pos, trans2.pos, BB.radius, BB2.radius, overlap))
					{
						m_entityManager.destoryEntity(i);
						m_entityManager.destoryEntity(j);

						if (!m_entityManager.getComponentVector<CLifeSpan>()[j].has)
						{
							std::cout << j << " big dead\n";
							spawnSmallEnemies(j);
						}

						break;
					}
				}
			}
		}
	}

}


void SceneGeometryWar::update()
{
	m_currentFrame++;

	sLifeSpan();
	if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI)
	{
		spawnEnemy();
	}
	sCollision();
	sMovement();
	sRender();
}