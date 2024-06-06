#include "GlobalChatBox.hpp"



int GlobalChatBox::max = 0;
int GlobalChatBox::min = 0;
int GlobalChatBox::currentSlide = 0;


GlobalChatBox::GlobalChatBox() {};



void GlobalChatBox::Log(const std::string& str) {
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
		log->AddComponent<CText>(str, "src/Assets/Fonts/PixelFont.ttf", 24, 0, 0);
		
		
		min = std::max(0, max - 5);
};

void GlobalChatBox::Update( sf::RenderWindow* ctx) {

		sf::Vector2f viewCenter = ctx->getView().getCenter();
		sf::Vector2f viewSize = ctx->getView().getSize();
		sf::Vector2f bottomLeft(viewCenter.x - (viewSize.x / 2), viewCenter.y + viewSize.y / 2);

		for (size_t i = min; i < max; i++) {
			std::shared_ptr<Entity> e = EntityManager::GetInstance()->GetEntities("ChatLog")[i];
			auto txt = e->GetComponent<CText>();
			txt->text.setPosition(bottomLeft.x + 100, (bottomLeft.y - 100)- ((i - min) * 30));

		}

};

void GlobalChatBox::Render( sf::RenderWindow* ctx) {

	for (size_t i = min; i < max; i++) {
		std::shared_ptr<Entity> e = EntityManager::GetInstance()->GetEntities("ChatLog")[i];
		auto txt = e->GetComponent<CText>();
		ctx->draw(txt->text);
		

	}


};

void GlobalChatBox::HandleScrollEvent(sf::Event* e) {

	auto logs = EntityManager::GetInstance()->GetEntities("ChatLog");
	if (logs.size() > 5) {
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
	

}