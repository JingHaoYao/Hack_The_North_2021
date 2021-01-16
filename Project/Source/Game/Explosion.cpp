#include "Explosion.h"

Game::Explosion::Explosion(sf::Vector2f pos, sf::Vector2f size) {
	spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	spriteRenderComponent->SetTexture(GameEngine::eTexture::Explosion_0);
	spriteRenderComponent->SetFillColor(sf::Color(0, 0, 0, 0));
	spriteRenderComponent->SetZLevel(2);
	animationComponent = AddComponent<GameEngine::AnimationComponent>();
	animationComponent->SetShouldDestroy(true);
	animationComponent->SetIsLooping(false);
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