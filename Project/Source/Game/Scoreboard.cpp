#include "Scoreboard.h"

using namespace Game;

Scoreboard::Scoreboard(){
	//initialize both player scores to 0
	p1Score = 0; 
	p2Score = 0;
	
	p1ScoreString = std::to_string(p1Score);
	p2ScoreString = std::to_string(p2Score);
	roundString = std::to_string(numRounds);
	
	

	//render
	textRenderComponent->SetString(/*"Round #: " + roundString + " "*/  p1ScoreString + " - " + p2ScoreString); // p1 score - p2 score

	
}

Scoreboard::~Scoreboard() {

}

int Scoreboard::getp1Score() {
	return p1Score;
}

int Scoreboard::getp2Score() {
	return p2Score;
}

int Scoreboard::getRound() {
	return numRounds;
}

void Scoreboard::setp1Score(int p1ScorePlus1) { //assumed: use player who wins would have score added by one player who lost would have same score
	p1Score = p1ScorePlus1;
}

void Scoreboard::setp2Score(int p2ScorePlus1) {
	p2Score = p2ScorePlus1;
}

void Scoreboard::setRound(int round) {
	numRounds = round;
}