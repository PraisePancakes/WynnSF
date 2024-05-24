#pragma once
#include "../ECS.hpp"
#include <SFML/Graphics.hpp>

class CText : public Component<CText> {
public:
	sf::Text text;
	sf::Font font;
	CText() {};
	CText(const std::string& str, const std::string& fontPath, int fontSize, float xPos, float yPos)  {
		if (!font.loadFromFile(fontPath)) {
			std::cout << "Error loading font at path : " << fontPath << std::endl;
		}

		this->text.setFont(font);
		this->text.setString(str);
		this->text.setCharacterSize(fontSize);
		
		this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
		this->text.setPosition(xPos, yPos);
		std::cout << "Text Size : " << text.getGlobalBounds().width << " x " << text.getGlobalBounds().height << std::endl;
		std::cout << "Text Pos : " << text.getPosition().x << " : " << text.getPosition().y << std::endl;
		std::cout << "Text Origin : " << text.getOrigin().x << " : " << text.getOrigin().y << std::endl;
	};


};