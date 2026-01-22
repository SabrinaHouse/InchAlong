#include "Worm.h"
#include "Resources.h"
#include "Physics.h"
#include "Game.h"
#include "Enemy.h"
#include <iostream>

constexpr float M_PI = 22.0f / 7.0f;
float movementSpeed = 7.0f;
const float jumpVelocity = 7.0f;

void Worm::Begin() {
	runAnimation = Animation(0.8f,
		{
			AnimFrame(0.4, Resources::textures["EarthWormRun.png"]),
			AnimFrame(0.0, Resources::textures["EarthWorm.png"]),
		});

	idleAnimation = Animation(1.0f,
		{
			AnimFrame(0.5, Resources::textures["EarthWormIdle.png"]),
			AnimFrame(0.0, Resources::textures["EarthWorm.png"]),
		});

	fixtureData.listener = this;
	fixtureData.worm = this;
	fixtureData.type = FixtureDataType::Worm;

	//create a dynamic body for player
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};
	fixtureDef.density = 1;
	fixtureDef.friction = 0.0f;
	fixtureDef.userData = &fixtureData;

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(0.5f, 0.25f);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(0.4f, 0.1f, b2Vec2(0.0f, 0.24f), 0.0f);
	fixtureDef.isSensor = true;
	groundFixture = body->CreateFixture(&fixtureDef);
}

void Worm::Update(float deltaTime) 
{
	runAnimation.Update(deltaTime);
	idleAnimation.Update(deltaTime);

	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) //SPRINT
	{
		movementSpeed *= 2;
	}*/

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //LEFT
	{
		velocity.x -= movementSpeed;
		//body->ApplyForceToCenter(b2Vec2(-movementSpeed, 0.0f), true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //RIGHT
	{
		velocity.x += movementSpeed;
		//body->ApplyForceToCenter(b2Vec2(movementSpeed, 0.0f), true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && onGround 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) //JUMP 
	{
		velocity.y = -jumpVelocity;
	}

	//set texture to current animation frame
	textureToDraw = runAnimation.GetTexture();

	if (velocity.x < -0.02f) {
		facingLeft = true;
	}
	else if (velocity.x > 0.02f) {
		facingLeft = false;
	}
	else
	{
		textureToDraw = idleAnimation.GetTexture();
	}

	//set texture to falling/jumping when in air
	if (!onGround)
	{
		if (velocity.y > 0) {
			textureToDraw = Resources::textures["EarthWormFall.png"];
		}
		else if (velocity.y < 0) {
			textureToDraw = Resources::textures["EarthWormJump.png"];
		}
		
	}

	body->SetLinearVelocity(velocity);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180 / M_PI);
}

void Worm::Draw(Renderer& renderer) {
	renderer.Draw(textureToDraw, position, sf::Vector2f(facingLeft ? -1.0f : 1.0f, 0.5f));
}

int Worm::GetLeaves() {
	return leaves;
}

void Worm::OnBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData();

	if (!data) {
		return;
	}

	if (groundFixture == self && data->type == FixtureDataType::MapTile) {
		onGround++;
	}
	else if (groundFixture == self && data->type == FixtureDataType::Spike) {
		isDead = true;
	}
	else if (groundFixture == self && data->type == FixtureDataType::FinishLine) {
		hasWon = true;
	}
	else if(groundFixture == self && data->type == FixtureDataType::Object && data->object && data->object->tag == "leaf"){
		DeleteObject(data->object);
		leaves++;
	} 
	else if  (data->type == FixtureDataType::Object && data->object->tag == "enemy") {
		if (groundFixture == self) {
			Enemy* enemy = dynamic_cast<Enemy*>(data->object);
			if (enemy) {
				enemy->Die();
			}
			
		}
		else {
			isDead = true;
		}
		
	}
}

void Worm::OnEndContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData();

	if (!data) {
		return;
	}

	if (groundFixture == self && data->type == FixtureDataType::MapTile && onGround > 0) {
		onGround--;
	}
}