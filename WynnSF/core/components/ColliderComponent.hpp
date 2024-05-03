#pragma once
#include "../ECS.hpp"
#include <stdio.h>


class ColliderComponent : public Component {
public:
	float radius = 0.0f;

	ColliderComponent(float r) : Component(GenComponentTypeID<ColliderComponent>()), radius(r) {};
	ColliderComponent() : Component(GenComponentTypeID<ColliderComponent>()) {};

	void LogComponent() const override {
		printf("\t\n\t\ColliderComponent :\n\t\t{\n\t\t\tradius : %f\n\t\t},\n\n", radius);
	};

	~ColliderComponent() override {};
};
