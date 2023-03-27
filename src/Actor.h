#pragma once
#include "Math.h"
#include <vector>
#include <stdint.h>

namespace SGF
{
	class Game;
	class Component;

	class Actor
	{
	public:
		enum class State { Active, Paused, Dead };

		Actor(Game* game);
		virtual ~Actor();

		void update(float deltaTime);
		void updateComponents(float deltaTime);
		virtual void updateActor(float deltaTime);

		void processInput(const uint8_t* keyboardState);
		virtual void actorInput(const uint8_t* keyboardState);

		void addComponent(Component* component);
		void removeComponent(Component* component);

		Game* getGame() const { return game_; }
		State getState() const { return state_; }
		Vector2 getPosition() const { return position_; }
		float getScale() const { return scale_; }
		float getRotation() const { return rotation_; }
		Vector2 getForward() const { return Vector2(Math::cos(rotation_), -Math::sin(rotation_)); }

		void setState(State state) { state_ = state; }
		void setPosition(const Vector2& position) { position_ = position; }
		void setScale(float scale) { scale_ = scale; }
		void setRotation(float rotation) { rotation_ = rotation; }

	private:
		State state_;
		Vector2 position_;
		float scale_;
		float rotation_; // radians
		std::vector<Component*> components_;
		Game* game_;
	};
}
