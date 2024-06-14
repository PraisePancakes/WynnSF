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
	int frameWidth = 0;
	


	CAnimator(CAnimator& other) = default;
	CAnimator() {};
	CAnimator(const std::string& texturePath, sf::IntRect srcRect,  int maxFrame, int frameWidth)  {
		this->maxFrame = maxFrame;
		this->frameWidth = frameWidth;
	
		this->path = texturePath;
		if (!this->texture.loadFromFile(texturePath)) {
			std::cerr << "Error opening file at path : " << texturePath << std::endl;
		};
		sprite.setTexture(this->texture);
		sprite.setTextureRect(srcRect);
		
		
		this->srcRect = srcRect;

	
		
	};

	void Play(float dt) {
		if (m_Clock.getElapsedTime().asSeconds() > dt) {
			
			if (this->srcRect.left >= maxFrame) {
				this->srcRect.left = 0;
			}
			else {
				this->srcRect.left += frameWidth;
				
			}
			sprite.setTextureRect(srcRect);

			m_Clock.restart();
		}
		sprite.setOrigin((float)srcRect.width / 2, (float)srcRect.height / 2);
	
	};

	void ScaleToN( const int nx, const int ny) {
		const int MAX_DIM_X = nx;
		const int MAX_DIM_Y = ny;

		float w = (float)this->srcRect.getSize().x;
		float h = (float)this->srcRect.getSize().y;
		float wScale = 0;
		float hScale = 0;

		wScale = (MAX_DIM_X / w);
		hScale = (MAX_DIM_Y / h);


		float newWidth = 1 * wScale;
		float newHeight = 1 * hScale;

		sprite.setScale(newWidth, newHeight);

	}

	void Reset(const std::string& texturePath, sf::IntRect srcRect, int maxFrame, int frameWidth) {
		this->maxFrame = maxFrame;
		this->frameWidth = frameWidth;
		this->path = texturePath;
		if (!this->texture.loadFromFile(texturePath)) {
			std::cerr << "Error opening file at path : " << texturePath << std::endl;
		};
		sprite.setTexture(this->texture);
		sprite.setTextureRect(srcRect);

		

		

	};

	

	void Set(sf::IntRect srcRect) {
		this->srcRect = srcRect;
	}


};