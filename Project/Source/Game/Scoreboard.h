#pragma once
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"
#include "GameEngine/EntitySystem/Entity.h"
#include <string>

namespace Game {
	class Scoreboard : public GameEngine::Entity {
	public:
		Scoreboard();
		~Scoreboard();

		//accessors
		int getp1Score();
		int getp2Score();
		int getRound();

		//mutators
		void setp1Score(int);
		void setp2Score(int);
		void setRound(int);



	protected:
		int p1Score;
		int p2Score;
		int numRounds;
		std::string p1ScoreString;
		std::string p2ScoreString;
		std::string roundString;
		GameEngine::TextRenderComponent* textRenderComponent;

	};
}