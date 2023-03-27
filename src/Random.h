#pragma once
#include <random>
#include "Math.h"

namespace SGF
{
	class Random
	{
	public:
		static void init();
		static Vector2 getVector(const Vector2& min, const Vector2& max);
		static float getFloat(float min, float max);
		static int getInt(int min, int max);

	private:
		static std::default_random_engine engine_;
	};
}
