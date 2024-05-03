#pragma once
#include "../../core/manager/EntityManager.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Include/Player.hpp"

#define WINDOW_W 1280
#define WINDOW_H 720

const char* title = "WynnSF";


class Game {
	
	sf::RenderWindow m_Window;
	bool m_Running;
	EntityManager em;
	bool m_Paused;
	int m_CurrentFrame;
	bool m_Started = false;
	std::unique_ptr<Player> m_Player;
	
	

	void SUserInput() {
		sf::Event e;
		auto& p = em.GetEntities("Player")[0];
		auto ic = p->GetComponent<InputComponent>();

		while (m_Window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				m_Running = false;
			}
			if (m_Started) {
				m_Player->HandleInput(e);
			}
			else {
				if (e.type == sf::Event::MouseButtonPressed) {
					m_Started = true;
				}

				if (e.type == sf::Event::KeyPressed) {
					switch (e.key.code) {
						case sf::Keyboard::Q :
							m_Running = false;
						break;
					}
				}
			}

		}
	};

	void SCollision() {
		
	
	
	};


	void SMovement() {
		if (m_Started) {
			m_Player->HandleMovement();
		}
		
	};

	void spawnPlayer(const std::string& name) {
		auto& player = em.AddEntity("Player");
		this->m_Player = std::make_unique<Player>(player, (float)m_Window.getSize().x / 2, (float)m_Window.getSize().y / 2, name);
	};

	void initMenu() {
		auto& logo = em.AddEntity("Logo");
		auto sc = logo.AddComponent<SpriteComponent>("src/Assets/Logo/logo.png", .3f, .3f, WINDOW_W / 2, WINDOW_H / 4);
		std::cout << "logo init success" << std::endl;

		auto& playText = em.AddEntity("Play");
		auto textc = playText.AddComponent<TextComponent>("src/Assets/Font/PixelFont.ttf", "Left Click to play...", 32);

		auto& quitText = em.AddEntity("Quit");
		auto quitTextc = quitText.AddComponent<TextComponent>("src/Assets/Font/PixelFont.ttf", "Q to quit...", 32);


		textc->Text.setPosition(sc->originalXpos - 100, sc->originalYpos + 150);
		quitTextc->Text.setPosition(sc->originalXpos - 100, sc->originalYpos + 200);
	}

	void renderLogo() {
		auto logoSc = em.GetEntities("Logo")[0]->GetComponent<SpriteComponent>();
		const int MAX_OSC = WINDOW_W / 2 + 50;
		const int MIN_OSC = WINDOW_W / 2 - 50;
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

		m_Window.draw(logoSc->sprite);
	}


	void renderTextQuit() {
		auto& quitText = em.GetEntities("Quit")[0];

		m_Window.draw(quitText->GetComponent<TextComponent>()->Text);
	};

	void renderTextPlay() {
		auto &playText = em.GetEntities("Play")[0];

		m_Window.draw(playText->GetComponent<TextComponent>()->Text);
		
	};

	void renderMenu() {
		renderLogo();
		renderTextPlay();
		renderTextQuit();
	};


	void SRender() {

		if (!m_Started) {
			renderMenu();
		}
		else {
			m_Player->Render(&m_Window, m_CurrentFrame);
		}
		
	}


	
public:
	Game() {
		std::string username;
		std::cout << "Enter your wynn username : ";
		std::cin >> username;

		m_Window.create(sf::VideoMode(WINDOW_W, WINDOW_H), title, sf::Style::Close | sf::Style::Titlebar);
		spawnPlayer(username);
		initMenu();
		m_Paused = false;
		m_Running = true;
		m_CurrentFrame = 0;
		m_Window.setFramerateLimit(60);
	
	};
	void Run() {

		
		while (m_Running) {
			
			em.Update();
			em.LogEntites();
			m_Window.clear();
			if (!m_Paused) {	
				SUserInput();
				SMovement();
				SCollision();
			}

			
			SRender();
			m_CurrentFrame++;
			
			m_Window.display();
		}

		
	
	};
	~Game() {};
};