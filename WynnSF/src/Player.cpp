#include "Player.hpp"

#include "../core/Components/CTransform.hpp"
#include "../core/Components/CInput.hpp"
#include "../core/Components/CCollider.hpp"
#include "../core/Components/CHealth.hpp"
#include "../core/Components/CText.hpp"

Player::Player(float spawnX, float spawnY) {
	this->entity = EntityManager::GetInstance()->AddEntity("Player");
	auto playerHealthE = EntityManager::GetInstance()->AddEntity("Player-Health");

	auto tc = entity->AddComponent<CTransform>(Core::Physics::Vec2D(spawnX, spawnY), Core::Physics::Vec2D(0, 0), 0);
	entity->AddComponent<CInput>();

	

	std::cout << "Player" << std::endl;
	auto ac = entity->AddComponent<CAnimator>("src/Assets/Sprites/Player/playersheet.png", sf::IntRect(0, 0, 50, 40), 64, 64, 0, 150, 50);
	entity->AddComponent<CCollider>(ac->sprite.getGlobalBounds().width / 2);

	auto healthC = playerHealthE->AddComponent<CHealth>(100);
	auto healthTxtC= playerHealthE->AddComponent<CText>("", "src/Assets/Fonts/PixelFont.ttf", 24, 0, 0, true);
	
	InitIdleAnimation();
};

void Player::InitIdleAnimation() {
	auto ac = entity->GetComponent<CAnimator>();
	
	ac->Set(sf::IntRect(0, 0, 50, 40));
};

void Player::InitMovingAnimation() {
	auto ac = entity->GetComponent<CAnimator>();
	ac->Set(sf::IntRect(50, 40, 50, 40));
}

void Player::PlayIdleAnimation() {
	auto ac = entity->GetComponent<CAnimator>();
	ac->Play(.4f);
};

void Player::PlayMovingAnimation() {
	auto ac = entity->GetComponent<CAnimator>();
	ac->Play(.1f);
};


static void validateHealth() {
	std::shared_ptr<Entity> playerHealthE = EntityManager::GetInstance()->GetEntities("Player-Health")[0];
	std::shared_ptr<CHealth> healthC = playerHealthE->GetComponent<CHealth>();

	if (healthC->CurrHp <= 0) {
		healthC->CurrHp = 0;
	}
	if (healthC->CurrHp >= healthC->MaxHP) {
		healthC->CurrHp = healthC->MaxHP;
	}
}

void Player::_updateMovement() {
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


void Player::Update() {
	validateHealth();
	_updateMovement();

}

void Player::Render(sf::RenderWindow& ctx) {
	auto ac = entity->GetComponent<CAnimator>();

	if (!moving) {
		PlayIdleAnimation();
	}
	else {
		PlayMovingAnimation();
	}
	
	ctx.draw(ac->sprite);
};


void Player::SetPos(float x, float y) {
	auto tc = this->entity->GetComponent<CTransform>();
	tc->Position.x = x;
	tc->Position.y = y;
	auto ac = entity->GetComponent<CAnimator>();
	ac->sprite.setPosition(x, y);

}

bool Player::IsMoving() {
	if (entity->GetComponent<CTransform>()->Velocity.x != 0 || entity->GetComponent<CTransform>()->Velocity.y != 0) {
		moving = true;
		return true;
	}
	moving = false;
	return false;
}

void Player::HandleInput(sf::Event* e) {
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

		if (e->key.scancode == 128) {

			sprinting = true;
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

		if (e->key.scancode == 128) {
			sprinting = false;
		}
	}
}


Core::Physics::Vec2D Player::GetPos() const {
	std::shared_ptr<CTransform> tc = entity->GetComponent<CTransform>();
	return tc->Position;
};

void Player::HandleMovement() {

	auto playerInput = entity->GetComponent<CInput>();
	float MOVEMENT_SPEED = 3.0f;
	auto tc = entity->GetComponent<CTransform>();

	if (sprinting) {
		MOVEMENT_SPEED = 4.f;
	}

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
