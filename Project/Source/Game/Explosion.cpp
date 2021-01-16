#include "Explosion.h"

Game::Explosion::Explosion(sf::Vector2f pos, sf::Vector2f size) {
	spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	animationComponent = AddComponent<GameEngine::AnimationComponent>();
	SetPos(pos);
	SetSize(size);
}

Game::Explosion::~Explosion() {

}

void Game::Explosion::OnAddToWorld() {
	animationComponent->PlayAnim(GameEngine::EAnimationId::Explosion_0);
	Entity::OnAddToWorld();
}

void Game::Explosion::OnRemoveFromWorld() {
	Entity::OnRemoveFromWorld();
}