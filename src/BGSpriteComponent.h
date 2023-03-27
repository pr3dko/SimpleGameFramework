#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>

namespace SGF
{
	class BGSpriteComponent : public SpriteComponent
	{
	public:
		BGSpriteComponent(Actor* owner, int drawOrder = 10);

		void update(float deltaTime) override;
		void draw(SDL_Renderer* renderer) override;

		void setBGTextures(const std::vector<SDL_Texture*>& textures);
		void setScreenSize(float width, float height);
		void setScrollSpeed(float speed) { scrollSpeed_ = speed; }

	private:
		struct BGTexture
		{
			SDL_Texture* texture_;
			Vector2 offset_;
		};
		std::vector<BGTexture> bgTextures_;
		Vector2 screenSize_;
		float scrollSpeed_;
	};
}
