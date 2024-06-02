#include "GlobalChatLogger.hpp"
#include "../core/Components/CText.hpp"

	std::queue<std::string> GlobalChatLogger::chatq = {};

	bool GlobalChatLogger::updateFlag = false;
	std::queue<std::string> GlobalChatLogger::copyq = {};

	void GlobalChatLogger::Log(const std::string& message) {
		
		if (chatq.size() >= MAX_Q_ELEMS) {
			chatq.pop();
		}
		updateFlag = false;
		chatq.push(message);
	
	};

	void GlobalChatLogger::Display(sf::RenderWindow* ctx, EntityManager* em) {
		
		std::queue<std::string> copyq = chatq;
		
		
		for (size_t i = 0; i < em->GetEntities("LogItem").size(); i++) {
			auto e = em->GetEntities("LogItem")[i];
			ctx->draw(e->GetComponent<CText>()->text);
		}
	
		
		updateFlag = true;
	};

	void GlobalChatLogger::Update(EntityManager* em) {
		if (!updateFlag) {
			copyq = chatq;
			static int heightModifier = 0;
			while (!copyq.empty()) {
				heightModifier += 25;
				std::cout << heightModifier;
				auto e = em->AddEntity("LogItem");
				auto logItem = e->AddComponent<CText>(copyq.front(), "src/Assets/Fonts/PixelFont.ttf", 24, MAX_LOG_W / 2, (MAX_LOG_H / 2) + heightModifier);
				copyq.pop();

			}
		}
		updateFlag = true;
		
	};

	GlobalChatLogger::~GlobalChatLogger() {};
