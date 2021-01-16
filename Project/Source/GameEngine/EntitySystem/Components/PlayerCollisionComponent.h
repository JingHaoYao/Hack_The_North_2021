#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "Game/Player.h"

class PlayerCollisionComponent : public GameEngine::CollidableComponent {
public:
	PlayerCollisionComponent();
	virtual ~PlayerCollisionComponent();

	virtual void OnAddToWorld() override;
	virtual void OnRemoveFromWorld() override;

	virtual void Update() override;

	void SetPlayerInstant(Game::Player*);

protected:
	Game::Player* playerInstant;
};
