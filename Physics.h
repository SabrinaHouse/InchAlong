#pragma once
#include <Box2D.h>
#include "Renderer.h"


class MyDebugDraw;
class Worm;
class Object;

class ContactListener
{
public:
	virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) = 0;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) = 0;
};

enum class FixtureDataType
{
	Worm,
	MapTile,
	Spike,
	Object,
	FinishLine
};

struct FixtureData
{
	ContactListener* listener;
	FixtureDataType type;

	union {
		Worm* worm;
		struct { int mapX, mapY; };
		Object* object;
	};
	
};

class Physics
{
public:
	static void Init();
	static void Update(float deltaTime);
	static void DebugDraw(Renderer& renderer);

	static b2World* world;
	static MyDebugDraw* debugDraw;
};

