#pragma once
#include "../core/Manager/EntityManager.hpp"
#include "Menu.hpp"
#include <ctime>

#include <fstream>





enum class Scenes {
	SCENE_MENU,
	SCENE_RAGNI,
	SCENE_DETLAS,
	SCENE_ALMUJ,

	SCENE_QUIT,
};


struct TXTopLayerTiles {
	const std::string TXWallSetPath = "src/Assets/Tiles/TXWallSet.png";
	//Wall tiles
	const sf::IntRect wall = { 32, 192, 128, 64 };
	const sf::IntRect cornerWall = { 384, 64, 64, 96 };
	const sf::IntRect leftWall = { 288, 31, 13, 96 };
	const sf::IntRect rightWall = {344, 31, 13, 96};
};

struct TXBaseLayerTiles {
	
	const std::string TXGrassSetPath = "src/Assets/Tiles/TXGrassSet.png";
	const std::string TXStoneGroundSetPath = "src/Assets/Tiles/TXStoneGroundSet.png";
	//Ground tiles
	const sf::IntRect grass = { 0, 0, 128, 128 };
	const sf::IntRect flower = { 128, 0, 128, 128 };
	const sf::IntRect stone_path = { 0, 128, 128, 128 };
	const sf::IntRect stone_path2 = { 128, 128, 128, 128 };
	const sf::IntRect stone_ground = {160, 0, 95, 95};

};



class SceneManager {

	Scenes m_currentScene = Scenes::SCENE_MENU;
	sf::RenderWindow* ctx;
	EntityManager* em;
	std::unique_ptr<Menu> menu = nullptr;
	std::vector<std::vector<int>> scenetl = {};
	std::vector<std::vector<int>> scenebl = {};

	std::unique_ptr<TXBaseLayerTiles> blTiles;
	std::unique_ptr<TXTopLayerTiles> tlTiles;

	void loadSceneData(const std::string& filename) {

		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Unable to open file: " << filename << std::endl;
			return;
		}

		std::string line;
		std::string b;
		std::string t;
		bool onB = false;
		bool onT = false;

		while (std::getline(file, line)) {
			if (line == "b") {
				onB = true;
				onT = false;
				continue;
			}

			if (line == "t") {
				onT = true;
				onB = false;
				continue;
			}

			if (onB) {
				b += line;
			}
			else {
				t += line;
			}
		}

	

		std::vector<int> row;
		for (size_t i = 0; i < b.length(); i++) {
			if (b[i] == 'e') {
				scenebl.push_back(row);
				row.clear();
			}
			else {
				row.push_back(b[i] - '0');
			}
		}


