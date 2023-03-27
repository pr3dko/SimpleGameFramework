#include "BGSpriteComponent.h"
#include "Actor.h"

namespace SGF
{
	BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder) :
		SpriteComponent(owner, drawOrder),
		screenSize_(),
		scrollSpeed_(0.0f)
	{
	}

	void BGSpriteComponent::update(float deltaTime)
	{
		SpriteComponent::update(deltaTime);

		for (auto& tex : bgTextures_)
		{
			tex.offset_.x += scrollSpeed_ * deltaTime;
			if (tex.offset_.x < -screenSize_.x)
			{
				tex.offset_.x = (bgTextures_.size() - 1) * screenSize_.x - 1;
			}
		}
	}

	void BGSpriteComponent::draw(SDL_Renderer* renderer)
	{
		for (auto& tex : bgTextures_)
		{
			SDL_Rect rect;
			rect.w = static_cast<int>(screenSize_.x);
			rect.h = static_cast<int>(screenSize_.y);
			rect.x = static_cast<int>(owner_->getPosition().x - rect.w / 2 + tex.offset_.x);
			rect.y = static_cast<int>(owner_->getPosition().y - rect.h / 2 + tex.offset_.y);

			SDL_RenderCopy(renderer, tex.texture_, nullptr, &rect);
		}
	}

	void BGSpriteComponent::setBGTextures(const std::vector<SDL_Texture*>& textures)
	{
		int count = 0;
		for (auto tex : textures)
		{
			BGTexture bgTex;
			bgTex.texture_ = tex;
			bgTex.offset_.x = count * screenSize_.x;
			bgTex.offset_.y = 0;
			bgTextures_.emplace_back(bgTex);
			count++;
		}
	}

	void BGSpriteComponent::setScreenSize(float width, float height)
	{
		screenSize_.x = width;
		screenSize_.y = height;
	}
}

