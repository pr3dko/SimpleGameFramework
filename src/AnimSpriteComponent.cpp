#include "AnimSpriteComponent.h"
#include <algorithm>

namespace SGF
{
	AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder) :
		SpriteComponent(owner, drawOrder),
		currFrame_(0.0f),
		animFPS_(24.0f)
	{
	}

	void AnimSpriteComponent::update(float deltaTime)
	{
		SpriteComponent::update(deltaTime);

		if (animTextures_.size() > 0)
		{
			currFrame_ += animFPS_ * deltaTime;

			if (currAnim_.looping_)
			{
				while (currFrame_ >= currAnim_.startFrame_ + currAnim_.frameCount_)
				{
					currFrame_ -= currAnim_.frameCount_;
				}
			}
			else if (currFrame_ >= currAnim_.startFrame_ + currAnim_.frameCount_)
			{
				currFrame_ = static_cast<float>(currAnim_.startFrame_ + currAnim_.frameCount_ - 1);
			}

			setTexture(animTextures_[static_cast<int>(currFrame_)]);
		}
	}

	void AnimSpriteComponent::setAnimTextures(const std::vector<SDL_Texture*>& textures)
	{
		animTextures_ = textures;
		if (animTextures_.size() > 0)
		{
			currFrame_ = 0.0f;
			setTexture(animTextures_[0]);
		}
	}

	void AnimSpriteComponent::addAnim(const std::string& name, int startFrame, int frameCount, bool looping)
	{
		anims_.emplace_back(AnimData{ name, startFrame, frameCount, looping });

		currAnim_ = anims_.back();
		currFrame_ = static_cast<float>(startFrame);
	}

	void AnimSpriteComponent::setAnim(const std::string& name)
	{
		if (currAnim_.name_ != name)
		{
			auto iter = std::find_if(anims_.begin(), anims_.end(),
				[=](const AnimData& anim) {return anim.name_ == name; });
			if (iter != anims_.end())
			{
				currAnim_ = *iter;
				currFrame_ = static_cast<float>(currAnim_.startFrame_);
			}
			else
			{
				SDL_Log("Error: no animation with name %s exists.\n", name.c_str());
			}
		}
	}
}