
#include "Leaf.h"
#include "Resources.h"

void Leaf::Begin() {
	animation = Animation(.8f,
		{
			AnimFrame(0.6, Resources::textures["leaf1.png"]),
			AnimFrame(0.4, Resources::textures["leaf2.png"]),
			AnimFrame(0.2, Resources::textures["leaf3.png"]),
			AnimFrame(0.0, Resources::textures["leaf4.png"])
		}
	);
}

void Leaf::Update(float deltaTime) {
	animation.Update(deltaTime);
}

void Leaf::Render(Renderer& renderer) {
	renderer.Draw(animation.GetTexture(), position, sf::Vector2f(0.8, 0.8));
}