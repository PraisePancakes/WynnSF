#pragma once
#include "../ECS.hpp"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <cmath>
//picked up by SRenderer to render all sprites to window context call to texture.update(window) sprite.setPosition(entityPos) 

class SpriteComponent : public Component {
public:
	sf::Texture texture;
	sf::Sprite sprite;

	float originalXpos;
	float originalYpos;

	SpriteComponent(const std::string& imgFilePath, float xScale, float yScale, float xPos, float yPos) : Component(GenComponentTypeID<SpriteComponent>()) {
		SetSprite(imgFilePath, xScale, yScale, xPos, yPos);
		originalXpos = xPos;
		originalYpos = yPos;
	};

	void SetSprite(const std::string& imgFilePath, float xScale, float  yScale, float xPos, float yPos) {
		if (!texture.loadFromFile(imgFilePath)) {
			std::string err = "Failed to load texture : " + (std::string)imgFilePath;
			std::cout << err;
		};
	

		sprite.setTexture(this->texture);
		sprite.setScale(xScale, yScale);
		sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);

		sprite.setPosition(xPos, yPos);
		
	
	}


	void LogComponent() const override {
		printf("\t\n\t\tSpriteComponent:");
	};

};