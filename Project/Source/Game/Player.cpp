#include "Player.h"
#include "Explosion.h"
#include "GameEngine/GameEngineMain.h"

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
    collidableComponent = AddComponent<GameEngine::PlayerCollisionComponent>();
    collidableComponent->SetPlayerIndex(binding);

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
    collidableComponent->Update();
}

Projectile* Player::GetCurrentProjectile() {
    return currentProjectile;
}

void Player::SetCurrentProjectile(Projectile* p) {
    currentProjectile = p;
}

void Player::PlayerDied() {
    // spawn explosion
    Explosion* explosionInstant = new Explosion(GetPos(), sf::Vector2f(60.f, 60.f));
    GameEngine::GameEngineMain::GetInstance()->AddEntity(explosionInstant);
    // reload player state
}
