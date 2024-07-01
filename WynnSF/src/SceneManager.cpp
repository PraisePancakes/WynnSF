#include "SceneManager.hpp"
#include "../core/Utils/Utils.hpp"

static std::string getSceneName(Scenes id) {
	switch (id) {
	case Scenes::SCENE_RAGNI:
		return "Ragni";
	case Scenes::SCENE_DETLAS:
		return "Detlas";
	case Scenes::SCENE_PIGMANS:
		return "Pigmen's Ravines";
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
		case Scenes::SCENE_PIGMANS:
			return "src/Data/Scenes/pigmans.txt";
		case Scenes::SCENE_ALMUJ:
			return "";
		default:
			return "";
	
		}

	
	};

	void SceneManager::initTable() {
		for (Scenes scene = (Scenes)0; scene < Scenes::SCENE_QUIT; scene = static_cast<Scenes>((size_t)scene + 1)) {
			std::shared_ptr<Scene> s = std::make_shared<Scene>(scene, getSceneFilePath(scene));
			sceneTable.push_back(s);
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


	void SceneManager::updateTransitioningPlayer() {

		std::vector<Entrance> entranceV = this->sceneTable[(int)currentSceneToProcess]->GetEntranceVector();
		Core::Physics::Vec2D plPos = player->GetPos();

		for (size_t i = 0; i < entranceV.size(); i++) {

			if (plPos.x >= entranceV[i].pos.x && plPos.x <= entranceV[i].pos.x + entranceV[i].size.x) {
				if (plPos.y >= entranceV[i].pos.y && plPos.y <= entranceV[i].pos.y + entranceV[i].size.y) {
					switch (entranceV[i].side) {

					case Side::SIDE_LEFT:
					{
						auto scene = this->sceneTable[(int)currentSceneToProcess]->GetExternals()->left;
						SetScene(scene);
						auto entrances = this->sceneTable[(int)currentSceneToProcess]->GetEntranceVector();

						for (auto e : entrances) {
							if (e.side == Side::SIDE_RIGHT) {
								player->SetPos(e.pos.x - 200, e.pos.y);
							}
						}

					}

					break;
					case Side::SIDE_RIGHT:
					{
						auto scene = this->sceneTable[(int)currentSceneToProcess]->GetExternals()->right;
						SetScene(scene);

						auto entrances = this->sceneTable[(int)currentSceneToProcess]->GetEntranceVector();

						for (auto e : entrances) {
							if (e.side == Side::SIDE_LEFT) {
								player->SetPos(e.pos.x + 200, e.pos.y);
							}
						}

					}

					break;
					case Side::SIDE_TOP:
					{
						auto scene = this->sceneTable[(int)currentSceneToProcess]->GetExternals()->top;
						SetScene(scene);
						auto entrances = this->sceneTable[(int)currentSceneToProcess]->GetEntranceVector();

						for (auto e : entrances) {
							if (e.side == Side::SIDE_BOTTOM) {
								player->SetPos(e.pos.x, e.pos.y - 200);
							}
						}
					}

					break;
					case Side::SIDE_BOTTOM:
					{
						auto scene = this->sceneTable[(int)currentSceneToProcess]->GetExternals()->bottom;
						SetScene(scene);
						auto entrances = this->sceneTable[(int)currentSceneToProcess]->GetEntranceVector();

						for (auto e : entrances) {
							if (e.side == Side::SIDE_TOP) {
								player->SetPos(e.pos.x, e.pos.y + 200);
							}
						}
					}

					break;
					default:
						break;
					}

				}
			}
		}
	
	};

	void SceneManager::initTransition() {
		sf::View v = ctx->getView();
		sf::Vector2f size = { v.getSize().x , v.getSize().y  };
		this->transititionOverlay = std::make_shared<sf::RectangleShape>(size);
		transititionOverlay->setFillColor(sf::Color::Transparent);
		
	};

	void SceneManager::updateTransitioningPos() {
		sf::View v = ctx->getView();
		sf::Vector2f topLeft = { v.getCenter().x - (v.getSize().x / 2) , v.getCenter().y - (v.getSize().y / 2)};
		this->transititionOverlay->setPosition(topLeft);
	};

	void SceneManager::updateTransitioningAnimation() {

			sf::Color color = transititionOverlay->getFillColor();
			static bool flag = false;
			static int __iter_count = 0;
			
			if (!flag) {
				
				color.a++;
				__iter_count++;
				transititionOverlay->setFillColor(color);
				if (__iter_count >= 255) {
					flag = true;
				}
			}
			else if (flag) {
				color.a--;
				__iter_count--;
				transititionOverlay->setFillColor(color);
				if (__iter_count <= 0) {
					isTransitioning = false;
					flag = false;
				}
			}

		}

	

	void SceneManager::updateTransitioning() {
		if (isTransitioning) {
			player->Disable();
			updateTransitioningAnimation();
			updateTransitioningPos();
			
		}
		else {
			player->Enable();
		}
		updateTransitioningPlayer();
	}

	void SceneManager::Update() {
		if (currentSceneToProcess == Scenes::SCENE_MENU || currentSceneToProcess == Scenes::SCENE_KIT_SELECTION || currentSceneToProcess == Scenes::SCENE_QUIT) {
			return;
		}
		updateTransitioning();
		
		
		updateIntroduction();
	}

	 void SceneManager::updateIntroductionColor() {
		sf::Color currentColor = this->currentIntroText->text.getFillColor();
		currentColor.a -= .001;
		currentIntroText->text.setFillColor(currentColor);
	}

	void SceneManager::initIntroduction() {
		if (currentSceneToProcess == Scenes::SCENE_MENU || currentSceneToProcess == Scenes::SCENE_KIT_SELECTION || currentSceneToProcess == Scenes::SCENE_QUIT) {
			return;
		}

		currentIntroText = nullptr;
		sf::View view = ctx->getView();
		sf::Vector2f center(view.getCenter().x, view.getCenter().y);
		const std::string sceneName = getSceneName(currentSceneToProcess);
		this->currentIntroText = std::make_shared<CText>("Welcome to " + sceneName + "!", "src/Assets/Fonts/RingBearer.TTF", 72, 0, 0, true);
	
	}

	void SceneManager::updateIntroduction() {
		
			if (this->currentIntroText != nullptr) {
				updateIntroductionColor();
				updateIntroductionPos();
			}
		
		
	};

	void SceneManager::updateIntroductionPos() {
		sf::View view = ctx->getView();
		sf::Vector2f pos(view.getCenter().x, view.getCenter().y - 200);
		this->currentIntroText->text.setPosition(pos.x, pos.y);
		
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
			SetScene(Scenes::SCENE_PIGMANS);
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
		isTransitioning = true;
		initIntroduction();
		initTransition();
		//log welcome
	}

	void SceneManager::renderIntroduction() {		
		ctx->draw(this->currentIntroText->text);
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
			if (isTransitioning) {
				ctx->draw(*this->transititionOverlay);
			}
			
			renderIntroduction();
		}

	}

	std::shared_ptr<Scene> SceneManager::GetCurrentScene() const {
		return sceneTable[(int)currentSceneToProcess];
	}


	SceneManager::~SceneManager() {};