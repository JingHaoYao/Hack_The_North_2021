#include "GameBoard.h"
#include "Player.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/TextureManager.h"
#include "Game/PowerUpCrate.h"
#include <cstdlib>
#include <random>

using namespace Game;

GameBoard* GameBoard::m_gameboard = nullptr;

GameBoard::GameBoard()
{
	CreateBackground();
	currentScoreBoard = CreateScoreBoard();
	CreatePlayer();
	widthPx = GameEngine::GameEngineMain::GetWinWidth();
	heightPx = GameEngine::GameEngineMain::GetWinHeight();
	numX = (widthPx-20) / 16;
	numY = (heightPx-20) / 16;
	remainderX = (widthPx) % (numX * 16);
	remainderY = (heightPx) % (numY * 16);
	losingPlayer = -1;
	projectileSpawnTimer = 15.f;
	projectileTimeElapsed = 0.f;
	map;
	activeCrates;
	for (int i = 0; i < numX; i++) {
		wallGrid.push_back(std::vector<int>(numY, 0));
	}
	PopulateWalls();
}

GameBoard::~GameBoard()
{

}

void GameBoard::Update()
{	
	if (projectileTimeElapsed >= projectileSpawnTimer) {
		projectileTimeElapsed = 0.f;

		int whichPowerUp = rand() % 4 + 1;

		switch (whichPowerUp) {
		case 1:
			activeCrates.push_back(CreateUpgradeCrate(PlayerUpgrade::Laser, ProjectileSpawnPosition())); 
			break;
		case 2:
			activeCrates.push_back(CreateUpgradeCrate(PlayerUpgrade::Bomb, ProjectileSpawnPosition()));
			break;
		case 3:
			CreateUpgradeCrate(PlayerUpgrade::MachineGun, ProjectileSpawnPosition());
			break;
		case 4:
			CreateUpgradeCrate(PlayerUpgrade::Rocket, ProjectileSpawnPosition());
			break;
		}
	}
	else {
		projectileTimeElapsed += GameEngine::GameEngineMain::GetTimeDelta();
	}
	if (gameOver) {
		gameOver = false;
		DestroyWalls();
		std::vector<Game::Player*> currentPlayers = GameBoard::getInstance()->GetAllPlayers();

		std::vector<Projectile*> activeProjectiles;
		for (int i = 0; i < currentPlayers.size(); i++) {
			playerProjectiles = currentPlayers[i]->GetCurrentProjectiles();
			for (int j = 0; j < playerProjectiles.size(); j++) {
				activeProjectiles.push_back(playerProjectiles[j]);
			}
		}
		DestroyProjectiles(activeProjectiles);
		PopulateWalls();
		UpdateScoreBoard();
	}
}

PowerUpCrate* GameBoard::CreateUpgradeCrate(PlayerUpgrade u, sf::Vector2f p) {
	PowerUpCrate* newCrate = new PowerUpCrate(u, p);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(newCrate);
	return newCrate;
}

sf::Vector2f GameBoard::GetPlayerSpawnPosition(int i) {
	switch (i) {
	case 0:
		return GameBoard::Player1SpawnPosition();
	case 1:
		return GameBoard::Player2SpawnPosition();
	}
}

void GameBoard::EndGame(int playerIndex) {
	gameOver = true;
	losingPlayer = playerIndex;
}

void GameBoard::CreateBackground() {
	GameEngine::Entity* background = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(background);

	background->SetPos(sf::Vector2f(640, 360));
	background->SetSize(sf::Vector2f(1280, 720));

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(background->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::Background);
	render->SetFillColor(sf::Color::Transparent);
	render->SetZLevel(-2);
}

void GameBoard::CreatePlayer() 
{
	GameEngine::eTexture::type sprite1 = GameEngine::eTexture::type::Tank_Red;
	Player* newPlayer1 = new Player(sprite1, 0);
	this->players.push_back(newPlayer1);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(newPlayer1);

	newPlayer1->SetPos(GameBoard::Player1SpawnPosition());
	newPlayer1->SetSize(sf::Vector2f(36.f, 50.f));

	GameEngine::eTexture::type sprite2 = GameEngine::eTexture::type::Tank_Blue;
	Player* newPlayer2 = new Player(sprite2, 1);
	this->players.push_back(newPlayer2);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(newPlayer2);

	newPlayer2->SetPos(GameBoard::Player2SpawnPosition());
	newPlayer2->SetSize(sf::Vector2f(36.f, 50.f));
}

Player* GameBoard::GetPlayerByIndex(int i) {
	return players[i];
}

std::vector<Game::Player*> GameBoard::GetAllPlayers() {
	return players;
}

sf::Vector2f GameBoard::Player1SpawnPosition() {

	srand(time(0));

	bool positionFound = false;
	float currentX = 0;
	float currentY = 0;

	while (!positionFound) {
		currentX = rand() % (1280 - 120) + 60;
		currentY = rand() % (720 - 120) + 60;

		positionFound = GameBoard::CheckAvailablePosition(currentX / 16, currentY / 16);
	}	

	return sf::Vector2f(currentX, currentY);
}

sf::Vector2f GameBoard::Player2SpawnPosition() {

	bool positionFound = false;
	float currentX = 0;
	float currentY = 0;

	while (!positionFound) {
		currentX = rand() % (1280 - 120) + 60;
		currentY = rand() % (720 - 120) + 60;

		positionFound = GameBoard::CheckAvailablePosition(currentX / 16, currentY / 16);
	}

	return sf::Vector2f(currentX, currentY);
}

