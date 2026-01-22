#include "Camera.h"

Camera::Camera(float zoomLevel)
	: zoomLevel(zoomLevel)
{
}

sf::Vector2f Camera::getViewSize() {
	return viewSize;
}


sf::View Camera::getView(sf::Vector2u windowSize)
{
	float aspect = (float)windowSize.x / (float)windowSize.y;
	if (aspect < 1.0f)
		viewSize = sf::Vector2f(zoomLevel, zoomLevel / aspect);
	else
		viewSize = sf::Vector2f(zoomLevel * aspect, zoomLevel);

	return sf::View(position, viewSize);
}

sf::View Camera::GetUIView() {
	float aspect = viewSize.x / viewSize.y;
	viewSize = sf::Vector2f(100, 100 / aspect);
	return sf::View(sf::Vector2f(), viewSize);
}