#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/Util/TextureManager.h"

namespace Game {

    class Player : public GameEngine::Entity
    {
    public:
        Player(GameEngine::eTexture::type);

        ~Player();

    protected:
        GameEngine::SpriteRenderComponent* spriteRenderComponent;
        GameEngine::CollidableComponent* collidableComponent;
        GameEngine::SoundComponent* soundComponent;
        void Update();
    };

}


