#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Camera.h"
#include "Renderer.h";
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
public:
	Menu(Camera camera, sf::RenderWindow* window);
	~Menu();

	void PauseScreen(Camera camera, sf::RenderWindow* window);
	void DeathScreen(Camera camera, sf::RenderWindow* window);
	void LevelUpScreen(Camera camera, sf::RenderWindow* window, int currentLevel);
	void FinalScreen(Camera camera, sf::RenderWindow* window, int totalLeaves);
	
	void draw(sf::RenderWindow* window, Renderer& renderer);
	void updatePosition(Camera camera, sf::RenderWindow* window);
	void moveUp();
	void moveDown();
	const int getPressedItem()
	{
		return selectedItemIndex;
	}

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text* menu[MAX_NUMBER_OF_ITEMS];
};

