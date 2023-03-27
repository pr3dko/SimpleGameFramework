#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"
#include "Game.h"

namespace SGF
{
	MoveComponent::MoveComponent(Actor* owner, bool screenWrap, int updateOrder) :
		Component(owner, updateOrder),
		forwardSpeed_(0.0f),
		angularSpeed_(0.0f),
		screenWrap_(screenWrap)
	{
	}

	void MoveComponent::update(float deltaTime)
	{
		if (!Math::nearZero(angularSpeed_))
		{
			float rotation = owner_->getRotation();
			rotation += angularSpeed_ * deltaTime;
			owner_->setRotation(rotation);
		}

		if (!Math::nearZero(forwardSpeed_))
		{
			Vector2 position = owner_->getPosition();
			position += owner_->getForward() * forwardSpeed_ * deltaTime;

			if (screenWrap_)
			{
				if (position.x < 0.0f)
				{
					position.x = static_cast<float>(owner_->getGame()->getWidth());
				}
				else if (position.x > owner_->getGame()->getWidth())
				{
					position.x = 0.0f;
				}
				if (position.y < 0.0f)
				{
					position.y = static_cast<float>(owner_->getGame()->getHeight());
				}
				else if (position.y > owner_->getGame()->getHeight())
				{
					position.y = 0.0f;
				}
			}
			else
			{
				if (position.x < 0.0f || position.x > owner_->getGame()->getWidth()
					|| position.y < 0.0f || position.y > owner_->getGame()->getHeight())
				{
					owner_->setState(Actor::State::Dead);
				}
			}

			owner_->setPosition(position);
		}
	}
}

