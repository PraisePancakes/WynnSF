#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../core/Manager/EntityManager.hpp"
#include "../core/Components/CAnimator.hpp"
#include "../core/Components/CButton.hpp"
#include "../core/Components/CText.hpp"
#include "Kit.hpp"

constexpr float SPRITE_END = 360;

class KitSelection {
	sf::RenderWindow* ctx{ nullptr };


	bool idleInit = false;
	void _initKitSelectionSprites();
	void _initKitSelectionButtons();


public:
	KitSelection(sf::RenderWindow* ctx);

	int HandleEvents() const;
	void Render();

	~KitSelection();
};