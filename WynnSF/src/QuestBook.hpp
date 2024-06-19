#pragma once
#include "Quest.hpp"
#include "../core/Manager/EntityManager.hpp"

constexpr float SPRITE_BOOK_PADDING = 10;

class QuestBook {
	QuestDB* db{ nullptr };
	bool _opened = false;
	sf::RenderWindow* ctx{ nullptr };


public:

	QuestBook(QuestDB* db, sf::RenderWindow* ctx) {
		this->db = db;
		this->ctx = ctx;
		std::shared_ptr<Entity> book = EntityManager::GetInstance()->AddEntity("QuestBook");
		book->AddComponent<CSprite>("src/Assets/UI/UI_QuestBook.png", sf::IntRect(0, 0, 128, 117), 64, 64);
		book->AddComponent<CButton>(sf::RectangleShape(sf::Vector2f(64, 64)), sf::Vector2f(SPRITE_BOOK_PADDING, SPRITE_BOOK_PADDING), sf::Color::Transparent, sf::Color::Transparent);
	};

	bool IsOpen() const {
		return _opened;
	}
	
	void HandleEvents() {
		std::shared_ptr<Entity> book = EntityManager::GetInstance()->GetEntities("QuestBook")[0];
		auto btn = book->GetComponent<CButton>();
		

		btn->OnClick(ctx, [this]() {
			this->_opened = true;

		});
		

	}

	void Update() {
		sf::View view = ctx->getView();
		std::shared_ptr<Entity> book = EntityManager::GetInstance()->GetEntities("QuestBook")[0];
		
		auto sc = book->GetComponent<CSprite>();
		
		const sf::Vector2f center = view.getCenter();
		const sf::Vector2f topLeft((center.x - (view.getSize().x / 2)) + SPRITE_BOOK_PADDING, (center.y - (view.getSize().y / 2)) + SPRITE_BOOK_PADDING);
		const sf::Vector2f bookSpriteOffset(32, 32);
		
		sc->sprite.setPosition(topLeft.x + bookSpriteOffset.x, topLeft.y + bookSpriteOffset.y);
		
		//update the books sprite positioning to be top left of the view at all times unless opened



	}

	void Render() {
		std::shared_ptr<Entity> book = EntityManager::GetInstance()->GetEntities("QuestBook")[0];
		auto sc = book->GetComponent<CSprite>();

		if (_opened) {
			//render book open relative to view
		}
		else {
			//render book sprite relative to view
			ctx->draw(sc->sprite);

		}
		
	};

	~QuestBook() {};

};