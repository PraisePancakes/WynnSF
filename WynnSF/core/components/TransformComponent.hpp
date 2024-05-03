#pragma once
#include "../ECS.hpp"
#include "../physics/Vec2.hpp"
#include <stdio.h>

class TransformComponent : public Component {
public:
	Core::Physics::Vec2 Position = { 0.0f, 0.0f };
	Core::Physics::Vec2 Velocity = { 0.0f, 0.0f };
	float Angle = 0.0f;

	TransformComponent() : Component(GenComponentTypeID<TransformComponent>()) {};

	TransformComponent(Core::Physics::Vec2 pos, Core::Physics::Vec2 vel, float angle) 
		: Component(GenComponentTypeID<TransformComponent>()), Position(pos), Velocity(vel), Angle(angle) {};

	void LogComponent() const override {
		printf("\t\n\t\tTransformComponent :\n\t\t{\n\t\t\tPosition :\n\t\t\t{\n\t\t\t\tx: %f,\n\t\t\t\ty: %f\n\t\t\t},\n\n\t\t\tVelocity:\n\t\t\t{\n\t\t\t\tx: %f,\n\t\t\t\ty: %f\n\t\t\t},\n\n\t\t\tAngle : %f\n\t\t},\n\n\t", Position.x, Position.y, Velocity.x, Velocity.y, Angle);
	};
};
