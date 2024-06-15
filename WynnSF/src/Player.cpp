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
	_initKits();
};

void Player::_initKits() {
	this->kits.push_back(std::make_shared<ArcherKit>());
	this->kits.push_back(std::make_shared<AssassinKit>());
	this->kits.push_back(std::make_shared<WarriorKit>());
	this->kits.push_back(std::make_shared<WizardKit>());
}

void Player::SetKit(KitTypes kit) {
	
	this->currentKitType = kit;
	std::shared_ptr<Kit> kitPtr = this->kits[(int)currentKitType];
	if (kitPtr) {
		this->entity->AddComponent<CCollider>(this->kits[(int)currentKitType]->GetCurrentAnimator().sprite.getLocalBounds().width / 2);
	}
}

void Player::InitIdleAnimation() {
	
	std::shared_ptr<Kit> kitPtr = this->kits[(int)currentKitType];
	
	if (kitPtr) {
		auto archerKit = dynamic_cast<ArcherKit*>(kitPtr.get());
		if (archerKit) {
			archerKit->SetCurrentAnimator(archerKit->animatorData.idle);
		}

		auto assassinKit = dynamic_cast<AssassinKit*>(kitPtr.get());
		if (assassinKit) {
			assassinKit->SetCurrentAnimator(assassinKit->animatorData.idle);
		}

		auto warriorKit = dynamic_cast<WarriorKit*>(kitPtr.get());
		if (warriorKit) {
			warriorKit->SetCurrentAnimator(warriorKit->animatorData.idle);
		}

		auto wizardKit = dynamic_cast<WizardKit*>(kitPtr.get());
		if (wizardKit) {
			wizardKit->SetCurrentAnimator(wizardKit->animatorData.idle);
		}
	}

	
};

void Player::InitMovingAnimation() {
	std::shared_ptr<Kit> kitPtr = this->kits[(int)currentKitType];

	if (kitPtr) {
		auto archerKit = dynamic_cast<ArcherKit*>(kitPtr.get());
		if (archerKit) {
			archerKit->SetCurrentAnimator(archerKit->animatorData.run);
		}

		auto assassinKit = dynamic_cast<AssassinKit*>(kitPtr.get());
		if (assassinKit) {
			assassinKit->SetCurrentAnimator(assassinKit->animatorData.run);
		}

		auto warriorKit = dynamic_cast<WarriorKit*>(kitPtr.get());
		if (warriorKit) {
			warriorKit->SetCurrentAnimator(warriorKit->animatorData.run);
		}

		auto wizardKit = dynamic_cast<WizardKit*>(kitPtr.get());
		if (wizardKit) {
			wizardKit->SetCurrentAnimator(wizardKit->animatorData.run);
		}
	}


	
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
	_setPosRelativeToTransform();
	
	if (IsMoving() && !movingAnimationInitialized) {
		InitMovingAnimation();
		movingAnimationInitialized = true;
	}
	else if (!IsMoving() && movingAnimationInitialized) {
		InitIdleAnimation();
		movingAnimationInitialized = false;
	}

	if (lookingLeft) {
		std::shared_ptr<Kit> kitPtr = this->kits[(int)currentKitType];
		if (kitPtr) {

			auto archerKit = dynamic_cast<ArcherKit*>(kitPtr.get());
			if (archerKit) {
				archerKit->GetCurrentAnimator().ScaleToN(-128, 128);
			}

			auto assassinKit = dynamic_cast<AssassinKit*>(kitPtr.get());
			if (assassinKit) {
				assassinKit->GetCurrentAnimator().ScaleToN(-128, 128);
			}

			auto warriorKit = dynamic_cast<WarriorKit*>(kitPtr.get());
			if (warriorKit) {
				warriorKit->GetCurrentAnimator().ScaleToN(-128, 128);
			}

			auto wizardKit = dynamic_cast<WizardKit*>(kitPtr.get());
			if (wizardKit) {
				
				wizardKit->GetCurrentAnimator().ScaleToN(-128, 128);
			}
		}
	}
	else {
		std::shared_ptr<Kit> kitPtr = this->kits[(int)currentKitType];
		if (kitPtr) {

			auto archerKit = dynamic_cast<ArcherKit*>(kitPtr.get());
			if (archerKit) {
				archerKit->GetCurrentAnimator().ScaleToN(128, 128);
			}

			auto assassinKit = dynamic_cast<AssassinKit*>(kitPtr.get());
			if (assassinKit) {
				assassinKit->GetCurrentAnimator().ScaleToN(128, 128);
			}

			auto warriorKit = dynamic_cast<WarriorKit*>(kitPtr.get());
			if (warriorKit) {
				warriorKit->GetCurrentAnimator().ScaleToN(128, 128);
			}

			auto wizardKit = dynamic_cast<WizardKit*>(kitPtr.get());
			if (wizardKit) {
				wizardKit->GetCurrentAnimator().ScaleToN(128, 128);
			}
		}
	}

}


