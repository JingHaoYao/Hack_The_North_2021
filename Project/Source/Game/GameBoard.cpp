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
}