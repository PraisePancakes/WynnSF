#pragma once
#include "../../core/manager/EntityManager.hpp"

enum class Scenes {
	SCENE_MENU,
	WYNN_MIN,
	SCENE_RAGNI,
	SCENE_EMERALD_TRAIL,
	SCENE_DETLAS,
	SCENE_ALMUJ,
	WYNN_MAX,

};

class SceneManager {
	Scenes m_CurrentSceneIdx = Scenes::SCENE_MENU; //MENU, LOCATION, etc...
	EntityManager* em = nullptr;
	std::vector<std::vector<int>> map;
	sf::RenderWindow *ctx;


public:
	SceneManager( sf::RenderWindow* ctx, EntityManager* em, Scenes scene) {
		this->em = em;
		this->ctx = ctx;
		this->m_CurrentSceneIdx = scene;
		
	};


	void InitScene() {
		switch (m_CurrentSceneIdx) {
		case Scenes::SCENE_MENU:
		{

			auto& logo = em->AddEntity("Logo");
			auto sc = logo.AddComponent<SpriteComponent>("src/Assets/Logo/logo.png", .3f, .3f, ctx->getSize().x / 2, ctx->getSize().y / 2);
			std::cout << "logo init success" << std::endl;

			auto& playText = em->AddEntity("Play");
			auto textc = playText.AddComponent<TextComponent>("src/Assets/Font/PixelFont.ttf", "Left Click to play...", 32);

			auto& quitText = em->AddEntity("Quit");
			auto quitTextc = quitText.AddComponent<TextComponent>("src/Assets/Font/PixelFont.ttf", "Q to quit...", 32);

			textc->Text.setPosition(sc->originalXpos - 100, sc->originalYpos + 150);
			quitTextc->Text.setPosition(sc->originalXpos - 100, sc->originalYpos + 200);
		}
			break;
		case Scenes::SCENE_RAGNI:
			
			break;
		}
	}

	Scenes GetCurrentScene() const {
		return m_CurrentSceneIdx;
	}

	void RenderScene() {
		switch (m_CurrentSceneIdx) {
		case Scenes::SCENE_MENU:
			auto logoSc = em->GetEntities("Logo")[0]->GetComponent<SpriteComponent>();
			const int MAX_OSC = ctx->getSize().x / 2 + 50;
			const int MIN_OSC = ctx->getSize().x / 2 - 50;
			static bool moveLeft = false;

			if (!moveLeft) {
				logoSc->sprite.setPosition(logoSc->sprite.getPosition().x + .5f, logoSc->sprite.getPosition().y);
				if (logoSc->sprite.getPosition().x == MAX_OSC) {
					moveLeft = true;
				}
			}
			else {
				logoSc->sprite.setPosition(logoSc->sprite.getPosition().x - .5f, logoSc->sprite.getPosition().y);
				if (logoSc->sprite.getPosition().x == MIN_OSC) {
					moveLeft = false;
				}
			}

			auto& quitText = em->GetEntities("Quit")[0];

			ctx->draw(quitText->GetComponent<TextComponent>()->Text);
			auto& playText = em->GetEntities("Play")[0];

			ctx->draw(playText->GetComponent<TextComponent>()->Text);
			ctx->draw(logoSc->sprite);
			break;

		}
	};

	void LoadScene() {
		switch (m_CurrentSceneIdx) {
		case Scenes::SCENE_MENU:
			break;
		case Scenes::SCENE_RAGNI:
			this->map = {
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
			};
			break;
		}
		
	};

	void SetScene(Scenes scene) {
		m_CurrentSceneIdx = scene;
	};
};