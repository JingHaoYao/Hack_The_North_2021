#include "CrateDisplay.h"
#include "Game/GameBoard.h"

using namespace Game;

CrateDisplay::CrateDisplay(int i) {
	spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	spriteRenderComponent->SetFillColor(sf::Color(0, 0, 0, 0));
	switch (static_cast<PlayerUpgrade>(i)) {
	case PlayerUpgrade::Bomb:
		spriteRenderComponent->SetTexture(GameEngine::eTexture::Crate_Bomb);
		break;
	case PlayerUpgrade::Laser:
		spriteRenderComponent->SetTexture(GameEngine::eTexture::Crate_Laser);
		break;
	case PlayerUpgrade::MachineGun:
		spriteRenderComponent->SetTexture(GameEngine::eTexture::Crate_Machine_Gun);
		break;
	case PlayerUpgrade::Rocket:
		spriteRenderComponent->SetTexture(GameEngine::eTexture::Create_Rocket);
		break;
	}
	SetSize(sf::Vector2f(27, 36));
}

CrateDisplay::~CrateDisplay() {

}

void CrateDisplay::Update() {
	SetPos(Game::GameBoard::getInstance()->GetPlayerByIndex(playerIndex)->GetPos());
	SetRotation(Game::GameBoard::getInstance()->GetPlayerByIndex(playerIndex)->GetRot());
}

void CrateDisplay::SetPlayerIndex(int i) {
	playerIndex = i;
}
