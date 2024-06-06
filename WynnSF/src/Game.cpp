#include "Game.hpp"
#include "../core/Components/CSprite.hpp"
#include "../core/Components/CCollider.hpp"
#include "../core/Components/CTransform.hpp"


//TO-DO make chat log relative to player pos

Game::Game(const std::string & title) {
	m_running = true;
	m_Window.create(sf::VideoMode::VideoMode(WINDOW_W, WINDOW_H), title, sf::Style::Titlebar | sf::Style::Close);
	m_Window.setFramerateLimit(60);
	spawnPlayer();
	
	m_sceneManager = std::make_unique<SceneManager>(&this->m_Window);
	m_sceneManager->SetScene(Scenes::SCENE_MENU);

	m_Cam.setSize(WINDOW_W, WINDOW_H);
	

};


void Game::Run() {

	while (m_running) {
		m_Window.clear();
	
		sUserInput();
		sUpdate();
		
		if (m_sceneManager->GetCurrentScene()->GetID() == Scenes::SCENE_QUIT) {
			m_running = false;
			m_Window.close();
		}
		//handle game events
		if (m_sceneManager->GetCurrentScene()->GetID() != Scenes::SCENE_MENU) {
			sCollider();
			sMovement();
			
		}


		sRenderer();
		EntityManager::GetInstance()->Update();
		m_Window.display();

	}
};


void Game::sUserInput() {
	sf::Event e;

	while (m_Window.pollEvent(e)) {
		if (e.type == sf::Event::EventType::Closed) {
			m_Window.close();
			m_running = false;
		}

		

		if (m_sceneManager->GetCurrentScene()->GetID() != Scenes::SCENE_MENU) {
			m_Player->HandleInput(&e);
			GlobalChatManager::GetInstance().HandleScrollEvent(&e, &m_Window);
		}

		m_sceneManager->HandleEvents(&e);
	}

};

void Game::sMovement() {
	m_Player->HandleMovement();
};

void Game::updateCam() {
	m_Cam.setCenter(m_Player->GetPos().x, m_Player->GetPos().y);
	m_Window.setView(m_Cam);
}

void Game::sUpdate() {
	
	if (m_sceneManager->GetCurrentScene()->GetID() != Scenes::SCENE_MENU) {
		m_Player->Update();
		updateCam();
		GlobalChatManager::GetInstance().Update(&this->m_Window);
	}

	
	
}
/*
	since we are using a circle collider, the collision system will work based positioning of each circle collider when collision occurs

	refer to diagrams/collision.png


*/

void Game::checkCollision(EntityVec& ev) {

	float plx = m_Player->GetPos().x;
	float ply = m_Player->GetPos().y;


	for (auto& e : ev) {
		if (e->HasComponent<CCollider>()) {
			float ex = e->GetComponent<CSprite>()->sprite.getPosition().x;
			float ey = e->GetComponent<CSprite>()->sprite.getPosition().y;
			float xDiff = plx - ex;
			float yDiff = ply - ey;

			float distance = std::sqrt(xDiff * xDiff + yDiff * yDiff);
			float pr = m_Player->GetEntityInstance()->GetComponent<CCollider>()->radius;
			float er = e->GetComponent<CCollider>()->radius;

			if (distance < pr + er) {
				auto tc = m_Player->GetEntityInstance()->GetComponent<CTransform>();

				if (xDiff < 0 && std::abs(xDiff) > std::abs(yDiff)) {
					tc->Position.x -= std::abs(m_Player->GetEntityInstance()->GetComponent<CTransform>()->Velocity.x);
				}
				else if (xDiff > 0 && std::abs(xDiff) > std::abs(yDiff)) {
					tc->Position.x += std::abs(m_Player->GetEntityInstance()->GetComponent<CTransform>()->Velocity.x);
				}
				else if (yDiff < 0 && std::abs(yDiff) > std::abs(xDiff)) {
					tc->Position.y -= std::abs(m_Player->GetEntityInstance()->GetComponent<CTransform>()->Velocity.y);
				}
				else if (yDiff > 0 && std::abs(yDiff) > std::abs(xDiff)) {
					tc->Position.y += std::abs(m_Player->GetEntityInstance()->GetComponent<CTransform>()->Velocity.y);
				}
			}
		}
	}
};



void Game::sCollider() {
	EntityVec tlTiles = m_sceneManager->GetCurrentScene()->GetTopLayer();

	checkCollision(tlTiles);
};


//TEST


void Game::spawnPlayer() {
	
	float spawnX = WINDOW_W / 2 + 50;
	float spawnY = WINDOW_H / 2 + 100;

	m_Player = std::make_unique<Player>(spawnX, spawnY);

};

void Game::sRenderer() {
	m_sceneManager->RenderScene();
	if (m_sceneManager->GetCurrentScene()->GetID() != Scenes::SCENE_MENU) {
		m_Player->Render(this->m_Window);
		GlobalChatManager::GetInstance().Render(&m_Window);

	}
	


};
