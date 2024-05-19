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

	void clearPrevScene() {
		auto grassTiles = em->GetEntities("TileGrass");

		for (auto g : grassTiles) {
			g->DestroyEntity();
		}
	}

	void initScene() {
		switch (m_currentScene) {
		case Scenes::SCENE_RAGNI:
			this->scenemap = { 
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
			};
			break;
		case Scenes::SCENE_ALMUJ:
			this->scenemap = {
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
			};
			break;
		}
	};

	void loadScene() {
		for (size_t i = 0; i < scenemap.size(); i++) {
			for (size_t j = 0; j < scenemap[i].size(); j++) {
				switch (scenemap[i][j]) {
				case 0 :
					{
						
						auto grassTile = em->AddEntity("TileGrass");
						
						auto sc = grassTile->AddComponent<CSprite>("src/Assets/Tiles/Grass.png", sf::IntRect(0, 0, 128, 128), 128, 128);
						sc->sprite.setPosition(i * 128, j * 128);
						
					}
					break;
				case 1 :
					
					break;
				}
			}
		}

		
	
	};



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
		if (scene == Scenes::SCENE_QUIT) {
			this->m_currentScene = scene;
			return;
		}
		this->m_currentScene = scene;
		initScene();
		loadScene();
		
	};

	void Update() {
		
		if (m_currentScene == Scenes::SCENE_MENU) {
			
			int event = menu->GetMenuEvents();
			switch (event) {
			case 1 :
				SetScene(Scenes::SCENE_RAGNI);
				break;
			case 2 :
				SetScene(Scenes::SCENE_QUIT);
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
			
			auto grassTiles = em->GetEntities("TileGrass");
			
			for (auto g : grassTiles) {
				ctx->draw(g->GetComponent<CSprite>()->sprite);
			}
			
		}

	}


	Scenes GetCurrentScene() const { return m_currentScene; };

	~SceneManager() = default;
};