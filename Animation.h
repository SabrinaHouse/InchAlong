#pragma once

#include <SFML/Graphics.hpp>

struct AnimFrame
{
	AnimFrame(float time = 0, sf::Texture texture = sf::Texture()) : time(time), texture(texture) 
	{

	}

	float time = 0;
	sf::Texture texture{};
};

class Animation
{
public:
	Animation(float length = 0, std::vector<AnimFrame> frames = {});
	void Update(float deltaTime);

	sf::Texture GetTexture();

private:
	float time = 0;
	float length;
	std::vector<AnimFrame> frames;
};

