#pragma once

#include <map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Animation.h"

class Assets
{
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Sound> m_sounds;
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, Animation> m_animations;

public:
	void loadFromFile(const std::string& path);
	void loadAnimationFile(const std::string& path);

	void addTexture(std::string &name, std::string &path);
	void addSound(std::string &name, std::string &path);
	void addFont(std::string &name, std::string &path);
	void addAnimation(std::string name, Animation animation);

	sf::Texture & getTexture(std::string name) { return m_textures[name]; }
	sf::Sound & getSound(std::string name) { return m_sounds[name]; }
	sf::Font & getFont(std::string name) { return m_fonts[name]; }
	Animation & getAnimation(std::string name) { return m_animations[name]; }
};