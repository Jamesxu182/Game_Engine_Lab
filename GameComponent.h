#pragma once
#include <glm/glm.hpp>
namespace Game1
{
	class GameComponent
	{
	public:
		GameComponent(void);
		~GameComponent(void);

		glm::vec2 position;
		glm::vec2 look;
		float rotation;
		float speed;

		virtual bool Initialise();
		virtual void Update(float timeDelta);
		virtual void Draw();
		virtual void Cleanup();

	};
}
