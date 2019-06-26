#pragma once

#include "Quantum\Core.h"
#include <cmath>
#include <string>

namespace Quantum {

	class QUANTUM_API Vector2 {
		float x, y;
	public: // Methods
		inline float GetX() const 
		{ 
			return x; 
		}
		inline float GetY() const 
		{ 
			return y; 
		}
		inline void SetX(const float _x) 
		{ 
			x = _x; 
		}
		inline void SetY(const float _y) 
		{ 
			y = _y; 
		}

		inline void Set(const float x, const float y) 
		{ 
			SetX(x); 
			SetY(y); 
		}

		inline void Set(const Vector2& other) 
		{ 
			Set(other.GetX(), other.GetY()); 
		}

		
		Vector2(const float x, const float y) 
		{
			Set(x, y);
		}

		Vector2() 
		{
			Vector2(0, 0);
		}

		inline float Length() const 
		{
			return std::sqrt((x * x) + (y * y));
		}

		inline float Angle() const 
		{
			return std::atan2f(y, x);
		}
		inline float Dot(const Vector2& other) const 
		{
			return (x * other.GetX()) + (y * other.GetY());
		}
		inline float Cross(const Vector2& other) const 
		{
			return (x * other.GetX()) - (y * other.GetY());
		}

		inline Vector2& Add(const Vector2& other) { x += other.GetX(); y += other.GetY(); return *this; }
		inline Vector2& Add(const float c) { x += c; y += c;  return *this; }
		inline Vector2& Sub(const Vector2& other) { x -= other.GetX(); y -= other.GetY(); return *this; }
		inline Vector2& Sub(const float c) { x -= c; y -= c; return *this; }
		inline Vector2& Mult(const Vector2& other) { x *= other.GetX(); y *= other.GetY(); return *this; }
		inline Vector2& Mult(const float c) { x *= c; y *= c; return *this;  }
		inline Vector2& Div(const Vector2& other) { x /= other.GetX(); y /= other.GetY(); return *this; }
		inline Vector2& Div(const float c) { x /= c; y /= c; return *this; }

		inline Vector2& Abs() { x = std::abs(x); y = std::abs(y); return *this; }
		inline bool Equals(const Vector2 other) const { return x == other.GetX() && y == other.GetY(); }
		inline std::string ToString() const { return "(" + std::to_string(x) + "," + std::to_string(y) + ")";  }

		inline Vector2& Copy() const { return Vector2(x, y);  }

		inline Vector2& interpolate(const Vector2& dest, float factor) 
		{
			return Sub(dest, *this).Mult(factor).Add(*this);
		}

		inline Vector2& Normalize() 
		{
			Div(Length());
			return *this;
		}

		Vector2& Rotate(const float angle) 
		{
			float rad = (float)((PI / 180) * angle);
			float cosine = std::cos(rad);
			float sine = std::sin(rad);

			Set(x * cosine - y * sine, y * cosine + x * sine);
			return *this;
		}

		inline Vector2& Perpendicular() 
		{
			return Vector2(-y, x);
		}

		// Static functions
		inline static Vector2 Add(const Vector2& v1, const Vector2& v2) { return Vector2(v1.GetX() + v2.GetX(), v1.GetY() + v2.GetY()); }
		inline static Vector2 Add(const Vector2& v1, const float c) { return Vector2(v1.GetX() + c, v1.GetY() + c); }
		inline static Vector2 Sub(const Vector2& v1, const Vector2& v2) { return Vector2(v1.GetX() - v2.GetX(), v1.GetY() - v2.GetY()); }
		inline static Vector2 Sub(const Vector2& v1, const float c) { return Vector2(v1.GetX() - c, v1.GetY() - c); }
		inline static Vector2 Mult(const Vector2& v1, const Vector2& v2) { return Vector2(v1.GetX() * v2.GetX(), v1.GetY() * v2.GetY()); }
		inline static Vector2 Mult(const Vector2& v1, const float c) { return Vector2(v1.GetX() * c, v1.GetY() * c); }
		inline static Vector2 Div(const Vector2& v1, const Vector2& v2) { return Vector2(v1.GetX() / v2.GetX(), v1.GetY() / v2.GetY()); }
		inline static Vector2 Div(const Vector2& v1, const float c) { return Vector2(v1.GetX() / c, v1.GetY() / c); }

		inline static Vector2 Abs(const Vector2& v1) { return Vector2(std::abs(v1.GetX()), std::abs(v1.GetY())); }
		inline static Vector2 Normal(const Vector2& v1) 
		{
			float l = v1.Length();
			return Vector2(v1.GetX() / l, v1.GetY() / l);
		}

		static Vector2 Rotate(const Vector2& v, const float angle) 
		{
			float rad = (float)((PI / 180) * angle);
			float cosine = std::cos(rad);
			float sine = std::sin(rad);

			return Vector2(v.GetX() * cosine - v.GetY() * sine, v.GetY() * cosine + v.GetX() * sine);
		}

		inline static float Distance(const Vector2& v1, const Vector2& v2) 
		{
			return Sub(v2, v1).Length();
		}

		static float AngleBetween(const Vector2& v1, const Vector2& v2) 
		{
			float cosine = v1.Dot(v2) / (v1.Length() * v2.Length());
			return std::acos(cosine);
		}

		inline static float AngleTo(const Vector2& v1, const Vector2& v2) 
		{
			return Sub(v2, v1).Angle();
		}
	};
}