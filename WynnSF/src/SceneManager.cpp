#include "SceneManager.hpp"
#include "../core/Components/CCollider.hpp"
#include "../core/Components/CSprite.hpp"
#include "GlobalChatBox.hpp"


SceneManager::SceneManager(Scenes startingScene, sf::RenderWindow* ctx) {
	m_currentScene = startingScene;
	this->ctx = ctx;

	menu = std::make_unique<Menu>(ctx);

	blTiles = std::make_unique<TXBaseLayerTiles>();
	tlTiles = std::make_unique<TXTopLayerTiles>();

};


void SceneManager::SetScene(Scenes scene) {
	clearPrevScene();
	if (scene == Scenes::SCENE_QUIT) {
		this->m_currentScene = scene;
		return;
	}
	this->m_currentScene = scene;
	initScene();
	loadScene();

};


void SceneManager::Update() {

	if (m_currentScene == Scenes::SCENE_MENU) {

		int event = menu->GetMenuEvents();
		switch (event) {
		case 1:
			SetScene(Scenes::SCENE_RAGNI);
			//@test
			GlobalChatBox::Log("Welcome To Wynn1");
			GlobalChatBox::Log("Welcome To Wynn2");
			GlobalChatBox::Log("Welcome To Wynn3");
			GlobalChatBox::Log("Welcome To Wynn4");
			GlobalChatBox::Log("Welcome To Wynn5");
			GlobalChatBox::Log("Welcome To Wynn6");
			GlobalChatBox::Log("Welcome To Wyn7");
			GlobalChatBox::Log("Welcome To Wynn8");
			GlobalChatBox::Log("Welcome To Wynn9");
			GlobalChatBox::Log("Welcome To Wynn10");
			GlobalChatBox::Log("Welcome To Wynn11");
			GlobalChatBox::Log("Welcome To Wynn12");
			GlobalChatBox::Log("Welcome To Wynn13");
		
			
			
			break;
		case 2:
			SetScene(Scenes::SCENE_QUIT);
			break;
		default:
			break;
		}
	}
	else {
	
		//update scene based on player actions
	}

};

void SceneManager::RenderScene() {
	if (this->m_currentScene == Scenes::SCENE_MENU) {
		menu->Render();
	}
	else {
		//render base layer
		auto blTiles = EntityManager::GetInstance()->GetEntities("blTiles");
		for (auto& blt : blTiles) { //im hungry can u tell
			ctx->draw(blt->GetComponent<CSprite>()->sprite);
		}

		//render top layer
		auto tlTiles = EntityManager::GetInstance()->GetEntities("tlTiles");

		for (auto& tlt : tlTiles) {
			ctx->draw(tlt->GetComponent<CSprite>()->sprite);
		}

	}

}

void SceneManager::parseSceneData(const std::string& filename) {

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Unable to open file: " << filename << std::endl;
		return;
	}

	std::string line;
	std::string b;
	std::string t;
	bool onB = false;
	bool onT = false;


	
	while (std::getline(file, line)) {
		if (line == " ") {
			continue;
		}

		if (line == "b") {
			onB = true;
			onT = false;
			continue;
		}
		
		if (line == "t") {
			onT = true;
			onB = false;
			continue;
		}

		if (onB) {
			b += line;
		}
		else {
			t += line;
		}
	}

	std::vector<int> row;
	for (size_t i = 0; i < b.length(); i++) {
		if (b[i] == ' ') {
			continue;
		}
		if (b[i] == 'e') {
			scenebl.push_back(row);
			row.clear();
		}
		else {
			if (b[i + 1] != ' ') {
				std::string numStr;
				while (b[i] != ' ') {
					numStr += b[i];
					i++;
				}
				int num = std::stoi(numStr);
				row.push_back(num);
			}
			else {
				row.push_back(b[i] - '0');
			}
		}
	}


	for (size_t i = 0; i < t.length(); i++) {
		if (t[i] == ' ') {
			continue;
		}

		if (t[i] == 'e') {
			scenetl.push_back(row);
			row.clear();
		}
		else {
			if (t[i + 1] != ' ') {
				std::string numStr;
				while (t[i] != ' ') {
					numStr += t[i];
					i++;
				}
				int num = std::stoi(numStr);
				row.push_back(num);
			}
			else {
				row.push_back(t[i] - '0');
			}

			
		}
	}


	file.close();
}

void SceneManager::clearPrevScene() {
	if (m_currentScene == Scenes::SCENE_MENU) {
		menu->Clean();
	}

	auto blTiles = EntityManager::GetInstance()->GetEntities("blTiles");

	for (auto& blt : blTiles) {
		blt->DestroyEntity();
	}

	auto tiles = EntityManager::GetInstance()->GetEntities("tlTiles");

	for (auto& t : tiles) {
		t->DestroyEntity();
	}

	scenetl.clear();
	scenebl.clear();
}

void SceneManager::initScene() {

	switch (m_currentScene) {
	case Scenes::SCENE_RAGNI: {
		parseSceneData("src/Data/Scenes/ragni.txt");
	}
	break;

	}
};

