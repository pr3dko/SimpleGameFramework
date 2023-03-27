#pragma once
#include "MoveComponent.h"
#include "Math.h"

namespace SGF
{
	class NavComponent : public MoveComponent
	{
	public:
		NavComponent(Actor* owner, bool screenWrap = true, int updateOrder = 10);

		void update(float deltaTime) override;
		void turnTo(const Vector2& pos);
		virtual Vector2 getNextPoint() = 0;

	protected:
		Vector2 nextPoint_;
	};
}