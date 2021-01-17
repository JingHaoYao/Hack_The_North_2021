#define _USE_MATH_DEFINES
#include "PlayerShootComponent.h"

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
            if (playerPressDict[0] == 0) {
                playerPressDict[0] = 1;
                CreateProjectile();
            }
        }
        else {
            playerPressDict[0] = 0;
        }
        break;
    case 1:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            if (playerPressDict[1] == 0) {
                playerPressDict[1] = 1;
                CreateProjectile();
            }
        }
        else {
            playerPressDict[1] = 0;
        }
        break;
    }
}

void PlayerShootComponent::CreateProjectile() {
    Game::Player* playerInstance = Game::GameBoard::getInstance()->GetPlayerByIndex(GetPlayerIndex());
        Projectile* newProjectile = NULL;
        sf::Vector2f playerPos = playerInstance->GetPos();
        float playerRot = playerInstance->GetRot();
        sf::Vector2f projectileOffset = sf::Vector2f(shaftLength * cos((playerInstance->GetRot() - 90) * M_PI / 180.f), shaftLength * sin((playerInstance->GetRot() - 90) * M_PI / 180.f));

        switch (playerInstance->GetPlayerUpgrade()) {
        case PlayerUpgrade::None:
            if (playerInstance->GetCurrentProjectiles().size() <= 0) {
                newProjectile = new Projectile();
                playerInstance->AddCurrentProjectile(newProjectile);

                GameEngine::GameEngineMain::GetInstance()->AddEntity(newProjectile);

                newProjectile->SetAngleOfTravel(playerRot - 90.f);
                shaftLength = 25.f;

                newProjectile->SetPos(playerPos + projectileOffset);
                newProjectile->SetPlayerIndex(GetPlayerIndex());
            }

            break;
        case PlayerUpgrade::Laser:
            if (playerInstance->GetCurrentProjectiles().size() <= 0) {
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
            }
            break;
        case PlayerUpgrade::Bomb:
            if (playerInstance->GetCurrentProjectiles().size() <= 0) {
                newProjectile = new BouncingBomb();
                playerInstance->AddCurrentProjectile(newProjectile);

                GameEngine::GameEngineMain::GetInstance()->AddEntity(newProjectile);

                newProjectile->SetAngleOfTravel(playerRot - 90.f);
                shaftLength = 25.f;

                newProjectile->SetPos(playerPos + projectileOffset);
                newProjectile->SetPlayerIndex(GetPlayerIndex());

                playerInstance->SetPlayerUpgrade(PlayerUpgrade::Bomb_State_2);
                break;
            }
        case PlayerUpgrade::Bomb_State_2:
            playerInstance->GetCurrentProjectiles()[0]->ReClickAction();
            playerInstance->SetPlayerUpgrade(PlayerUpgrade::None);
            break;
        }
        return newProjectile;
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