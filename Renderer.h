#pragma once
#include <SFML/Graphics.hpp>

class Renderer
{
public:
	Renderer(sf::RenderTarget& target);
	//passing by reference is more efficient
	//const because none of these values should be changing
	//you cannont draw on a constant -> render target cant be a const
	void Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f size, float angle = 0);
	
	sf::RenderTarget& target;

private:
	sf::Sprite sprite{};
	
};

