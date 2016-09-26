#include "Bullet.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

using namespace Game1;
using namespace std;

Bullet::Bullet(void) : GameComponent()
{
	position = glm::vec2(100, 100);
	look = glm::vec2(0, -1);
	speed = 50.0f;
	isOutOfBounds = false;
	std::cout << "Bullet class Constructor" << std::endl;
}

Bullet::Bullet(glm::vec2 position, glm::vec2 look, float speed) : GameComponent()
{
	this->position = position;
	this->look = look;
	this->speed = speed;
	std::cout << "Bullet class Constructor" << std::endl;
}

bool Bullet::Initialise()
{
	SDL_Surface * temp = NULL;
	temp = SDL_LoadBMP("bullet.bmp");

	if (temp == nullptr)
	{
		cout << "Could not load player texture" << endl;
		return false;
	}

	texture = SDL_CreateTextureFromSurface(Game::Instance()->renderer, temp);
	SDL_FreeSurface(temp);

	return true;
}


Bullet::~Bullet(void)
{
	std::cout << "Bullet class Destructor" << std::endl;
}

void Bullet::Update(float timeDelta)
{
	const Uint8 * keyState = SDL_GetKeyboardState(NULL);

	position += look * speed * timeDelta;


}

void Bullet::Draw()
{
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;

	SDL_QueryTexture(texture, nullptr, nullptr, & rect.w, & rect.h);

	SDL_Point center;
	center.x = rect.w / 2;
	center.y = rect.h / 2;
	SDL_RenderCopyEx(Game::Instance()->renderer, texture, nullptr, & rect, rotation, & center, SDL_FLIP_NONE);

  std::cout<< "Postion: (" << position.x << ", " << position.y << ")" << std::endl;
  //std::cout<< "Rect: (" << rect.w <<", "<< rect.h << ")" << std::endl;

}

void Bullet::Cleanup()
{
	SDL_Rect rect;

  SDL_QueryTexture(texture, nullptr, nullptr, & rect.w, & rect.h);

  if((!isOutOfBounds) && ((position.x > 640) || (position.y > 480) || (position.x < 0) || (position.y < 0))) {
    std::cout<< "Postion: (" << position.x << ", " << position.y << ")" << std::endl;
    //std::cout<< "Rect: (" << rect.w <<", "<< rect.h << ")" << std::endl;
		std::cout<< "Out of the bound" << std::endl;
		this->isOutOfBounds = true;
  }
}
