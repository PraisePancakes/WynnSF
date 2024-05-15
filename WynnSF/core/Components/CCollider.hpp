#pragma once
#include "../ECS.hpp"

class CCollider : public Component {
public:
	float radius = 0.f;

	CCollider(float r) : Component(GenComponentTypeID<CCollider>()) {
		this->radius = r;

	};

};