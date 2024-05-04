#pragma once
#include "../../core/manager/EntityManager.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Include/Player.hpp"
#include "../Include/Camera.hpp"
#include "../Include/SceneManager.hpp"


#define WINDOW_W 1280
#define WINDOW_H 720

const char* title = "WynnSF";

/*
	TO DO
	seperate implementation details into source files
*/


class Game {
	
	sf::RenderWindow m_Window;
	bool m_Running;
	EntityManager em;
	bool m_Paused;
	int m_CurrentFrame;
	bool m_Started = false;
	std::unique_ptr<Player> m_Player;
	std::unique_ptr<Camera> m_Camera;
	std::unique_ptr<SceneManager> sm;
	
	void SUserInput() {
		sf::Event e;
		auto& p = em.GetEntities("Player")[0];
		auto ic = p->GetComponent<InputComponent>();

		while (m_Window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				m_Running = false;
			}
			if (sm->GetCurrentScene() != Scenes::SCENE_MENU) {
				m_Player->HandleInput(e);
			}
			else {
				if (e.type == sf::Event::MouseButtonPressed) {
					sm->SetScene(Scenes::SCENE_RAGNI);
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
		if (sm->GetCurrentScene() != Scenes::SCENE_MENU) {
			m_Player->HandleMovement();
		}
		
	};

	void spawnPlayer(const std::string& name) {
		auto& player = em.AddEntity("Player");
		this->m_Player = std::make_unique<Player>(player, (float)m_Window.getSize().x / 2, (float)m_Window.getSize().y / 2, name);
	};

	/*TEST*/void spawnTestDummy() {
			auto& testD = em.AddEntity("Dummy");
			testD.AddComponent<SpriteComponent>("src/Assets/Player/Idle/idle0.png", 1.f, 1.f, WINDOW_W / 2, WINDOW_H / 2);
		};
	

	void SRender() {
		auto& test = em.GetEntities("Dummy")[0];
		auto test_sc = test->GetComponent<SpriteComponent>();

		
			sm->RenderScene();

			if (sm->GetCurrentScene() != Scenes::SCENE_MENU) {
				m_Player->Render(&m_Window, m_CurrentFrame);
				m_Window.draw(test_sc->sprite); /*TEST*/
				m_Camera->Update(m_Player->entity->GetComponent<TransformComponent>()->Velocity.x, m_Player->entity->GetComponent<TransformComponent>()->Velocity.y);
				m_Window.setView(m_Camera->GetView());
			}
		
		
		
	}


	
public:
	Game() {
		std::string username;
		std::cout << "Enter your wynn username : ";
		std::cin >> username;

		m_Window.create(sf::VideoMode(WINDOW_W, WINDOW_H), title, sf::Style::Close | sf::Style::Titlebar);
		spawnPlayer(username);
		spawnTestDummy();


		m_Paused = false;
		m_Running = true;
		m_CurrentFrame = 0;
		m_Window.setFramerateLimit(60);
		m_Camera = std::make_unique<Camera>(WINDOW_W, WINDOW_H, m_Player->entity->GetComponent<TransformComponent>()->Position.x, m_Player->entity->GetComponent<TransformComponent>()->Position.y);
		m_Window.setView(m_Camera->GetView());
		sm = std::make_unique<SceneManager>(&m_Window, &em, Scenes::SCENE_MENU);
		sm->InitScene();

	
	};
	void Run() {

		
		while (m_Running) {
			
			em.Update();
		
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