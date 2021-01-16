#include "PlayerProjectileCollisionComponent.h"
#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/GameEngineMain.h"
#include <vector>

using namespace GameEngine;

PlayerProjectileCollisionComponent::PlayerProjectileCollisionComponent() {
	leftPlayerHitbox = false;
}

PlayerProjectileCollisionComponent::~PlayerProjectileCollisionComponent() {

}

void PlayerProjectileCollisionComponent::OnAddToWorld()
{
	CollidableComponent::OnAddToWorld();
}


void PlayerProjectileCollisionComponent::OnRemoveFromWorld()
{
	CollidableComponent::OnRemoveFromWorld();
}

void PlayerProjectileCollisionComponent::Update()
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
				// need to find which side of the wall it crashes with.
				sf::Vector2f pos = GetEntity()->GetPos();
				if (intersection.width < intersection.height)
				{
					if (myBox.left < colideBox.left) {
						// hit right
					}
					else {
						// hit left
					}
				}
				else
				{
					if (myBox.top < colideBox.top) {
						// hit top
					}
					else {
						// hit bottom
					}
				}

				GetEntity()->SetPos(pos);
			}
		}
	}
}

bool PlayerProjectileCollisionComponent::HasLeftPlayerHitBox() {
	return leftPlayerHitbox;
}

void PlayerProjectileCollisionComponent::FlagLeftPlayerHitBox() {
	leftPlayerHitbox = true;
}

void PlayerProjectileCollisionComponent::SetProjectileInstant(Game::Projectile* p) {
	projectileInstance = p;
}
