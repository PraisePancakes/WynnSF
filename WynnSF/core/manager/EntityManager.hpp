#pragma once
#include "../ECS.hpp"
#include <memory>
#include <vector>
#include <map>
#include <algorithm>


class Entity;

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap; //maps entities of a tag to a vector


class EntityManager {


	EntityMap m_entityMap = {};
	EntityVec m_toAdd = {}; //prevent iterator invalidation, where some entites might not be counted when the m_entities gets modified therefore, we add all entities here then at the same time push them to the m_entities vector

public:
	EntityVec m_entities = {};
	EntityManager();

	std::shared_ptr<Entity> AddEntity();

	std::shared_ptr<Entity> AddEntity(const std::string& tag);

	EntityVec GetEntities();


	EntityVec GetEntities(const std::string& tag);

	void Update();


	EntityManager(const EntityManager& other) = delete;
	EntityManager(const EntityManager&& other) = delete;
	EntityManager& operator=(const EntityManager& other) = delete;
	
	~EntityManager();


};

