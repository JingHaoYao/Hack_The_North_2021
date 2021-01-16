#include "GameBoard.h"
#include "Player.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/TextureManager.h"


using namespace Game;

GameBoard* GameBoard::m_gameboard = nullptr;

GameBoard::GameBoard()
{
	CreatePlayer();
}

GameBoard::~GameBoard()
{

}

void GameBoard::Update()
{	
	
}

bool GameBoard::IsGameOver() {
	return false;
}

void GameBoard::CreatePlayer() 
{
	GameEngine::eTexture::type sprite = GameEngine::eTexture::type::Tank_Red;
	Player* newPlayer = new Player(sprite, 0);
	this->players.push_back(newPlayer);

	GameEngine::GameEngineMain::GetInstance()->AddEntity(newPlayer);
	
	newPlayer->SetPos(sf::Vector2f(50.f, 50.f));
	newPlayer->SetSize(sf::Vector2f(36.f, 50.f));
}

Player* GameBoard::GetPlayerByIndex(int i) {
	return players[i];
}