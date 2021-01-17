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
    enum PlayerUpgrade {
        None = 0,
        Rocket = 1,
        Bomb = 2,
        Laser = 3,
        MachineGun = 4,
        Bomb_State_2 = 5,
        Count
    };

    class Projectile;

    class Player : public GameEngine::Entity
    {
    public:
        Player(GameEngine::eTexture::type, int);
        ~Player();
        
        std::vector<Projectile*> GetCurrentProjectiles();
        void AddCurrentProjectile(Projectile*);
        void RemoveProjectile(Projectile*);
        void ClearPlayerProjectiles();
        void PlayerDied(); //pepesad
        void SetPlayerUpgrade(PlayerUpgrade);
        PlayerUpgrade GetPlayerUpgrade();

    protected:
        GameEngine::SpriteRenderComponent* spriteRenderComponent;
        GameEngine::PlayerCollisionComponent* collidableComponent;
        GameEngine::SoundComponent* soundComponent;
        GameEngine::PlayerMovementComponent* playerMovementComponent;
        GameEngine::PlayerShootComponent* playerShootComponent;
        std::vector<Projectile*> currentProjectiles;
        PlayerUpgrade currentPlayerUpgrade;
        int playerNumber;

        void Update();
    };

}


