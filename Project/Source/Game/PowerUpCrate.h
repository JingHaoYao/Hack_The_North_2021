#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/PowerUpCrateCollisionComponent.h"
#include "Game/Player.h"

namespace Game {
	class PowerUpCrate : public GameEngine::Entity {
	public:
		PowerUpCrate(Game::PlayerUpgrade, sf::Vector2f);
		~PowerUpCrate();
		void Update() override;

	protected:
		GameEngine::SpriteRenderComponent* spriteRenderComponent;
		GameEngine::PowerUpCrateCollisionComponent* powerUpCrateCollisionComponent;
		Game::PlayerUpgrade whichUpgrade;
	};
}