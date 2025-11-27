#pragma once
#include <vector>
#include "Renderer.h"
#include "Object.h"
#include <SFML/Graphics.hpp>


class Map
{
public:
	Map(float cellSize = 30.0f);
	void CreateCheckerboard(size_t width, size_t height);
	void Draw(Renderer& renderer);
	//take an image and turn it into your map
	sf::Vector2f MapFromImage(const sf::Image& image, std::vector<Object*>& objects);

	std::vector<std::vector<int>> grid;
	float cellSize;
};

