#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
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
			Explosion_0 = 11,
			Explosion_0_Base = 12,

			Count,
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture) {
			case eTexture::Basic_Projectile: return "basic_projectile.png";
			case eTexture::Bomb_Projectile: return "bomb_projectile.png";
			case eTexture::Crate_Bomb: return "crate_bomb.png";
			case eTexture::Crate_Laser: return "crate_laser.png";
			case eTexture::Crate_Machine_Gun: return "crate_machine_gun.png";
			case eTexture::Create_Rocket: return "crate_rocket.png";
			case eTexture::Rocket_Projectile: return "rocket_projectile.png";
			case eTexture::Tank_Blue: return "tank_blue.png";
			case eTexture::Tank_Green: return "tank_green.png";
			case eTexture::Tank_Red: return "tank_red.png";
			case eTexture::Tank_Yellow: return "tank_yellow.png";
			case eTexture::Explosion_0: return "explosion_0.png";
			case eTexture::Explosion_0_Base: return "explosion_0_base.png";
		}
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

