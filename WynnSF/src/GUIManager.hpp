#pragma once
#include "GlobalChatManager.hpp"
#include "../core/Manager/EntityManager.hpp"
#include "../core/Components/CHealth.hpp"
#include "../core/Components/CTransform.hpp"
#include <vector>

class GUIManager {

	sf::RenderWindow* ctx{nullptr};
	sf::RectangleShape healthBarContainer;
	sf::RectangleShape healthBar;

	void _initHealthBarUI();


public:
	GUIManager(sf::RenderWindow* ctx);

	void updateHealthBarUI();

	void renderHealthBarUI();
	void renderChatUI() const;

	void updateChatUI() const;

	void Update();

	void Render();

	void HandleEvents(sf::Event* e);


	~GUIManager();
};