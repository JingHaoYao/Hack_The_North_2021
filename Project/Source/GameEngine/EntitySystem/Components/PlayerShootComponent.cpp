#define _USE_MATH_DEFINES
#include "PlayerShootComponent.h"
#include "Game/GameBoard.h"
#include "Game/Projectile.h"
#include "Game/LaserProjectile.h"
#include "Game/RocketProjectile.h"
#include "Game/BouncingBomb.h"
#include "GameEngine/GameEngineMain.h"
#include <SFML/Window/Keyboard.hpp>
#include <GameEngine\Util\TextureManager.h>
#include <cmath>
#include <math.h>
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
            if (playerPressDict[0] == 0) {
                playerPressDict[0] = 1;
                CreateProjectile();
            }
        }
        else {
            currentMachineGunThreshold = 0;
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
            currentMachineGunThreshold = 0;
            playerPressDict[1] = 0;
        }
        break;
    }

    if (currentMachineGunTimer < currentMachineGunThreshold && currentMachineGunThreshold != 0) {
        currentMachineGunTimer += GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
        fireGunTimer += GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
        float fireTimer = 0.05f * (currentMachineGunThreshold - currentMachineGunTimer);
        fireTimer = (fireTimer < 0.1f ? 0.1f : 0.5f * (currentMachineGunThreshold - currentMachineGunTimer));
        if (fireGunTimer >= fireTimer) {
            fireGunTimer = 0;
            Projectile* newProjectile = new Projectile();
            Game::Player* playerInstance = Game::GameBoard::getInstance()->GetPlayerByIndex(GetPlayerIndex());
            playerInstance->AddCurrentProjectile(newProjectile);
            sf::Vector2f projectileOffset = sf::Vector2f(shaftLength * cos((playerInstance->GetRot() - 90) * M_PI / 180.f), shaftLength * sin((playerInstance->GetRot() - 90) * M_PI / 180.f));

            GameEngine::GameEngineMain::GetInstance()->AddEntity(newProjectile);

            if (rand() % 2 + 1 == 1) {
                newProjectile->SetAngleOfTravel(playerInstance->GetRot() - 90.f + rand() % 10);
            }
            else {
                newProjectile->SetAngleOfTravel(playerInstance->GetRot() - 90.f - rand() % 10);
            }

            shaftLength = 25.f;

            newProjectile->SetPos(playerInstance->GetPos() + projectileOffset);
            newProjectile->SetPlayerIndex(GetPlayerIndex());
        }
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
            }
            break;
        case PlayerUpgrade::Bomb_State_2:
            playerInstance->GetCurrentProjectiles()[0]->ReClickAction();
            playerInstance->SetPlayerUpgrade(PlayerUpgrade::None);
            break;
        case PlayerUpgrade::MachineGun:
            currentMachineGunTimer = 0;
            currentMachineGunThreshold = 5;
            fireGunTimer = 0;


            playerInstance->SetPlayerUpgrade(PlayerUpgrade::None);
            break;
        case PlayerUpgrade::Rocket:
            if (playerInstance->GetCurrentProjectiles().size() <= 0) {
                RocketProjectile* newRocket = new RocketProjectile();
                newProjectile = newRocket;

                float max = 9999;
                for (auto var : Game::GameBoard::getInstance()->GetAllPlayers()) {
                    if (var != Game::GameBoard::getInstance()->GetPlayerByIndex(playerIndex)) {
                        newRocket->SetEntityToFollow(var);
                    }
                }
                playerInstance->AddCurrentProjectile(newProjectile);

                GameEngine::GameEngineMain::GetInstance()->AddEntity(newProjectile);

                newProjectile->SetAngleOfTravel(playerRot - 90.f);
                shaftLength = 25.f;

                newProjectile->SetPos(playerPos + projectileOffset);
                newProjectile->SetPlayerIndex(GetPlayerIndex());
            }
            break;
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