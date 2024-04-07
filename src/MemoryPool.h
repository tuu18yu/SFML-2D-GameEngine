#pragma once

#include <tuple>
#include <vector>

#include "Components.h"

constexpr int MAX_ENTITIES = 10;
constexpr int NUM_COMPONENTS = 7;

// MemoryPool where it contains 'rows' or vector of each Component where each 'column' or index of the tuple is an Entity
typedef std::tuple<
	std::vector<CTransform>,
	std::vector<CLifeSpan>,
	std::vector<CInput>,
	std::vector<CBoundingBox>,
	std::vector<CGravity>,
	std::vector<CAnimation>,
	std::vector<CState>
> ComponentVecTuple;

// MemoryPool plays the role of storing, deleting, and managing Entities

class MemoryPool
{
	size_t						m_numEntities = 0;
	size_t						m_lastAssignedID = 0;
	ComponentVecTuple			m_data;
	std::vector<std::string>	m_tags;
	std::vector<bool>			m_active;

	// MemoryPool class should only be instantized once as game only needs one Pool => constructor is private
	MemoryPool(int maxEntities);

public:
	// In c++ static is not destroyed after th function ends
	static MemoryPool & getInstance()
	{
		static MemoryPool pool(MAX_ENTITIES);
		return pool;
	}

	template <typename T> std::vector<T> & getComponentVector()
	{
		return std::get<std::vector<T>>(m_data);
	}

	template <typename T> T & getComponent(size_t entityID)
	{
		return std::get<std::vector<T>>(m_data)[entityID];
	}

	template <typename T> bool hasComponent(size_t entityID)
	{
		return std::get<std::vector<T>>(m_data)[entityID].has;
	}

	std::vector<bool> & getActiveVector()
	{
		return m_active;
	}

	const std::string getTag(size_t entityID) const
	{
		return m_tags[entityID];
	}

	size_t getEmptyIndex();
	size_t addEntity(const std::string tag);
	void removeEntity(size_t entityID)
	{
		m_active[entityID] = false;
	}
};