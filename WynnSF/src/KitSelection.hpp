#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../core/Manager/EntityManager.hpp"
#include "../core/Components/CAnimator.hpp"
#include "../core/Components/CButton.hpp"
#include "../core/Components/CText.hpp"
#include "Player.hpp"
#include "SceneManager.hpp"
#include "Kit.hpp"

constexpr float SPRITE_END = 360;




class KitSelection {
	sf::RenderWindow* ctx{ nullptr };
	
	Player* player;
	SceneManager* sm;

	bool idleInit = false;


	void _initKitSprites();

	void _initKitButtons();


public:
	KitSelection(sf::RenderWindow* ctx, Player* player, SceneManager* sceneManager);


	void HandleEvents() const;

	void Update();

	void Render();

	~KitSelection();
};