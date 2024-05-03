#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:

	sf::View m_View;
	
	Camera(float w, float h, float centerX, float centerY) {
		m_View.setSize(w, h);
		m_View.setCenter(centerX, centerY);
	};

	sf::View GetView() const { return m_View; };


	void Update(float offsetX, float offsetY) {
		m_View.move(offsetX, offsetY);
	};

	sf::Vector2f GetCenter() const {
		return m_View.getCenter();
	};


};