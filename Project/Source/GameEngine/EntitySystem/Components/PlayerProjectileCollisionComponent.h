#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

namespace GameEngine { 
	class PlayerProjectileCollisionComponent : public GameEngine::CollidableComponent {
	public:
		PlayerProjectileCollisionComponent();
		virtual ~PlayerProjectileCollisionComponent();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		virtual void Update() override;

		bool HasLeftPlayerHitBox();
		void FlagLeftPlayerHitBox();
		void SetCurrentAngleTravel(float);
		float GetCurrentAngleTravel();

	protected:
		bool leftPlayerHitbox;
		float currentAngleTravel;
	};
}