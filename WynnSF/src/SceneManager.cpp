#include "SceneManager.hpp"
#include "../core/Utils/Utils.hpp"

static std::string getSceneName(Scenes id) {
	switch (id) {
	case Scenes::SCENE_RAGNI:
		return "Ragni";
	case Scenes::SCENE_DETLAS:
		return "Detlas";
	case Scenes::SCENE_ALMUJ:
		return "Almuj";
	default: return "";
	}
};

std::string SceneManager::getSceneFilePath(Scenes id) {
		
		switch (id) {
		case Scenes::SCENE_RAGNI:
			return "src/Data/Scenes/ragni.txt";
			
		case Scenes::SCENE_DETLAS:
			return "";
		case Scenes::SCENE_ALMUJ:
			return "";
		default:
			return "";
	
		}

	
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

	void SceneManager::Update() {
		if (currentSceneToProcess == Scenes::SCENE_MENU || currentSceneToProcess == Scenes::SCENE_KIT_SELECTION || currentSceneToProcess == Scenes::SCENE_QUIT) {
			return;
		}

		updateIntroduction();
	}

	static void updateIntroductionColor() {
		std::shared_ptr<Entity> sceneIntroE = EntityManager::GetInstance()->GetEntities("Scene-Introduction")[0];
		std::shared_ptr<CText> textC = sceneIntroE->GetComponent<CText>();

		
		static sf::Color currentColor = textC->text.getFillColor();
		currentColor.a -= .001;

		if (currentColor.a <= 0) {
			sceneIntroE->DestroyEntity();

		}

		textC->text.setFillColor(currentColor);
	}

	void SceneManager::initIntroduction() {
		if (currentSceneToProcess == Scenes::SCENE_MENU || currentSceneToProcess == Scenes::SCENE_KIT_SELECTION || currentSceneToProcess == Scenes::SCENE_QUIT) {
			return;
		}

		sf::View view = ctx->getView();
		sf::Vector2f center(view.getCenter().x, view.getCenter().y);
		const std::string sceneName = getSceneName(currentSceneToProcess);
		std::shared_ptr<Entity> sceneIntroE = EntityManager::GetInstance()->AddEntity("Scene-Introduction");
		std::shared_ptr<CText> textC = sceneIntroE->AddComponent<CText>("Welcome to " + sceneName + "!", "src/Assets/Fonts/RingBearer.TTF", 72, 0, 0, true);
		
		
		
	}

	void SceneManager::updateIntroduction() {
		EntityVec vec = EntityManager::GetInstance()->GetEntities("Scene-Introduction");
		if (vec.size() > 0) {
			updateIntroductionColor();
			updateIntroductionPos();
		}
	};

	void SceneManager::updateIntroductionPos() {
		sf::View view = ctx->getView();
		sf::Vector2f pos(view.getCenter().x, view.getCenter().y - 200);
		std::shared_ptr<Entity> sceneIntroE = EntityManager::GetInstance()->GetEntities("Scene-Introduction")[0];
		std::shared_ptr<CText> textC = sceneIntroE->GetComponent<CText>();

		textC->text.setPosition(pos.x, pos.y);
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
		initIntroduction();
		//log welcome
	}

	void SceneManager::renderIntroduction() {
		EntityVec vec = EntityManager::GetInstance()->GetEntities("Scene-Introduction");
		if (vec.size() > 0) {
			std::shared_ptr<Entity> introEntity = EntityManager::GetInstance()->GetEntities("Scene-Introduction")[0];
			if (introEntity) {
				auto txtC = introEntity->GetComponent<CText>();
				ctx->draw(txtC->text);
			}
		}
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
			renderIntroduction();
		}

	}

	std::shared_ptr<Scene> SceneManager::GetCurrentScene() const {
		return sceneTable[(int)currentSceneToProcess];
	}


	SceneManager::~SceneManager() {};