#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"

namespace Game {
	class Explosion : public GameEngine::Entity {
	public:
		Explosion(sf::Vector2f, sf::Vector2f);
		~Explosion();

		void OnAddToWorld() override;
		void OnRemoveFromWorld() override;

	protected:
		GameEngine::SpriteRenderComponent* spriteRenderComponent;
		GameEngine::AnimationComponent* animationComponent;
	};
}
