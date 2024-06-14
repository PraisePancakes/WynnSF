#pragma once
#include "../core/ECS.hpp"
#include "../core/Manager/EntityManager.hpp"
#include "../core/Components/CAnimator.hpp"
#include "../core/Physics/Vec2D.hpp"
#include "Kit.hpp"

class Player {

	std::shared_ptr<Entity> entity = nullptr;
	bool moving = false;
	bool movingAnimationInitialized = false;
	bool lookingLeft = false;
	bool sprinting = false;
	void _updateMovement();
	std::shared_ptr<Kit> kit{ nullptr };

public:
	Player(float spawnX, float spawnY);

	void SetKit(std::shared_ptr<Kit> kit);
	void InitIdleAnimation();
	void InitMovingAnimation();

	inline std::shared_ptr<Entity> GetEntityInstance() const { return this->entity; };
	void Update();
	void Render(sf::RenderWindow& ctx);
	void SetPos(float x, float y);
	bool IsMoving();
	void HandleInput(sf::Event* e);
	Core::Physics::Vec2D GetPos() const;

	void HandleMovement();


};