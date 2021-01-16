#include "Wall.h"

using namespace Game;

Wall::Wall(int x, int y, GameEngine::eTexture::type eTexture) {
    Wall::SetLayer(GameEngine::CollisionLayer::Player);

    // Variables
    posX = x;
    posY = y;

    // Render
    spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
    spriteRenderComponent->SetTexture(eTexture);
    spriteRenderComponent->SetFillColor(sf::Color(200, 200, 200, 255));

    // Collisions
    collidableComponent = AddComponent<GameEngine::CollidableComponent>();

    // Sounds
    soundComponent = AddComponent<GameEngine::SoundComponent>();
}

Wall::~Wall() {
}

int Wall::GetPosX() {
    return posX;
}

void Wall::SetPosX(int x) {
    posX = x;
}

int Wall::GetPosY() {
    return posY;
}

void Wall::SetPosY(int y) {
    posY = y;
}