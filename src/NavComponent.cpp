#include "NavComponent.h"
#include "Actor.h"

namespace SGF
{
	NavComponent::NavComponent(Actor* owner, bool screenWrap, int updateOrder) :
		MoveComponent(owner, screenWrap, updateOrder)
	{

	}

	void NavComponent::update(float deltaTime)
	{
		Vector2 diff = nextPoint_ - owner_->getPosition();
		if (diff.magnitude() <= 2.0f)
		{
			nextPoint_ = getNextPoint();
			turnTo(nextPoint_);
		}

		MoveComponent::update(deltaTime);
	}

	void NavComponent::turnTo(const Vector2& pos)
	{
		Vector2 diff = pos - owner_->getPosition();
		float rotation = Math::atan2(-diff.y, diff.x);
		owner_->setRotation(rotation);
	}

}