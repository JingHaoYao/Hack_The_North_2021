#define _USE_MATH_DEFINES

#include "PlayerMovementComponent.h"
#include "GameEngine/GameEngineMain.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

using namespace GameEngine;
using namespace std;

PlayerMovementComponent::PlayerMovementComponent() {
	movementSpeed = 100.f;
	rotateSpeed = 120.f;
	whatKeyBinding = 1;
}

PlayerMovementComponent::~PlayerMovementComponent() {

}

void PlayerMovementComponent::Update() {
	switch (whatKeyBinding) {
	case 1: 
		sf::Vector2f movementVector = sf::Vector2f(0.f, 0.f);
		int angleOffset = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			angleOffset = -1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angleOffset = +1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			movementVector += sf::Vector2f(cos((GetEntity()->GetRot() - 90) * M_PI / 180.f), sin((GetEntity()->GetRot() - 90) * M_PI / 180.f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			movementVector += sf::Vector2f(cos((GetEntity()->GetRot() + 90) * M_PI / 180.f), sin((GetEntity()->GetRot() + 90) * M_PI / 180.f));
		}

		GetEntity()->SetPos(GetEntity()->GetPos() + movementVector * movementSpeed * GameEngine::GameEngineMain::GetTimeDelta());
		GetEntity()->SetRotation(GetEntity()->GetRot() + angleOffset * rotateSpeed * GameEngine::GameEngineMain::GetTimeDelta());

		break;
	}
}