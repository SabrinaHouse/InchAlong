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

	//inherited from ContactListener
	virtual void OnBeginContact() override;
	virtual void OnEndContact() override;

	sf::Vector2f position{};
	float angle{};

private:
	Animation runAnimation;
	Animation idleAnimation;
	sf::Texture textureToDraw{};

	b2Body* body;
	size_t onGround = 0;
	bool facingLeft = false;
};

