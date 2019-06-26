#pragma once

#include "Quantum\Core.h"
#include <cmath>
#include <string>
#include "Vector2.h"

namespace Quantum {

	class QUANTUM_API Vector3 {
		float x, y, z;
	public: // Methods
		inline float GetX() const 
		{
			return x;
		}
		inline float GetY() const 
		{
			return y;
		}
		inline float GetZ() const 
		{
			return z;
		}
		inline void SetX(const float _x) 
		{
			x = _x;
		}
		inline void SetY(const float _y) 
		{
			y = _y;
		}
		inline void SetZ(const float _z) 
		{
			z = _z;
		}

		inline void Set(const float x, const float y, const float z) 
		{
			SetX(x);
			SetY(y);
			SetZ(z);
		}

		inline void Set(const Vector3& other) 
		{
			Set(other.GetX(), other.GetY(), other.GetZ());
		}


		Vector3(const float x, const float y, const float z) 
		{
			Set(x, y, z);
		}

		Vector3() 
		{
			Vector3(0, 0, 0);
		}

		Vector3(const Vector2& v) 
		{
			Vector3(v.GetX(), v.GetY(), 0);
		}
		
		inline float max() const 
		{
			return std::fmax(x, std::fmax(y, z));
		}

		Vector3 max(const Vector3& other) const 
		{
			Vector3 result = Vector3();
			result.SetX(std::fmax(x, other.GetX()));
			result.SetY(std::fmax(y, other.GetY()));
			result.SetZ(std::fmax(z, other.GetZ()));

			return result;
		}

		inline float min() const 
		{
			return std::fmin(x, std::fmin(y, z));
		}

		Vector3 min(const Vector3& other) const 
		{
			Vector3 result = Vector3();
			result.SetX(std::fmin(x, other.GetX()));
			result.SetY(std::fmin(y, other.GetY()));
			result.SetZ(std::fmin(z, other.GetZ()));

			return result;
		}

		inline float Length() const 
		{
			return std::sqrt((x * x) + (y * y) + (z * z));
		}

