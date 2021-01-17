#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/PlayerProjectileCollisionComponent.h"

namespace Game {
	class DamagingExplosion : public GameEngine::Entity {
	public:
		DamagingExplosion();
		~DamagingExplosion();

		void Update() override;

		void OnAddToWorld() override;

	protected:
		GameEngine::AnimationComponent* animator;
		GameEngine::SpriteRenderComponent* spriteRenderer;
		GameEngine::PlayerProjectileCollisionComponent* collider;
	};
}