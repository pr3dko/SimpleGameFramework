#include "Actor.h"
#include "Component.h"
#include "Game.h"
#include <algorithm>

namespace SGF
{
	Actor::Actor(Game* game) :
		state_(State::Active),
		scale_(1.0f),
		rotation_(0.0f),
		game_(game)
	{
		game_->addActor(this);
	}

	Actor::~Actor()
	{
		game_->removeActor(this);

		while (!components_.empty())
		{
			delete components_.back();
		}
	}

	void Actor::update(float deltaTime)
	{
		if (state_ == State::Active)
		{
			updateComponents(deltaTime);
			updateActor(deltaTime);
		}
	}

	void Actor::updateComponents(float deltaTime)
	{
		for (auto component : components_)
		{
			component->update(deltaTime);
		}
	}

	void Actor::updateActor(float deltaTime)
	{
	}

	void Actor::processInput(const uint8_t* keyboardState)
	{
		if (state_ == State::Active)
		{
			for (auto component : components_)
			{
				component->processInput(keyboardState);
			}

			actorInput(keyboardState);
		}
	}

	void Actor::actorInput(const uint8_t* keyboardState)
	{
	}

	void Actor::addComponent(Component* component)
	{
		// Find the first component with an update order greater than this new component
		auto insertPoint = std::find_if(components_.begin(), components_.end(),
			[=](Component* existingComp) { return existingComp->getUpdateOrder() > component->getUpdateOrder(); }
		);

		components_.insert(insertPoint, component);
	}

	void Actor::removeComponent(Component* component)
	{
		auto iter = std::find(components_.begin(), components_.end(), component);
		if (iter != components_.end())
		{
			components_.erase(iter);
		}
	}
}