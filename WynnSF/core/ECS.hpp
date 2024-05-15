#pragma once
#include <iostream>
#include <memory>
#include "Manager/EntityManager.hpp"
#define MAX_COMPONENTS_SIZE 10

class Component;
class Entity;

using ComponentID = std::size_t;
using EntityID = std::uint64_t;

ComponentID GenComponentTypeID() {
	static ComponentID lastID = 0;

	return lastID++;
};

template<class T>
ComponentID GenComponentTypeID() {
	static ComponentID typeID = GenComponentTypeID();
	return typeID;
}

class Component {
	ComponentID m_id;

public:
	Component(ComponentID generatedID) { this->m_id = generatedID; };
	Entity* owner = nullptr;

	ComponentID GetComponentTypeID() const {
		return this->m_id;
	}

};



class Entity {

	friend class EntityManager;

private:
	EntityID m_eId;
	EntityID genUEID() {
		static EntityID lastID = 0;
		return lastID++;
	};

	std::shared_ptr<Component> m_Components[MAX_COMPONENTS_SIZE];

	std::string m_eTag = "Default";

	Entity() {
		this->m_eId = genUEID();
	};

	Entity(const std::string& tag) {
		this->m_eId = genUEID();
		this->m_eTag = tag;
	}


	bool m_active = true;

public:



	template<class T, typename ...TArgs>
	std::shared_ptr<T> AddComponent(TArgs&&... args) {
		std::shared_ptr<T> newComponent = std::make_shared<T>(std::forward<TArgs>(args)...);
		newComponent->owner = this;
		m_Components[newComponent->GetComponentTypeID()] = newComponent;
		return newComponent;
	};

	template<class T>
	bool HasComponent() const {
		ComponentID id = GenComponentTypeID<T>();

		if (m_Components[id] != nullptr) {
			return true;
		}

		return false;

	};

	std::string GetTag() const {
		return m_eTag;
	}

	EntityID GetID() const { return this->m_eId; };

	template<class T>
	std::shared_ptr<T> GetComponent() {
		ComponentID id = GenComponentTypeID<T>();

		if (m_Components[id] != nullptr) {
			return std::static_pointer_cast<T>(m_Components[id]);
		}

		std::cout << "Component : " << typeid(T).name() << " does not exist" << std::endl;

	}

	void DestroyEntity() {
		this->m_active = false;
	}

	bool IsActive() const {
		return this->m_active;
	}

};
