#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../core/Manager/EntityManager.hpp"
#include "SceneManager.hpp"
#include "Player.hpp"
#include <cmath>
#define WINDOW_W 1280
#define WINDOW_H 720
#define PI 3.14159265


class Game {

	bool m_running = false;
	sf::RenderWindow m_Window;
	EntityManager m_entManager;
	sf::View m_Cam;
	std::unique_ptr<Player> m_Player = nullptr;
	std::unique_ptr<SceneManager> m_sceneManager;

	void sUserInput() {
		sf::Event e;

		while (m_Window.pollEvent(e)) {
			if (e.type == sf::Event::EventType::Closed) {
				m_Window.close();
				m_running = false;
			}

		

			if (m_sceneManager->GetCurrentScene() != Scenes::SCENE_MENU) {
				m_Player->HandleInput(&e);
			}
		}

	};

	void sMovement() {
		m_Player->HandleMovement();
	};

	void sUpdate() {
		m_entManager.Update();
		m_Player->Update();
		m_sceneManager->Update();
	
	}
	/*
		since we are using a circle collider, the collision system will work based positioning of each circle collider when collision occurs

		refer to diagrams/collision.png
		
		 
	*/

	void checkCollision(EntityVec& ev) {

		float plx = m_Player->GetPos().x;
		float ply = m_Player->GetPos().y;
		

		for (auto& e : ev) {
			if (e->HasComponent<CCollider>()) {
				float ex = e->GetComponent<CSprite>()->sprite.getPosition().x;
				float ey = e->GetComponent<CSprite>()->sprite.getPosition().y;
				float xDiff = plx - ex;
				float yDiff = ply - ey;

				float distance = std::sqrt(xDiff * xDiff + yDiff * yDiff);
				float pr = m_Player->GetEntityInstance()->GetComponent<CCollider>()->radius;
				float er = e->GetComponent<CCollider>()->radius;

				if (distance < pr + er) {
					auto tc = m_Player->GetEntityInstance()->GetComponent<CTransform>();
					
					if (xDiff < 0 && std::abs(xDiff) > std::abs(yDiff)) { 
						tc->Position.x -= std::abs(m_Player->GetEntityInstance()->GetComponent<CTransform>()->Velocity.x);
					}
					else if (xDiff > 0 && std::abs(xDiff) > std::abs(yDiff)) { 
						tc->Position.x += std::abs(m_Player->GetEntityInstance()->GetComponent<CTransform>()->Velocity.x);
					}
					else if (yDiff < 0 && std::abs(yDiff) > std::abs(xDiff)) { 
						tc->Position.y -= std::abs(m_Player->GetEntityInstance()->GetComponent<CTransform>()->Velocity.y);
					}
					else if (yDiff > 0 && std::abs(yDiff) > std::abs(xDiff)) { 
						tc->Position.y += std::abs(m_Player->GetEntityInstance()->GetComponent<CTransform>()->Velocity.y);
					}
				}
			}
		}
	};



	void sCollider() {
		EntityVec tlTiles = m_entManager.GetEntities("tlTiles");
		EntityVec dumVec /*npc vec*/ = m_entManager.GetEntities("Dummy");
		checkCollision(dumVec);
		checkCollision(tlTiles);
	};


	//TEST
	void spawnTestDummy() {
		auto dum = m_entManager.AddEntity("Dummy");
		std::cout << "Dummy" << std::endl;
		auto ac = dum->AddComponent<CSprite>("src/Assets/Sprites/Player/playersheet.png", sf::IntRect(0, 0, 50, 40.7), 64, 64);
		dum->AddComponent<CCollider>(15);
		auto tc = dum->AddComponent<CTransform>(Core::Physics::Vec2D(WINDOW_W / 2, WINDOW_H / 2), Core::Physics::Vec2D(0, 0), 0.f);
		ac->sprite.setPosition(tc->Position.x, tc->Position.y);

	};

	void spawnPlayer() {
		auto player = m_entManager.AddEntity("Player");
		float spawnX = WINDOW_W / 2 + 50;
		float spawnY = WINDOW_H / 2 + 100;

		m_Player = std::make_unique<Player>(player, spawnX, spawnY);

	};

	void sRenderer() {
		m_sceneManager->RenderScene();
		if (m_sceneManager->GetCurrentScene() != Scenes::SCENE_MENU) {
			std::shared_ptr<Entity> dum = m_entManager.GetEntities("Dummy")[0];
			auto sc = dum->GetComponent<CSprite>();
			m_sceneManager->RenderScene();
			m_Player->Render(this->m_Window);
			m_Window.draw(sc->sprite);
			m_Cam.setCenter(m_Player->GetPos().x, m_Player->GetPos().y);
			m_Window.setView(m_Cam);
			
		}
		
	

	};


public:
	Game(const std::string& title) {
		m_running = true;
		m_Window.create(sf::VideoMode::VideoMode(WINDOW_W, WINDOW_H), title, sf::Style::Titlebar | sf::Style::Close);
		m_Window.setFramerateLimit(60);
		spawnPlayer();
		spawnTestDummy();
		m_sceneManager = std::make_unique<SceneManager>(Scenes::SCENE_MENU, &this->m_Window, &this->m_entManager);
		m_Cam.setSize(WINDOW_W, WINDOW_H);

	};
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	~Game() = default;



	void Run() {
		
		while (m_running) {
			m_Window.clear();
			sUserInput();
			sUpdate();
			if (m_sceneManager->GetCurrentScene() == Scenes::SCENE_QUIT) {
				m_running = false;
				m_Window.close();
			}
			//handle game events
			if (m_sceneManager->GetCurrentScene() != Scenes::SCENE_MENU) {
				sCollider();
				sMovement();
				
			}

			
			sRenderer();
			m_Window.display();

		}
	};
};