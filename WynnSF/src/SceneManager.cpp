#include "SceneManager.hpp"


std::string SceneManager::getSceneFilePath(Scenes id) {
		std::string path = "";
		switch (id) {
		case Scenes::SCENE_MENU:
			break;
		case Scenes::SCENE_KIT_SELECTION:
			break;
		case Scenes::SCENE_RAGNI:
			path = "src/Data/Scenes/ragni.txt";
			GUI::GlobalChatManager::GetInstance().Log("Testing");
			GUI::GlobalChatManager::GetInstance().Log("Testing1");
			GUI::GlobalChatManager::GetInstance().Log("Testing2");
			GUI::GlobalChatManager::GetInstance().Log("Testing3");
			GUI::GlobalChatManager::GetInstance().Log("Testing4");
			GUI::GlobalChatManager::GetInstance().Log("Testing5");
			GUI::GlobalChatManager::GetInstance().Log("Testing6");
			GUI::GlobalChatManager::GetInstance().Log("Testing7");
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

	void SceneManager::initTable() {
		for (Scenes scene = (Scenes)0; scene < Scenes::SCENE_QUIT; scene = static_cast<Scenes>((size_t)scene + 1)) {
			std::shared_ptr<Scene> item = std::make_shared<Scene>(scene, getSceneFilePath(scene));
			sceneTable.push_back(item);
		}
	};

	void SceneManager::handleMenuEvent() {
		if (currentSceneToProcess == Scenes::SCENE_MENU) {
			int event = menu->GetMenuEvents();
			switch (event) {
			case 1:
				currentSceneToProcess = Scenes::SCENE_KIT_SELECTION;
				break;
			case 2:
				currentSceneToProcess = Scenes::SCENE_QUIT;
				break;


			}

		}
	}

	

	SceneManager::SceneManager(sf::RenderWindow* ctx) {
		menu = std::make_unique<Menu>(ctx);
		initTable();
		this->ctx = ctx;
	};


	void SceneManager::HandleEvents(sf::Event* e) {
		if (currentSceneToProcess == Scenes::SCENE_MENU) {
			handleMenuEvent();
		}
		else {
			//handle scene events if there are any
		}
	};

	void SceneManager::SetScene(Scenes scene) {
		this->currentSceneToProcess = scene;
		//log welcome
	}

	void SceneManager::RenderScene() {
		if (this->currentSceneToProcess == Scenes::SCENE_MENU) {
			menu->Render();
			return;
		}
		else if (this->currentSceneToProcess == Scenes::SCENE_KIT_SELECTION) {
			//render kit selection scene
			return;
		}
	

		sceneTable[(int)currentSceneToProcess]->RenderScene(ctx);


	}

	std::shared_ptr<Scene> SceneManager::GetCurrentScene() const {
		return sceneTable[(int)currentSceneToProcess];
	}


	SceneManager::~SceneManager() {};