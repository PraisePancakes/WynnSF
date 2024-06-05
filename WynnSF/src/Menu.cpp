#include "Menu.hpp"
#include "../core/Components/CButton.hpp"
#include "../core/Components/CShape.hpp"
#include "../core/Components/CSprite.hpp"
#include "../core/Components/CText.hpp"
#include "../core/Components/CTransform.hpp"


Menu::Menu( sf::RenderWindow* ctx) {
	
	this->ctx = ctx;
	initMenu();
};


Core::Physics::Vec2D Menu::getRandomParticlePos(sf::RenderWindow* ctx) {

	const int MAX_X_POS = ctx->getSize().x;
	const int MAX_Y_POS = ctx->getSize().y;

	float xPos = std::rand() % MAX_X_POS;
	float yPos = std::rand() % MAX_Y_POS;

	return Core::Physics::Vec2D(xPos, yPos);

};


void Menu::renderMenuText() {
	std::shared_ptr<Entity> play = EntityManager::GetInstance()->GetEntities("Play-text")[0];


	auto playTextC = play->GetComponent<CText>();

	std::shared_ptr<Entity> quit = EntityManager::GetInstance()->GetEntities("Quit-text")[0];


	auto quitTextC = quit->GetComponent<CText>();
	ctx->draw(quitTextC->text);
	ctx->draw(playTextC->text);
};

void Menu::renderMenuParticles() {
	EntityVec particles = EntityManager::GetInstance()->GetEntities("Menu-particle");

	const float MIN_Y_BOUND = 0;
	const float MAX_Y_BOUND = ctx->getSize().y;

	for (size_t i = 0; i < particles.size(); i++) {
		std::shared_ptr<Entity> e = particles[i];
		auto shapeC = e->GetComponent<CShape>();
		auto tc = e->GetComponent<CTransform>();

		tc->Velocity.Normalize();

		tc->Velocity.y *= PARTICLE_SPEED;
		tc->Position.y += tc->Velocity.y;


		if (tc->Position.y > MAX_Y_BOUND) {
			tc->Position.y = MIN_Y_BOUND;
			shapeC->shape.setPosition(tc->Position.x, tc->Position.y);
		}


		shapeC->shape.move(tc->Velocity.x, tc->Velocity.y);
		ctx->draw(shapeC->shape);
	}


};

void Menu::initMenuParticles() {
	for (size_t i = 0; i < PARTICLE_COUNT; i++) {
		Core::Physics::Vec2D randomPos = getRandomParticlePos(ctx);

		auto particle = EntityManager::GetInstance()->AddEntity("Menu-particle");

		auto sc = particle->AddComponent<CShape>(PARTICLE_VERTICES, PARTICLE_RADIUS, sf::Color(20, 80, 35), sf::Color(20, 80, 35));
		auto tc = particle->AddComponent<CTransform>(Core::Physics::Vec2D(randomPos.x, randomPos.y), Core::Physics::Vec2D(0, 5), 0);
		sc->shape.setPosition(tc->Position.x, tc->Position.y);


	}

}

