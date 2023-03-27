#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"

namespace SGF
{
	SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) :
		Component(owner),
		texture_(nullptr),
		width_(0),
		height_(0),
		drawOrder_(drawOrder)
	{
		owner_->getGame()->addSprite(this);
	}

	SpriteComponent::~SpriteComponent()
	{
		owner_->getGame()->removeSprite(this);
	}

	void SpriteComponent::draw(SDL_Renderer* renderer)
	{
		if (texture_)
		{
			SDL_Rect rect;
			rect.w = static_cast<int>(width_ * owner_->getScale());
			rect.h = static_cast<int>(height_ * owner_->getScale());
			rect.x = static_cast<int>(owner_->getPosition().x - rect.w / 2);
			rect.y = static_cast<int>(owner_->getPosition().y - rect.h / 2);

			SDL_RenderCopyEx(renderer, texture_, nullptr, &rect, -Math::radiansToDegrees(owner_->getRotation()), nullptr, SDL_FLIP_NONE);
		}
	}

	void SpriteComponent::setTexture(SDL_Texture* texture)
	{
		texture_ = texture;
		SDL_QueryTexture(texture, nullptr, nullptr, &width_, &height_);
	}
}

