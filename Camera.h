#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(float zoomLevel = 5.0f);
	sf::Vector2f getViewSize();
	sf::View getView(sf::Vector2u windowSize);
	sf::View GetUIView();

	float zoomLevel;
	sf::Vector2f position;

private:
	sf::Vector2f viewSize{};
};

