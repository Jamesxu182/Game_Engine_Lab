#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "Player.h"

using namespace Game1;

Game * Game::instance = nullptr;

Game::Game(void)
{
	instance = this;
	std::cout << "Game class Constructor!" <<endl;
}


Game::~Game(void)
{
	std::cout << "Game class Destructor!" <<endl;
}

bool Game::InitialiseSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL Init Everything Failed" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	SDL_Window *win = nullptr;
	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

	if (win == nullptr)
	{
		std::cout << "Window Creates Failed" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "Render Creates Failed" << std::endl;
 		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	SDL_RenderSetLogicalSize(renderer, 640, 480);

	// Mistaken, Miss 'return true'
	return true;
}

bool Game::Initialise()
{
	if (! InitialiseSDL())
	{
		return false;
	}

	std::cout<<"Game Initialised!"<< std::endl;

	shared_ptr<Player> player = make_shared<Player>();
	children.push_back(player);

	list<shared_ptr<GameComponent>>::iterator it = children.begin();
	while (it != children.end())
	{
		(*it)->Initialise();
		++ it;
	}

	std::cout<<"Children Initialised!"<<std::endl;

	return true;
}

void Game::Update(float timeDelta)
{
	list<shared_ptr<GameComponent>>::iterator it = children.begin();
	while (it != children.end())
	{
		(*it)->Update(timeDelta);
		++ it;
	}
}

void Game::Draw()
{
	list<shared_ptr<GameComponent>>::iterator it = children.begin();
	while (it != children.end())
	{
		(*it)->Draw();
		++ it;
	}
}

void Game::Cleanup()
{
	list<shared_ptr<GameComponent>>::iterator it = children.begin();
	while (it != children.end())
	{
		(*it)->Cleanup();
		++ it;
	}
}

Game * Game::Instance()
{
	return Game::instance;
}

void Game::Start()
{
	if (!Initialise())
	{
		return;
	}

	SDL_Event event;
	long last = SDL_GetTicks();
	running = true;
	const Uint8 * keyState = SDL_GetKeyboardState(NULL);
	while (running)
	{
		SDL_RenderClear(renderer);

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				continue;
			}
		}

		if (keyState[SDL_SCANCODE_ESCAPE])
		{
			running = false;
			continue;
		}

		long now = SDL_GetTicks();
		float ellapsed = ((float) (now - last)) / 1000.0f;
		Update(ellapsed);
		Cleanup();
		Draw();
		last = now;
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

}
