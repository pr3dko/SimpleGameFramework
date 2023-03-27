#pragma once

namespace SGF
{
	class AIComponent;

	class AIState
	{
	public:
		AIState(AIComponent* owner) : owner_(owner) {}

		virtual void update(float deltaTime) = 0;
		virtual void onEnter() = 0;
		virtual void onExit() = 0;
		virtual const char* getName() const = 0;

	private:
		AIComponent* owner_;
	};
}
