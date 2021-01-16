#include "PlayerProjectileCollisionComponent.h"
#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/GameEngineMain.h"
#include <vector>

using namespace GameEngine;

PlayerProjectileCollisionComponent::PlayerProjectileCollisionComponent() {
	leftPlayerHitbox = false;
	currentAngleTravel = 0;
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
		
		std::vector<CollidableComponent*> intersectedComponents;

		if (myBox.intersects(colideBox, intersection))
		{
			intersectedComponents.push_back(colComponent);

			if (colComponent->GetEntity()->GetLayer() == CollisionLayer::Wall) {
				// need to find which side of the wall it crashes with.
				sf::Vector2f pos = GetEntity()->GetPos();
				float boundedAngle = fmod(currentAngleTravel + 360, 360);
				if (intersection.width < intersection.height)
				{
					// reflect across Y-axis
					SetCurrentAngleTravel(fmod(180 - boundedAngle + 360, 360));
					if (myBox.left < colideBox.left)
						pos.x -= intersection.width;
					else
						pos.x += intersection.width;
				}
				else
				{
					// reflect across X-axis
					SetCurrentAngleTravel(fmod(-boundedAngle + 360, 360));
					if (myBox.top < colideBox.top)
						pos.y -= intersection.height;
					else
						pos.y += intersection.height;
				}
				GetEntity()->SetPos(pos);
				break;
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

void PlayerProjectileCollisionComponent::SetCurrentAngleTravel(float angleTravel) {
	currentAngleTravel = angleTravel;
}

float PlayerProjectileCollisionComponent::GetCurrentAngleTravel() {
	return currentAngleTravel;
}
