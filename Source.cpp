#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Camera.h"
#include "Renderer.h"
#include "Menu.h"


int main() {
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Inch Along");
	sf::Clock deltaClock;
	Renderer renderer(*window);

	window->setFramerateLimit(60);

	Begin(*window);

	//main menu
	Menu menu(camera, window);

	while (window->isOpen()) {
		//standardizes clock across computers
		float deltaTime = deltaClock.restart().asSeconds();

		// Event processing
		sf::Event event;
		while (window->pollEvent(event))
		{
			//Request for closing the window
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			//pause game / open menu
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				paused = !paused;
				inMenu = !inMenu;
				menu.PauseScreen(camera, window);
			}

			if (inMenu) {
				//selction moved up
				if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) ||
					(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)) {
					menu.moveUp();
				}

				//selection moved down
				if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) ||
					(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)) {
					menu.moveDown();
				}

				if (((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
					(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space))) {
					switch (menu.getPressedItem()) {
					case 0:
						//title
						break;
					case 1:
						//restart level
						if (wormDead) {
							Restart();
						}
						//restart whole game
						else if (gameComplete) {
							totalLeaves = 0;
							currentLevel = 1;
							Restart();
						}
						//unpause
						inMenu = false;
						paused = false;
						
						break;
					case 2:
						//quit
						window->close();
						break;
					case 3:
						//skip level
						//does nothing when the game is complete, no levels to skip to
						if (!gameComplete) {
							ChangeLevel();
						}
						break;
					}
				}

			}

		}

		window->setView(camera.getView(window->getSize()));

		if (!inMenu) {
			Update(deltaTime);
			window->clear();
			Render(renderer);
			window->setView(camera.GetUIView());
			RenderUI(renderer);
		}
		else {
			//change the text in the menu based on the state of the player
			if (wormDead) {
				menu.DeathScreen(camera, window);
			}
			else if (gameComplete) {
				menu.FinalScreen(camera, window, totalLeaves);
			}
			else if (wormWon) {
				menu.LevelUpScreen(camera, window, currentLevel);
			}

			menu.updatePosition(camera, window);
			window->clear();
			renderer.Draw(Resources::textures["sky.png"], camera.position, sf::Vector2f(camera.getViewSize().x * 1.5, camera.getViewSize().y * 1.5));
			menu.draw(window, renderer);
		}

		window->display();
	}
	return 0;
}
