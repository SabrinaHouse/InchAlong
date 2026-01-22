#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Camera.h"
#include "Object.h"

extern Camera camera;
extern bool paused;
extern bool inMenu;
extern bool wormDead;
extern bool wormWon;
extern bool gameComplete;

extern int currentLevel;
extern int totalLeaves;


void Begin(const sf::Window& window);
void Update(float deltaTime);
void Restart();
void Render(Renderer& renderer);
void RenderUI(Renderer& renderer);

void DeleteObject(Object* object);
void ChangeLevel();