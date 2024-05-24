#pragma once
#include "../ECS.hpp"

class CShape : public Component<CShape> {
public:
	sf::CircleShape shape;
	CShape() {};
	CShape(size_t vertices, float radius, sf::Color shapeOutline, sf::Color shapeFill) {
		shape.setPointCount(vertices);
		shape.setFillColor(shapeFill);
		shape.setOutlineColor(shapeOutline);
		shape.setRadius(radius);
	};


	~CShape() {};
};