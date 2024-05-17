#pragma once
#include "../ECS.hpp"

class CShape : public Component {
public:
	sf::CircleShape shape;

	CShape(size_t vertices, float radius, sf::Color shapeOutline, sf::Color shapeFill) : Component(GenComponentTypeID<CShape>()) {
		shape.setPointCount(vertices);
		shape.setFillColor(shapeFill);
		shape.setOutlineColor(shapeOutline);
		shape.setRadius(radius);
		
	};


	~CShape() {};
};