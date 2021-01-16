#include "PlayerCollisionComponent.h"
#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameBoard.h"
#include <vector>

using namespace GameEngine;

PlayerCollisionComponent::PlayerCollisionComponent()
{
	playerIndex = 0;
}

PlayerCollisionComponent::~PlayerCollisionComponent()
{

}

void PlayerCollisionComponent::OnAddToWorld()
{
	CollidableComponent::OnAddToWorld();
}


void PlayerCollisionComponent::OnRemoveFromWorld()
{
	CollidableComponent::OnRemoveFromWorld();
}

void PlayerCollisionComponent::SetPlayerIndex(int i) 
{
	playerIndex = i;
}

void PlayerCollisionComponent::Update()
{
	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
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
			if (colComponent->GetEntity()->GetLayer() == CollisionLayer::Wall) {
				sf::Vector2f pos = GetEntity()->GetPos();
				if (intersection.width < intersection.height)
				{
					if (myBox.left < colideBox.left)
						pos.x -= intersection.width;
					else
						pos.x += intersection.width;
				}
				else
				{
					if (myBox.top < colideBox.top)
						pos.y -= intersection.height;
					else
						pos.y += intersection.height;
				}

				GetEntity()->SetPos(pos);

			}
			else if (colComponent->GetEntity()->GetLayer() == CollisionLayer::PlayerProjectile) {
				std::vector<Game::Projectile*> allProjectiles = Game::GameBoard::getInstance()->GetPlayerByIndex(playerIndex)->GetCurrentProjectiles();

				auto foundIterator = std::find(allProjectiles.begin(), allProjectiles.end(), colComponent->GetEntity());

				if (foundIterator != allProjectiles.end()) {
					if (!(*foundIterator)->HasLeftPlayerHitbox()) {
						continue;
					}
				}

				// player hit

				for each (auto var in Game::GameBoard::getInstance()->GetAllPlayers())
				{
					std::vector<Game::Projectile*> playerCurrentProjectiles = var->GetCurrentProjectiles();
					auto it = std::find(playerCurrentProjectiles.begin(), playerCurrentProjectiles.end(), colComponent->GetEntity());
					if (it != playerCurrentProjectiles.end()) {
						var->RemoveProjectile(*it);
					}
				}

				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(colComponent->GetEntity());
				Game::GameBoard::getInstance()->GetPlayerByIndex(playerIndex)->PlayerDied();
			}
		}
		else {
			std::vector<Game::Projectile*> allProjectiles = Game::GameBoard::getInstance()->GetPlayerByIndex(playerIndex)->GetCurrentProjectiles();

			auto foundIterator = std::find(
				allProjectiles.begin(),
				allProjectiles.end(),
				colComponent->GetEntity());

			if (foundIterator != allProjectiles.end()) {
				(*foundIterator)->FlagPlayerHitbox();
				// TODO: Check for if the collider is the player projectile, so we can set a flag to it that says it left the hitbox of the player.
			}
		}
	}
}