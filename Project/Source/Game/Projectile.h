#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/PlayerProjectileCollisionComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/EntitySystem/Components/PlayerShootComponent.h"

namespace Game {

    class Projectile : public GameEngine::Entity
    {
    public:
        Projectile(GameEngine::eTexture::type);
        Projectile();
        ~Projectile();

        void SetAngleOfTravel(float);
        float GetAngleOfTravel();
        void SetDuration(float);
        float GetDuration();
        void SetTimeElapsed(float);
        float GetTimeElapsed();
        bool HasLeftPlayerHitbox();
        void FlagPlayerHitbox();
        int GetPlayerIndex();
        void SetPlayerIndex(int);

    protected:
        int keybinding;
        float projectileSpeed;
        float angleOfTravel;
        float duration;
        float timeElapsed;
        bool leftPlayerHitbox;
        int playerIndex;

        GameEngine::SpriteRenderComponent* spriteRenderComponent;
        GameEngine::PlayerProjectileCollisionComponent* collidableComponent;
        GameEngine::SoundComponent* soundComponent;
        void Update();
    };

}