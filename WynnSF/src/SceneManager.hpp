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


struct TXTiles {
	const std::string TXGrassSetPath = "src/Assets/Tiles/TXGrassSet.png";
	sf::IntRect grass = {0, 0, 128, 128};
	sf::IntRect flower = {128, 0, 128, 128};
	sf::IntRect stone = { 0, 128, 128, 128 };
	sf::IntRect stone2 = { 128, 128, 128, 128 };
};

class SceneManager {

	Scenes m_currentScene = Scenes::SCENE_MENU;
	sf::RenderWindow* ctx;
	EntityManager* em;
	std::unique_ptr<Menu> menu = nullptr;
	std::vector<std::vector<int>> scenemap = { {} };
	std::unique_ptr<TXTiles> tiles;

	void clearPrevScene() {
		auto tiles = em->GetEntities("Tiles");

		for (auto& t : tiles) {
			t->DestroyEntity();
		}
	}

	void initScene() {
		//read scene data from file?
		switch (m_currentScene) {
		case Scenes::SCENE_RAGNI:
			this->scenemap = { 
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,1,0,0,0,3,0,0,0,3,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,2,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
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
		//TO DO : Fix manual offsets that have to be added to sprite positioning
		for (size_t i = 0; i < scenemap.size(); i++) {
			for (size_t j = 0; j < scenemap[i].size(); j++) {
				switch (scenemap[j][i]) {
				case 0 :
					{
						auto grassTile = em->AddEntity("Tiles");	
						auto sc = grassTile->AddComponent<CSprite>(tiles->TXGrassSetPath,tiles->grass, 128, 128);
						sc->sprite.setPosition(i * 128, j * 128);
					}
					break;
				case 1 :
					{
						auto flowerTile = em->AddEntity("Tiles");

						auto sc = flowerTile->AddComponent<CSprite>(tiles->TXGrassSetPath, tiles->flower, 128, 128);
						sc->sprite.setPosition((i + 1) * 128, (j) * 128);
					}
					break;
				case 2 :
					{
						auto stoneTile = em->AddEntity("Tiles");
						auto sc = stoneTile->AddComponent<CSprite>(tiles->TXGrassSetPath, tiles->stone, 128, 128);
						sc->sprite.setPosition((i) * 128, (j + 1) * 128);
						
					}
					break;
				case 3 :
					{
					auto stoneTile = em->AddEntity("Tiles");
					auto sc = stoneTile->AddComponent<CSprite>(tiles->TXGrassSetPath, tiles->stone2, 128, 128);
					sc->sprite.setPosition((i + 1) * 128, (j + 1 )* 128);
					}
					break;
				case 4:
				{
					
				}
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
		tiles = std::make_unique<TXTiles>();
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
			
			auto tiles = em->GetEntities("Tiles");
			
			for (auto& t : tiles) {
				ctx->draw(t->GetComponent<CSprite>()->sprite);
			}
			
		}

	}


	Scenes GetCurrentScene() const { return m_currentScene; };

	~SceneManager() = default;
};