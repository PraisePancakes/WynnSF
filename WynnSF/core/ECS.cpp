#include "ECS.hpp"

EntityID Entity::genUEID() {
	static EntityID lastID = 0;
	return lastID++;
};

Entity::Entity() {
	this->m_eId = genUEID();
};

Entity::Entity(const std::string& tag) {
	this->m_eId = genUEID();
	this->m_eTag = tag;
}


ComponentID GenComponentTypeID() {
	static ComponentID lastID = 0;

	return lastID++;
};