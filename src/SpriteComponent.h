#pragma once
#include "Component.h"
#include <SDL.h>

namespace SGF
{
	class SpriteComponent : public Component
	{
	public:
		// The lower the draw order, the further back in the scene the sprite is drawn
		SpriteComponent(Actor* owner, int drawOrder = 100);
		~SpriteComponent();

		virtual void draw(SDL_Renderer* renderer);
		virtual void setTexture(SDL_Texture* texture);

		int getWidth() const { return width_; }
		int getHeight() const { return height_; }
		int getDrawOrder() const { return drawOrder_; }

	protected:
		SDL_Texture* texture_;
		int width_;
		int height_;
		int drawOrder_;
	};
}
