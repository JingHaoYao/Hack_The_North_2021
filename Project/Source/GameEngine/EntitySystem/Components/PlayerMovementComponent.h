#pragma once
#include "GameEngine/EntitySystem/Component.h"

namespace GameEngine
{
	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		virtual void Update() override;

		void SetKeyBinding(int);

	private:
		// Speed Definitions
		float movementSpeed;
		float rotateSpeed;
		int whatKeyBinding;
	};
}
