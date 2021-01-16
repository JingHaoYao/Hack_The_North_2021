#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/EntitySystem/Components/PlayerShootComponent.h"

namespace Game {

    class Projectile : public GameEngine::Entity
    {
    public:
        Projectile(GameEngine::eTexture::type);
        ~Projectile();

        void SetAngleOfTravel(float);
        float GetAngleOfTravel();

    protected:
        int keybinding;
        float projectileSpeed;
        float angleOfTravel;
        float duration;
        GameEngine::SpriteRenderComponent* spriteRenderComponent;
        GameEngine::CollidableComponent* collidableComponent;
        GameEngine::SoundComponent* soundComponent;
        GameEngine::PlayerShootComponent* playerShootComponent;
        void Update();
    };
    
}