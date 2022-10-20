#pragma once
#include <cstdlib>

namespace Crusade
{
	class Random final
	{
	public:
		Random() = delete;
		~Random() = delete;

		Random(const Random& other) = delete;
		Random(Random&& other) = delete;
		Random& operator=(const Random& other) = delete;
		Random& operator=(Random&& other) = delete;

		static unsigned Range(const unsigned min, const unsigned max)
		{
			if (max < min)
				return 0;

			return (rand() % ((max - min)+1)) + min;
		}
		static float Range(const float min, const float max)
		{
			if (max < min)
				return 0;
			return min + (max - min) * (float(rand()) / float(RAND_MAX));
		}

		static Color4f Color()
		{
			float r = Range(0, 1.f);
			float g = Range(0, 1.f);
			float b = Range(0, 1.f);
			return Color4f{r,g,b,1.f};
		}

		static Vector2f Unitvector()
		{
			return Vector2f{Range(0,1.f),Range(0,1.f)};
		}
	};
}
