#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "MemoryPool.h"


class EntityManager
{
	//std::vector<Entity> m_entities;
	//std::map<int, std::vector<Entity>> m_entityMap;

	//template <typename T> void removeComponent(int ID) {
	//	MemoryPool::getInstance().getComponent<T>(ID).has = false;
	//}

public:
	EntityManager() {};

	/*void update();*/

	size_t addEntity(const std::string tag)
	{
		size_t ID = MemoryPool::getInstance().addEntity(tag);
		//Entity e(ID, tag);

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

	const std::string& getTag(int ID) const
	{
		return MemoryPool::getInstance().getTag(ID);
	}

	void destoryEntity(int ID)
	{
		MemoryPool::getInstance().removeEntity(ID);
	}

	void clear()
	{
		MemoryPool::getInstance().clear();
	}

	//std::vector<Entity> & getEntities() { return m_entities; }
	//std::vector<Entity> & getEntities(const int tag) { return m_entityMap[tag]; }
};