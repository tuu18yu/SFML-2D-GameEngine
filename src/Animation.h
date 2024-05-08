#pragma once

#include "SFML/Graphics.hpp"
#include "Vec2.h"
#include <vector>

class Animation
{
	sf::Sprite		m_sprite;
	std::size_t		m_totalFrame = 1; // number of frames in the animation
	std::size_t		m_currentFrame = 0; // the current frame of the animation
	std::size_t		m_speed = 0; // after how many gameFrames, the animation move to next frame
	Vec2			m_size = { 1, 1 }; // texWidth/frameCount, texHeight
	Vec2			m_position = { 0, 0 }; // the position of target image from the sprite sheet
	Vec2			m_offset = { 0, 0 };
	Vec2			m_scale = { 1.f, 1.f };
	std::string		m_name = "none";
	bool			m_hasEnded = false;
	bool			m_hasPlayed = false;
	bool			m_repeat = true;


public:

	Animation();
	Animation(const std::string& name, const sf::Texture& t);
	Animation(const std::string& name, const sf::Texture& t, std::size_t totalFrame, std::size_t speed);

	void setTexture(const sf::Texture& t) { m_sprite.setTexture(t); }
	void setName(const std::string& name) { m_name = name; }
	void setTotalFrame(std::size_t totalFrame) { m_totalFrame = totalFrame; }
	void setSpeed(std::size_t speed) { m_speed = speed; }

	void update(int gameFrame);

	void setSize(float width, float height) { m_size = Vec2(width, height); };
	void setPosition(float x, float y) { m_position = Vec2(x, y); };
	void setOffset(float width, float height) { m_offset = Vec2(width, height); };
	void endAnimation(bool end) { m_hasEnded = end; };
	void setRepeat(bool isRepeated) { m_repeat = isRepeated; }
	void setScale(float x, float y) { m_scale = Vec2(x, y); }

	void setOrigin(float x, float y) { m_sprite.setPosition(x, y); }

	bool hasEnded() const { return m_hasEnded; };
	const Vec2& getSize() const { return m_size; };
	const Vec2& getScale() const { return m_scale; };
	const std::string& getName() const { return m_name; };
	sf::Sprite& getSprite() { return m_sprite; };
};