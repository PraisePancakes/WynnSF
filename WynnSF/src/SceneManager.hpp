#include <iostream>
#include "Scene.hpp"
#include "Menu.hpp"
#include "GlobalChatBox.hpp"

class SceneManager {
	std::vector<std::shared_ptr<Scene>> sceneTable = {};
	Scenes currentSceneToProcess = Scenes::SCENE_MENU;
	sf::RenderWindow* ctx;
	std::unique_ptr<Menu> menu;

	std::string getSceneFilePath(Scenes id) {
		std::string path = "";
		switch (id) {
		case Scenes::SCENE_MENU:
			break;
		case Scenes::SCENE_RAGNI:
			path = "src/Data/Scenes/ragni.txt";
		
			break;
		case Scenes::SCENE_DETLAS:
			break;
		case Scenes::SCENE_ALMUJ:
			break;
		case Scenes::SCENE_QUIT:
			break;
		}

		return path;
	};

	void initTable() {
		for (Scenes scene = (Scenes)0; scene < Scenes::SCENE_QUIT; scene = static_cast<Scenes>((size_t)scene + 1)) {
			std::shared_ptr<Scene> item = std::make_shared<Scene>(scene, getSceneFilePath(scene));
			sceneTable.push_back(item);
		}
	};

	void handleMenuEvent() {
		if (currentSceneToProcess == Scenes::SCENE_MENU) {
			int event = menu->GetMenuEvents();
			switch (event) {
			case 1:
				currentSceneToProcess = Scenes::SCENE_RAGNI;
			break;
			case 2:
				currentSceneToProcess = Scenes::SCENE_QUIT;
				break;
	
				
			}

		}
	}
public:
	SceneManager(sf::RenderWindow* ctx) {
		menu = std::make_unique<Menu>(ctx);
		initTable();
		this->ctx = ctx;
	};


	void HandleEvents(sf::Event* e) {
		if (currentSceneToProcess == Scenes::SCENE_MENU) {
			handleMenuEvent();
		}
		else {
			//handle scene events if there are any
		}
	};

	void SetScene(Scenes scene) {
		this->currentSceneToProcess = scene;
		//log welcome
	}

	void RenderScene() {
		if (this->currentSceneToProcess == Scenes::SCENE_MENU) {
			menu->Render();
			return;
		}
		
		sceneTable[(int)currentSceneToProcess]->RenderScene(ctx);
		
		
	}

	std::shared_ptr<Scene> GetCurrentScene() const {
		return sceneTable[(int)currentSceneToProcess];
	}
};