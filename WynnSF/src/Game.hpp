#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../core/Manager/EntityManager.hpp"
#include "SceneManager.hpp"
#include "Player.hpp"
#include "GlobalChatBox.hpp"

#include <cmath>

#define WINDOW_W 1280
#define WINDOW_H 720



class Game {

	bool m_running = false;
	sf::RenderWindow m_Window;
	EntityManager m_entManager;
	sf::View m_Cam;
	std::unique_ptr<Player> m_Player = nullptr;
	std::unique_ptr<SceneManager> m_sceneManager;
	std::unique_ptr<GlobalChatBox> m_chatBox;

	void sUserInput();
	void sMovement();
	void sUpdate();
	/*
		since we are using a circle collider, the collision system will work based positioning of each circle collider when collision occurs

		refer to diagrams/collision.png
		
		 
	*/

	void checkCollision(EntityVec& ev);
	void sCollider();


	//TEST
	void spawnTestDummy();

	void spawnPlayer();

	void sRenderer();


public:
	Game(const std::string& title);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	~Game() = default;



	void Run();
	
};