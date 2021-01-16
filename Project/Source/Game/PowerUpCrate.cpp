#include "PowerUpCrate.h"

Game::PowerUpCrate::PowerUpCrate(Game::PlayerUpgrade u, sf::Vector2f pos) {
	whichUpgrade = u;
	spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	powerUpCrateCollisionComponent = AddComponent<GameEngine::PowerUpCrateCollisionComponent>();
	powerUpCrateCollisionComponent->SetUpgradeType(u);
	SetSize(sf::Vector2f(27.f, 36.f));
	SetPos(pos);

	switch (u) {
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
}

Game::PowerUpCrate::~PowerUpCrate() {

}

void Game::PowerUpCrate::Update() {
	powerUpCrateCollisionComponent->Update();
}