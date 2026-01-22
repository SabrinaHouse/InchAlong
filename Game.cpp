#include "Game.h"
#include "Resources.h"
#include "Map.h"
#include "Worm.h"
#include "Object.h"
#include "Physics.h"
#include "Menu.h"
#include <iostream>
#include <Box2D.h>
#include <filesystem>


sf::CircleShape circle(2.0f, 360u);
sf::Texture texture;

Map map(1.0f);
Camera camera(20.0f);
Worm worm;
std::vector<Object*> objects;

//game and player state bools
bool paused{};
bool inMenu{};
bool wormDead{};
bool wormWon{};
bool gameComplete{};

int totalLeaves{};

sf::Font font{};
sf::Text leavesText("", font);

sf::Image mapImage;
int currentLevel = 1;
int maxLevel = 5;

sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));

sf::Text levelsText("", font);


void Restart() {
	Physics::Init();
	objects.clear();
	
	//load map from image based on level
	switch (currentLevel) {
	case 1: 
		mapImage.loadFromFile("./resources/textures/Level1.png");
		break;
	case 2:
		mapImage.loadFromFile("./resources/textures/Level2.png");
		break;
	case 3:
		mapImage.loadFromFile("./resources/textures/Level3.png");
		break;
	case 4:
		mapImage.loadFromFile("./resources/textures/Level4.png");
		break;
	case 5:
		mapImage.loadFromFile("./resources/textures/Level5.png");
		break;
	case 6:
		gameComplete = true;
		return;
		break;
	}

	worm = Worm();
	worm.position = map.MapFromImage(mapImage, objects);
	worm.Begin();

	worm.isDead = false;
	wormDead = false;

	worm.hasWon = false;
	wormWon = false;

	gameComplete = false;


	for (auto& object : objects)
	{
		object->Begin();
	}

}


void Begin(const sf::Window& window)
{
	//file loader
	for (auto& file : std::filesystem::directory_iterator("./resources/textures/"))
	{
		if (file.is_regular_file() && file.path().extension() == ".png" || file.path().extension() == ".jpg")
		{
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
		else if (file.is_regular_file() && (file.path().extension() == ".ttf")) {
			if (!Resources::fonts[file.path().filename().string()].loadFromFile(file.path().string()))
				std::abort();
		}
	}

	font = Resources::fonts["StackedPixel.ttf"];
	leavesText.setFillColor(sf::Color::White);
	leavesText.setOutlineColor(sf::Color::Black);
	leavesText.setOutlineThickness(1.0f);
	leavesText.setScale(0.1f, 0.1f);

	levelsText.setFillColor(sf::Color::White);
	levelsText.setOutlineColor(sf::Color::Black);
	levelsText.setOutlineThickness(1.0f);
	levelsText.setScale(0.1f, 0.1f);

	Restart();

	paused = true;
	inMenu = true;
}

void Update(float deltaTime)
{
	if (worm.isDead) {
		wormDead = true;
		paused = true;
		inMenu = true;
	}

	if (worm.hasWon) {
		totalLeaves += worm.GetLeaves();
		ChangeLevel();
		wormWon = true;
		paused = true;
		inMenu = true;
	}

	if (paused) {
		return;
	}

	Physics::Update(deltaTime);
	worm.Update(deltaTime);

	for (auto& object : objects)
	{
		object->Update(deltaTime);

	}

	camera.position = worm.position;


}
void Render(Renderer& renderer)
{
	renderer.Draw(Resources::textures["sky.png"], worm.position, 
		sf::Vector2f(camera.getViewSize().x * 1.5, camera.getViewSize().y * 1.5));
	map.Draw(renderer);
	worm.Draw(renderer);

	for (auto& object : objects)
	{
		object->Render(renderer);
	}

	Physics::DebugDraw(renderer);
}

void RenderUI(Renderer& renderer)
{
	leavesText.setPosition(-camera.getViewSize() / 2.0f + sf::Vector2f(2.0f, 5.0f));
	leavesText.setString("Leaves: " + std::to_string(worm.GetLeaves() + totalLeaves));
	//leavesText.setString("Leaves: " + std::to_string(worm.totalLeaves));


	levelsText.setPosition(-camera.getViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
	levelsText.setString("Level: " + std::to_string(currentLevel));
	
	renderer.target.draw(levelsText);
	renderer.target.draw(leavesText);
}


void DeleteObject(Object* object) {
	const auto& it = std::find(objects.begin(), objects.end(), object);
	if (it != objects.end()) {
		delete *it;
		objects.erase(it);
	}
}

void ChangeLevel() {
	//check theres a level to skip to
	if (currentLevel + 1 <= maxLevel) {
		currentLevel++;
		paused = false;
		inMenu = false;
		Restart();
	}
	//if player is on last level, end the game
	else {
		gameComplete = true;
	}
	
}