#include "Game.h"
#include "Resources.h"
#include "Map.h"
#include "Worm.h"
#include "Object.h"
#include "Physics.h"
#include <iostream>
#include <Box2D.h>
#include <filesystem>


sf::CircleShape circle(2.0f, 360u);
sf::Texture texture;

Map map(1.0f);
Camera camera(20.0f);
Worm worm;
std::vector<Object*> objects;

void Begin(const sf::Window& window)
{
	//file loader
	for (auto& file : std::filesystem::directory_iterator("./resources/textures/"))
	{
		if (file.is_regular_file() && file.path().extension() == ".png" || file.path().extension() == ".jpg")
		{
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	} 

	Physics::Init();

	//load map from image
	sf::Image image;
	image.loadFromFile("./resources/textures/map.png");
	worm.position = map.MapFromImage(image, objects);
	
	worm.Begin();
	for (auto& object : objects)
	{
		object->Begin();
	}

}
void Update(float deltaTime)
{
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