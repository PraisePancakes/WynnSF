#pragma once
#include <deque>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../core/Manager/EntityManager.hpp"
#include "../core/Components/CText.hpp"
#include <mutex>
constexpr size_t CHAT_LOG_MAX_SIZE = 10;


class GlobalChatManager {

	static std::mutex mut;
	static GlobalChatManager* pinstance;

protected:

	 int min = 0;
	 int max = 0;
	 int currentSlide = 0;
	 sf::RectangleShape chatBox;

	GlobalChatManager();
	
	~GlobalChatManager();
	
public:
	
	static GlobalChatManager& GetInstance();
	//two iterators to keep track of chat scrolling, use a sliding window algorithm to 'scroll' through the deque
	// one iterator will point to the beginning at vec and one will gradually increase as more strings get pushed
	// and an end iterator representing the oldest chat
	// 
	// e.g.. if we have 5 strings pushed
	//	  begin	         end               N    where cbegin <= cend <= N where N is a constant max size
	//  dq = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
	// 
	// now the window should be a length of 5 meaning each scroll is limited to the 5 strings of the current scroll positions
	// 
	// e.g.. say we scroll once
	//		  begin        end
	// dq = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
	// 
	// now only chats [2,6] inclusive are rendered rather than [1, 5] inclusive.
	// 
	// to push chats we make certain to push to the front via 
	// and if n >= N => k=N−i for i=0,1,2,…,N−1 k[N] = k[N - 1]
	// 
	//be able to call this anywhere on the 
	void Log(const std::string& str);
	void Update(sf::RenderWindow* ctx);
	void HandleScrollEvent(sf::Event* e, sf::RenderWindow* ctx);
	//we need a hold of the iterators here
	
	 void Render( sf::RenderWindow* ctx);



	


};