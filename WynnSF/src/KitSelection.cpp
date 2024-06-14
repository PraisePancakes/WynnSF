#include "KitSelection.hpp"


	void KitSelection::_initKits() {
		CAnimator archerAnimator("", sf::IntRect(0, 0, 100, 100), 900, 100);
		CAnimator assassinAnimator("", sf::IntRect(0, 0, 200, 200), 600, 200);
		CAnimator warriorAnimator("", sf::IntRect(0, 0, 162, 162), 1458, 162);
		CAnimator wizardAnimator("", sf::IntRect(0, 0, 230, 190), 925, 230);

		archer = std::make_shared<Kit>("Archer", "src/Assets/Sprites/Player/Archer/Sprites/Character/", archerAnimator);
		assassin = std::make_shared<Kit>("Assassin", "src/Assets/Sprites/Player/Assassin/Sprites/Character/", assassinAnimator);
		warrior = std::make_shared<Kit>("Warrior", "src/Assets/Sprites/Player/Warrior/Sprites/Character/", warriorAnimator);
		wizard = std::make_shared<Kit>("Wizard", "src/Assets/Sprites/Player/Wizard/Sprites/Character/", wizardAnimator);

	}

	void KitSelection::_initKitSprites() {
		std::shared_ptr<Entity> archerKit = EntityManager::GetInstance()->AddEntity("KitSelection");
		std::shared_ptr<Entity> assassinKit = EntityManager::GetInstance()->AddEntity("KitSelection");
		std::shared_ptr<Entity> warriorKit = EntityManager::GetInstance()->AddEntity("KitSelection");
		std::shared_ptr<Entity> wizardKit = EntityManager::GetInstance()->AddEntity("KitSelection");


		auto archerAc = archerKit->AddComponent<CAnimator>("src/Assets/Sprites/Player/Archer/Sprites/Character/Idle.png", sf::IntRect(0, 0, 100, 100), 900, 100);
		auto assassinAc = assassinKit->AddComponent<CAnimator>("src/Assets/Sprites/Player/Assassin/Sprites/Character/Idle.png", sf::IntRect(0, 0, 200, 200), 600, 200);
		auto warriorAc = warriorKit->AddComponent<CAnimator>("src/Assets/Sprites/Player/Warrior/Sprites/Character/Idle.png", sf::IntRect(0, 0, 162, 162), 1458, 162);
		auto wizardAc = wizardKit->AddComponent<CAnimator>("src/Assets/Sprites/Player/Wizard/Sprites/Character/Idle.png", sf::IntRect(0, 0, 230, 190), 925, 230);

		archerAc->ScaleToN(256, 256);
		assassinAc->ScaleToN(356, 356);
		warriorAc->ScaleToN(356, 356);
		wizardAc->ScaleToN(256, 256);

		archerAc->sprite.setPosition((float)ctx->getSize().x / 2 + SPRITE_END, (float)ctx->getSize().y / 2);
		assassinAc->sprite.setPosition((float)ctx->getSize().x / 2 + SPRITE_END - 256, (float)ctx->getSize().y / 2);
		warriorAc->sprite.setPosition((float)ctx->getSize().x / 2 + SPRITE_END - (256 * 2), (float)ctx->getSize().y / 2);
		wizardAc->sprite.setPosition((float)ctx->getSize().x / 2 + SPRITE_END - (256 * 3), (float)ctx->getSize().y / 2);

		auto archerTxt = archerKit->AddComponent<CText>("Archer", "src/Assets/Fonts/PixelFont.ttf", 24, archerAc->sprite.getPosition().x, archerAc->sprite.getPosition().y - 100, true);
		auto assassinTxt = assassinKit->AddComponent<CText>("Assassin", "src/Assets/Fonts/PixelFont.ttf", 24, assassinAc->sprite.getPosition().x, assassinAc->sprite.getPosition().y - 100, true);
		auto warriorTxt = warriorKit->AddComponent<CText>("Warrior", "src/Assets/Fonts/PixelFont.ttf", 24, warriorAc->sprite.getPosition().x, warriorAc->sprite.getPosition().y - 100, true);
		auto wizardTxt = wizardKit->AddComponent<CText>("Wizard", "src/Assets/Fonts/PixelFont.ttf", 24, wizardAc->sprite.getPosition().x, wizardAc->sprite.getPosition().y - 100, true);
	}

	void KitSelection::_initKitButtons() {
		std::shared_ptr<Entity> archerKit = EntityManager::GetInstance()->GetEntities("KitSelection")[0];
		std::shared_ptr<Entity> assassinKit = EntityManager::GetInstance()->GetEntities("KitSelection")[1];
		std::shared_ptr<Entity> warriorKit = EntityManager::GetInstance()->GetEntities("KitSelection")[2];
		std::shared_ptr<Entity> wizardKit = EntityManager::GetInstance()->GetEntities("KitSelection")[3];

		auto archerAc = archerKit->GetComponent<CAnimator>();
		auto assassinAc = assassinKit->GetComponent<CAnimator>();
		auto warriorAc = warriorKit->GetComponent<CAnimator>();
		auto wizardAc = wizardKit->GetComponent<CAnimator>();

		// Button dimensions
		const sf::Vector2f buttonSize(256, 256);

		// Calculating the new positions to center the sprite inside the button
		const sf::Vector2f archerAcPos = archerAc->sprite.getPosition() - buttonSize / 2.f;
		const sf::Vector2f assassinAcPos = assassinAc->sprite.getPosition() - buttonSize / 2.f;
		const sf::Vector2f warriorAcPos = warriorAc->sprite.getPosition() - buttonSize / 2.f;
		const sf::Vector2f wizardAcPos = wizardAc->sprite.getPosition() - buttonSize / 2.f;

		// Creating the button shapes
		const sf::RectangleShape archerAcBtnShape(buttonSize);
		const sf::RectangleShape assassinAcBtnShape(buttonSize);
		const sf::RectangleShape warriorAcBtnShape(buttonSize);
		const sf::RectangleShape wizardAcBtnShape(buttonSize);

		// Adding the buttons to the kits
		archerKit->AddComponent<CButton>(archerAcBtnShape, archerAcPos, sf::Color::White, sf::Color::Transparent);
		assassinKit->AddComponent<CButton>(assassinAcBtnShape, assassinAcPos, sf::Color::White, sf::Color::Transparent);
		warriorKit->AddComponent<CButton>(warriorAcBtnShape, warriorAcPos, sf::Color::White, sf::Color::Transparent);
		wizardKit->AddComponent<CButton>(wizardAcBtnShape, wizardAcPos, sf::Color::White, sf::Color::Transparent);
	}

	KitSelection::KitSelection(sf::RenderWindow* ctx, Player* player, SceneManager* sceneManager) {
		this->ctx = ctx;
		this->player = player;
		this->sm = sceneManager;

		std::shared_ptr<Entity> title = EntityManager::GetInstance()->AddEntity("KitSelection-Title");
		auto titleText = title->AddComponent<CText>("Select A Kit", "src/Assets/Fonts/PixelFont.ttf", 72, (float)ctx->getSize().x / 2, 100, true);

		_initKits();
		_initKitSprites();
		_initKitButtons();


	};


	void KitSelection::HandleEvents() const {
		auto kits = EntityManager::GetInstance()->GetEntities("KitSelection");
		int kit_iterator = -1;
		bool selected = false;

		for (int i = 0; i < kits.size(); ++i) {
			auto& kit = kits[i];
			auto ac = kit->GetComponent<CAnimator>();
			auto btn = kit->GetComponent<CButton>();

			btn->OnHover(ctx, [btn]() {
				btn->buttonRect.setOutlineColor(sf::Color::Green);
				});

			btn->OnClick(ctx, [this, &selected, i, &kit_iterator]() {
				if (!selected) {
					selected = true;
					kit_iterator = i;
				}
				});
		}

		if (selected) {
			// set kit based on selectedKit
			switch (kit_iterator) {
			case 0:
				player->SetKit(archer);
				break;
			case 1:
				player->SetKit(assassin);
				break;
			case 2:
				player->SetKit(warrior);
				break;
			case 3:
				player->SetKit(wizard);
				break;
			default:
				break;
			}
			selected = false; // reset selection
			this->sm->SetScene(Scenes::SCENE_RAGNI);
		}



	};

	void KitSelection::Update() {
		auto kitSprites = EntityManager::GetInstance()->GetEntities("KitSelection");

		auto archer = kitSprites[0]->GetComponent<CAnimator>();;
		auto assassin = kitSprites[1]->GetComponent<CAnimator>();;
		auto warrior = kitSprites[2]->GetComponent<CAnimator>();;
		auto wizard = kitSprites[3]->GetComponent<CAnimator>();

		archer->Play(.2f);
		assassin->Play(.2f);
		warrior->Play(.2f);
		wizard->Play(.2f);

	};

	void KitSelection::Render()
	{
		auto kitSprites = EntityManager::GetInstance()->GetEntities("KitSelection");
		std::shared_ptr<Entity> title = EntityManager::GetInstance()->GetEntities("KitSelection-Title")[0];


		auto titleText = title->GetComponent<CText>();
		for (auto& kit : kitSprites) {
			auto ac = kit->GetComponent<CAnimator>();
			auto txt = kit->GetComponent<CText>();
			auto btn = kit->GetComponent<CButton>();
			ctx->draw(btn->buttonRect);
			ctx->draw(ac->sprite);
			ctx->draw(txt->text);
		}

		ctx->draw(titleText->text);
	};

	KitSelection::~KitSelection() {};
