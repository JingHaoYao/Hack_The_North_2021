#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

namespace GameEngine {
	class PlayerCollisionComponent : public GameEngine::CollidableComponent {
	public:
		PlayerCollisionComponent();
		virtual ~PlayerCollisionComponent();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		virtual void Update() override;

		void SetPlayerIndex(int);

	protected:
		int playerIndex;
	};
}