void Menu::initMenu() {
	std::srand(std::time(NULL));
	auto logo = EntityManager::GetInstance()->AddEntity("Logo");

	auto tc = logo->AddComponent<CTransform>();
	tc->Position.x = (float)ctx->getSize().x / 2;
	tc->Position.y = (float)ctx->getSize().y / 4;
	std::cout << "Logo" << std::endl;
	auto sc = logo->AddComponent<CSprite>("src/Assets/Sprites/Logo/logo.png", sf::IntRect(0, 0, 1974, 687), 256, 128);
	sc->sprite.setPosition(tc->Position.x, tc->Position.y);

	auto playTxt = EntityManager::GetInstance()->AddEntity("Play-text");
	auto playTextC = playTxt->AddComponent<CText>("Play", "src/Assets/Fonts/PixelFont.ttf", 36, (float)ctx->getSize().x / 2, (float)ctx->getSize().y / 2);

	auto playBtn = EntityManager::GetInstance()->AddEntity("Play-btn");
	auto playBtnC = playBtn->AddComponent<CButton>(sf::RectangleShape(sf::Vector2f(playTextC->text.getGlobalBounds().width + 10, playTextC->text.getGlobalBounds().height + 10)), sf::Vector2f(playTextC->text.getPosition().x - playTextC->text.getGlobalBounds().width / 2 - 3, playTextC->text.getPosition().y), sf::Color::White, sf::Color::Black);

	auto quitTxt = EntityManager::GetInstance()->AddEntity("Quit-text");
	auto quitTextC = quitTxt->AddComponent<CText>("Quit", "src/Assets/Fonts/PixelFont.ttf", 36, (float)ctx->getSize().x / 2, (float)ctx->getSize().y / 2 + 50);

	auto quitBtn = EntityManager::GetInstance()->AddEntity("Quit-btn");
	auto quitBtnC = quitBtn->AddComponent<CButton>(sf::RectangleShape(sf::Vector2f(quitTextC->text.getGlobalBounds().width + 10, quitTextC->text.getGlobalBounds().height + 10)), sf::Vector2f(quitTextC->text.getPosition().x - quitTextC->text.getGlobalBounds().width / 2 - 3, quitTextC->text.getPosition().y + 5), sf::Color::White, sf::Color::Black);

	initMenuParticles();


};

void Menu::renderLogo() {
	std::shared_ptr<Entity> logo = EntityManager::GetInstance()->GetEntities("Logo")[0];
	auto sc = logo->GetComponent<CSprite>();

	const int MAX_X_DIM = 510;
	const int MAX_Y_DIM = 210;

	const int MIN_X_DIM = 256;
	const int MIN_Y_DIM = 128;

	static int currentX = 256;
	static int currentY = 128;
	static bool reachedMax = false;

	if (!reachedMax) {
		if (currentX < MAX_X_DIM && currentY < MAX_Y_DIM) {
			currentX++;
			currentY++;

		}
		else {
			reachedMax = true;
		}
	}
	else {
		if (currentX > MIN_X_DIM && currentY > MIN_Y_DIM) {
			currentX--;
			currentY--;
		}
		else {
			reachedMax = false;
		}

	}
	sc->ScaleToN(&sc->srcRect, currentX, currentY);




	ctx->draw(sc->sprite);
}



void Menu::renderMenuButtons() {
	std::shared_ptr<Entity> btn = EntityManager::GetInstance()->GetEntities("Play-btn")[0];
	auto btnC = btn->GetComponent<CButton>();

	std::shared_ptr<Entity> quitbtn = EntityManager::GetInstance()->GetEntities("Quit-btn")[0];

	auto qbtnC = quitbtn->GetComponent<CButton>();

	qbtnC->OnHover(ctx, [qbtnC]() {
		qbtnC->buttonRect.setOutlineColor(sf::Color::Red);

		});

	btnC->OnHover(ctx, [btnC]() {
		btnC->buttonRect.setOutlineColor(sf::Color::Green);
		});


	ctx->draw(qbtnC->buttonRect);
	ctx->draw(btnC->buttonRect);
}


int Menu::GetMenuEvents() const {
	int event = 0;

	std::shared_ptr<Entity> playbtn = EntityManager::GetInstance()->GetEntities("Play-btn")[0];
	auto playbtnC = playbtn->GetComponent<CButton>();

	std::shared_ptr<Entity> quitbtn = EntityManager::GetInstance()->GetEntities("Quit-btn")[0];
	auto quitbtnC = quitbtn->GetComponent<CButton>();

	playbtnC->OnClick(this->ctx, [&event]() {
		event = 1;
		});

	quitbtnC->OnClick(this->ctx, [&event]() {
		event = 2;
		});


	return event;

};

void Menu::Clean() {
	std::cout << "Particles destroyed " << std::endl;
	EntityVec particles = EntityManager::GetInstance()->GetEntities("Menu-particle");

	for (auto& p : particles) {
		p->DestroyEntity();
	}

	particles.clear();


}

void Menu::Render() {
	renderMenuParticles();
	renderLogo();
	renderMenuButtons();
	renderMenuText();

};


Menu::~Menu() {

	Clean();
};