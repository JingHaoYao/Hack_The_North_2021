#define _USE_MATH_DEFINES
#include "PlayerShootComponent.h"
#include "Game/GameBoard.h"
#include "Game/Projectile.h"
#include "Game/LaserProjectile.h"
#include "GameEngine/GameEngineMain.h"
#include <SFML/Window/Keyboard.hpp>
#include <GameEngine\Util\TextureManager.h>
#include <cmath>
#include "Game/Player.h"

using namespace Game;
using namespace GameEngine;
using namespace std;

PlayerShootComponent::PlayerShootComponent() {
    keyBinding = 1;
    projectileSpeed = 5.f;
    shaftLength = 25.f;
    playerIndex = 0;
}

PlayerShootComponent::~PlayerShootComponent() {
    Component::~Component();
}

void PlayerShootComponent::Update() {
    switch (keyBinding) {
    case 0:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            CreateProjectile();
        }
        break;
    case 1:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            CreateProjectile();
        }
        break;
    }
}



void PlayerShootComponent::CreateProjectile() {
    Game::Player* playerInstance = Game::GameBoard::getInstance()->GetPlayerByIndex(GetPlayerIndex());
    if (playerInstance->GetCurrentProjectiles().size() <= 0) {
        Projectile* newProjectile = NULL;
        sf::Vector2f playerPos = playerInstance->GetPos();
        float playerRot = playerInstance->GetRot();
        sf::Vector2f projectileOffset = sf::Vector2f(shaftLength * cos((playerInstance->GetRot() - 90) * M_PI / 180.f), shaftLength * sin((playerInstance->GetRot() - 90) * M_PI / 180.f));

        switch (playerInstance->GetPlayerUpgrade()) {
        case PlayerUpgrade::None:
            newProjectile = new Projectile();
            playerInstance->AddCurrentProjectile(newProjectile);

            GameEngine::GameEngineMain::GetInstance()->AddEntity(newProjectile);

            newProjectile->SetAngleOfTravel(playerRot - 90.f);
            shaftLength = 25.f;

            newProjectile->SetPos(playerPos + projectileOffset);
            newProjectile->SetPlayerIndex(GetPlayerIndex());

            break;
        case PlayerUpgrade::Laser:
            for (int i = 0; i < 3; i++) {
                newProjectile = new LaserProjectile();
                playerInstance->AddCurrentProjectile(newProjectile);

                GameEngine::GameEngineMain::GetInstance()->AddEntity(newProjectile);

                newProjectile->SetAngleOfTravel(playerRot - 90.f - 15 + 15 * i);
                shaftLength = 25.f;
          
                newProjectile->SetPos(playerPos + projectileOffset);
                newProjectile->SetPlayerIndex(GetPlayerIndex());
            }

            playerInstance->SetPlayerUpgrade(PlayerUpgrade::None);
            break;
        }
    }
}

void PlayerShootComponent::SetPlayerIndex(int i) {
    playerIndex = i;
}
int PlayerShootComponent::GetPlayerIndex() {
    return playerIndex;
}

void PlayerShootComponent::SetBinding(int binding) {
    keyBinding = binding;
}