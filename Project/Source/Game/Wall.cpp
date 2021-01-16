#include "Wall.h"

using namespace Game;

Wall::Wall() {
    Wall::SetLayer(GameEngine::CollisionLayer::Player);

    // Render
    spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
    spriteRenderComponent->SetFillColor(sf::Color(200, 200, 200, 255));

    // Collisions
    collidableComponent = AddComponent<GameEngine::CollidableComponent>();

    // Sounds
    soundComponent = AddComponent<GameEngine::SoundComponent>();
}

Wall::~Wall() {
}