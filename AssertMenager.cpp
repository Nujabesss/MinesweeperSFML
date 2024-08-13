#include "AssertMenager.h"
AssertMenager* AssertMenager::sInstance = nullptr;
AssertMenager::AssertMenager()
{
	assert(sInstance == nullptr);
	sInstance = this;
}



sf::Texture& AssertMenager::GetTexture(std::string const& filename)
{
	auto& texMap = sInstance->m_Textures;
	auto pairFound = texMap.find(filename);
	if (pairFound != texMap.end()) {
		return pairFound->second;
	}
	else
	{
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

sf::SoundBuffer& AssertMenager::GetSound(std::string const& filename)
{
	auto& sBufferMap = sInstance->m_Sound;
	auto pairFound = sBufferMap.find(filename);
	if (pairFound != sBufferMap.end()) {
		return pairFound->second;
	}
	else
	{
		auto& sBuffer = sBufferMap[filename];
		sBuffer.loadFromFile(filename);
		return sBuffer;
	}
}

sf::Font& AssertMenager::GetFont(std::string const& filename)
{
	auto& sFonts = sInstance->m_Fonts;
	auto pairFound = sFonts.find(filename);
	if (pairFound != sFonts.end()) {
		return pairFound->second;
	}
	else
	{
		auto& Fonts = sFonts[filename];
		Fonts.loadFromFile(filename);
		return Fonts;
	}
}