		for (size_t i = 0; i < t.length(); i++) {
			if (t[i] == 'e') {
				scenetl.push_back(row);
				row.clear();
			}
			else {
				row.push_back(t[i] - '0');
			}
		}

		
		file.close();
	}

	void clearPrevScene() {
		auto blTiles = em->GetEntities("blTiles");

		for (auto& blt : blTiles) {
			blt->DestroyEntity();
		}

		auto tiles = em->GetEntities("tlTiles");

		for (auto& t : tiles) {
			t->DestroyEntity();
		}

		scenetl.clear();
		scenebl.clear();
	}

	void initScene() {
		
		switch (m_currentScene) {
		case Scenes::SCENE_RAGNI: {
			loadSceneData("src/Data/Scenes/ragni.txt");
		}
			break;
		
		}
	};

	void loadBaseLayer() {
		for (size_t i = 0; i < scenebl.size(); i++) {
			for (size_t j = 0; j < scenebl[i].size(); j++) {
				switch (scenebl[j][i]) {
				case 0:
				{
					auto grassTile = em->AddEntity("blTiles");
					auto sc = grassTile->AddComponent<CSprite>(blTiles->TXGrassSetPath, blTiles->grass, 128, 128);
					sc->sprite.setPosition(i * 128, j * 128);
				}
				break;
				case 1:
				{
					auto flowerTile = em->AddEntity("blTiles");

					auto sc = flowerTile->AddComponent<CSprite>(blTiles->TXGrassSetPath, blTiles->flower, 128, 128);
					sc->sprite.setPosition(i * 128, j * 128);
				}
				break;
				case 2:
				{
					auto stoneTile = em->AddEntity("blTiles");
					auto sc = stoneTile->AddComponent<CSprite>(blTiles->TXGrassSetPath, blTiles->stone_path, 128, 128);
					sc->sprite.setPosition(i * 128, j * 128);

				}
				break;
				case 3:
				{
					auto stoneTile = em->AddEntity("blTiles");
					auto sc = stoneTile->AddComponent<CSprite>(blTiles->TXGrassSetPath, blTiles->stone_path2, 128, 128);
					sc->sprite.setPosition(i * 128, j * 128);
				}
				break;
				case 4:
				{
					auto stoneTile = em->AddEntity("blTiles");
					auto sc = stoneTile->AddComponent<CSprite>(blTiles->TXStoneGroundSetPath, blTiles->stone_ground, 128, 128);
					sc->sprite.setPosition(i * 128, j * 128);
				}
				break;
				}
			}
		}
	
	};

	void loadTopLayer() {
		for (size_t i = 0; i < scenetl.size(); i++) {
			for (size_t j = 0; j < scenetl[i].size(); j++) {
				switch (scenetl[j][i]) {
				
				case 1:
				{
					auto wallTile = em->AddEntity("tlTiles");
					auto sc = wallTile->AddComponent<CSprite>(tlTiles->TXWallSetPath, tlTiles->leftWall, 128, 128);
					sc->sprite.setPosition(i * 128, j * 128);
					wallTile->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
				}
				break;
				case 2:
				{
					auto wallTile = em->AddEntity("tlTiles");
					auto sc = wallTile->AddComponent<CSprite>(tlTiles->TXWallSetPath, tlTiles->rightWall, 128, 128);
					sc->sprite.setPosition((i * 128) + 50, j * 128);
					wallTile->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
				}
				break;

				case 4:
				{
					auto wallTile = em->AddEntity("tlTiles");
					auto sc = wallTile->AddComponent<CSprite>(tlTiles->TXWallSetPath, tlTiles->wall, 128, 128);
					sc->sprite.setPosition(i * 128, j * 128);
					wallTile->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
				}
				break;
				case 5:
				{
					auto cornerWall = em->AddEntity("tlTiles");
					auto sc = cornerWall->AddComponent<CSprite>(tlTiles->TXWallSetPath, tlTiles->cornerWall, 128, 128);
					sc->sprite.setPosition(i * 128, j * 128);
					cornerWall->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
				}
				break;

				default:
					break;
				}
			}
		}

	}

	void loadScene() {
		loadBaseLayer();
		loadTopLayer();
	};



public:
	SceneManager(Scenes startingScene, sf::RenderWindow* ctx, EntityManager* em)  {
		m_currentScene = startingScene;
		this->ctx = ctx;
		this->em = em;
		menu = std::make_unique<Menu>(em, ctx);
	
		blTiles = std::make_unique<TXBaseLayerTiles>();
		tlTiles = std::make_unique<TXTopLayerTiles>();
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
				menu->Clean();
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
			//render base layer
			auto blTiles = em->GetEntities("blTiles");
			for (auto& blt : blTiles) { //im hungry can u tell
				ctx->draw(blt->GetComponent<CSprite>()->sprite);
			}

			//render top layer
			auto tlTiles = em->GetEntities("tlTiles");
			
			for (auto& tlt : tlTiles) {
				ctx->draw(tlt->GetComponent<CSprite>()->sprite);
			}
			
		}

	}


	Scenes GetCurrentScene() const { return m_currentScene; };

	~SceneManager() {
		clearPrevScene();
	};
};