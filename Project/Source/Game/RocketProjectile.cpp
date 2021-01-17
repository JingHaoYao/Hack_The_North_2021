#define _USE_MATH_DEFINES

#include "RocketProjectile.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"
#include "Game/DamagingExplosion.h"

using namespace Game;

Game::RocketProjectile::RocketProjectile() {
	Projectile::Projectile();
	animator = AddComponent<GameEngine::AnimationComponent>();
	animator->SetIsLooping(true);
	spriteRenderComponent->SetTexture(GameEngine::eTexture::Rocket_Blink);
	collidableComponent->SetCollideWithWall(false);
	m_layer = GameEngine::CollisionLayer::PlayerProjectile;
	SetSize(sf::Vector2f(25, 45));
	projectileSpeed = 200;
	duration = 3.f;
}

Game::RocketProjectile::~RocketProjectile() {

}

void Game::RocketProjectile::Update() {
	animator->Update();
	spriteRenderComponent->Update();
	collidableComponent->Update();

	sf::Vector2f projectileVector = sf::Vector2f(cos(GetAngleOfTravel() * M_PI / 180.f), (sin(GetAngleOfTravel() * M_PI / 180.f)));

	SetPos(GetPos() + projectileVector * projectileSpeed * GameEngine::GameEngineMain::GetTimeDelta());
	SetRotation(angleOfTravel + 90);
	
	// Duration
	if (GetTimeElapsed() >= GetDuration()) {
		explode();
	}
	else {
		SetTimeElapsed(GetTimeElapsed() + GameEngine::GameEngineMain::GetTimeDelta());
	}
}

void RocketProjectile::SetEntityToFollow(Entity* e) {
	entityToFollow = e;
}

void Game::RocketProjectile::explode() {

	DamagingExplosion* newExplosion = new DamagingExplosion();
	newExplosion->SetPos(GetPos());
	GameEngine::GameEngineMain::GetInstance()->AddEntity(newExplosion);
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(this);
	Game::GameBoard::getInstance()->GetPlayerByIndex(GetPlayerIndex())->RemoveProjectile(this);
	Game::GameBoard::getInstance()->GetPlayerByIndex(GetPlayerIndex())->SetPlayerUpgrade(Game::PlayerUpgrade::None);
}

void Game::RocketProjectile::OnAddToWorld() {
	Projectile::OnAddToWorld();
	animator->PlayAnim(GameEngine::EAnimationId::Rocket_Blink);
}