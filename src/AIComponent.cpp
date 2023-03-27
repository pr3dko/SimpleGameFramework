#include "AIComponent.h"
#include "AIState.h"
#include <SDL.h>

namespace SGF
{
	AIComponent::AIComponent(Actor* owner) :
		Component(owner),
		currentState_(nullptr)
	{
	}

	void AIComponent::update(float deltaTime)
	{
		if (currentState_)
		{
			currentState_->update(deltaTime);
		}
	}

	void AIComponent::changeState(const std::string& name)
	{
		if (currentState_)
		{
			currentState_->onExit();
		}

		auto iter = states_.find(name);
		if (iter != states_.end())
		{
			currentState_ = iter->second;
			currentState_->onEnter();
		}
		else
		{
			SDL_Log("Error: could not find state %s\n", name.c_str());
			currentState_ = nullptr;
		}
	}

	void AIComponent::registerState(AIState* state)
	{
		states_.emplace(state->getName(), state);
	}

}
