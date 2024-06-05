#include "EntityManager.hpp"


EntityManager* EntityManager::pinstance{ nullptr };
 std::mutex EntityManager::mut;

EntityManager* EntityManager::GetInstance() {

	std::lock_guard<std::mutex> lock(mut);
	if (pinstance == nullptr)
	{
		pinstance = new EntityManager();
	}
	return pinstance;
};
std::shared_ptr<Entity> EntityManager::AddEntity() {
	auto e = std::shared_ptr<Entity>(new Entity);
	m_toAdd.push_back(e);
	return e;
};

std::shared_ptr<Entity> EntityManager::AddEntity(const std::string& tag) {
	
	auto e = std::shared_ptr<Entity>(new Entity(tag));
	m_toAdd.push_back(e);
	Update();
	return e;
};

EntityVec EntityManager::GetEntities() {
	return this->m_entityMap["Default"];
}

EntityVec EntityManager::GetEntities(const std::string& tag) {
	return this->m_entityMap[tag];
}

void EntityManager::Update() {
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
