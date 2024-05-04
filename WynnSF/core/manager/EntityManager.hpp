#pragma once
#include <vector>
#include <memory>
#include <map>
#include "../ECS.hpp"
#include "../components/ColliderComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/SpriteComponent.hpp"
#include "../components/InputComponent.hpp"
#include "../components/AnimatorComponent.hpp"
#include "../components/TextComponent.hpp"

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager {
	
	EntityMap m_EntityMap;
	EntityID m_EntitiesSize = 0;
	EntityVector m_ToAdd;
	
public:
	EntityVector Entities;
	EntityManager() {};

	Entity& AddEntity() {
		std::shared_ptr<Entity> e(new Entity());
		Entity& addedEntity = *e;
		m_ToAdd.push_back(e);
		
		return addedEntity;
	};

	Entity& AddEntity(const std::string& tag) {
		std::shared_ptr<Entity> e(new Entity(tag));
		Entity& addedEntity = *e;
		m_ToAdd.push_back(e);
		
		return addedEntity;
	};

	void Update() {
		
		for (auto& e : m_ToAdd) {
			Entities.push_back(e);
			m_EntityMap[e->m_Tag].push_back(e);
		}

		m_ToAdd.clear();
		
	}

	void LogEntites() const {
		for (auto& e : Entities) {
			e->LogEntity();
			std::cout << "	Components :";
			if (e->GetComponentsLength() == 0) {
				std::cout << " No Components" << std::endl;
			}
			else {		
				std::cout << "\n\t{" << std::endl;
				for (auto c : e->m_Components) {
					if (c) {
						c->LogComponent();
						
					}
				}

				std::cout << "\t}" << std::endl;

			}
			
		}
	}

	EntityVector& GetEntities() {
		return this->m_EntityMap["Default"];
	}

	EntityVector& GetEntities(const std::string& tag) {
		if (this->m_EntityMap[tag].size() == 0) {
			std::cout << "Tag vector : " << tag << " has a size of 0" << std::endl;
		}
		return this->m_EntityMap[tag];
	}

	void Destroy() {
		Entities.erase(std::remove_if(Entities.begin(), Entities.end(),
			[](const std::shared_ptr<Entity>& entity) {
				return !entity->IsActive();
			}),
			Entities.end());

		for (auto& pair : m_EntityMap) {
			pair.second.erase(std::remove_if(pair.second.begin(), pair.second.end(),
				[](const std::shared_ptr<Entity>& entity) {
					return !entity->IsActive();
				}),
				pair.second.end());
		}
	}



};