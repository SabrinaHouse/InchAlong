#pragma once
#include "Animation.h"
#include "Object.h"
#include "Physics.h"

class Enemy
	: public Object
{
public:
	~Enemy();

	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& renderer) override;

	void Die();



private:
	Animation animation{};
	float movement = 5.0f;
	bool facingLeft = true;

	float destroyTimer = 0;
	bool isDead = false; 

	b2Body* body{};
	FixtureData fixtureData{};
};

