#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}


void AnimationManager::InitStaticGameAnimations()
{
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::Explosion_0,
			eTexture::Explosion_0,
			sf::Vector2i(0, 0),
			8,
			12)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::Bomb_Blink,
			eTexture::Bomb_Blink,
			sf::Vector2i(0, 0),
			4,
			12)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::Explosion_1,
			eTexture::Explosion_1,
			sf::Vector2i(0, 0),
			8,
			12)
	);
}


void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}
