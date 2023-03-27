#pragma once
#include <math.h>

namespace SGF
{
	class Vector2;

	namespace Math
	{
		const float pi = 3.14159265359f;

		inline float radiansToDegrees(float radians)
		{
			return radians * 180.0f / pi;
		}

		inline float degreesToRadians(float degrees)
		{
			return degrees * pi / 180.0f;
		}

		inline float sqrt(float x)
		{
			return sqrtf(x);
		}

		inline float cos(float x)
		{
			return cosf(x);
		}

		inline float sin(float x)
		{
			return sinf(x);
		}

		inline float atan2(float y, float x)
		{
			return atan2f(y, x);
		}

		inline float acos(float x)
		{
			return acosf(x);
		}

		inline float abs(float x)
		{
			return fabsf(x);
		}

		inline bool nearZero(float x, float epsilon = 0.5f)
		{
			return Math::abs(x) < epsilon;
		}

		namespace Heuristic
		{
			float euclideanDistance(const Vector2& a, const Vector2& b);
		}
	}

	class Vector2
	{
	public:
		float x;
		float y;

		Vector2() : x(0.0f), y(0.0f) {}
		Vector2(float a, float b) : x(a), y(b) {}

		Vector2& operator+=(const Vector2& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vector2& operator-=(const Vector2& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		Vector2& operator*=(float s)
		{
			x *= s;
			y *= s;
			return *this;
		}

		Vector2& operator/=(float s)
		{
			return (*this) *= 1 / s;
		}

		Vector2 operator-()
		{
			Vector2 result = *this;
			return result *= -1.0f;
		}

		float magnitudeSquared() const
		{
			return x * x + y * y;
		}

		float magnitude() const
		{
			return Math::sqrt(magnitudeSquared());
		}

		Vector2& normalize()
		{
			x /= magnitude();
			y /= magnitude();
			return *this;
		}

		static Vector2 normalize(const Vector2& v)
		{
			Vector2 result = v;
			return result.normalize();
		}

		static float dot(const Vector2& a, const Vector2& b)
		{
			return a.x * b.x + a.y * b.y;
		}
	};

	inline Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		Vector2 result = a;
		result += b;
		return result;
	}

	inline Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		Vector2 result = a;
		result -= b;
		return result;
	}

	inline Vector2 operator*(const Vector2& v, float s)
	{
		Vector2 result = v;
		result *= s;
		return result;
	}

	inline Vector2 operator*(float s, const Vector2& v)
	{
		return v * s;
	}

	inline Vector2 operator/(const Vector2& v, float s)
	{
		return v * 1 / s;
	}
}