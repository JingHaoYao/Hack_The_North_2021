#include "Player.h"
#include "Explosion.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"

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
    playerNumber = binding;
    currentPlayerUpgrade = PlayerUpgrade::None;
}

Player::~Player() {
    
}

void Player::Update() {
    playerMovementComponent->Update();
    playerShootComponent->Update();
    collidableComponent->Update();
}

std::vector<Projectile*> Player::GetCurrentProjectiles() {
    return currentProjectiles;
}

void Player::AddCurrentProjectile(Projectile* p) {
    currentProjectiles.push_back(p);
}

void Player::RemoveProjectile(Projectile* p) {
    auto it = std::find(currentProjectiles.begin(), currentProjectiles.end(), p);
    currentProjectiles.erase(it);
}

void Player::PlayerDied() {
    // spawn explosion
    Explosion* explosionInstant = new Explosion(GetPos(), sf::Vector2f(60.f, 60.f));
    GameEngine::GameEngineMain::GetInstance()->AddEntity(explosionInstant);

    SetPos(Game::GameBoard::getInstance()->GetPlayerSpawnPosition(playerNumber));
    // reload player state
}

void Player::SetPlayerUpgrade(PlayerUpgrade u) {
    currentPlayerUpgrade = u;
}

PlayerUpgrade Player::GetPlayerUpgrade() {
    return currentPlayerUpgrade;
}
