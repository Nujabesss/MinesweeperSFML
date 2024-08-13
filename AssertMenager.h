#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include<map>
#include<assert.h>
class AssertMenager
{
public:
	AssertMenager();
	
	static sf::Texture& GetTexture(std::string const& filename);
	static sf::SoundBuffer& GetSound(std::string const& filename);
	static sf::Font& GetFont(std::string const& filename);

private:

	std::map<std::string, sf::Texture>m_Textures;
	std::map<std::string, sf::SoundBuffer>m_Sound;
	std::map<std::string, sf::Font>m_Fonts;
	static AssertMenager* sInstance; 
};

