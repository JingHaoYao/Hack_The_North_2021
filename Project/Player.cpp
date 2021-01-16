#include <GameEngine\EntitySystem\Components\SpriteRenderComponent.h>
#include "Player.h"
using namespace Game;


Player::Player(GameEngine::eTexture::type eTexture) {

	// Movement


	// Render
	spriteRenderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	spriteRenderComponent->SetTexture(eTexture);

	// Collisions
	collidableComponent = AddComponent<GameEngine::CollidableComponent>();

	// Sounds
	soundComponent = AddComponent<GameEngine::SoundComponent>();
}

Player::~Player() {

}

void Player::Update() {

}

