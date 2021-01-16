#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "Game/Projectile.h"

class PlayerProjectileCollisionComponent : public GameEngine::CollidableComponent {
public:
	PlayerProjectileCollisionComponent();
	virtual ~PlayerProjectileCollisionComponent();

	virtual void OnAddToWorld() override;
	virtual void OnRemoveFromWorld() override;

	virtual void Update() override;

	bool HasLeftPlayerHitBox();
	void FlagLeftPlayerHitBox();
	void SetProjectileInstant(Game::Projectile*);

protected: 
	bool leftPlayerHitbox;
	Game::Projectile* projectileInstance;
};