sf::Vector2f GameBoard::ProjectileSpawnPosition() {
	
	bool positionFound = false;
	float currentX = 0;
	float currentY = 0;

	while (!positionFound) {
		currentX = rand() % (1280 - 120) + 60;
		currentY = rand() % (720 - 120) + 60;

		positionFound = GameBoard::CheckAvailablePosition(currentX / 16, currentY / 16);
	}

	return sf::Vector2f(currentX, currentY);
}

bool GameBoard::CheckAvailablePosition(int x, int y) {

	// Hard-code bypass
	return true;

	int distance = 2;

	for (int i = 0; i < 3; i++) {
		if (wallGrid[x][y] == 1) {
			return false;
		}
		if (wallGrid[x + i][y] == 1) {
			return false;
		}
		if (wallGrid[x - i][y] == 1) {
			return false;
		}
		if (wallGrid[x][y + i] == 1) {
			return false;
		}
		if (wallGrid[x][y - i] == 1) {
			return false;
		}
		if (wallGrid[x + i][y + i] == 1) {
			return false;
		}
		if (wallGrid[x + i][y - i] == 1) {
			return false;
		}
		if (wallGrid[x - i][y + i] == 1) {
			return false;
		}
		if (wallGrid[x - i][y - i] == 1) {
			return false;
		}
	}
	return true;
}

void GameBoard::PopulateWalls() {
	//1:wall 0:no wall
	for (int i = 0; i < numX; i++) {
		for (int j = 0; j < numY; j++) {
			wallGrid[i][j] = 0;
		}
	}

	// create borders
	for (int i = 0; i < numX; i++) {
		if (i == 0 || i == numX - 1) {
			for (int j = 0; j < numY; j++) {
				wallGrid[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < numX; i++) {
		for (int j = 0; j < numY; j++) {
			if (j == 0 || j == numY-1) {
			wallGrid[i][j] = 1;
			}
		}
	}

	// Create Walls
	for (int i = 0; i < 15; i++) {
		wallGrid = ProceduralWallGeneration(wallGrid);
	}

	for (int i = 0; i < numX; i++) {
		for (int j = 0; j < numY; j++) {
			if (wallGrid[i][j] == 1) {
				Wall* newWall = CreateWall(i, j);
				map.push_back(newWall);
			}
		}
	}
}

std::vector<std::vector<int>> GameBoard::ProceduralWallGeneration(std::vector<std::vector<int>> grid) {

	int currentX = rand() % (numX-6) + 6;
	int currentY = rand() % (numY-6) + 6;
	int randomDirection = 0;
	int lastDirection = 0;
	int minPathLength = 5;
	sf::Vector2f newPos = sf::Vector2f(0,0);
	sf::Vector2f currentPos = sf::Vector2f(currentX, currentY);
	std::vector<std::vector<int>> directions =	{ {0,-1}, {0,1}, {-1,0}, {1, 0} };
	
	grid[currentX][currentY] = 1;

	for (int i = 0; i < 3; i++) {
		
		randomDirection = rand() % 4;
		lastDirection = randomDirection;
		for (int i = 0; i < minPathLength; i++) {
			newPos = sf::Vector2f(directions[randomDirection][0], directions[randomDirection][1]);
			if (currentPos.x + newPos.x > 0 && currentPos.x + newPos.x < numX - 1 && currentPos.y + newPos.y > 0 && currentPos.y + newPos.y < numY - 1) {
				currentPos += newPos;
				grid[currentPos.x][currentPos.y] = 1;
			}
			else {
				while (lastDirection == randomDirection) {
					randomDirection = rand() % 4;
				}
			}
		}
	}
	return grid;
}

Wall* GameBoard::CreateWall(int i, int j) {

	GameEngine::eTexture::type wallSprite = GameEngine::eTexture::type::Transparent_Wall;
	Wall* newWall = new Wall(i * 16 + remainderX / 2 + 5, j * 16 + remainderY / 2 + 5, wallSprite);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(newWall);

	newWall->SetPos(sf::Vector2f(newWall->GetPosX(), newWall->GetPosY()));
	newWall->SetSize(sf::Vector2f(18.f, 18.f));

	return newWall;
}

void GameBoard::DestroyWalls() {
	for (int i = 0; i < map.size(); i++) {
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(map[i]);
	}
	map.clear();
}
Game::Scoreboard* GameBoard::CreateScoreBoard() {
	Scoreboard* newScoreBoard = new Scoreboard;
	GameEngine::GameEngineMain::GetInstance()->AddEntity(newScoreBoard);

	newScoreBoard->SetPos(sf::Vector2f(320, 180));
	newScoreBoard->SetSize(sf::Vector2f(1, 1));
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(newScoreBoard->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::Background);
	render->SetFillColor(sf::Color::Transparent);

	return newScoreBoard;
}

void GameBoard::UpdateScoreBoard() {
	if (losingPlayer == 0) { // p2 dub
		currentScoreBoard->setp2Score(currentScoreBoard->getp2Score() + 1);
	}
	else if (losingPlayer == 1) {//p1 dub
		currentScoreBoard->setp1Score(currentScoreBoard->getp1Score() + 1);
	}
}

void GameBoard::DestroyProjectiles(std::vector<Projectile*> projectiles) {
	for (int i = 0; i < projectiles.size(); i++) {
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(projectiles[i]);
	}

	for each (auto player in GetAllPlayers()) {
		player->ClearPlayerProjectiles();
		player->SetPlayerUpgrade(Game::None);
	}

	projectiles.clear();
}
