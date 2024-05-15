#pragma once
#include "../core/ECS.hpp"
#include "../core/Manager/EntityManager.hpp"

class Player {

	std::shared_ptr<Entity> entity = nullptr;
	bool moving = false;
	bool movingAnimationInitialized = false;
	bool lookingLeft = false;



public:
	Player(std::shared_ptr<Entity> e, float spawnX, float spawnY) {
		this->entity = e;
		auto tc = entity->AddComponent<CTransform>(Core::Physics::Vec2D(spawnX, spawnY), Core::Physics::Vec2D(0, 0), 0);
		entity->AddComponent<CInput>();
		std::cout << "Player" << std::endl;
		auto ac = entity->AddComponent<CAnimator>("src/Assets/Sprites/Player/playersheet.png", sf::IntRect(0, 0, 50, 40.7), 64, 64);
		entity->AddComponent<CCollider>(ac->sprite.getGlobalBounds().width / 2);
		InitIdleAnimation();
	};

	void InitIdleAnimation() {
		auto ac = entity->GetComponent<CAnimator>();
		ac->Set(sf::IntRect(0, 0, 50, 40.7));
	};

	void InitMovingAnimation() {
		auto ac = entity->GetComponent<CAnimator>();
		ac->Set(sf::IntRect(50, 39.9, 50, 39.9));
	}

	void PlayIdleAnimation() {
		auto ac = entity->GetComponent<CAnimator>();
		ac->Play(50, 150, .1f);
	};

	void PlayMovingAnimation() {
		auto ac = entity->GetComponent<CAnimator>();
		ac->Play(50, 300, .1f);
	};

	std::shared_ptr<Entity> GetEntityInstance() const { return this->entity; };

	void Update() {
		auto tc = entity->GetComponent<CTransform>();
		auto ac = entity->GetComponent<CAnimator>();
		ac->sprite.setPosition(tc->Position.x, tc->Position.y);
		if (IsMoving() && !movingAnimationInitialized) {
			InitMovingAnimation();
			movingAnimationInitialized = true;
		}
		else if (!IsMoving() && movingAnimationInitialized) {
			InitIdleAnimation();
			movingAnimationInitialized = false;
		}

		if (lookingLeft) {
			ac->sprite.setScale(-1.28f, 1.6f); //scaled to 64 x 64
		}
		else if (!lookingLeft) {
			ac->sprite.setScale(1.28f, 1.6f);
		}

	}

	void Render(sf::RenderWindow& ctx) {
		auto ac = entity->GetComponent<CAnimator>();

		if (!moving) {
			PlayIdleAnimation();
		}
		else {
			PlayMovingAnimation();
		}
		ctx.draw(ac->sprite);
	};

	bool IsMoving() {
		if (entity->GetComponent<CTransform>()->Velocity.x != 0 || entity->GetComponent<CTransform>()->Velocity.y != 0) {
			moving = true;
			return true;
		}
		moving = false;
		return false;
	}

	void HandleInput(sf::Event* e) {
		auto ic = entity->GetComponent<CInput>();
		if (e->type == sf::Event::KeyPressed) {
			if (e->key.scancode == sf::Keyboard::W) {
				ic->iup = true;
			}

			if (e->key.scancode == sf::Keyboard::A) {
				ic->ileft = true;
			}

			if (e->key.scancode == sf::Keyboard::S) {
				ic->idown = true;
			}

			if (e->key.scancode == sf::Keyboard::D) {
				ic->iright = true;
			}


		}
		else if (e->type == sf::Event::KeyReleased) {
			if (e->key.scancode == sf::Keyboard::W) {
				ic->iup = false;
			}

			if (e->key.scancode == sf::Keyboard::A) {
				ic->ileft = false;
			}

			if (e->key.scancode == sf::Keyboard::S) {
				ic->idown = false;
			}

			if (e->key.scancode == sf::Keyboard::D) {
				ic->iright = false;
			}
		}
	}


	Core::Physics::Vec2D GetPos() const {
		std::shared_ptr<CTransform> tc = entity->GetComponent<CTransform>();
		return tc->Position;
	};

	void HandleMovement() {

		auto playerInput = entity->GetComponent<CInput>();
		const float MOVEMENT_SPEED = 3.0f;
		auto tc = entity->GetComponent<CTransform>();

		float velX = 0;
		float velY = 0;

		if (playerInput->idown) {
			velY += MOVEMENT_SPEED;
		}

		if (playerInput->ileft) {
			lookingLeft = true;
			velX -= MOVEMENT_SPEED;
		}

		if (playerInput->iright) {
			lookingLeft = false;
			velX += MOVEMENT_SPEED;
		}

		if (playerInput->iup) {
			velY -= MOVEMENT_SPEED;
		}

		tc->Velocity.x = velX;
		tc->Velocity.y = velY;


		tc->Velocity.Normalize();

		tc->Velocity.x *= MOVEMENT_SPEED;
		tc->Velocity.y *= MOVEMENT_SPEED;

		tc->Position += tc->Velocity;
	}



};