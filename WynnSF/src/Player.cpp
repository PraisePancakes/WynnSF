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


	auto healthC = playerHealthE->AddComponent<CHealth>(100);
	auto healthTxtC= playerHealthE->AddComponent<CText>("", "src/Assets/Fonts/PixelFont.ttf", 24, 0, 0, true);
	
};

void Player::SetKit(std::shared_ptr<Kit> kit) {
	
	this->kit = kit;
	this->entity->AddComponent<CCollider>(this->kit->animator.sprite.getGlobalBounds().width / 2);
	
	InitIdleAnimation();

}

void Player::InitIdleAnimation() {
	std::string kitPath = kit->kitBasePath + "Idle.png";
	std::cout << kitPath;
	auto tc = entity->GetComponent<CTransform>();
	this->kit->animator.Reset(kitPath, this->kit->animator.srcRect, this->kit->animator.maxFrame, this->kit->animator.frameWidth);
	
};

void Player::InitMovingAnimation() {
	std::string kitPath = kit->kitBasePath + "Run.png";

	this->kit->animator.Reset(kitPath, this->kit->animator.srcRect, this->kit->animator.maxFrame, this->kit->animator.frameWidth);
	
}


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
	
	
	if (IsMoving() && !movingAnimationInitialized) {
		InitMovingAnimation();
		movingAnimationInitialized = true;
	}
	else if (!IsMoving() && movingAnimationInitialized) {
		InitIdleAnimation();
		movingAnimationInitialized = false;
	}

}


void Player::Update() {
	validateHealth();
	_updateMovement();
	

}

void Player::Render(sf::RenderWindow& ctx) {
	

	
	this->kit->animator.Play(.1f);
	
	
	std::cout << this->kit->animator.sprite.getPosition().x << std::endl;
	std::cout << "here" << kit->animator.path << std::endl;
	ctx.draw(this->kit->animator.sprite);
	
};


void Player::SetPos(float x, float y) {
	auto tc = this->entity->GetComponent<CTransform>();
	tc->Position.x = x;
	tc->Position.y = y;
	this->kit->animator.sprite.setPosition(x, y);

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

	this->kit->animator.sprite.setPosition(tc->Position.x, tc->Position.y);
}
