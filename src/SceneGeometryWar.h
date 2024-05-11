#pragma once

#include "Scene.h"
#include <map>
#include <memory>

#include "EntityManager.h"

class GameEngine;

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class SceneGeometryWar : public Scene
{


protected:
	PlayerConfig	m_playerConfig;
	EnemyConfig		m_enemyConfig;
	BulletConfig	m_bulletConfig;

	int				m_playerID;
	int				m_score = 0;
	int				m_lastEnemySpawnTime = 0;
	float			m_rotationAngle = 2.5f;

	bool			m_paused = false;
	bool			m_running = true;


	
	void loadConfig(std::string file);
	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(int parent);
	void spawnBullet();


public:
	SceneGeometryWar(GameEngine* gameEngine);
	void init() override;
	void sRender() override;
	void update() override;

	void sDoAction(const Action& action) override;
	void sMovement();
	void sLifeSpan();
	void sCollision();
};