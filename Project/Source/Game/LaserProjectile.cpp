#include "LaserProjectile.h"

Game::LaserProjectile::LaserProjectile() {

    // Render
    spriteRenderComponent->SetTexture(GameEngine::eTexture::Laser_Projectile);
	animator = AddComponent<GameEngine::AnimationComponent>();
	animator->SetIsLooping(true);
	projectileSpeed = 1000.f;
	SetSize(sf::Vector2f(20, 50));
}

Game::LaserProjectile::~LaserProjectile() {
	Game::Projectile::~Projectile();
}

void Game::LaserProjectile::OnAddToWorld() {
	animator->PlayAnim(GameEngine::EAnimationId::Laser_Projectile);
	Entity::OnAddToWorld();
}

void Game::LaserProjectile::Update() {
	Projectile::Update();
	animator->Update();
	spriteRenderComponent->Update();
}
