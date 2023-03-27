#pragma once
#include "Component.h"

namespace SGF
{
	class MoveComponent : public Component
	{
	public:
		MoveComponent(Actor* owner, bool screenWrap = true, int updateOrder = 10);

		void update(float deltaTime) override;

		float getAngularSpeed() const { return angularSpeed_; }
		float getForwardSpeed() const { return forwardSpeed_; }

		void setAngularSpeed(float speed) { angularSpeed_ = speed; }
		void setForwardSpeed(float speed) { forwardSpeed_ = speed; }

	private:
		float angularSpeed_; // radians/second
		float forwardSpeed_; // pixels/second
		bool screenWrap_;
	};
}
