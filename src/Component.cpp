#include "Component.h"
#include "Actor.h"

namespace SGF
{
	Component::Component(Actor* owner, int updateOrder) :
		owner_(owner),
		updateOrder_(updateOrder)
	{
		owner_->addComponent(this);
	}

	Component::~Component()
	{
		owner_->removeComponent(this);
	}

	void Component::update(float deltaTime)
	{
	}

	void Component::processInput(const uint8_t* keyboardState)
	{
	}
}

