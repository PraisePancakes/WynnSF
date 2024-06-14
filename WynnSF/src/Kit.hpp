#pragma once
#include <iostream>
#include "../core/Manager/EntityManager.hpp"
#include "../core/Components/CAnimator.hpp"

class Kit {
public:
	std::string kitTitle;
	std::string kitBasePath;
	sf::IntRect src;
	CAnimator animator;

	Kit(const std::string& title, const std::string& basePath, CAnimator animator) {
		this->kitTitle = title;
		this->kitBasePath = basePath;
		this->animator = animator;
		
	};
	

	std::string GetKitTitle() const {
		return kitTitle;
	}


	~Kit() {};
};
