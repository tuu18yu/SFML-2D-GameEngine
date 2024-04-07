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
	

	m_data = std::make_tuple( trans, life, input, box, gravity, animation, state);
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

size_t MemoryPool::addEntity(const std::string tag)
{
	size_t ID = getEmptyIndex();
	// set all vectors[index] = 0
	getComponent<CTransform>(ID).has = false;
	getComponent<CLifeSpan>(ID).has = false;
	getComponent<CInput>(ID).has = false;
	getComponent<CBoundingBox>(ID).has = false;
	getComponent<CGravity>(ID).has = false;
	getComponent<CAnimation>(ID).has = false;
	getComponent<CState>(ID).has = false;

	// set all tag[index], active[index] = defaults
	m_tags[ID] = -1;
	m_active[ID] = true;
	return ID;
}