void Player::Update() {
	validateHealth();
	_updateMovement();
	

}

void Player::Render(sf::RenderWindow& ctx) {
	

	
	std::shared_ptr<Kit> kitPtr = this->kits[(int)currentKitType];
	if (kitPtr) {

		auto archerKit = dynamic_cast<ArcherKit*>(kitPtr.get());
		if (archerKit) {
			archerKit->GetCurrentAnimator().Play(.2f);
			ctx.draw(archerKit->GetCurrentAnimator().sprite);
		}

		auto assassinKit = dynamic_cast<AssassinKit*>(kitPtr.get());
		if (assassinKit) {
			assassinKit->GetCurrentAnimator().Play(.2f);
			ctx.draw(assassinKit->GetCurrentAnimator().sprite);
		}

		auto warriorKit = dynamic_cast<WarriorKit*>(kitPtr.get());
		if (warriorKit) {
			warriorKit->GetCurrentAnimator().Play(.2f);
			ctx.draw(warriorKit->GetCurrentAnimator().sprite);
		}

		auto wizardKit = dynamic_cast<WizardKit*>(kitPtr.get());
		if (wizardKit) {
			wizardKit->GetCurrentAnimator().Play(.2f);
			ctx.draw(wizardKit->GetCurrentAnimator().sprite);
		}
		
	}
	
};


void Player::_setPosRelativeToTransform() {
	auto tc = this->entity->GetComponent<CTransform>();
	tc->Position.x;
	tc->Position.y;

	std::shared_ptr<Kit> kitPtr = this->kits[(int)currentKitType];
	if (kitPtr) {
		auto archerKit = dynamic_cast<ArcherKit*>(kitPtr.get());
		if (archerKit) {
			archerKit->GetCurrentAnimator().sprite.setPosition(tc->Position.x, tc->Position.y);
		}

		auto assassinKit = dynamic_cast<AssassinKit*>(kitPtr.get());
		if (assassinKit) {
			assassinKit->GetCurrentAnimator().sprite.setPosition(tc->Position.x, tc->Position.y);
			
		}

		auto warriorKit = dynamic_cast<WarriorKit*>(kitPtr.get());
		if (warriorKit) {
			warriorKit->GetCurrentAnimator().sprite.setPosition(tc->Position.x, tc->Position.y);

		}

		auto wizardKit = dynamic_cast<WizardKit*>(kitPtr.get());
		if (wizardKit) {
			wizardKit->GetCurrentAnimator().sprite.setPosition(tc->Position.x, tc->Position.y);

		}
	}

}


void Player::SetPos(float x, float y) {
	auto tc = this->entity->GetComponent<CTransform>();
	tc->Position.x = x;
	tc->Position.y = y;

	std::shared_ptr<Kit> kitPtr = this->kits[(int)currentKitType];
	if (kitPtr) {
		auto archerKit = dynamic_cast<ArcherKit*>(kitPtr.get());
		if (archerKit) {
			archerKit->GetCurrentAnimator().sprite.setPosition(x, y);
		}

		auto assassinKit = dynamic_cast<AssassinKit*>(kitPtr.get());
		if (assassinKit) {
			
			assassinKit->GetCurrentAnimator().sprite.setPosition(x, y);
		}

		auto warriorKit = dynamic_cast<WarriorKit*>(kitPtr.get());
		if (warriorKit) {

			warriorKit->GetCurrentAnimator().sprite.setPosition(x, y);
		}

		auto wizardKit = dynamic_cast<WizardKit*>(kitPtr.get());
		if (wizardKit) {

			wizardKit->GetCurrentAnimator().sprite.setPosition(x, y);
		}

	}

	

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
