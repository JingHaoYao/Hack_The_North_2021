#include "PowerUpCrateCollisionComponent.h"
#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"
#include "Game/Player.h"
#include <vector>
#include <iostream>

GameEngine::PowerUpCrateCollisionComponent::PowerUpCrateCollisionComponent() {
	whatUpgrade = 0;
}

GameEngine::PowerUpCrateCollisionComponent::~PowerUpCrateCollisionComponent() {

}

void GameEngine::PowerUpCrateCollisionComponent::OnAddToWorld() {
	CollidableComponent::OnAddToWorld();
}

void GameEngine::PowerUpCrateCollisionComponent::OnRemoveFromWorld() {
	CollidableComponent::OnRemoveFromWorld();
}

void GameEngine::PowerUpCrateCollisionComponent::Update() {
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			continue;

		// If colliding with a wall, do the regular physics things.
		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect colideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(colideBox, intersection))
		{
			if (colComponent->GetEntity()->GetLayer() == CollisionLayer::Player) {
				
				for each (auto var in Game::GameBoard::getInstance()->GetAllPlayers())
				{
					if (var == colComponent->GetEntity()) {
						if (var->GetPlayerUpgrade() == Game::PlayerUpgrade::None) {
							var->SetPlayerUpgrade(static_cast<Game::PlayerUpgrade>(whatUpgrade));
							GameEngine::GameEngineMain::GetInstance()->RemoveEntity(GetEntity());
							break;
						}
					}
				}
			}
		}
	}
}

void GameEngine::PowerUpCrateCollisionComponent::SetUpgradeType(int i) {
	whatUpgrade = i;
}
