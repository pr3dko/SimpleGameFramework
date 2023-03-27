#pragma once
#include <stdint.h>

namespace SGF
{
	class Actor;

	class Component
	{
	public:
		// The lower the update order, the sooner this component is updated
		Component(Actor* owner, int updateOrder = 100);
		virtual ~Component();

		virtual void update(float deltaTime);
		virtual void processInput(const uint8_t* keyboardState);

		int getUpdateOrder() const { return updateOrder_; }

	protected:
		Actor* owner_;
		int updateOrder_;
	};
}