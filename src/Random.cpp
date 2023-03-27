#include "Random.h"

namespace SGF
{
	std::default_random_engine Random::engine_;

	void Random::init()
	{
		std::random_device rd;
		engine_.seed(rd());
	}

	Vector2 Random::getVector(const Vector2& min, const Vector2& max)
	{
		std::uniform_real_distribution<float> ux(min.x, max.x);
		std::uniform_real_distribution<float> uy(min.y, max.y);
		return Vector2(ux(engine_), uy(engine_));
	}

	float Random::getFloat(float min, float max)
	{
		std::uniform_real_distribution<float> u(min, max);
		return u(engine_);
	}

	int Random::getInt(int min, int max)
	{
		std::uniform_int_distribution<int> u(min, max);
		return u(engine_);
	}
}

