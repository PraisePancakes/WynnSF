#pragma once
#include "../core/Manager/EntityManager.hpp"
#include "Menu.hpp"
#include <ctime>





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
	std::unique_ptr<Menu> menu = nullptr;
	std::vector<std::vector<int>> scenemap = { {} };

public:
	SceneManager(Scenes startingScene, sf::RenderWindow* ctx, EntityManager* em)  {
		m_currentScene = startingScene;
		this->ctx = ctx;
		this->em = em;
		menu = std::make_unique<Menu>(em, ctx);
	};

	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;

	void SetScene(Scenes scene) {
		this->m_currentScene = scene;
	};

	void Update() {
		
		if (m_currentScene == Scenes::SCENE_MENU) {
			
			int event = menu->GetMenuEvents();
			switch (event) {
			case 1 :
				m_currentScene = Scenes::SCENE_RAGNI;
				break;
			case 2 :
				m_currentScene = Scenes::SCENE_QUIT;
				break;
			default:
				break;
			}
		}
		else {
			//update
		}
		
	};

	void RenderScene() {
		if (this->m_currentScene == Scenes::SCENE_MENU) {
			menu->Render();
		}
		else {
			//render scene
		}

	}


	Scenes GetCurrentScene() const { return m_currentScene; };

	~SceneManager() = default;
};