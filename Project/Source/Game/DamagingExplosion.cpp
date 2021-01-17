#include "DamagingExplosion.h"

Game::DamagingExplosion::DamagingExplosion() {
	spriteRenderer = AddComponent<GameEngine::SpriteRenderComponent>();
	spriteRenderer->SetTexture(GameEngine::eTexture::Explosion_1);
	spriteRenderer->SetFillColor(sf::Color(0, 0, 0, 0));
	animator = AddComponent<GameEngine::AnimationComponent>();
	animator->SetIsLooping(false);
	animator->SetShouldDestroy(true);
	collider = AddComponent<GameEngine::PlayerProjectileCollisionComponent>();
	collider->FlagLeftPlayerHitBox();
	collider->SetCollideWithWall(false);
	SetSize(sf::Vector2f(100.f, 100.f));
	m_layer = GameEngine::CollisionLayer::PlayerProjectile;
}

Game::DamagingExplosion::~DamagingExplosion() {

}

void Game::DamagingExplosion::Update() {
	animator->Update();
	spriteRenderer->Update();
	collider->Update();
}

void Game::DamagingExplosion::OnAddToWorld() {
	animator->PlayAnim(GameEngine::EAnimationId::Explosion_1);
	GameEngine::Entity::OnAddToWorld();
}