#pragma once

#include "MemoryPool.h"

class Entity
{
	size_t m_id = 0;
	std::string m_tag;


public:
	Entity(size_t id, std::string tag) : m_id(id), m_tag(tag) {}
	//template<typename T> T & getComponent() {
	//	return MemoryPool::getInstance().getComponent<T>(m_id);
	//}

	//template <typename T> bool hasComponent() {
	//	return MemoryPool::getInstance().hasComponent<T>(m_id);
	//}

	////template <typename T> void addComponent() {
	////	MemoryPool::getInstance().getComponent<T>(m_id).has = true;
	////}


	//size_t getID() { return m_id; }
	//void destroy() 
	//{ 
	//	MemoryPool::getInstance().removeEntity(m_id); 
	//	removeComponent<CTransform>();
	//	removeComponent<CLifeSpan>();
	//	removeComponent<CInput>();
	//	removeComponent<CBoundingBox>();
	//	removeComponent<CGravity>();
	//	removeComponent<CAnimation>();
	//	removeComponent<CState>();
	//}
};