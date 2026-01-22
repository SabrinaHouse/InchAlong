#pragma once
#include "Object.h"
#include "Physics.h"
#include "Animation.h"

class Leaf :
	public Object
{
public:
	~Leaf();

	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& renderer) override;

	b2Body* body;
private:
	Animation animation;
};

