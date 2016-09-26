#pragma once
#include "GameComponent.h"
#include <SDL2/SDL.h>
#include <list>
#include <memory>
#include "Bullet.h"

using namespace std;

namespace Game1
{
	class Player : public GameComponent
	{
		public:
			Player(void);
			~Player(void);

			SDL_Texture * texture;
			list<shared_ptr<Bullet>> bullets;
			int i;
			int j;

			void Update(float timeDelta);
			bool Initialise();
			void Update();
			void Draw();
			void Cleanup();

	};
}
