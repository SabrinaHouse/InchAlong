#include "Leaf.h"
#include "Resources.h"
#include <iostream>


Leaf::~Leaf() {
	Physics::world->DestroyBody(body);
}

void Leaf::Begin() {
	animation = Animation(.8f,
		{
			AnimFrame(0.6, Resources::textures["leaf1.png"]),
			AnimFrame(0.4, Resources::textures["leaf2.png"]),
			AnimFrame(0.2, Resources::textures["leaf3.png"]),
			AnimFrame(0.0, Resources::textures["leaf4.png"])
		}
	);

	tag = "leaf";

	b2BodyDef bodyDef{};
	bodyDef.position.Set(position.x , position.y);
	b2Body* body = Physics::world->CreateBody(&bodyDef);
	b2PolygonShape shape{};
	shape.SetAsBox(0.4, 0.4);

	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Object;
	fixtureData->object = this;

	b2FixtureDef fixtureDef{};
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = true;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);
}

void Leaf::Update(float deltaTime) {
	animation.Update(deltaTime);
}

void Leaf::Render(Renderer& renderer) {
	renderer.Draw(animation.GetTexture(), position, sf::Vector2f(0.8, 0.8));
}