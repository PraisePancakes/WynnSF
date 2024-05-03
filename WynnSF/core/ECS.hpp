#pragma once
#include <iostream>
#include <vector>
#include <memory>
#define MAX_COMPONENT_SIZE 10


class Entity;
class Component;

using EntityID = std::uint32_t;
using ComponentTypeID = std::size_t;

ComponentTypeID GenComponentTypeID() {
	static ComponentTypeID lastID = 0;
	return lastID++;
};


template<typename T>
inline ComponentTypeID GenComponentTypeID() {
	static ComponentTypeID id = GenComponentTypeID();
	return id;
}


class Entity {
	friend class EntityManager;

	EntityID m_EntityID;
	std::shared_ptr<Component> m_Components[MAX_COMPONENT_SIZE] = { nullptr };

	
	std::string m_Tag = "Default";
	bool m_IsActive = true;

	EntityID _genEntityID() const {
		static EntityID id = 0;
		return id++;
	};

	Entity() {
	
		static EntityID id = 0;
		this->m_EntityID = _genEntityID();
	};

	Entity(const std::string& tag) {
		
		static EntityID id = 0;
		this->m_EntityID = _genEntityID();
		this->m_Tag = tag;
	};

public:


	template<typename T>
	std::shared_ptr<T> GetComponent() {
		ComponentTypeID typeID = GenComponentTypeID<T>();

		if (HasComponent<T>()) {
			return std::static_pointer_cast<T>(m_Components[typeID]);
		}
		std::cout << typeID;
		std::cout << "Component " << typeid(T).name() << " for entity #" << this->m_EntityID << " not found" << std::endl;
		throw std::runtime_error("Invalid Component");
	};

	template<typename T, typename ...TArgs>
	std::shared_ptr<T> AddComponent(TArgs&&...args) {
		ComponentTypeID typeID = GenComponentTypeID<T>();
		if (HasComponent<T>()) {
			return GetComponent<T>();
		}
		
		std::shared_ptr<T> subComponent = std::make_shared<T>(std::forward<TArgs>(args)...);
		subComponent->Owner = this;
		this->m_Components[typeID] = subComponent;
		return subComponent;
	}
	ComponentTypeID GetComponentsLength() const { return 5; /*change this, not correct size */ };

	template<typename T>
	bool HasComponent() {
		ComponentTypeID typeID = GenComponentTypeID<T>();

		if (typeID <= 10 && m_Components[typeID] != nullptr)
		{
			return true;
		}
		return false;

	
		
	};



	EntityID GetEntityID() const { return this->m_EntityID; };
	bool IsActive() const { return this->m_IsActive; };

	void DestroyEntity() { this->m_IsActive = false; };

	void LogEntity() const {
		std::cout << "Entity" << std::endl;
		std::cout << " ID : " << GetEntityID() << std::endl;
		std::cout << " Tag: " << m_Tag << std::endl;
	}
	~Entity() {};

	
};




class Component {
	ComponentTypeID m_ComponentID;


public:
	Entity* Owner = nullptr;
	Component(ComponentTypeID id) {
		this->m_ComponentID = id;
	};
	
	inline ComponentTypeID GetTypeID() const { return this->m_ComponentID; };
	Entity& GetOwner() const { return *this->Owner; };
	virtual void LogComponent() const = 0;
	virtual ~Component() {};

};