#include <iostream>
#include "Scene.hpp"
#include "Menu.hpp"
#include "GlobalChatManager.hpp"

//avoid making this manager a singleton, renderwindow doesnt handle well with static objects

class SceneManager {
	std::vector<std::shared_ptr<Scene>> sceneTable = {};
	Scenes currentSceneToProcess = Scenes::SCENE_MENU;
	sf::RenderWindow* ctx;
	std::unique_ptr<Menu> menu;

	std::string getSceneFilePath(Scenes id);
	void initTable();
	void handleMenuEvent();

public:
	SceneManager(sf::RenderWindow* ctx);

	void HandleEvents(sf::Event* e);
	void SetScene(Scenes scene);
	void RenderScene();

	std::shared_ptr<Scene> GetCurrentScene() const;
};