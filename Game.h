#pragma once
#include "GameComponent.h"
#include <list>
#include <SDL2/SDL.h>
#include <memory>

using namespace std;

namespace Game1
{
	class Game : public GameComponent
	{
	public:
		Game(void);
		~Game(void);

		list<shared_ptr<GameComponent>> children;

		static Game * instance;
		static Game * Instance();

		// SDL Stuff
		SDL_Renderer * renderer;
		bool running;

		bool Initialise();
		bool InitialiseSDL();
		void Update(float timeDelta);
		void Draw();
		void Cleanup();
		void Start();

	};
}
