#pragma once
#include "../ECS.hpp"

class CShape : public Component {
public:
	sf::CircleShape shape;
	float xStep = 0;
	float yStep = 0;

	CShape(size_t vertices, float radius, sf::Color shapeOutline, sf::Color shapeFill, float xStep, float yStep) : Component(GenComponentTypeID<CShape>()) {
		shape.setPointCount(vertices);
		shape.setFillColor(shapeFill);
		shape.setOutlineColor(shapeOutline);
		shape.setRadius(radius);
		this->xStep = xStep;
		this->yStep = yStep;
		
	};


	~CShape() {};
};