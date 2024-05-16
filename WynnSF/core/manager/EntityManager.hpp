#pragma once
#include "../ECS.hpp"
#include "../Components/CTransform.hpp"
#include "../Components/CAnimator.hpp"
#include "../Components/CInput.hpp"
#include "../Components/CCollider.hpp"
#include "../Components/CSprite.hpp"
#include "../Components/CText.hpp"
#include "../Components/CButton.hpp"

#include <memory>
#include <vector>
#include <map>
#include <algorithm>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap; //maps entities of a tag to a vector


class EntityManager {


	EntityMap m_entityMap = {};
	EntityVec m_toAdd = {}; //prevent iterator invalidation, where some entites might not be counted when the m_entities gets modified therefore, we add all entities here then at the same time push them to the m_entities vector

public:
	EntityVec m_entities = {};
	EntityManager() {};


	std::shared_ptr<Entity> AddEntity() {
		auto e = std::shared_ptr<Entity>(new Entity);
		m_toAdd.push_back(e);
		return e;
	};

	std::shared_ptr<Entity> AddEntity(const std::string& tag) {
		auto e = std::shared_ptr<Entity>(new Entity(tag));
		m_toAdd.push_back(e);
		return e;
	};

	EntityVec GetEntities() {
		return this->m_entityMap["Default"];
	}

	EntityVec GetEntities(const std::string& tag) {
		return this->m_entityMap[tag];
	}

	void Update() {
		for (auto& e : m_toAdd) {
			m_entities.push_back(e);
			m_entityMap[e->GetTag()].push_back(e);
		}


		m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](const std::shared_ptr<Entity>& e) {
			return !e->IsActive();
			}), m_entities.end());



		for (auto& pair : m_entityMap) {
			pair.second.erase(std::remove_if(pair.second.begin(), pair.second.end(), [](const std::shared_ptr<Entity>& e) {
				return !e->IsActive();
				}), pair.second.end());
		}

		m_toAdd.clear();

	};


	EntityManager(const EntityManager& other) = delete;
	EntityManager(const EntityManager&& other) = delete;
	EntityManager& operator=(const EntityManager& other) = delete;
	~EntityManager() = default;



};

