#pragma once
#include "../ECS.hpp"
#include <SFML/Graphics.hpp>

class TextComponent : public Component {
public:
	sf::Text Text;
	sf::Font Font;


	TextComponent(const std::string& fontPath, const std::string& text, int fontSize) : Component(GenComponentTypeID<TextComponent>()) {
		if (!Font.loadFromFile(fontPath)) {
			std::cout << "Failed to load font : " << fontPath << std::endl;
		}
		Text.setFont(Font);
		Text.setCharacterSize(fontSize);
		Text.setString(text);
		
	};


	void LogComponent() const override {
		std::string str = Text.getString();
		
		printf("\t\n\t\TextComponent: %s\n\t\tID : %d", str.c_str(), this->GetTypeID());
	};

};