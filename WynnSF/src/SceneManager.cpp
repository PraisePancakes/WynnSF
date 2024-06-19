#include "SceneManager.hpp"
#include "../core/Utils/Utils.hpp"

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

	

	SceneManager::SceneManager(sf::RenderWindow* ctx, Player* player) {
		this->ctx = ctx;
		this->player = player;
		this->m_KitSelection = std::make_unique<KitSelection>(ctx);
		menu = std::make_unique<Menu>(ctx);
		initTable();
		
	};

	void SceneManager::handleKitSelectionEvent() {
		int type = m_KitSelection->HandleEvents();

		switch (type) {
		case 0:

			player->SetKit(KitTypes::KIT_ARCHER);
			SetScene(Scenes::SCENE_RAGNI);
			break;
		case 1:
			player->SetKit(KitTypes::KIT_ASSASSIN);
			SetScene(Scenes::SCENE_RAGNI);
			break;
		case 2:
			player->SetKit(KitTypes::KIT_WARRIOR);
			SetScene(Scenes::SCENE_RAGNI);
			break;
		case 3:
			player->SetKit(KitTypes::KIT_WIZARD);
			SetScene(Scenes::SCENE_RAGNI);
			break;
		default:

			break;
		}
	}


	void SceneManager::HandleEvents(sf::Event* e) {
		if (currentSceneToProcess == Scenes::SCENE_MENU) {
			handleMenuEvent();
		}
		else if(currentSceneToProcess == Scenes::SCENE_KIT_SELECTION) {
			//handle scene events if there are any
			handleKitSelectionEvent();

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
			m_KitSelection->Render();
		}
		else {
			sceneTable[(int)currentSceneToProcess]->RenderScene(ctx);
		}

	}

	std::shared_ptr<Scene> SceneManager::GetCurrentScene() const {
		return sceneTable[(int)currentSceneToProcess];
	}


	SceneManager::~SceneManager() {};