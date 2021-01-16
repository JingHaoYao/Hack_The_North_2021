#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"

namespace Game {

    class Wall : public GameEngine::Entity
    {
    public:
        Wall(int, int, GameEngine::eTexture::type);
        ~Wall();
        int GetPosX();
        void SetPosX(int);
        int GetPosY();
        void SetPosY(int);

    protected:
        int posX;
        int posY;
        GameEngine::SpriteRenderComponent* spriteRenderComponent;
        GameEngine::CollidableComponent* collidableComponent;
    };

}