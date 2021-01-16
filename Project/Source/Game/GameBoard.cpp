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
	GameEngine::eTexture::type sprite1 = GameEngine::eTexture::type::Tank_Red;
	Player* newPlayer1 = new Player(sprite1, 0);
	this->players.push_back(newPlayer1);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(newPlayer1);

	newPlayer1->SetPos(sf::Vector2f(50.f, 50.f));
	newPlayer1->SetSize(sf::Vector2f(36.f, 50.f));

	GameEngine::eTexture::type sprite2 = GameEngine::eTexture::type::Tank_Blue;
	Player* newPlayer2 = new Player(sprite2, 1);
	this->players.push_back(newPlayer2);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(newPlayer2);

	newPlayer2->SetPos(sf::Vector2f(1230.f, 670.f));
	newPlayer2->SetSize(sf::Vector2f(36.f, 50.f));
}

Player* GameBoard::GetPlayerByIndex(int i) {
	return players[i];
}