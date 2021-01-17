#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include <map>
#include "Game/GameBoard.h"
#include "Game/Projectile.h"
#include "Game/LaserProjectile.h"
#include "Game/BouncingBomb.h"
#include "GameEngine/GameEngineMain.h"
#include <SFML/Window/Keyboard.hpp>
#include <GameEngine\Util\TextureManager.h>
#include <cmath>
#include "Game/Player.h"

namespace GameEngine
{
    class PlayerShootComponent : public GameEngine::Component
    {
    public:
        PlayerShootComponent();
        ~PlayerShootComponent();

        virtual void Update() override;
        void SetPlayerIndex(int);
        int GetPlayerIndex();
        void SetBinding(int);

    protected:
        int keyBinding;
        float projectileSpeed;
        float shaftLength;
        int playerIndex;
        std::map<int, int> playerPressDict;

        void CreateProjectile();
    };
}