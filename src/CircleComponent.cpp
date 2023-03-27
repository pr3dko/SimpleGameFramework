#include "CircleComponent.h"
#include "Actor.h"

namespace SGF
{
	CircleComponent::CircleComponent(Actor* owner) :
		Component(owner),
		radius_(0.0f)
	{
	}

	Vector2 CircleComponent::getCentre() const
	{
		return owner_->getPosition();
	}

	bool intersect(const CircleComponent& a, const CircleComponent& b)
	{
		Vector2 diff = a.getCentre() - b.getCentre();
		float diffSquared = diff.magnitudeSquared();

		float sumOfRadiiSquared = a.getRadius() + b.getRadius();
		sumOfRadiiSquared *= sumOfRadiiSquared;

		return diffSquared <= sumOfRadiiSquared;
	}
}

