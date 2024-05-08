#include "MemoryPool.h"


MemoryPool::MemoryPool(int maxEntities)
{
	m_tags = std::vector<std::string>(maxEntities, "N/A");
	m_active = std::vector<bool>(maxEntities, false);
	
	std::vector<CTransform> trans(maxEntities);
	std::vector<CLifeSpan> life(maxEntities);
	std::vector<CInput> input(maxEntities);
	std::vector<CBoundingBox> box(maxEntities);
	std::vector<CGravity> gravity(maxEntities);
	std::vector<CAnimation> animation(maxEntities);
	std::vector<CState> state(maxEntities);
	std::vector<CShape> shape(maxEntities);
	

	m_data = std::make_tuple( trans, life, input, box, gravity, animation, state, shape);
}

size_t MemoryPool::getEmptyIndex()
{
	for (size_t i = m_lastAssignedID + 1; i < MAX_ENTITIES; i++)
	{
		if (!m_active[i]) { return i; }
	}

	for (size_t i = 0; i < m_lastAssignedID; i++)
	{
		if (!m_active[i]) { return i; }
	}

	return -1;
}

size_t MemoryPool::addEntity(std::string tag)
{
	size_t ID = getEmptyIndex();
	m_lastAssignedID = ID;
	m_numEntities++;
	// set all tag[index], active[index] = defaults
	m_tags[ID] = tag;
	m_active[ID] = true;
	return ID;
}

void MemoryPool::removeEntity(size_t ID)
{
	m_numEntities--;
	m_active[ID] = false;
	m_tags[ID] = "N/A";
	getComponent<CTransform>(ID).has = false;
	getComponent<CLifeSpan>(ID).has = false;
	getComponent<CInput>(ID).has = false;
	getComponent<CBoundingBox>(ID).has = false;
	getComponent<CGravity>(ID).has = false;
	getComponent<CAnimation>(ID).has = false;
	getComponent<CState>(ID).has = false;
	getComponent<CShape>(ID).has = false;
}

void MemoryPool::clear()
{
	for (int ID = 0; ID < MAX_ENTITIES; ID++)
	{
		removeEntity(ID);
	}
}