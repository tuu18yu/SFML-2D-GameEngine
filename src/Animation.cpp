#include "Animation.h"

Animation::Animation() 
{
	m_sprite = sf::Sprite();
}

Animation::Animation(const std::string& name, const sf::Texture& t)
	:m_name(name)
{
	m_sprite = sf::Sprite(t);
}

Animation::Animation(const std::string& name, const sf::Texture& t, std::size_t totalFrame, std::size_t speed)
	:m_name(name), m_totalFrame(totalFrame), m_speed(speed)
{
	m_sprite = sf::Sprite(t);
}

void Animation::update(int gameFrame)
{
	if (!m_repeat && m_hasPlayed && m_currentFrame == 0)
	{
		m_hasEnded = true;
	}

	if (m_hasEnded) 
	{ 
		m_hasPlayed = false;
		return; 
	}

	m_totalFrame == 1 ? m_currentFrame = 0 : m_currentFrame = (gameFrame / m_speed) % m_totalFrame;
	int left_pos = (int) m_position.x + (m_currentFrame * ((int)m_offset.x + (int) m_size.x));
	int top_pos = (int) m_offset.y + (int) m_position.y;
	sf::IntRect boundary{ left_pos, top_pos, (int) m_size.x, (int) m_size.y };
	m_sprite.setTextureRect(boundary);
}