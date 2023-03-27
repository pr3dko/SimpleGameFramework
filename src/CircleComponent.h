#pragma once
#include "Component.h"
#include "Math.h"

namespace SGF
{
	class CircleComponent : public Component
	{
	public:
		CircleComponent(Actor* owner);

		Vector2 getCentre() const;

		void setRadius(float radius) { radius_ = radius; }
		float getRadius() const { return radius_; }

	private:
		float radius_;
	};

	bool intersect(const CircleComponent& a, const CircleComponent& b);
}
