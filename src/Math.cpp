#include "Math.h"

namespace SGF
{
	namespace Math
	{
		namespace Heuristic
		{
			float euclideanDistance(const Vector2& a, const Vector2& b)
			{
				return (a - b).magnitude();
			}
		}
	}
}