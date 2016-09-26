#include "GameComponent.h"
#include <iostream>
using namespace Game1;

GameComponent::GameComponent(void)
{
	std::cout << "Base class constructor" << std::endl;
	position = glm::vec2(0.0f);
	look = glm::vec2(0.0f, 1.0f);
	rotation = 0.0f;
	speed = 0.0f;
}


GameComponent::~GameComponent(void)
{
	std::cout << "Base class destructor" << std::endl;
}

bool GameComponent::Initialise()
{
	return true;
}

void GameComponent::Update(float timeDelta)
{

}

void GameComponent::Draw()
{

}

void GameComponent::Cleanup()
{

}
