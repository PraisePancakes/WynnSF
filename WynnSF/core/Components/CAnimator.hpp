#pragma once
#include "../ECS.hpp"
#include <SFML/Graphics.hpp>



//TO DO incorporate state machine to play, stop, set, pause animations



class CAnimator : public Component {
public:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect srcRect;

	sf::Clock m_Clock;

	void scaleToN(sf::IntRect* rect, const int nx, const int ny) {
		const int MAX_DIM_X = nx;
		const int MAX_DIM_Y = ny;

		float w = rect->getSize().x;
		float h = rect->getSize().y;
		float wScale = 0;
		float hScale = 0;

		wScale = (MAX_DIM_X / w);
		hScale = (MAX_DIM_Y / h);


		float newWidth = 1 * wScale;
		float newHeight = 1 * hScale;

		sprite.setScale(newWidth, newHeight);

	}

	CAnimator(const std::string& texturePath, sf::IntRect srcRect, const int finalDimensionX, const int finalDimensionY) : Component(GenComponentTypeID<CAnimator>()) {
		if (!this->texture.loadFromFile(texturePath)) {
			std::cerr << "Error opening file at path : " << texturePath << std::endl;
		};
		sprite.setTexture(this->texture);
		sprite.setTextureRect(srcRect);

		scaleToN(&srcRect, finalDimensionX, finalDimensionY);
		std::cout << "Scale : " << sprite.getScale().x << " : " << sprite.getScale().y << std::endl;
		std::cout << "Sprite Dimensions : " << sprite.getGlobalBounds().width << " : " << sprite.getGlobalBounds().height << std::endl;


		sprite.setOrigin((float)(srcRect.left + srcRect.width / 2), (float)(srcRect.top + srcRect.height / 2));

	};


	void Play(float minFrame, float maxFrame, float fps) {
		if (m_Clock.getElapsedTime().asSeconds() > fps) {

			if (this->srcRect.left == maxFrame) {
				this->srcRect.left = minFrame;
			}
			else {
				this->srcRect.left += minFrame;
			}
			sprite.setTextureRect(srcRect);

			m_Clock.restart();
		}
	};

	void Set(sf::IntRect srcRect) {
		this->srcRect = srcRect;
	}


};