#pragma once
#include "../ECS.hpp"

class CText : public Component {
public:
	sf::Text text;
	sf::Font font;
	CText(const std::string& text, const std::string& fontPath) : Component(GenComponentTypeID<CText>()) {
		if (!this->font.loadFromFile(fontPath)) {
			std::cout << "Error loading font at path : " << fontPath << std::endl;
		}

		this->text.setFont(font);
		this->text.setString(text);

	};


};