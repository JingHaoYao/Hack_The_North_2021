#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Game/Player.h"
#include "Game/Wall.h"

namespace Game
{
	//Used for storing and controlling all game related entities, as well as providing an entry point for the "game" side of application	
	class PlayerEntity;	
	class Player;

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		void Update();		
		bool IsGameOver();
		Player* GetPlayerByIndex(int);
		static GameBoard* getInstance() { if (!m_gameboard) m_gameboard = new GameBoard(); return m_gameboard; }
		Wall* CreateWall(int, int);


	protected:
		int widthPx, heightPx,numX,numY,remainderX,remainderY;
		void CreatePlayer();
		std::vector<Game::Player*> players;
		static GameBoard* m_gameboard;
		std::vector<std::vector<int>> wallGrid;
		void populateWalls();
	};
}