void SceneManager::loadBaseLayer() {
	for (size_t i = 0; i < scenebl.size(); i++) {
		for (size_t j = 0; j < scenebl[i].size(); j++) {
			switch (scenebl[j][i]) {
			case 0:
			{
				auto grassTile = EntityManager::GetInstance()->AddEntity("blTiles");
				auto sc = grassTile->AddComponent<CSprite>(blTiles->TXGrassSetPath, blTiles->grass, 128, 128);
				sc->sprite.setPosition(i * 128, j * 128);
			}
			break;
			case 1:
			{
				auto flowerTile = EntityManager::GetInstance()->AddEntity("blTiles");

				auto sc = flowerTile->AddComponent<CSprite>(blTiles->TXGrassSetPath, blTiles->flower, 128, 128);
				sc->sprite.setPosition(i * 128, j * 128);
			}
			break;
			case 2:
			{
				auto stoneTile = EntityManager::GetInstance()->AddEntity("blTiles");
				auto sc = stoneTile->AddComponent<CSprite>(blTiles->TXGrassSetPath, blTiles->stone_path, 128, 128);
				sc->sprite.setPosition(i * 128, j * 128);

			}
			break;
			case 3:
			{
				auto stoneTile = EntityManager::GetInstance()->AddEntity("blTiles");
				auto sc = stoneTile->AddComponent<CSprite>(blTiles->TXGrassSetPath, blTiles->stone_path2, 128, 128);
				sc->sprite.setPosition(i * 128, j * 128);
			}
			break;
			case 4:
			{
				auto stoneTile = EntityManager::GetInstance()->AddEntity("blTiles");
				auto sc = stoneTile->AddComponent<CSprite>(blTiles->TXStoneGroundSetPath, blTiles->stone_ground, 128, 128);
				sc->sprite.setPosition(i * 128, j * 128);
			}
			break;
		
			}
		}
	}

};

void SceneManager::loadTopLayer() {
	for (size_t i = 0; i < scenetl.size(); i++) {
		for (size_t j = 0; j < scenetl[i].size(); j++) {
			switch (scenetl[j][i]) {

			case 1:
			{
				auto leftWall = EntityManager::GetInstance()->AddEntity("tlTiles");
				auto sc = leftWall->AddComponent<CSprite>(tlTiles->TXWallSetPath, tlTiles->leftWall, 128, 128);
				sc->sprite.setPosition(i * 128, j * 128);
				leftWall->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
			}
			break;
			case 2:
			{
				auto rightWall = EntityManager::GetInstance()->AddEntity("tlTiles");
				auto sc = rightWall->AddComponent<CSprite>(tlTiles->TXWallSetPath, tlTiles->rightWall, 128, 128);
				sc->sprite.setPosition((i * 128) + 50, j * 128);
				rightWall->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
			}
			break;

			case 4:
			{
				auto wallTile = EntityManager::GetInstance()->AddEntity("tlTiles");
				auto sc = wallTile->AddComponent<CSprite>(tlTiles->TXWallSetPath, tlTiles->wall, 128, 128);
				sc->sprite.setPosition(i * 128, j * 128);
				wallTile->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
			}
			break;
			case 5:
			{
				auto cornerWall = EntityManager::GetInstance()->AddEntity("tlTiles");
				auto sc = cornerWall->AddComponent<CSprite>(tlTiles->TXWallSetPath, tlTiles->cornerWall, 128, 128);
				sc->sprite.setPosition(i * 128, j * 128);
				cornerWall->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
			}
			break;
			case 6:
			{
				auto grassPatchTile = EntityManager::GetInstance()->AddEntity("tlTiles");
				auto sc = grassPatchTile->AddComponent<CSprite>(tlTiles->TXPlantSetPath, tlTiles->grass_patch, 128, 128);
				sc->sprite.setPosition(i * 128, j * 128);
			}
			break;
			case 7 :
			{
				auto tree1 = EntityManager::GetInstance()->AddEntity("tlTiles");
				auto sc = tree1->AddComponent<CSprite>(tlTiles->TXPlantSetPath, tlTiles->tree1, 256, 256);
				sc->sprite.setPosition(i * 128, j * 128);
				tree1->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
			}
			break;
			case 8:
			{
				auto bushSmall = EntityManager::GetInstance()->AddEntity("tlTiles");
				auto sc = bushSmall->AddComponent<CSprite>(tlTiles->TXPlantSetPath, tlTiles->bushSmall, 64, 64);
				sc->sprite.setPosition(i * 128, j * 128);
				bushSmall->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
			}
			break;
			case 9:
			{
				auto bushBig = EntityManager::GetInstance()->AddEntity("tlTiles");
				auto sc = bushBig->AddComponent<CSprite>(tlTiles->TXPlantSetPath, tlTiles->bushBig, 75, 75);
				sc->sprite.setPosition(i * 128, j * 128);
				bushBig->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
			}
			break;
			case 10:
			{
				auto house1 = EntityManager::GetInstance()->AddEntity("tlTiles");
				auto sc = house1->AddComponent<CSprite>(tlTiles->TXSVSet, tlTiles->house1, 256, 256);
				sc->sprite.setPosition(i * 128, j * 128);
				house1->AddComponent<CCollider>(sc->sprite.getGlobalBounds().height / 2);
			}
			break;
			default:
				break;
			}
		}
	}

}

void SceneManager::loadScene() {
	loadBaseLayer();
	loadTopLayer();
};


SceneManager::~SceneManager() {
	clearPrevScene();
};