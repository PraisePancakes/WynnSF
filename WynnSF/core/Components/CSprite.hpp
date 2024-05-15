#pragma once
#include "../ECS.hpp"


//static sprite use only, dynamic sprites (animators) used by CAnimator component
class CSprite : public Component {



public:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect srcRect;

	CSprite(const std::string& spritePath, sf::IntRect srcRect, const int finalDimensionX, const int finalDimensionY) : Component(GenComponentTypeID<CSprite>()) {

		if (!this->texture.loadFromFile(spritePath)) {
			std::cerr << "Error opening file at path : " << spritePath << std::endl;
		};

		sprite.setTexture(this->texture);
		sprite.setTextureRect(srcRect);
		this->srcRect = srcRect;
		ScaleToN(&srcRect, finalDimensionX, finalDimensionY);


		sprite.setOrigin((float)(srcRect.left + srcRect.width / 2), (float)(srcRect.top + srcRect.height / 2));
		std::cout << sprite.getScale().x << " : " << sprite.getScale().y << std::endl;
	};


	void ScaleToN(sf::IntRect* rect, const int nx, const int ny) {
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

	~CSprite() = default;
};