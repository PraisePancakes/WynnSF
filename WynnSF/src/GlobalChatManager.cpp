#include "GlobalChatManager.hpp"




std::mutex GlobalChatManager::mut;
GlobalChatManager* GlobalChatManager::pinstance{ nullptr };


GlobalChatManager::GlobalChatManager() {
	chatBox.setSize(sf::Vector2f(500, 150));
	
	sf::Color fill(0, 0, 0, 100);
	chatBox.setOutlineColor(sf::Color::Black);
	chatBox.setOutlineThickness(2);

	chatBox.setFillColor(fill);

	chatScroller.setPointCount(10);
	chatScroller.setRadius(4);
	chatScroller.setFillColor(sf::Color::Red);
	chatScroller.setOutlineColor(sf::Color::White);
	chatScroller.setOutlineThickness(2);

};


GlobalChatManager& GlobalChatManager::GetInstance() {
	
	std::lock_guard<std::mutex> lock(mut);

	if (pinstance == nullptr) {
		pinstance = new GlobalChatManager();

	}
	return *pinstance;

};


void GlobalChatManager::Log(const std::string& str) {
		//push front

		auto logs = EntityManager::GetInstance()->GetEntities("ChatLog");
		if (logs.size() >= CHAT_LOG_MAX_SIZE) {
			std::shared_ptr<Entity> e = EntityManager::GetInstance()->GetEntities("ChatLog")[0];
			e->DestroyEntity();
			max = max;
		}
		else {
			max++;
		}
		std::shared_ptr<Entity> log = EntityManager::GetInstance()->AddEntity("ChatLog");
		log->AddComponent<CText>(str, "src/Assets/Fonts/PixelFont.ttf", 24, 0, 0, false);
		
		
		min = std::max(0, max - 5);
};

void GlobalChatManager::Update( sf::RenderWindow* ctx) {

		sf::Vector2f viewCenter = ctx->getView().getCenter();
		sf::Vector2f viewSize = ctx->getView().getSize();
		sf::Vector2f bottomLeft(viewCenter.x - (viewSize.x / 2), viewCenter.y + viewSize.y / 2);
		chatBox.setPosition(bottomLeft.x, bottomLeft.y - 150);
		chatScroller.setPosition(chatBox.getPosition().x + 495, (bottomLeft.y) - (min * 50));

		if (max > 0) {
			for (size_t i = min; i < max; i++) {
				std::shared_ptr<Entity> e = EntityManager::GetInstance()->GetEntities("ChatLog")[i];
				auto txt = e->GetComponent<CText>();
				txt->text.setPosition(bottomLeft.x + 50, (bottomLeft.y - 35) - ((i - min) * 30));
				
			}

		}
		
};

void GlobalChatManager::Render( sf::RenderWindow* ctx) {

	ctx->draw(chatBox);
	ctx->draw(chatScroller);
	for (size_t i = min; i < max; i++) {
		std::shared_ptr<Entity> e = EntityManager::GetInstance()->GetEntities("ChatLog")[i];
		auto txt = e->GetComponent<CText>();
		ctx->draw(txt->text);
		

	}


};

void GlobalChatManager::HandleScrollEvent(sf::Event* e, sf::RenderWindow* ctx) {

	auto logs = EntityManager::GetInstance()->GetEntities("ChatLog");
	if (logs.size() > 5) {
		sf::Vector2i mousepixelpos = sf::Mouse::getPosition(*ctx);
		sf::Vector2f mouseworldpos = ctx->mapPixelToCoords(mousepixelpos);
		
		if (chatBox.getGlobalBounds().contains(mouseworldpos)) {
			
			if (e->type == sf::Event::MouseWheelScrolled) {
				if (e->mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
					//hande sliding 
					if (e->mouseWheelScroll.delta > 0) {
						//slide right
						if (max >= logs.size()) {
							max = max;
							min = min;
						}
						else {
							max++;
							min++;
						}

					}
					else if (e->mouseWheelScroll.delta < 0) {
						//slide left
						if (min <= 0) {
							max = max;
							min = min;
						}
						else {
							min--;
							max--;
						}


					}



				}

			}
		}
		
		//handle drag scroll

			
		
	}

}


GlobalChatManager::~GlobalChatManager() {};