#pragma once
#include "../ECS.hpp"

class CInput : public Component<CInput> {
public:
	bool ileft = false;
	bool iright = false;
	bool iup = false;
	bool idown = false;

	CInput()  {};


};