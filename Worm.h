#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Renderer.h"
#include "Physics.h"
#include <Box2D.h>

class Worm
	: public ContactListener
{
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);
	int GetLeaves();

	//inherited from ContactListener
	virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) override;

	sf::Vector2f position{};
	float angle{};

	FixtureData fixtureData{};

	bool isDead = false;
	bool hasWon = false;

	size_t leaves{};


private:
	Animation runAnimation;
	Animation idleAnimation;
	sf::Texture textureToDraw{};

	b2Body* body;
	size_t onGround = 0;
	bool facingLeft = false;

	b2Fixture* groundFixture;

};

