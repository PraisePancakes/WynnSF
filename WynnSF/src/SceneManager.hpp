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

	void loadSceneData(const std::string& filename);
	void clearPrevScene();
	void loadBaseLayer();
	void loadTopLayer();
	void loadScene();
	void initScene();


public:
	SceneManager(Scenes startingScene, sf::RenderWindow* ctx, EntityManager* em);

	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;

	void SetScene(Scenes scene);
	void Update();

	void RenderScene();

	inline Scenes GetCurrentScene() const { return m_currentScene; };
	~SceneManager();
};