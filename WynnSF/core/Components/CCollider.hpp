#pragma once
#include "../ECS.hpp"

class CCollider : public Component<CCollider> {
public:
	float radius = 0.f;

	CCollider() {};

	CCollider(float r) {
		this->radius = r;

	};

};