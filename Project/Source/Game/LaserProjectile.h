#pragma once
#include "Projectile.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"

namespace Game {
	class LaserProjectile : public Game::Projectile {
	public:
		LaserProjectile();
		~LaserProjectile();

		void OnAddToWorld() override;
		

	protected:
		GameEngine::AnimationComponent* animator;
	};
}