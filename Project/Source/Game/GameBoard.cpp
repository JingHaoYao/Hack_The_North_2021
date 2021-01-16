#include "GameBoard.h"
#include "Player.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/TextureManager.h"


using namespace Game;

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

void GameBoard::CreatePlayer() 
{
	GameEngine::eTexture::type sprite = GameEngine::eTexture::type::Tank_Red;
	Player* newPlayer = new Player(sprite);
	this->players.push_back(newPlayer);

	GameEngine::GameEngineMain::GetInstance()->AddEntity(newPlayer);
	
	newPlayer->SetPos(sf::Vector2f(50.f, 50.f));
	newPlayer->SetSize(sf::Vector2f(36.f, 50.f));
}