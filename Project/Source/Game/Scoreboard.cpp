#include "Scoreboard.h"

using namespace Game;

Scoreboard::Scoreboard(){
	//initialize both player scores to 0
	p1Score = 0; 
	p2Score = 0;
	numRounds = 0;
	
	p1ScoreString = std::to_string(p1Score);
	p2ScoreString = std::to_string(p2Score);
	roundString = std::to_string(numRounds);
	
	// p1 score - p2 score
	scoreboardString =/*"Round #: " + roundString + " "*/  p1ScoreString + " - " + p2ScoreString;
	
	//render
	textRenderComponent = AddComponent<GameEngine::TextRenderComponent>();
	textRenderComponent->SetString(scoreboardString); 
	textRenderComponent->SetFillColor(sf::Color(1, 1, 1, 0));
	textRenderComponent->SetColor(sf::Color(1, 1, 1, 100));
	textRenderComponent->SetFont("Roboto-Regular.ttf");
	textRenderComponent->SetCharacterSizePixels(300);
	textRenderComponent->SetZLevel(-1);
	
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

void Scoreboard::setp1Score(int p1ScorePlus1) {
	p1Score = p1ScorePlus1;
	Scoreboard::UpdateScoreboard();
}

void Scoreboard::setp2Score(int p2ScorePlus1) {
	p2Score = p2ScorePlus1;
	Scoreboard::UpdateScoreboard();
}

void Scoreboard::UpdateScoreboard() {
	p1ScoreString = std::to_string(p1Score);
	p2ScoreString = std::to_string(p2Score);
	roundString = std::to_string(numRounds+1);

	scoreboardString =/*"Round #: " + roundString + " "*/  p1ScoreString + " - " + p2ScoreString;
	textRenderComponent->SetString(scoreboardString);
}

void Scoreboard::setRound(int round) {
	numRounds = round;
}