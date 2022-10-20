#pragma once
#include "GeneralStucts.h"
#include <vector>
namespace Crusade
{
	class Math final
	{
	public:
		Math() = delete;
		~Math() = delete;

		Math(const Math& other) = delete;
		Math(Math&& other) = delete;
		Math& operator=(const Math& other) = delete;
		Math& operator=(Math&& other) = delete;
		
#pragma region CollisionFunctionality
		struct HitInfo
		{
			float lambda;
			Point2f intersectPoint;
			Vector2f normal;
		};
		static bool IsPointInRect(const Point2f& p, const Rectf& r);
		static bool IsPointInCircle(const Point2f& p, const Circlef& c);
		static bool IsPointInPolygon(const Point2f& p, const std::vector<Point2f>& vertices);
		static bool IsPointInPolygon(const Point2f& p, const Point2f* vertices, size_t nrVertices);

		static bool IsOverlapping(const Point2f& a, const Point2f& b, const Circlef& c);
		static bool IsOverlapping(const Point2f& a, const Point2f& b, const Rectf& r);

		static bool IsOverlapping(const Rectf& r1, const Rectf& r2);
		static bool IsOverlapping(const Rectf& r, const Circlef& c);
		static bool IsOverlapping(const Circlef& c1, const Circlef& c2);
		static bool IsOverlapping(const std::vector<Point2f>& vertices, const Circlef& c);
		static bool IsOverlapping(const Point2f* vertices, size_t nrVertices, const Circlef& c);
		static bool Raycast(const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo);
		static  bool Raycast(const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo);

		static bool IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon = 1e-6);
		static float DistPointLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
		static bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
		static bool IntersectRectLine(const Rectf& r, const Point2f& p1, const Point2f& p2, float& intersectMin, float& intersectMax);

#pragma endregion CollisionFunctionality

		
		const float PI{ 3.1415926535f };
		static float DegreeToRadian(const float degrees);
		static float RadianToDegree(const float radian);
		static float MoveTowards(float number, float target, float speed);
		static float Lerp(float start_value, float end_value, float pct);
		static void Clamp(float& value, float min, float max);
		static Vector2f PerpendicularClockwise(const Vector2f& vector2);
		static Vector2f PerpendicularCounterClockwise(const Vector2f& vector2);
		static float DirectionToAngle(const Vector2f& direction);
	};
}
