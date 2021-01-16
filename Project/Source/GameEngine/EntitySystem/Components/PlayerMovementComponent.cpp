#define _USE_MATH_DEFINES

#include "PlayerMovementComponent.h"
#include "GameEngine/GameEngineMain.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

using namespace GameEngine;
using namespace std;

PlayerMovementComponent::PlayerMovementComponent() {
	movementSpeed = 150.f;
	rotateSpeed = 120.f;
	whatKeyBinding = 1;
}

PlayerMovementComponent::~PlayerMovementComponent() {
	Component::~Component();
}

void PlayerMovementComponent::Update() {
	sf::Vector2f movementVector = sf::Vector2f(0.f, 0.f);
	int angleOffset = 0;
	switch (whatKeyBinding) {
	case 0: 

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			angleOffset += -1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angleOffset += +1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			movementVector += sf::Vector2f(cos((GetEntity()->GetRot() - 90) * M_PI / 180.f), sin((GetEntity()->GetRot() - 90) * M_PI / 180.f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			movementVector += sf::Vector2f(cos((GetEntity()->GetRot() + 90) * M_PI / 180.f)*0.5, sin((GetEntity()->GetRot() + 90) * M_PI / 180.f)*0.5);
		}

		GetEntity()->SetPos(GetEntity()->GetPos() + movementVector * movementSpeed * GameEngine::GameEngineMain::GetTimeDelta());
		GetEntity()->SetRotation(GetEntity()->GetRot() + angleOffset * rotateSpeed * GameEngine::GameEngineMain::GetTimeDelta());

		break;
	case 1:

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			angleOffset += -1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			angleOffset += +1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			movementVector += sf::Vector2f(cos((GetEntity()->GetRot() - 90) * M_PI / 180.f), sin((GetEntity()->GetRot() - 90) * M_PI / 180.f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			movementVector += sf::Vector2f(cos((GetEntity()->GetRot() + 90) * M_PI / 180.f) * 0.5, sin((GetEntity()->GetRot() + 90) * M_PI / 180.f) * 0.5);
		}

		GetEntity()->SetPos(GetEntity()->GetPos() + movementVector * movementSpeed * GameEngine::GameEngineMain::GetTimeDelta());
		GetEntity()->SetRotation(GetEntity()->GetRot() + angleOffset * rotateSpeed * GameEngine::GameEngineMain::GetTimeDelta());

		break;
	}
}

void PlayerMovementComponent::SetKeyBinding(int binding) {
	whatKeyBinding = binding;
}
