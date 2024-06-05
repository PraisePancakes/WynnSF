#pragma once
#include "../core/Manager/EntityManager.hpp"
#include "../core/Physics/Vec2D.hpp"
#include <SFML/Graphics.hpp>

#define PARTICLE_COUNT 50
#define PARTICLE_SPEED 3
#define PARTICLE_VERTICES 4
#define PARTICLE_RADIUS 5

class Menu {
	
	sf::RenderWindow* ctx;

	Core::Physics::Vec2D getRandomParticlePos(sf::RenderWindow* ctx);


	void renderMenuText();

	void renderMenuParticles();
	

	void initMenuParticles();

	void initMenu();
	void renderLogo();
	

	void renderMenuButtons();



public:
	Menu( sf::RenderWindow* ctx);
	int GetMenuEvents() const;
	void Clean();
	void Render();

	~Menu();

};