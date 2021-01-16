#define _USE_MATH_DEFINES
#include "Projectile.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"
#include <cmath>

using namespace Game;

Projectile::Projectile(GameEngine::eTexture::type eTexture) {

    // Variables
    keybinding = 1;
    projectileSpeed = 200.f;
    angleOfTravel = 0.f;
    duration = 5.f;
    timeElapsed = 0.f;

    // Render
    spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
    spriteRenderComponent->SetTexture(eTexture);
    spriteRenderComponent->SetFillColor(sf::Color(1, 1, 1, 0));

    // Collisions
    collidableComponent = AddComponent<GameEngine::PlayerProjectileCollisionComponent>();

    // Sounds
    soundComponent = AddComponent<GameEngine::SoundComponent>();

    m_layer = GameEngine::CollisionLayer::PlayerProjectile; // set layer
}

Projectile::~Projectile() {

}

void Projectile::Update() {

    angleOfTravel = collidableComponent->GetCurrentAngleTravel();

    sf::Vector2f projectileVector = sf::Vector2f(cos(GetAngleOfTravel() * M_PI / 180.f), (sin(GetAngleOfTravel() * M_PI / 180.f)));
    SetPos(GetPos() + projectileVector * projectileSpeed * GameEngine::GameEngineMain::GetTimeDelta());

    // Duration
    if (GetTimeElapsed() >= GetDuration()) {
        GameEngine::GameEngineMain::GetInstance()->RemoveEntity(this);
        Game::GameBoard::getInstance()->GetPlayerByIndex(GetPlayerIndex())->SetCurrentProjectile(NULL);
    }
    else {
        SetTimeElapsed(GetTimeElapsed() + GameEngine::GameEngineMain::GetTimeDelta());
    }
}

void Projectile::SetAngleOfTravel(float angle) {
    angleOfTravel = fmod(angle + 360, 360);
    collidableComponent->SetCurrentAngleTravel(angle);
}

float Projectile::GetAngleOfTravel() {
    return angleOfTravel;
}

void Projectile::SetDuration(float d) {
    duration = d;
}

float Projectile::GetDuration() {
    return duration;
}

void Projectile::SetTimeElapsed(float time) {
    timeElapsed = time;
}

float Projectile::GetTimeElapsed() {
    return timeElapsed;
}

bool Projectile::HasLeftPlayerHitbox() {
    return leftPlayerHitbox;
}

void Projectile::FlagPlayerHitbox() {
    leftPlayerHitbox = true;
}

void Projectile::SetPlayerIndex(int i) {
    playerIndex = i;
}

int Projectile::GetPlayerIndex() {
    return playerIndex;
}
