#include "LaserProjectile.h"

Game::LaserProjectile::LaserProjectile() {
	Game::Projectile::Projectile(GameEngine::eTexture::Laser_Projectile);
	animator = AddComponent<GameEngine::AnimationComponent>();
	animator->SetIsLooping(true);
	projectileSpeed = 1000.f;
}

Game::LaserProjectile::~LaserProjectile() {
	Game::Projectile::~Projectile();
}

void Game::LaserProjectile::OnAddToWorld() {
	animator->PlayAnim(GameEngine::EAnimationId::Laser_Projectile);
	Game::Projectile::OnAddToWorld();
}
