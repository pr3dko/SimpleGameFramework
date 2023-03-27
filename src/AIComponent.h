#pragma once
#include "Component.h"
#include <unordered_map>
#include <string>

namespace SGF
{
	class AIState;

	class AIComponent : public Component
	{
	public:
		AIComponent(Actor* owner);

		void update(float deltaTime) override;
		void changeState(const std::string& name);
		void registerState(AIState* state);

	private:
		std::unordered_map<std::string, AIState*> states_;
		AIState* currentState_;
	};
}
