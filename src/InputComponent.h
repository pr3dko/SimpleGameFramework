#pragma once
#include "MoveComponent.h"

namespace SGF
{
	class InputComponent : public MoveComponent
	{
	public:
		InputComponent(Actor* owner);

		void processInput(const uint8_t* keyboardState);

		void setMaxForwardSpeed(float speed) { maxForwardSpeed_ = speed; }
		void setMaxAngularSpeed(float speed) { maxAngularSpeed_ = speed; }
		void setForwardKey(int key) { forwardKey_ = key; }
		void setBackwardKey(int key) { backwardKey_ = key; }
		void setClockwiseKey(int key) { clockwiseKey_ = key; }
		void setAntiClockwiseKey(int key) { antiClockwiseKey_ = key; }

	private:
		float maxForwardSpeed_;
		float maxAngularSpeed_;

		int forwardKey_;
		int backwardKey_;

		int clockwiseKey_;
		int antiClockwiseKey_;
	};
}
