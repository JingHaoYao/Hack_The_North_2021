#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"

namespace Game {

    class Wall : public GameEngine::Entity
    {
    public:
        Wall();
        ~Wall();

    protected:
        GameEngine::SpriteRenderComponent* spriteRenderComponent;
        GameEngine::CollidableComponent* collidableComponent;
        GameEngine::SoundComponent* soundComponent;
    };

}