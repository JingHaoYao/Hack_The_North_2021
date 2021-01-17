#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include <map>

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