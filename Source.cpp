#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Camera.h"
#include "Renderer.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Inch Along");
	sf::Clock deltaClock;
	Renderer renderer(window);

	window.setFramerateLimit(60);

	Begin(window);
	while (window.isOpen()) {
		//standardizes clock across computers
		float deltaTime = deltaClock.restart().asSeconds();

		// Event processing
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Request for closing the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.setView(camera.getView(window.getSize()));
		
		Update(deltaTime);

		window.clear();

		Render(renderer);

		window.display();
	}
	return 0;
}
