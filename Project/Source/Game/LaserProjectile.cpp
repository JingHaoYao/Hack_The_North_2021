#include "LaserProjectile.h"

Game::LaserProjectile::LaserProjectile() {

    // Render
    spriteRenderComponent->SetTexture(GameEngine::eTexture::Laser_Projectile);
	SetSize(sf::Vector2f(10, 10));
}

Game::LaserProjectile::~LaserProjectile() {
	Game::Projectile::~Projectile();
}

void Game::LaserProjectile::OnAddToWorld() {
	Entity::OnAddToWorld();
}

void Game::LaserProjectile::Update() {
	Projectile::Update();
}
