#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/PlayerCollisionComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/EntitySystem/Components/PlayerMovementComponent.h"
#include "GameEngine/EntitySystem/Components/PlayerShootComponent.h"
#include "GameEngine/Util/TextureManager.h"
#include "Game/Projectile.h"

namespace Game {
    class Projectile;

    class Player : public GameEngine::Entity
    {
    public:
        Player(GameEngine::eTexture::type, int);
        ~Player();
        
        Projectile* GetCurrentProjectile();
        void SetCurrentProjectile(Projectile*);

    protected:
        GameEngine::SpriteRenderComponent* spriteRenderComponent;
        GameEngine::PlayerCollisionComponent* collidableComponent;
        GameEngine::SoundComponent* soundComponent;
        GameEngine::PlayerMovementComponent* playerMovementComponent;
        GameEngine::PlayerShootComponent* playerShootComponent;
        Projectile* currentProjectile;

        void Update();
    };

}


