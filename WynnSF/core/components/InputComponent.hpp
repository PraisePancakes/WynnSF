#pragma once
#include "../ECS.hpp"

class InputComponent : public Component {
public:
	bool right = false;
	bool up = false;
	bool down = false;
	bool left = false;

	InputComponent() : Component(GenComponentTypeID<InputComponent>()) {};

	void LogComponent() const override {};
};
