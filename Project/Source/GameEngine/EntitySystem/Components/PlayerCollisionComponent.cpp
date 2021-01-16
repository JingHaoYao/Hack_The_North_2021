#include "PlayerCollisionComponent.h"
#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/GameEngineMain.h"
#include <vector>

using namespace GameEngine;

PlayerCollisionComponent::PlayerCollisionComponent()
{
	playerInstant = NULL;
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

void PlayerCollisionComponent::SetPlayerInstant(Game::Player* player) 
{
	this->playerInstant = player;
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
				// need to check if the entity is the same as the projectile the player just shot.
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(colComponent->GetEntity());
				// TODO: run death procedure on player instant
			}
		}
		else {
			// TODO: Check for if the collider is the player projectile, so we can set a flag to it that says it left the hitbox of the player.
		}
	}
}