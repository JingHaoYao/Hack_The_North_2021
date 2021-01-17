#define _USE_MATH_DEFINES

#include "BouncingBomb.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"
#include "Game/DamagingExplosion.h"

Game::BouncingBomb::BouncingBomb() {

	Projectile();

	// Variables
	projectileSpeed = 150.f;
	angleOfTravel = 0.f;
	duration = 5.f;
	timeElapsed = 0.f;
	playerIndex = 0;

	// Render
	animator = AddComponent<GameEngine::AnimationComponent>();
	animator->SetIsLooping(true);
	spriteRenderComponent->SetTexture(GameEngine::eTexture::Bomb_Blink);
	spriteRenderComponent->SetFillColor(sf::Color(1, 1, 1, 0));
	SetSize(sf::Vector2f(50, 50));

	m_layer = GameEngine::CollisionLayer::None; // set layer
}

Game::BouncingBomb::~BouncingBomb() {

}

void Game::BouncingBomb::ReClickAction() {
	explode();
}

void Game::BouncingBomb::Update() {
	animator->Update();
	spriteRenderComponent->Update();

	collidableComponent->Update();
	angleOfTravel = collidableComponent->GetCurrentAngleTravel();

	sf::Vector2f projectileVector = sf::Vector2f(cos(GetAngleOfTravel() * M_PI / 180.f), (sin(GetAngleOfTravel() * M_PI / 180.f)));
	SetPos(GetPos() + projectileVector * projectileSpeed * GameEngine::GameEngineMain::GetTimeDelta());
	SetRotation(angleOfTravel - 90);

	// Duration
	if (GetTimeElapsed() >= GetDuration()) {
		explode();
	}
	else {
		SetTimeElapsed(GetTimeElapsed() + GameEngine::GameEngineMain::GetTimeDelta());
	}
}

void Game::BouncingBomb::explode() {
	
	DamagingExplosion* newExplosion = new DamagingExplosion();
	newExplosion->SetPos(GetPos());
	GameEngine::GameEngineMain::GetInstance()->AddEntity(newExplosion);
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(this);
	Game::GameBoard::getInstance()->GetPlayerByIndex(GetPlayerIndex())->RemoveProjectile(this);
	Game::GameBoard::getInstance()->GetPlayerByIndex(GetPlayerIndex())->SetPlayerUpgrade(Game::PlayerUpgrade::None);
}

void Game::BouncingBomb::OnAddToWorld() {
	Projectile::OnAddToWorld();
	animator->PlayAnim(GameEngine::EAnimationId::Bomb_Blink);
}