#pragma once

#include <vector>
#include <map>

#include "MemoryPool.h"


class EntityManager
{
	//std::vector<Entity> m_entities;
	//std::map<int, std::vector<Entity>> m_entityMap;
	size_t m_totalEntities = 0;

	template <typename T> void removeComponent(int ID) {
		MemoryPool::getInstance().getComponent<T>(ID).has = false;
	}

public:
	EntityManager() {};

	/*void update();*/

	size_t addEntity(const std::string tag)
	{
		size_t ID = MemoryPool::getInstance().addEntity(tag);
		//Entity e(ID, tag);

		//m_entities.push_back(e);
		//m_entityMap[tag].push_back(e);

		return ID;
	}

	template <typename T> std::vector<T> & getComponentVector()
	{
		return MemoryPool::getInstance().getComponentVector<T>();
	}

	std::vector<bool>& getActiveVector()
	{
		return MemoryPool::getInstance().getActiveVector();
	}

	void destoryEntity(int ID)
	{
		MemoryPool::getInstance().removeEntity(ID);
		removeComponent<CTransform>(ID);
		removeComponent<CLifeSpan>(ID);
		removeComponent<CInput>(ID);
		removeComponent<CBoundingBox>(ID);
		removeComponent<CGravity>(ID);
		removeComponent<CAnimation>(ID);
		removeComponent<CState>(ID);
	}

	//std::vector<Entity> & getEntities() { return m_entities; }
	//std::vector<Entity> & getEntities(const int tag) { return m_entityMap[tag]; }
};