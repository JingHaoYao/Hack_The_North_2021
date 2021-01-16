#include "Player.h"

using namespace Game;

Player::Player(GameEngine::eTexture::type eTexture, int binding) {
    Player::SetLayer(GameEngine::CollisionLayer::Player);

    // Movement
    playerMovementComponent = AddComponent<GameEngine::PlayerMovementComponent>();
    playerMovementComponent->SetKeyBinding(binding);

    // Render
    spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
    spriteRenderComponent->SetTexture(eTexture);
    spriteRenderComponent->SetFillColor(sf::Color(1, 1, 1, 0));

    // Collisions
    collidableComponent = AddComponent<GameEngine::CollidableComponent>();

    // Sounds
    soundComponent = AddComponent<GameEngine::SoundComponent>();

    playerShootComponent = AddComponent<GameEngine::PlayerShootComponent>();
    playerShootComponent->SetPlayerIndex(binding);
    playerShootComponent->SetBinding(binding);
}

Player::~Player() {
    delete currentProjectile;
}

void Player::Update() {
    playerMovementComponent->Update();
    playerShootComponent->Update();
}

Projectile* Player::GetCurrentProjectile() {
    return currentProjectile;
}

void Player::SetCurrentProjectile(Projectile* p) {
    currentProjectile = p;
}
