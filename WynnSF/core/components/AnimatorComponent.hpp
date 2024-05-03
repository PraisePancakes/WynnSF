#pragma once
#include "../ECS.hpp"
#include <SFML/Graphics.hpp>
#include "../components/SpriteComponent.hpp"
#include <vector>


/*
	TO DO remove non constant members
	basePath, 
	MaxAppendable
	duration
*/
class AnimatorComponent : public Component {
private:
	float m_FrameDuration = 0;
	int m_CurrentFrame = 0;
	int m_MaxAppendablePath = 0;
	

public:
	
	std::string basePath;
	SpriteComponent* m_sc;

	AnimatorComponent(SpriteComponent* sc) 
		: Component(GenComponentTypeID<AnimatorComponent>()), m_sc(sc) {};



	void SetAnimatedSprite(const std::string& path, int maxPathAppend, int currentFrame, float xScale, float yScale, float duration) {
		this->basePath = path;
		this->m_MaxAppendablePath = maxPathAppend;
		this->m_FrameDuration = duration;
		this->m_CurrentFrame = currentFrame;
		
		static sf::Clock clock;
		if (clock.getElapsedTime().asSeconds() > this->m_FrameDuration) {
			clock.restart();
			
			std::string finalPath = basePath + std::to_string(m_CurrentFrame % m_MaxAppendablePath) + ".png";
			
			m_sc->SetSprite(finalPath, xScale, yScale, m_sc->sprite.getPosition().x, m_sc->sprite.getPosition().y);
		}
		
	};

	void LogComponent() const override {
		printf("\t\n\t\AnimatorComponent:");
	};
	

};
