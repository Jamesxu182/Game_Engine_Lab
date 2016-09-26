#include "Player.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

using namespace Game1;
using namespace std;

Player::Player(void) : GameComponent()
{
	position = glm::vec2(100, 100);
	look = glm::vec2(0, -1);
	speed = 50.0f;
	i = SDL_GetTicks();
	std::cout << "Player class Constructor" << std::endl;
}

bool Player::Initialise()
{
	SDL_Surface * temp = NULL;
	temp = SDL_LoadBMP("tank.bmp");

	if (temp == nullptr)
	{
		cout << "Could not load player texture" << endl;
		return false;
	}

	texture = SDL_CreateTextureFromSurface(Game::Instance()->renderer, temp);
	SDL_FreeSurface(temp);

	return true;
}

Player::~Player(void)
{
	std::cout << "Player class Destructor" << std::endl;
}

void Player::Update(float timeDelta)
{
	const Uint8 * keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_UP])
	{
		position += look * speed * timeDelta;
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		position -= look * speed * timeDelta;
	}

	if(keyState[SDL_SCANCODE_RIGHT])
	{
		rotation += 1;
		look = glm::vec2(glm::cos(glm::radians(rotation - 90.0f)), glm::sin(glm::radians(rotation - 90.0f)));
	}

	if(keyState[SDL_SCANCODE_LEFT])
	{
		rotation -= 1;
		look = glm::vec2(glm::cos(glm::radians(rotation - 90.0f)), glm::sin(glm::radians(rotation - 90.0f)));
	}

	if(keyState[SDL_SCANCODE_SPACE]) {

		j = SDL_GetTicks();

		if((j - i) > 100) {
			i = j;

			shared_ptr<Bullet> bullet = make_shared<Bullet>(position, look, speed * 2);

			bullet->Initialise();

			bullets.push_back(bullet);
		}

	}

	list<shared_ptr<Bullet>>::iterator it = bullets.begin();

	while (it != bullets.end())
	{
		if((!(* it)->isOutOfBounds)) {
			(* it)->Update(timeDelta);
		}

		++ it;
	}

}

void Player::Draw()
{
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;

	SDL_QueryTexture(texture, nullptr, nullptr, & rect.w, & rect.h);

	SDL_Point center;
	center.x = rect.w / 2;
	center.y = rect.h / 2;
	SDL_RenderCopyEx(Game::Instance()->renderer, texture, nullptr, & rect, rotation, & center, SDL_FLIP_NONE);

	list<shared_ptr<Bullet>>::iterator it = bullets.begin();

	while (it != bullets.end())
	{
		if(!((* it)->isOutOfBounds)) {
			(* it)->Draw();
		}
		++ it;
	}
}

void Player::Cleanup () {
	list<shared_ptr<Bullet>>::iterator it = bullets.begin();

	while (it != bullets.end())
	{
		(*it)->Cleanup();
		++ it;
	}
}
