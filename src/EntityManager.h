#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "MemoryPool.h"


class EntityManager
{
public:
	EntityManager() {};

	size_t addEntity(const std::string tag)
	{
		size_t ID = MemoryPool::getInstance().addEntity(tag);

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
};