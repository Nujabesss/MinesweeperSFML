#include"Animator.h"

Animator::Animator(sf::Sprite& sprite) :m_CurrentAnimation(nullptr), m_sprite(sprite) {}

Animator::Animation& Animator::CreatAnimation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool loop)
{
	m_Animations.emplace_back(name, textureName, duration, loop);
	//Если нет следующей анимации ,то использовать текущую анимцию
	if (m_CurrentAnimation == nullptr)SwitchAnimation(&m_Animations.back());
	return m_Animations.back();
}

void Animator::Update(sf::Time const& dt)
{
	if (m_CurrentAnimation == nullptr) return;
	m_CurrenTime += dt;
	float scaledTime = (m_CurrenTime.asSeconds() / m_CurrentAnimation->m_Duration.asSeconds());
	auto numFrames = static_cast<int>(m_CurrentAnimation->m_Frames.size());
	auto currentFrame = static_cast<int>(scaledTime * numFrames);
	if (m_CurrentAnimation->m_Looping)currentFrame%= numFrames;
	else 
		if (currentFrame >= numFrames) { currentFrame = numFrames - 1; endAnim = true; }
	m_sprite.setTextureRect(m_CurrentAnimation->m_Frames[currentFrame]); 

}

bool Animator::SwitchAnimation(std::string const& name)
{
	auto animation = FindtAnimation(name);
	if (animation != nullptr) {
		SwitchAnimation(animation);
		return true;
	}
	return false;
}

std::string Animator::GetCurrentAnamationName() const
{
	if (m_CurrentAnimation != nullptr)return m_CurrentAnimation->m_Name;
	return "";
}

void Animator::restart()
{
	m_CurrenTime = sf::Time::Zero;
	endAnim = false;
}

Animator::Animation* Animator::FindtAnimation(std::string const& name)
		
{	
	for (auto it = m_Animations.begin(); it != m_Animations.end(); ++it) {
		if (it->m_Name == name) return &*it;
	}

	return nullptr;
}

void Animator::SwitchAnimation(Animator::Animation* animation)
{

	//изменяем текстуру спрайта 
	if (animation != nullptr) {
		m_sprite.setTexture(AssertMenager::GetTexture(animation->m_TextureName));
	}
	m_CurrentAnimation = animation;
	m_CurrenTime = sf::Time::Zero;//Сброс времени 
}


