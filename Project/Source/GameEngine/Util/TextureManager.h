#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,

			Basic_Projectile = 0,
			Bomb_Projectile = 1,
			Crate_Bomb = 2,
			Crate_Laser = 3,
			Crate_Machine_Gun = 4,
			Create_Rocket = 5,
			Rocket_Projectile = 6,
			Tank_Blue = 7,
			Tank_Green = 8,
			Tank_Red = 9,
			Tank_Yellow = 10,
			Count,
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		return "UnknownTexType";
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture);
}

