#pragma once
#include "GameComponent.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace Game1
{
	class Bullet : public GameComponent
	{
		public:
			Bullet(void);
      Bullet(glm::vec2 position, glm::vec2 look, float speed);
			~Bullet(void);

			SDL_Texture * texture;
			bool isOutOfBounds;

			void Update(float timeDelta);
			bool Initialise();
			void Update();
			void Draw();
      void Cleanup();

	};
}
