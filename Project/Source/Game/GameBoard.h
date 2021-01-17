#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Game/Player.h"
#include "Game/Wall.h"
#include "Game/Scoreboard.h"

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
		void EndGame(int);
		Player* GetPlayerByIndex(int);
		sf::Vector2f GetPlayerSpawnPosition(int);
		static GameBoard* getInstance() { if (!m_gameboard) m_gameboard = new GameBoard(); return m_gameboard; }
		std::vector<Game::Player*> GetAllPlayers();
		Wall* CreateWall(int, int);
		std::vector<std::vector<int>> ProceduralWallGeneration(std::vector<std::vector<int>>);

	protected:
		int widthPx, heightPx,numX,numY,remainderX,remainderY,losingPlayer;
		float projectileSpawnTimer, projectileTimeElapsed;
		bool gameOver;
		std::vector<Wall*> map;
		Game::Scoreboard* currentScoreBoard;
		void CreateBackground();
		Game::Scoreboard* CreateScoreBoard();
		void CreatePlayer();
		sf::Vector2f Player1SpawnPosition();
		sf::Vector2f Player2SpawnPosition();
		sf::Vector2f ProjectileSpawnPosition();
		void CreateUpgradeCrate(PlayerUpgrade, sf::Vector2f);
		std::vector<Game::Player*> players;
		static GameBoard* m_gameboard;
		std::vector<std::vector<int>> wallGrid;
		void PopulateWalls();
		void DestroyWalls();
		void UpdateScoreBoard();
		bool CheckAvailablePosition(int, int);

	};
}

