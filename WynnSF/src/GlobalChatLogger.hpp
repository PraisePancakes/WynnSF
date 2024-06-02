#pragma once
#include <queue>
#include <iostream>
#define MAX_Q_ELEMS 10
#define MAX_LOG_W 500
#define MAX_LOG_H 500
#include <SFML/Graphics.hpp>
#include "../core/Manager/EntityManager.hpp"
// chat : q [ "chat 1" , "chat 2" , "chat 3" ]  << pop first elem when pushing to q, 
class EntityManager;
class GlobalChatLogger {

	static std::queue<std::string> chatq;
	static bool updateFlag;
	static std::queue<std::string> copyq;


public:
	static void Log(const std::string& message);

	static void Display(sf::RenderWindow* ctx, EntityManager* em);

	static void Update(EntityManager* em);

	~GlobalChatLogger();
};