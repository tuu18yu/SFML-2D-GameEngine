#include "Assets.h"
#include <fstream>
#include <iostream>


void Assets::loadFromFile(const std::string& path)
{
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
		else if (type == "Texture")
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
	Vec2 offset, position, size;

	// note configuration file will be in the format of Type Name Path
	while (!animationFile.eof())
	{
		animationFile >> name >> textureName >> totalFrames >> speed >> offset.x >> offset.y >>
			position.x >> position.y >> size.x >> size.y;

		std::cout << name << " " << textureName << " " << totalFrames << " " << speed << " " << offset.x << " " << offset.y << " " <<
			position.x << " " << position.y << " " << size.x << " " << size.y << "\n";

		Animation temp{ name, m_textures[textureName], totalFrames, speed };
		temp.setOffset(offset.x, offset.y);
		temp.setPosition(position.x, position.y);
		temp.setSize(size.x, size.y);
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