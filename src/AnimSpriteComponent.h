#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <string>

namespace SGF
{
	class AnimSpriteComponent : public SpriteComponent
	{
	public:
		AnimSpriteComponent(Actor* owner, int drawOrder = 100);

		void update(float deltaTime) override;

		float getAnimFPS() const { return animFPS_; }

		void setAnimTextures(const std::vector<SDL_Texture*>& textures);
		void setAnimFPS(float fps) { animFPS_ = fps; }

		void addAnim(const std::string& name, int startFrame, int frameCount, bool looping = true);
		void setAnim(const std::string& name);

	private:
		struct AnimData
		{
			std::string name_;
			int startFrame_;
			int frameCount_;
			bool looping_ = true;
		} currAnim_;
		std::vector<SDL_Texture*> animTextures_;
		std::vector<AnimData> anims_;
		float currFrame_;
		float animFPS_;
	};
}