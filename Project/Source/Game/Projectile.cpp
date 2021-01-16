#include "Projectile.h"

using namespace Game;

Projectile::Projectile(GameEngine::eTexture::type eTexture) {

    // Variables
    int keybinding = 1;
    float projectileSpeed = 200.f;
    float angleOfTravel = 0.f;
    float duration = 5.f;

    // Movement
    playerShootComponent = AddComponent<GameEngine::PlayerShootComponent>();

    // Render
    spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
    spriteRenderComponent->SetTexture(eTexture);
    spriteRenderComponent->SetFillColor(sf::Color(1, 1, 1, 0));

    // Collisions
    collidableComponent = AddComponent<GameEngine::CollidableComponent>();

    // Sounds
    soundComponent = AddComponent<GameEngine::SoundComponent>();
}

Projectile::~Projectile() {

}

void Projectile::Update() {
    playerShootComponent->Update();
}

void Projectile::SetAngleOfTravel(float angle) {
    angleOfTravel = angle;
}

float Projectile::GetAngleOfTravel() {
    return angleOfTravel;
}