#pragma once
#include "../ECS.hpp"
#include <SFML/Graphics.hpp>



//TO DO implement minframe and maxframe members that can be modified based on different sprite sheet paths



class CAnimator : public Component<CAnimator> {
public:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect srcRect;
	std::string path;
	sf::Clock m_Clock;
	
	int maxFrame = 0;
	int minFrame = 0;
	int frameWidth = 0;


	void scaleToN(sf::IntRect* rect, const int nx, const int ny) {
		const int MAX_DIM_X = nx;
		const int MAX_DIM_Y = ny;

		float w = (float)rect->getSize().x;
		float h = (float)rect->getSize().y;
		float wScale = 0;
		float hScale = 0;

		wScale = (MAX_DIM_X / w);
		hScale = (MAX_DIM_Y / h);


		float newWidth = 1 * wScale;
		float newHeight = 1 * hScale;

		sprite.setScale(newWidth, newHeight);

	}

	CAnimator() {};
	CAnimator(const std::string& texturePath, sf::IntRect srcRect, const int finalDimensionX, const int finalDimensionY, int minFrame, int maxFrame, int frameWidth)  {
		this->maxFrame = maxFrame;
		this->minFrame = minFrame;
		this->frameWidth = frameWidth;

		this->path = texturePath;
		if (!this->texture.loadFromFile(texturePath)) {
			std::cerr << "Error opening file at path : " << texturePath << std::endl;
		};
		sprite.setTexture(this->texture);
		sprite.setTextureRect(srcRect);
		
		scaleToN(&srcRect, finalDimensionX, finalDimensionY);
		this->srcRect = srcRect;

		sprite.setOrigin((float)(srcRect.left + srcRect.width / 2), (float)(srcRect.top + srcRect.height / 2));
		
	};


	void SetTexturePath(const std::string& path) {
		this->texture.loadFromFile(path);
	}


	void Play(float dt) {
		

	
		if (m_Clock.getElapsedTime().asSeconds() > dt) {
			
			if (this->srcRect.left >= maxFrame) {
				this->srcRect.left = minFrame;
			}
			else {
				this->srcRect.left += frameWidth;
				
			}
			sprite.setTextureRect(srcRect);

			m_Clock.restart();
		}

	
	};

	void Reset(const std::string& texturePath, sf::IntRect srcRect, const int finalDimensionX, const int finalDimensionY,  int minFrame, int maxFrame, int frameWidth) {
		this->maxFrame = maxFrame;
		this->minFrame = minFrame;
		this->frameWidth = frameWidth;

		this->path = texturePath;
		if (!this->texture.loadFromFile(texturePath)) {
			std::cerr << "Error opening file at path : " << texturePath << std::endl;
		};
		sprite.setTexture(this->texture);
		sprite.setTextureRect(srcRect);

		scaleToN(&srcRect, finalDimensionX, finalDimensionY);


		sprite.setOrigin((float)(srcRect.left + srcRect.width / 2), (float)(srcRect.top + srcRect.height / 2));

	};

	void Set(sf::IntRect srcRect) {
		this->srcRect = srcRect;
	}


};