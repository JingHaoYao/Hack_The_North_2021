#pragma once
#include "GameEngine/EntitySystem/Component.h"

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

    protected:
        int keyBinding;
        float projectileSpeed;
        float shaftLength;
        int playerIndex;

        void CreateProjectile();
    };
}