#pragma once
#include <string>
namespace Crusade
{

	struct Point2f
	{
		Point2f();
		explicit Point2f(float x, float y);

		float x;
		float y;
	};



	struct Rectf
	{
		Rectf();
		explicit Rectf(float left, float bottom, float width, float height);

		float left;
		float bottom;
		float width;
		float height;

	};


	struct Color4f
	{
		Color4f();
		explicit Color4f(float r, float g, float b, float a);

		float r;
		float g;
		float b;
		float a;
	};

	struct Circlef
	{
		Circlef();
		explicit Circlef(const Point2f& center, float radius);
		explicit Circlef(float centerX, float centerY, float radius);

		Point2f center;
		float radius;
	};


	struct Ellipsef
	{
		Ellipsef();
		explicit Ellipsef(const Point2f& center, float radiusX, float radiusY);
		explicit Ellipsef(float centerX, float centerY, float radiusX, float radiusY);

		Point2f center;
		float radiusX;
		float radiusY;
	};

	struct Vector2f
	{
		Vector2f();
		explicit Vector2f(float x, float y);
		explicit Vector2f(const Point2f& fromPoint, const Point2f& tillPoint);
		explicit Vector2f(const Point2f& point);

		Vector2f operator-() const;
		Vector2f operator+() const;
		Vector2f& operator*=(float rhs);
		Vector2f& operator/=(float rhs);
		Vector2f& operator+=(const Vector2f& rhs);
		Vector2f& operator-=(const Vector2f& rhs);
		explicit operator Point2f();

		Point2f	ToPoint2f() const;
		bool Equals(const Vector2f& other, float epsilon = 0.001f) const;
		std::string	ToString() const;
		float DotProduct(const Vector2f& other) const;
		float CrossProduct(const Vector2f& other) const;
		float Norm() const;
		float Length() const;
		float SquaredLength() const;
		float AngleWith(const Vector2f& other) const;
		Vector2f Normalized(float epsilon = 0.001f) const;
		Vector2f Orthogonal() const;
		Vector2f Reflect(const Vector2f& surfaceNormal) const;
		void Set(float newX, float newY);

		float x;
		float y;

		static Vector2f Zero() { return Vector2f{ 0,0 }; }
		static Vector2f Up() { return Vector2f{ 0,1 }; }
		static Vector2f Down() { return Vector2f{ 0,-1 }; }
		static Vector2f Right() { return Vector2f{ 1,0 }; }
		static Vector2f Left() { return Vector2f{ -1,0 }; }
	};



}
Crusade::Vector2f operator*(float lhs, Crusade::Vector2f rhs);
Crusade::Vector2f operator*(Crusade::Vector2f lhs, float rhs);
Crusade::Vector2f operator/(Crusade::Vector2f lhs, float rhs);
Crusade::Vector2f operator+(Crusade::Vector2f lhs, const Crusade::Vector2f& rhs);
Crusade::Vector2f operator-(Crusade::Vector2f lhs, const Crusade::Vector2f& rhs);
bool operator==(const Crusade::Vector2f& lhs, const Crusade::Vector2f& rhs);
bool operator!=(const  Crusade::Vector2f& lhs, const Crusade::Vector2f& rhs);
std::ostream& operator<< (std::ostream& lhs, const Crusade::Vector2f& rhs);
Crusade::Point2f& operator+=(Crusade::Point2f& lhs, const Crusade::Vector2f& rhs);
Crusade::Point2f operator+(Crusade::Point2f lhs, const Crusade::Vector2f& rhs);
Crusade::Point2f& operator-=(Crusade::Point2f& lhs, const Crusade::Vector2f& rhs);
Crusade::Point2f operator-(Crusade::Point2f lhs, const Crusade::Vector2f& rhs);
Crusade::Vector2f operator-(const Crusade::Point2f& lhs, const Crusade::Point2f& rhs);