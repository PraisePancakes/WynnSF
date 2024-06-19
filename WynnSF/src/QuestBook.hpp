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
		std::shared_ptr<Entity> close = EntityManager::GetInstance()->AddEntity("QuestBook-Close");
		close->AddComponent<CSprite>("src/Assets/UI/UI_Back.png", sf::IntRect(0, 0, 100, 100), 64, 64);
		close->AddComponent<CButton>(sf::RectangleShape(sf::Vector2f(64, 64)), sf::Vector2f(SPRITE_BOOK_PADDING, SPRITE_BOOK_PADDING), sf::Color::Transparent, sf::Color::Transparent);
	};

	bool IsOpen() const {
		return _opened;
	}
	
	void HandleEvents() {
		std::shared_ptr<Entity> book = EntityManager::GetInstance()->GetEntities("QuestBook")[0];
		std::shared_ptr<Entity> close = EntityManager::GetInstance()->GetEntities("QuestBook-Close")[0];

		auto openBtn = book->GetComponent<CButton>();
		auto closeBtn = close->GetComponent<CButton>();

		if (!_opened) {
			openBtn->OnClick(ctx, [this]() {
				this->_opened = true;
				});
		}
		else {
			closeBtn->OnClick(ctx, [this]() {
			
				this->_opened = false;
				});
		}
		

		
		

	}

	void _updateQuestBookClosed() {
		sf::View view = ctx->getView();
		std::shared_ptr<Entity> book = EntityManager::GetInstance()->GetEntities("QuestBook")[0];

		auto sc = book->GetComponent<CSprite>();

		const sf::Vector2f center = view.getCenter();
		const sf::Vector2f topLeft((center.x - (view.getSize().x / 2)) + SPRITE_BOOK_PADDING, (center.y - (view.getSize().y / 2)) + SPRITE_BOOK_PADDING);
		const sf::Vector2f bookSpriteOffset(32, 32);

		sc->sprite.setPosition(topLeft.x + bookSpriteOffset.x, topLeft.y + bookSpriteOffset.y);
	}

	void _updateQuestBookBack() {
		sf::View view = ctx->getView();
		std::shared_ptr<Entity> close = EntityManager::GetInstance()->GetEntities("QuestBook-Close")[0];

		auto sc = close->GetComponent<CSprite>();

		const sf::Vector2f center = view.getCenter();
		const sf::Vector2f topLeft((center.x - (view.getSize().x / 2)) + SPRITE_BOOK_PADDING, (center.y - (view.getSize().y / 2)) + SPRITE_BOOK_PADDING);
		const sf::Vector2f bookSpriteOffset(32, 32);

		sc->sprite.setPosition(topLeft.x + bookSpriteOffset.x, topLeft.y + bookSpriteOffset.y);
	}

	void _updateQuestBookOpened() {
		_updateQuestBookBack();
	}

	void Update() {
		
		if (_opened) {
			_updateQuestBookOpened();
		}
		else {
			_updateQuestBookClosed();
		}
		
		//update the books sprite positioning to be top left of the view at all times unless opened



	}

	void Render() {
		std::shared_ptr<Entity> book = EntityManager::GetInstance()->GetEntities("QuestBook")[0];
		std::shared_ptr<Entity> close = EntityManager::GetInstance()->GetEntities("QuestBook-Close")[0];
		auto bookSc = book->GetComponent<CSprite>();
		auto closeSc = close->GetComponent<CSprite>();
		
		if (_opened) {
			//render book open relative to view

			ctx->draw(closeSc->sprite);
		}
		else {
			//render book sprite relative to view
			ctx->draw(bookSc->sprite);

		}
		
	};

	~QuestBook() {};

};