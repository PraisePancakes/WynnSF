#pragma once
#include <iostream>
#include "../core/Manager/EntityManager.hpp"
#include "../core/Components/CAnimator.hpp"

enum class KitTypes {
	KIT_NONE = -1,
	KIT_ARCHER,
	KIT_ASSASSIN,
	KIT_WARRIOR,
	KIT_WIZARD
};


enum class AnimationType {
	IDLE,
	RUN,
	ATTACK,
	LOOKING_LEFT,
	LOOKING_RIGHT,

};

class Kit {
public:
	std::string kitTitle;


	Kit(const std::string& title) {
		this->kitTitle = title;
	};

	virtual CAnimator& GetCurrentAnimator() = 0;
	virtual void SetCurrentAnimator(AnimationType animatorType) = 0;

	std::string GetKitTitle() const {
		return kitTitle;
	}


	~Kit() {};
};

struct ArcherAnimationData {
	CAnimator idle{ "src/Assets/Sprites/Player/Archer/Sprites/Character/Idle.png", sf::IntRect(0, 0, 100, 100), 900, 100 };
	CAnimator run{ "src/Assets/Sprites/Player/Archer/Sprites/Character/Run.png", sf::IntRect(0, 0, 100, 100), 700, 100 };
	
};

struct AssassinAnimatorData {
	CAnimator idle{ "src/Assets/Sprites/Player/Assassin/Sprites/Character/Idle.png", sf::IntRect(0, 0, 200, 200), 600, 200 };
	CAnimator run{ "src/Assets/Sprites/Player/Assassin/Sprites/Character/Run.png", sf::IntRect(0, 0, 200, 200), 800, 200 };
};

struct WarriorAnimatorData {
	CAnimator idle{ "src/Assets/Sprites/Player/Warrior/Sprites/Character/Idle.png", sf::IntRect(0, 0, 162, 162), 1458, 162 };
	CAnimator run{ "src/Assets/Sprites/Player/Warrior/Sprites/Character/Run.png", sf::IntRect(0, 0, 162, 162), 1134, 162 };
};


struct WizardAnimatorData {
	CAnimator idle{ "src/Assets/Sprites/Player/Wizard/Sprites/Character/Idle.png", sf::IntRect(0, 0, 230, 190), 925, 230 };
	CAnimator run{ "src/Assets/Sprites/Player/Wizard/Sprites/Character/Run.png", sf::IntRect(0, 0, 230, 190), 1610, 230 };

};

class WizardKit : public Kit {
public:
	WizardAnimatorData animatorData;
	CAnimator currentAnimator = animatorData.idle;

	WizardKit() : Kit("Wizard") {};
	CAnimator& GetCurrentAnimator() override {
		return this->currentAnimator;
	}

	void SetCurrentAnimator(AnimationType animatorType) override {
		switch (animatorType)
		{
		case AnimationType::IDLE:
			this->currentAnimator = animatorData.idle;
			break;
		case AnimationType::RUN:
			this->currentAnimator = animatorData.run;
			break;
		case AnimationType::ATTACK:
			break;
		case AnimationType::LOOKING_LEFT:
			currentAnimator.ScaleToN(-128, 128);
			break;
		case AnimationType::LOOKING_RIGHT:
			currentAnimator.ScaleToN(128, 128);
			break;
		default:
			break;
		}
	
	}
	~WizardKit() {};
};

class AssassinKit : public Kit {
public:
	AssassinAnimatorData animatorData;
	CAnimator currentAnimator = animatorData.idle;

	AssassinKit() : Kit("Assassin") {};
	CAnimator& GetCurrentAnimator() override {
		return this->currentAnimator;
	}

	void SetCurrentAnimator(AnimationType animatorType) override {
		switch (animatorType)
		{
		case AnimationType::IDLE:
			this->currentAnimator = animatorData.idle;
			break;
		case AnimationType::RUN:
			this->currentAnimator = animatorData.run;
			break;
		case AnimationType::ATTACK:
			break;
		case AnimationType::LOOKING_LEFT:
			currentAnimator.ScaleToN(-128, 128);
			break;
		case AnimationType::LOOKING_RIGHT:
			currentAnimator.ScaleToN(128, 128);
			break;
		default:
			break;
		}

	}
	~AssassinKit() {};
};

class ArcherKit : public Kit {
public:
	ArcherAnimationData animatorData;
	CAnimator currentAnimator = animatorData.idle;
	ArcherKit() : Kit("Archer") {};
	CAnimator& GetCurrentAnimator() override {
		return this->currentAnimator;
	}

	void SetCurrentAnimator(AnimationType animatorType) override {
		switch (animatorType)
		{
		case AnimationType::IDLE:
			this->currentAnimator = animatorData.idle;
			break;
		case AnimationType::RUN:
			this->currentAnimator = animatorData.run;
			break;
		case AnimationType::ATTACK:
			break;
		case AnimationType::LOOKING_LEFT:
			currentAnimator.ScaleToN(-128, 128);
			break;
		case AnimationType::LOOKING_RIGHT:
			currentAnimator.ScaleToN(128, 128);
			break;
		default:
			break;
		}

	}
	

	~ArcherKit() {};

};

class WarriorKit : public Kit {
public:
	WarriorAnimatorData animatorData;
	CAnimator currentAnimator = animatorData.idle;
	WarriorKit() : Kit("Warrior") {};
	CAnimator& GetCurrentAnimator() override {
		return this->currentAnimator;
	}
	void SetCurrentAnimator(AnimationType animatorType) override {
		switch (animatorType)
		{
		case AnimationType::IDLE:
			this->currentAnimator = animatorData.idle;
			break;
		case AnimationType::RUN:
			this->currentAnimator = animatorData.run;
			break;
		case AnimationType::ATTACK:
			break;
		case AnimationType::LOOKING_LEFT:
			currentAnimator.ScaleToN(-128, 128);
		case AnimationType::LOOKING_RIGHT:
			currentAnimator.ScaleToN(128, 128);
			break;
		default:
			break;
		}

	}


	~WarriorKit() {};

};