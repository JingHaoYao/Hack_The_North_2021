#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"

int main()
{
	GameEngine::GameEngineMain* mainEngine = GameEngine::GameEngineMain::GetInstance();
	Game::GameBoard* mainGameBoard = Game::GameBoard::getInstance();

	while (mainEngine->GetRenderWindow()->isOpen())
	{				
		mainEngine->Update();
	}

	delete mainEngine;
	return 0;
}