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
    crateDisplay = NULL;
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

void Player::ClearPlayerProjectiles() {
    currentProjectiles.clear();
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

    std::vector<Game::Player*> currentPlayers = GameBoard::getInstance()->GetAllPlayers();
    GameBoard::getInstance()->EndGame(playerNumber);

    for (int i = 0; i < currentPlayers.size(); i++) {
        currentPlayers[i]->SetPos(Game::GameBoard::getInstance()->GetPlayerSpawnPosition(i));
    }
}

void Player::SetPlayerUpgrade(PlayerUpgrade u) {
    currentPlayerUpgrade = u;
    if (u != PlayerUpgrade::None) {
        if (crateDisplay != NULL) {
            GameEngine::GameEngineMain::GetInstance()->RemoveEntity(crateDisplay);
            crateDisplay = NULL;
        }
        CrateDisplay* newCrateDisplay = new CrateDisplay(u);
        crateDisplay = newCrateDisplay;
        newCrateDisplay->SetPlayerIndex(playerNumber);
        GameEngine::GameEngineMain::GetInstance()->AddEntity(newCrateDisplay);
    }
    else {
        if (crateDisplay != NULL) {
            GameEngine::GameEngineMain::GetInstance()->RemoveEntity(crateDisplay);
            crateDisplay = NULL;
        }
    }
}

PlayerUpgrade Player::GetPlayerUpgrade() {
    return currentPlayerUpgrade;
}
