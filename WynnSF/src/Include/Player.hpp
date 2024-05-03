#pragma once
#include "../../core/ECS.hpp"

class Player  {

	
public:
	Entity* entity = nullptr;
	Player(Entity& e, float x, float y, const std::string& name) {
		this->entity = &e;
		std::shared_ptr<SpriteComponent> sc = entity->AddComponent<SpriteComponent>("src/Assets/Player/Idle/idle0.png", 2.f, 2.f, 0, 0);
		entity->AddComponent<ColliderComponent>(sc->sprite.getTextureRect().width);
		entity->AddComponent<InputComponent>();
		auto tc = entity->AddComponent<TransformComponent>();
		entity->AddComponent<AnimatorComponent>(sc.get());
		tc->Position.x = x;
		tc->Position.y = y;
		entity->AddComponent<TextComponent>("src/Assets/Font/PixelFont.ttf", name, 32);

	};

	bool IsMoving() const { 
		if (entity->GetComponent<TransformComponent>()->Velocity.x != 0 || entity->GetComponent<TransformComponent>()->Velocity.y != 0) {
			return true;
		}

		return false;
	
	};


	void Render(sf::RenderWindow* ctx, float currentFrame) {

		auto sc = entity->GetComponent<SpriteComponent>();
		auto tc = entity->GetComponent<TransformComponent>();
		sc->sprite.setPosition(tc->Position.x, tc->Position.y);
		auto ic = entity->GetComponent<InputComponent>();
		auto ac = entity->GetComponent<AnimatorComponent>();
		auto usernameTextc = entity->GetComponent<TextComponent>()->Text;

		if (IsMoving()) {
			if (LookingLeft()) {
				ac->SetAnimatedSprite("src/Assets/Player/Run/run", 5, currentFrame, -2.f, 2.f, .09f);
			}
			else {
				ac->SetAnimatedSprite("src/Assets/Player/Run/run", 5, currentFrame, 2.f, 2.f, .09f);
			}
		}
		else {
			if (LookingLeft()) {
				ac->SetAnimatedSprite("src/Assets/Player/Idle/idle", 7, currentFrame, -2.f, 2.f, .09f);

			}
			else {
				ac->SetAnimatedSprite("src/Assets/Player/Idle/idle", 7, currentFrame, 2.f, 2.f, .09f);
			}
		}

		ctx->draw(usernameTextc);
		ctx->draw(sc->sprite);
	};

	


	void HandleInput(sf::Event e) {
		auto ic = entity->GetComponent<InputComponent>();
		if (e.type == sf::Event::KeyPressed) {
			switch (e.key.code) {
			case sf::Keyboard::W:
				ic->up = true;
				break;
			case sf::Keyboard::A:
				ic->left = true;
				break;
			case sf::Keyboard::S:
				ic->down = true;
				break;
			case sf::Keyboard::D:
				ic->right = true;
				break;
			}
		}
		if (e.type == sf::Event::KeyReleased) {
			switch (e.key.code) {
			case sf::Keyboard::W:
				ic->up = false;
				break;
			case sf::Keyboard::A:
				ic->left = false;
				break;
			case sf::Keyboard::S:
				ic->down = false;
				break;
			case sf::Keyboard::D:
				ic->right = false;
				break;
			}
		}
	};


	void HandleMovement() {
		auto tc = entity->GetComponent<TransformComponent>();
		auto ic = entity->GetComponent<InputComponent>();
		auto& v = tc->Velocity;
		auto& pos = tc->Position;
		auto sc = entity->GetComponent<SpriteComponent>();
		auto ac = entity->GetComponent<AnimatorComponent>();

		const float PLAYER_SPEED = 5.0f;

		v.x = 0;
		v.y = 0;

		if (ic->right) {
			v.x += PLAYER_SPEED;
		}
		if (ic->up) {
			v.y -= PLAYER_SPEED;
		}
		if (ic->left) {
			v.x -= PLAYER_SPEED;
		}

		if (ic->down) {
			v.y += PLAYER_SPEED;
		}

		v.Normalize();
		v.x *= PLAYER_SPEED;
		v.y *= PLAYER_SPEED;

		pos += v;

		auto UsernameText = entity->GetComponent<TextComponent>();
		UsernameText->Text.setPosition(ac->m_sc->sprite.getPosition().x - 20 ,ac->m_sc->sprite.getPosition().y - 65);
	}

	bool LookingLeft() const {
		static bool lookingLeft = false;

		if (entity->GetComponent<InputComponent>()->left) {
			lookingLeft = true;
		}
		else if(entity->GetComponent<InputComponent>()->right) {
			lookingLeft = false;
		}

		return lookingLeft;
	}
	
};