#pragma once
#include <iostream>



class Kit {
	std::string kitTitle;
	std::string kitBasePath;


public:
	Kit(const std::string& title, const std::string& basePath) {
		this->kitTitle = title;
		this->kitBasePath = basePath;

	};
	

	std::string GetKitTitle() const {
		return kitTitle;
	}


	~Kit() {};
};
