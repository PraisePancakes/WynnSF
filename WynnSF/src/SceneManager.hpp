#pragma once

#include "../core/Components/CTransform.hpp"


enum class Scenes {
	SCENE_MENU,
	SCENE_RAGNI,
	SCENE_DETLAS,
	SCENE_ALMUJ,

	SCENE_QUIT,
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

		auto playTxt = em->AddEntity("Play-text");
		auto playTextC = playTxt->AddComponent<CText>("Play", "src/Assets/Fonts/PixelFont.ttf", 36, (float)ctx->getSize().x / 2 , (float)ctx->getSize().y / 2);
		
		auto playBtn = em->AddEntity("Play-btn");
		auto playBtnC = playBtn->AddComponent<CButton>(sf::RectangleShape(sf::Vector2f(playTextC->text.getGlobalBounds().width + 10, playTextC->text.getGlobalBounds().height + 10)), sf::Vector2f(playTextC->text.getPosition().x - playTextC->text.getGlobalBounds().width / 2 - 3, playTextC->text.getPosition().y), sf::Color::White, sf::Color::Black);

		auto quitTxt = em->AddEntity("Quit-text");
		auto quitTextC = quitTxt->AddComponent<CText>("Quit", "src/Assets/Fonts/PixelFont.ttf", 36, (float)ctx->getSize().x / 2, (float)ctx->getSize().y / 2 + 50);
		
		auto quitBtn = em->AddEntity("Quit-btn");
		auto quitBtnC = quitBtn->AddComponent<CButton>(sf::RectangleShape(sf::Vector2f(quitTextC->text.getGlobalBounds().width + 10, quitTextC->text.getGlobalBounds().height + 10)), sf::Vector2f(quitTextC->text.getPosition().x - quitTextC->text.getGlobalBounds().width / 2 - 3, quitTextC->text.getPosition().y + 5), sf::Color::White, sf::Color::Black);
	};

	
	
	void test() {
	};

	void renderMenuButtons() {
		std::shared_ptr<Entity> btn = em->GetEntities("Play-btn")[0];
		auto btnC = btn->GetComponent<CButton>();

		std::shared_ptr<Entity> quitbtn = em->GetEntities("Quit-btn")[0];

		auto qbtnC = quitbtn->GetComponent<CButton>();
	
		qbtnC->OnHover(ctx, [qbtnC]() {
			qbtnC->buttonRect.setOutlineColor(sf::Color::Red);
			
			});

		qbtnC->OnClick(ctx, [this]() {
			this->SetScene(Scenes::SCENE_QUIT);

			});

		btnC->OnHover(ctx, [btnC]() {
			btnC->buttonRect.setOutlineColor(sf::Color::Green);
			});

		btnC->OnClick(ctx, [this]() {
			this->SetScene(Scenes::SCENE_RAGNI);
		});


		ctx->draw(qbtnC->buttonRect);
		ctx->draw(btnC->buttonRect);
	}


	void renderMenuText() {
		std::shared_ptr<Entity> play = em->GetEntities("Play-text")[0];
		

		auto playTextC = play->GetComponent<CText>();

		std::shared_ptr<Entity> quit = em->GetEntities("Quit-text")[0];


		auto quitTextC = quit->GetComponent<CText>();
		ctx->draw(quitTextC->text);
		ctx->draw(playTextC->text);
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

	void renderMenu() {
		renderLogo();
		renderMenuButtons();
		renderMenuText();
	
	};

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

	

	void RenderScene() {
		if (this->m_currentScene == Scenes::SCENE_MENU) {
			renderMenu();
		}
		else {
			//render scene
		}

	};

	void Update() {
		
	
	};


	Scenes GetCurrentScene() const { return m_currentScene; };

	~SceneManager() = default;
};