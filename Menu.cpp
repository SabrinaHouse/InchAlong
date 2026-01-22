#include "Menu.h"

Menu::Menu(Camera camera, sf::RenderWindow* window) {

	selectedItemIndex = 0;
	sf::View cameraView = camera.getView(window->getSize());
	font = Resources::fonts["StackedPixel.ttf"];
	sf::FloatRect bounds;
	
	//set style
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i] = new sf::Text("", font);
		menu[i]->setFillColor(sf::Color::White);
		menu[i]->setOutlineColor(sf::Color::Black);
		menu[i]->setOutlineThickness(1);
		menu[i]->setScale(0.075f, 0.075f);
	}

	//title
	menu[0]->setString("Inch Along");
	//make title bigger
	menu[0]->setScale(0.1f, 0.1f);

	//play button
	menu[1]->setString("Play");

	//quit button
	menu[2]->setString("Quit");

	//highscore display
	menu[3]->setString("Skip Level");

	//set positions
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.width  / 2, bounds.height / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS + 1) * (-1 + i)) - 4 });
	}
}

Menu::~Menu() {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		delete menu[i];
	}
}

void Menu::PauseScreen(Camera camera, sf::RenderWindow* window) {
	sf::FloatRect bounds;
	sf::View cameraView = camera.getView(window->getSize());


	menu[0]->setString("Paused");
	menu[1]->setString("Resume");
	menu[3]->setString("Skip Level");


	//set positions
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.width / 2, bounds.height / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS + 1) * (-1 + i)) - 4 });
	}

}

void Menu::DeathScreen(Camera camera, sf::RenderWindow* window) {
	sf::FloatRect bounds;
	sf::View cameraView = camera.getView(window->getSize());


	menu[0]->setString("You Died!");
	menu[1]->setString("Try Again");
	menu[3]->setString("Skip Level");


	//set positions
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.width / 2, bounds.height / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS + 1) * (-1 + i)) - 4 });
	}

}

void Menu::LevelUpScreen(Camera camera, sf::RenderWindow* window, int currentLevel) {
	sf::FloatRect bounds;
	sf::View cameraView = camera.getView(window->getSize());


	menu[0]->setString("Level " + std::to_string(currentLevel));
	menu[1]->setString("Play");
	menu[3]->setString("Skip Level");


	//set positions
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.width / 2, bounds.height / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS + 1) * (-1 + i)) - 4 });
	}
}

void Menu::FinalScreen(Camera camera, sf::RenderWindow* window, int totalLeaves) {
	sf::FloatRect bounds;
	sf::View cameraView = camera.getView(window->getSize());


	menu[0]->setString("You Won Inch Along");
	menu[1]->setString("Play Again");
	menu[3]->setString("Your Score: " + std::to_string(totalLeaves));


	//set positions
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.width / 2, bounds.height / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS + 1) * (-1 + i)) - 4 });
	}
}


void Menu::updatePosition(Camera camera, sf::RenderWindow* window) {
	sf::View cameraView = camera.getView(window->getSize());
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS) * (-1 + i)) - 3 });
	}
}

void Menu::draw(sf::RenderWindow* window, Renderer& renderer) {

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window->draw(*menu[i]);
	}
}

void Menu::moveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex]->setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex]->setFillColor(sf::Color::Red);
	}
}
void Menu::moveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex]->setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex]->setFillColor(sf::Color::Red);
	}
}