#include "Assets.h"
#include <fstream>
#include <iostream>


void Assets::loadFromFile(const std::string& path)
{
	if (path == "NONE")
	{
		return;
	}
	std::ifstream assetFile(path);
	std::string type, name, fPath;
	// note configuration file will be in the format of Type Name Path
	while (!assetFile.eof())
	{
		assetFile >> type >> name >> fPath;
		std::cout << type << " " << name << " " << fPath << "\n";

		if (type == "Texture")
		{
			addTexture(name, fPath);
		}
		else if (type == "Sound")
		{
			addSound(name, fPath);
		}
		else if (type == "Font")
		{
			addFont(name, fPath);
		}
		else if (type == "Animation")
		{
			loadAnimationFile(fPath);
		}
	}

	std::cout << "done asset upload\n";

}

void Assets::loadAnimationFile(const std::string& path)
{
	std::ifstream animationFile(path);
	std::string name, textureName;
	std::size_t totalFrames, speed;
	Vec2 offset, position, size, scale;

	// note configuration file will be in the format of Type Name Path
	while (!animationFile.eof())
	{
		animationFile >> name >> textureName >> totalFrames >> speed >> offset.x >> offset.y >>
			position.x >> position.y >> size.x >> size.y >> scale.x >> scale.y;

		std::cout << name << " " << textureName << " " << totalFrames << " " << speed << " " << offset.x << " " << offset.y << " " <<
			position.x << " " << position.y << " " << size.x << " " << size.y << " " << scale.x << " " << scale.y << "\n";

		Animation temp{ name, m_textures[textureName], totalFrames, speed };
		temp.setOffset(offset.x, offset.y);
		temp.setPosition(position.x, position.y);
		temp.setSize(size.x, size.y);
		temp.setOrigin(size.x / 2, size.y / 2);
		temp.setScale(scale.x, scale.y);

		addAnimation(name, temp);
	}

	std::cout << "done animation upload\n";

}

void Assets::addTexture(std::string & name, std::string & path)
{
	sf::Texture texture;
	texture.loadFromFile(path);

	m_textures[name] = texture;
}

void Assets::addSound(std::string& name, std::string& path)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile(path);
	
	sf::Sound sound;
	sound.setBuffer(buffer);

	m_sounds[name] = sound;
}

void Assets::addFont(std::string& name, std::string& path)
{
	sf::Font font;
	font.loadFromFile(path);

	m_fonts[name] = font;
}

void Assets::addAnimation(std::string name, Animation animation)
{
	animation.setName(name);
	m_animations[name] = animation;
}

void Assets::clear()
{
	m_textures.clear();
	m_sounds.clear();
	m_fonts.clear();
	m_animations.clear();
}