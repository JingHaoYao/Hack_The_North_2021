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
    spriteRenderComponent->SetFillColor(sf::Color(0, 0, 0, 225));

    // Collisions
    collidableComponent = AddComponent<GameEngine::CollidableComponent>();

    m_layer = GameEngine::CollisionLayer::Wall;
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