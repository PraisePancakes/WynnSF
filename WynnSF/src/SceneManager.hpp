#pragma once

#include "../core/Components/CTransform.hpp"


enum class Scenes {
	SCENE_MENU,
	SCENE_RAGNI,
	SCENE_DETLAS,
	SCENE_ALMUJ,
};

class SceneManager {
	Scenes m_currentScene = Scenes::SCENE_MENU;
	sf::RenderWindow* ctx;
	EntityManager* em;

	void initMenu() {
		auto logo = em->AddEntity("Logo");

		auto tc = logo->AddComponent<CTransform>();
		tc->Position.x = (float)ctx->getSize().x / 2;
		tc->Position.y = (float)ctx->getSize().y / 4;
		std::cout << "Logo" << std::endl;
		auto sc = logo->AddComponent<CSprite>("src/Assets/Sprites/Logo/logo.png", sf::IntRect(0, 0, 1974, 687), 256, 128);
		sc->sprite.setPosition(tc->Position.x, tc->Position.y);

		auto b1 = em->AddEntity("Button");


	};

	void renderLogo() {
		std::shared_ptr<Entity> logo = em->GetEntities("Logo")[0];
		auto sc = logo->GetComponent<CSprite>();

		const int MAX_X_DIM = 510;
		const int MAX_Y_DIM = 210;

		const int MIN_X_DIM = 256;
		const int MIN_Y_DIM = 128;

		static int currentX = 256;
		static int currentY = 128;
		static bool reachedMax = false;

		if (!reachedMax) {
			if (currentX < MAX_X_DIM && currentY < MAX_Y_DIM) {
				currentX++;
				currentY++;

			}
			else {
				reachedMax = true;
			}
		}
		else {
			if (currentX > MIN_X_DIM && currentY > MIN_Y_DIM) {
				currentX--;
				currentY--;
			}
			else {
				reachedMax = false;
			}

		}
		sc->ScaleToN(&sc->srcRect, currentX, currentY);




		ctx->draw(sc->sprite);
	}

public:
	SceneManager(Scenes startingScene, sf::RenderWindow* ctx, EntityManager* em) {
		m_currentScene = startingScene;
		this->ctx = ctx;
		this->em = em;
		initMenu();
	};

	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;

	void SetScene(Scenes scene) {
		this->m_currentScene = scene;
	};

	void RenderMenu() {
		renderLogo();
	};

	void RenderScene() {


	};

	Scenes GetCurrentScene() const { return m_currentScene; };

	~SceneManager() = default;
};