#pragma once
#include "../ECS.hpp"

class CButton : public Component {
	

public:
	CButton() : Component(GenComponentTypeID<CButton>()) {};


};