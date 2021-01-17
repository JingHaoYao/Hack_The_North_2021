#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

namespace Game {
	class CrateDisplay : public GameEngine::Entity {
	public:
		CrateDisplay(int);
		~CrateDisplay();
		void Update() override;
		void SetPlayerIndex(int);

	protected:
		GameEngine::SpriteRenderComponent* spriteRenderComponent;
		int playerIndex;
	};
}