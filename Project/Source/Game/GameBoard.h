#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Game/Player.h"

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


	protected:
		void CreatePlayer();
		std::vector<Game::Player*> players;
		static GameBoard* m_gameboard;
	};
}

