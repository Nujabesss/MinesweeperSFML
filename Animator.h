#pragma once
#include<iostream>
#include<string>
#include <SFML/Graphics.hpp>
#include "AssertMenager.h"
#include<vector>
#include<list>
class  Animator
{

public:
	struct Animation
	{
		std::string m_Name;
		std::string m_TextureName;
		std::vector<sf::IntRect>m_Frames;
		sf::Time m_Duration; //время проигрывания
		bool m_Looping; //выключение анмации
		Animation(std::string const& name, std::string const& TextureName, sf::Time const& Durationm, bool looping) :m_Name(name), m_TextureName(TextureName), m_Duration(Durationm), m_Looping(looping) {}
		void AddFrames(sf::Vector2i const& startFrom, sf::Vector2i const& framesize, unsigned int frames, unsigned int traccia) { //координаты и размер область ,количество кадров по горз и каличество горизонталей
			sf::Vector2i current = startFrom;
			for (unsigned int t = 0; t < traccia; t++) {
				for (unsigned int i = 0; i < frames; i++) {
					m_Frames.push_back(sf::IntRect(current.x, current.y, framesize.x, framesize.y)); //вектор последовательности координат
					current.x = framesize.x;

				}
				current.y = framesize.y;
				current.x = startFrom.x;
			}
		}
	};
	explicit Animator(sf::Sprite& sprite);
	Animator::Animation& CreatAnimation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool loop = false);
	void Update(sf::Time const& dt);
	bool SwitchAnimation(std::string const& name);
	std::string GetCurrentAnamationName() const;
	void restart();
	
	 bool getEndAnim() const {
		 return endAnim;
	 }

private:
	Animator::Animation* FindtAnimation(std::string const& name);
	void SwitchAnimation(Animator::Animation* animation);
	sf::Sprite& m_sprite;
	sf::Time m_CurrenTime;
	std::list<Animator::Animation> m_Animations;
	Animator::Animation* m_CurrentAnimation;
	bool endAnim = false;
};

 
 