#include "Enemy.h"
#include "Resources.h"
#include "Game.h"
#include <iostream>

Enemy::~Enemy() {

}

void Enemy::Begin() {
	animation = Animation(0.5f,
		{
			AnimFrame(0.25f, Resources::textures["Ant1.png"]),
			AnimFrame(0.0f, Resources::textures["Ant2.png"]),
		});

	tag = "enemy";

	fixtureData.object = this;
	fixtureData.type = FixtureDataType::Object;

	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};
	fixtureDef.userData = &fixtureData;
	fixtureDef.density = 0;
	fixtureDef.friction = 0.0f;

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(0.75f, 0.375f);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);

	
}

void Enemy::Update(float deltaTime) {
	
	/*
	if (isDead)
	{
		destroyTimer += deltaTime;
		if (destroyTimer >= 3) {
			DeleteObject(this);
			return;
		}
	}*/

	animation.Update(deltaTime);

	b2Vec2 velocity = body->GetLinearVelocity();

	if (std::abs(velocity.x) <= 0.02f) {
		movement *= -1;
		facingLeft = !facingLeft;
	}

	velocity.x = movement;

	body->SetLinearVelocity(velocity);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / 3.14159f);
	
	}



void Enemy::Render(Renderer& renderer) {

	renderer.Draw(animation.GetTexture(), !isDead ? position : sf::Vector2f(position.x, position.y + 0.25), sf::Vector2f(facingLeft ? -1.5 : 1.5, isDead ? 0.375 : 0.75), angle);
}

void Enemy::Die() {
	//isDead = true;
	//body->SetUserData(0);
	//body = 0;
}
