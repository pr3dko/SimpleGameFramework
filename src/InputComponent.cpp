#include "InputComponent.h"

namespace SGF
{
	InputComponent::InputComponent(Actor* owner) :
		MoveComponent(owner),
		maxForwardSpeed_(0.0f),
		maxAngularSpeed_(0.0f),
		forwardKey_(0),
		backwardKey_(0),
		clockwiseKey_(0),
		antiClockwiseKey_(0)
	{

	}

	void InputComponent::processInput(const uint8_t* keyboardState)
	{
		float forwardSpeed = 0.0f;
		if (keyboardState[forwardKey_])
		{
			forwardSpeed += maxForwardSpeed_;
		}
		if (keyboardState[backwardKey_])
		{
			forwardSpeed -= maxForwardSpeed_;
		}
		setForwardSpeed(forwardSpeed);

		float angularSpeed = 0.0f;
		if (keyboardState[antiClockwiseKey_])
		{
			angularSpeed += maxAngularSpeed_;
		}
		if (keyboardState[clockwiseKey_])
		{
			angularSpeed -= maxAngularSpeed_;
		}
		setAngularSpeed(angularSpeed);
	}

}
