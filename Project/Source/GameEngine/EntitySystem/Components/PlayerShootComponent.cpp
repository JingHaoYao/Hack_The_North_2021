#define _USE_MATH_DEFINES
#include "PlayerShootComponent.h"
#include "Game/GameBoard.h"
#include "Game/Projectile.h"
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
    }
}

void PlayerShootComponent::CreateProjectile() {
    Game::Player* playerInstance = Game::GameBoard::getInstance()->GetPlayerByIndex(GetPlayerIndex());
    if (playerInstance->GetCurrentProjectile() == NULL) {
        GameEngine::eTexture::type sprite = GameEngine::eTexture::type::Basic_Projectile;
        Projectile* newProjectile = new Projectile(sprite);
        playerInstance->SetCurrentProjectile(newProjectile);
        GameEngine::GameEngineMain::GetInstance()->AddEntity(newProjectile);

        sf::Vector2f playerPos = playerInstance->GetPos();
        float playerRot = playerInstance->GetRot();

        newProjectile->SetAngleOfTravel(playerRot - 90.f);
        shaftLength = 25.f;
        sf::Vector2f projectileOffset = sf::Vector2f(shaftLength * cos(newProjectile->GetAngleOfTravel() * M_PI / 180.f), shaftLength * sin(newProjectile->GetAngleOfTravel() * M_PI / 180.f));

        newProjectile->SetPos(playerPos + projectileOffset);
        newProjectile->SetSize(sf::Vector2f(13.f, 13.f));
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