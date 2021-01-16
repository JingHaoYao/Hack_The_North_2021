#pragma once
#include "GameEngine/EntitySystem/Entity.h"

class Player : public GameEngine::Entity
{
	public:
		Player();
		~Player();

private:
	void Update();
};


