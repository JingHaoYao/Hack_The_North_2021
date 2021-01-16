#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

namespace GameEngine {
	class PowerUpCrateCollisionComponent : public CollidableComponent {
	public:
		PowerUpCrateCollisionComponent();
		virtual ~PowerUpCrateCollisionComponent();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		virtual void Update() override;

		void SetUpgradeType(int);
	protected:
		int whatUpgrade;
	};
}