		/*inline float Angle() const {
			return atan2f(y, x);
		}*/
		inline float Dot(const Vector3& other) const 
		{
			return (x * other.GetX()) + (y * other.GetY() + (z * other.GetZ());
		}
		inline Vector3& Cross(const Vector3& other) const 
		{
			return Vector3((y * other.GetZ()) - (z * other.GetY()), (z * other.GetX()) - (x * other.GetZ()), (x * other.GetY()) - (y * other.GetX()));
		}

		inline Vector3& Add(const Vector3& other) { x += other.GetX(); y += other.GetY(); z += other.GetZ(); return *this; }
		inline Vector3& Add(const float c) { x += c; y += c; z += c;  return *this; }
		inline Vector3& Sub(const Vector3& other) { x -= other.GetX(); y -= other.GetY(); z -= other.GetZ(); return *this; }
		inline Vector3& Sub(const float c) { x -= c; y -= c; z -= c; return *this; }
		inline Vector3& Mult(const Vector3& other) { x *= other.GetX(); y *= other.GetY(); z *= other.GetZ(); return *this; }
		inline Vector3& Mult(const float c) { x *= c; y *= c; z *= c; return *this; }
		inline Vector3& Div(const Vector3& other) { x /= other.GetX(); y /= other.GetY(); z /= other.GetZ(); return *this; }
		inline Vector3& Div(const float c) { x /= c; y /= c; z /= c; return *this; }

		inline Vector3& Abs() { x = std::abs(x); y = std::abs(y); z = std::abs(z); return *this; }
		inline bool Equals(const Vector3 other) const { return x == other.GetX() && y == other.GetY() && z == other.GetZ(); }
		inline std::string ToString() const { return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")"; }

		inline Vector3& Copy() const { return Vector3(x, y, z); }

		inline Vector3& interpolate(const Vector3& dest, float factor)
		{
			return Sub(dest, *this).Mult(factor).Add(*this);
		}

		inline Vector3& Normalize() 
		{
			Div(Length());
			return *this;
		}

		Vector3& Rotate(const float angle, const Vector3& axis) 
		{
			float cosine = std::cos(-angle);
			float sine = std::sin(-angle);

			Set(Cross(Mult(axis, sine)).Add( // X rotation
				Mult(*this, cosine).Add( // Z rotation
				Mult(axis, Dot(Mult(axis, 1 - cosine)))))); // Y rotation
			return *this;
		}

		inline Vector3& Project(const Vector3& norm)
		{
			Vector3 normal = Normal(norm);
			Set(Mult(normal, Dot(normal)));
			return *this;
		}

		inline Vector3& ProjectOnPlane(const Vector3& norm)
		{
			Set(Sub(Project(*this, norm)));
			return *this;
		}

		//Swizzle Functions
		inline Vector2 getXY() const { return Vector2(x, y); }
		inline Vector2 getYZ() const { return Vector2(y, z); }
		inline Vector2 getXZ() const { return Vector2(x, z); }
		inline Vector2 getYX() const { return Vector2(y, x); }
		inline Vector2 getZY() const { return Vector2(z, y); }
		inline Vector2 getZX() const { return Vector2(z, x); }

		// Static functions
		inline static Vector3 Add(const Vector3& v1, const Vector3& v2) { return Vector3(v1.GetX() + v2.GetX(), v1.GetY() + v2.GetY(), v1.GetZ() + v2.GetZ()); }
		inline static Vector3 Add(const Vector3& v1, const float c) { return Vector3(v1.GetX() + c, v1.GetY() + c, v1.GetZ() + c); }
		inline static Vector3 Sub(const Vector3& v1, const Vector3& v2) { return Vector3(v1.GetX() - v2.GetX(), v1.GetY() - v2.GetY(), v1.GetZ() - v2.GetZ()); }
		inline static Vector3 Sub(const Vector3& v1, const float c) { return Vector3(v1.GetX() - c, v1.GetY() - c, v1.GetZ() - c); }
		inline static Vector3 Mult(const Vector3& v1, const Vector3& v2) { return Vector3(v1.GetX() * v2.GetX(), v1.GetY() * v2.GetY(), v1.GetZ() * v2.GetZ()); }
		inline static Vector3 Mult(const Vector3& v1, const float c) { return Vector3(v1.GetX() * c, v1.GetY() * c, v1.GetZ() * c); }
		inline static Vector3 Div(const Vector3& v1, const Vector3& v2) { return Vector3(v1.GetX() / v2.GetX(), v1.GetY() / v2.GetY(), v1.GetZ() / v2.GetZ()); }
		inline static Vector3 Div(const Vector3& v1, const float c) { return Vector3(v1.GetX() / c, v1.GetY() / c, v1.GetZ() / c); }

		inline static Vector3 Abs(const Vector3& v1) { return Vector3(std::abs(v1.GetX()), std::abs(v1.GetY()), std::abs(v1.GetZ())); }
		inline static Vector3 Normal(const Vector3& v1) {
			float l = v1.Length();
			return Vector3(v1.GetX() / l, v1.GetY() / l, v1.GetZ() / l);
		}

		static Vector3 Rotate(const Vector3& v, const float angle, const Vector3& axis) {
			float rad = (PI / 180) * angle;
			float cosine = std::cos(rad);
			float sine = std::sin(rad);

			return v.Cross(Mult(axis, sine)).Add( // X rotation
				Mult(v, cosine).Add( // Z rotation
				Mult(axis, v.Dot(Mult(axis, 1 - cosine)))));// Y rotation
		}

		inline static float Distance(const Vector3& v1, const Vector3& v2) {
			return Sub(v2, v1).Length();
		}

		inline static Vector3 Project(const Vector3& v, const Vector3& norm)
		{
			Vector3& normal = Normal(norm);
			return Mult(normal, v.Dot(normal));
		}

		inline static Vector3 ProjectOnPlane(const Vector3& v, const Vector3& norm)
		{
			return Sub(v, Project(v, norm));
		}

		/*static float AngleBetween(const Vector3& v1, const Vector3& v2) {
			float cosine = v1.Dot(v2) / (v1.Length() * v2.Length());
			return acos(cosine);
		}

		inline static float AngleTo(const Vector3& v1, const Vector3& v2) {
			return Sub(v2, v1).Angle();
		}*/
	};
}