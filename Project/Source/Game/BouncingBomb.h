#pragma once
#include "Projectile.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/PlayerProjectileCollisionComponent.h"

namespace Game {
	class BouncingBomb : public Game::Projectile {
	public:
		BouncingBomb();
		~BouncingBomb();
		void Update() override;
		void OnAddToWorld() override;
		void explode();
		void ReClickAction() override;

	protected:
		GameEngine::AnimationComponent* animator;
	};
}
