#pragma once
#include "Projectile.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Entity.h"

namespace Game {
	class RocketProjectile : public Game::Projectile {
	public:
		RocketProjectile();
		~RocketProjectile();
		void Update() override;
		void OnAddToWorld() override;
		void SetEntityToFollow(Entity*);

	protected:
		GameEngine::AnimationComponent* animator;
		Entity* entityToFollow;
		void explode();

	};
}