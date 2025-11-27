#include "Worm.h"
#include "Resources.h"
#include "Physics.h"
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

	//create a dynamic body for player
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world.CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};
	fixtureDef.density = 1;
	fixtureDef.friction = 0.0f;

	
	//smoother shape so collisions are smoother
	b2CircleShape circleShape{};
	circleShape.m_radius = 0.26f;
	circleShape.m_p.Set(0.0f, 0.0f);
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef);

	circleShape.m_p.Set(0.0f, 0.0f);
	//body->CreateFixture(&fixtureDef);

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(0.5f, 0.25f);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(0.4f, 0.1f, b2Vec2(0.0f, 0.24f), 0.0f);
	fixtureDef.isSensor = true;
	fixtureDef.userData = this;
	body->CreateFixture(&fixtureDef);
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

void Worm::OnBeginContact() 
{
	//std::cout << "On Ground" << std::endl;
	onGround++;
}

void Worm::OnEndContact()
{
	if (onGround > 0) {
		onGround--;
	}
}