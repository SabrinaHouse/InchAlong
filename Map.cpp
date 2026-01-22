#include "Map.h"
#include "Resources.h"
#include "Physics.h"
#include "Object.h"
#include "Leaf.h"
#include "Enemy.h"
#include <iostream>
#include <Box2D.h>

Map::Map(float cellSize)
	: cellSize(cellSize), grid()
{
}

//test map
void Map::CreateCheckerboard(size_t width, size_t height) 
{
	grid = std::vector(width, std::vector(height, 0 ));

	bool last = 0;
	for (auto& column : grid)
	{
		for (auto& cell : column) 
		{
			cell = !last;
			last = cell;
		}
		//alter pattern if the grid is even
		if (width % 2 == 0) {
			last = !last;
		}
	}
}

sf::Vector2f Map::MapFromImage(const sf::Image& image, std::vector<Object*>& objects) 
{
	//empty the map
	grid.clear();
	sf::Vector2u image_size = image.getSize();

	//std::cout << "Size x: " << image_size.x << " Size y: " << image_size.y << std::endl;
	grid = std::vector(image_size.x, std::vector(image_size.y, 0));

	sf::Vector2f wormPosition{};

	/*
	Map Color Key:
	Black = Grass Tile
	Blue = Dirt Tile
	Red = Worm
	Magenta = Spikes
	Green = Leaf
	Cyan = Ant
	Yellow = Win!
	*/

	//for every column in the array
	for (size_t x = 0; x < grid.size(); x++)
	{
		//for every item in the column
		for (size_t y = 0; y < grid[x].size(); y++)
		{
			sf::Color color = image.getPixel(x, y);
			Object* object = nullptr;

			if (color == sf::Color::Black)
			{
				grid[x][y] = 1;

				//create a static body for map tiles
				b2BodyDef bodyDef{};
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				b2Body* body = Physics::world->CreateBody(&bodyDef);
				b2PolygonShape shape{};
				shape.SetAsBox(cellSize / 2.0f, cellSize / 2.0f);

				FixtureData* fixtureData = new FixtureData();
				fixtureData->type = FixtureDataType::MapTile;
				fixtureData->mapX = x;
				fixtureData->mapY = y;

				b2FixtureDef fixtureDef{};
				fixtureDef.shape = &shape;
				fixtureDef.userData = fixtureData;
				body->CreateFixture(&fixtureDef);
			}
			else if (color == sf::Color::Blue) {
				grid[x][y] = 2;

				//create a static body for map tiles
				b2BodyDef bodyDef{};
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				b2Body* body = Physics::world->CreateBody(&bodyDef);
				b2PolygonShape shape{};
				shape.SetAsBox(cellSize / 2.0f, cellSize / 2.0f);

				FixtureData* fixtureData = new FixtureData();
				fixtureData->type = FixtureDataType::MapTile;
				fixtureData->mapX = x;
				fixtureData->mapY = y;

				b2FixtureDef fixtureDef{};
				fixtureDef.shape = &shape;
				fixtureDef.userData = fixtureData;
				body->CreateFixture(&fixtureDef);
			}
			else if (color == sf::Color::Magenta) {
				grid[x][y] = 3;

				//create a static body for map tiles
				b2BodyDef bodyDef{};
				//position is set slightly lower to account for the spikes being smaller than an actual tile
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize/1.15f);
				b2Body* body = Physics::world->CreateBody(&bodyDef);
				b2PolygonShape shape{};
				shape.SetAsBox(cellSize / 2.0f, cellSize / 2.0f);

				FixtureData* fixtureData = new FixtureData();
				fixtureData->type = FixtureDataType::Spike;
				fixtureData->mapX = x;
				fixtureData->mapY = y;

				b2FixtureDef fixtureDef{};
				fixtureDef.shape = &shape;
				fixtureDef.userData = fixtureData;
				body->CreateFixture(&fixtureDef);
			}
			else if(color == sf::Color::Yellow){
				grid[x][y] = 4;

				//create a static body for map tiles
				b2BodyDef bodyDef{};
				//position is set slightly lower to account for the spikes being smaller than an actual tile
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 1.15f);
				b2Body* body = Physics::world->CreateBody(&bodyDef);
				b2PolygonShape shape{};
				shape.SetAsBox(cellSize / 2.0f, cellSize / 2.0f);

				FixtureData* fixtureData = new FixtureData();
				fixtureData->type = FixtureDataType::FinishLine;
				fixtureData->mapX = x;
				fixtureData->mapY = y;

				b2FixtureDef fixtureDef{};
				fixtureDef.shape = &shape;
				fixtureDef.userData = fixtureData;
				fixtureDef.isSensor = true;
				body->CreateFixture(&fixtureDef);
			}
			else if (color == sf::Color::Red) {
				wormPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
			}
			else if (color == sf::Color::Green) {
				object = new Leaf();
			} 
			else if (color == sf::Color::Cyan) {
				object = new Enemy();
			}

			if (object)
			{
				object->position = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				objects.push_back(object);
			}
		}
	}

	return wormPosition;

}

void Map::Draw(Renderer& renderer)
{
	int x = 0;
	for (const auto& column : grid)
	{
		int y = 0;
		for (const auto& cell : column)
		{
			if (cell == 1)
			{
				renderer.Draw(Resources::textures["GrassTile.png"], sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize, cellSize));
			}
			else if (cell == 2)
			{
				renderer.Draw(Resources::textures["DirtTile.png"], sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize, cellSize));
			}
			else if (cell == 3)
			{
				renderer.Draw(Resources::textures["Spikes.png"], sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize, cellSize));
			}
			else if (cell == 4) {
				renderer.Draw(Resources::textures["FinishLine.png"], sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize, cellSize));
			}
			y++;
		}
		x++;
	}
}
