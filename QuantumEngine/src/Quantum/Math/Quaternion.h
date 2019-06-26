#pragma once

#include "Quantum\Core.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Quantum {

	class QUANTUM_API Quaternion {
		float x, y, z, w;
	public:
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
		inline float GetW() const
		{
			return w;
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
		inline void SetW(const float _w)
		{
			w = _w;
		}

		inline void Set(const float x, const float y, const float z, const float w)
		{
			SetX(x);
			SetY(y);
			SetZ(z);
			SetW(w);
		}

		Quaternion(const float x, const float y, const float z, const float w)
		{
			Set(x, y, z, w);
		}

		Quaternion()
		{
			Set(0, 0, 0, 1);
		}

		Quaternion(const Vector3& axis, const float angle)
		{
			float sinHalfAngle = std::sin(angle / 2);
			float cosHalfAngle = std::cos(angle / 2);

			Set(axis.GetX() * sinHalfAngle, axis.GetY() * sinHalfAngle, axis.GetZ() * sinHalfAngle, cosHalfAngle);
		}

		inline float Length() const
		{
			return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
		}

		inline Quaternion& Normalize() 
		{
			float l = Length();
			Set(x / l, y / l, z / l, w / l);
			return *this;
		}

		inline Quaternion& Conjugate() {
			Set(-x, -y, -z, w);
			return *this;
		}

		inline Quaternion& Copy() const { return Quaternion(x, y, z, w); }
		inline Quaternion& Mult(const float r) { Set(x * r, y * r, z * r, w * r); return *this; }
		inline Quaternion Sub(const Quaternion& r) { Set(x - r.GetX(), y - r.GetY(), z - r.GetZ(), w - r.GetW()); return *this; }
		inline Quaternion Add(const Quaternion& r) { Set(x + r.GetX(), y + r.GetY(), z + r.GetZ(), w + r.GetW()); return *this; }

		Quaternion& Mult(const Quaternion& r)
		{
			float w_ = w * r.GetW() - x * r.GetX() - y * r.GetY() - z * r.GetZ();
			float x_ = x * r.GetW() + w * r.GetX() + y * r.GetZ() - z * r.GetY();
			float y_ = y * r.GetW() + w * r.GetY() + z * r.GetX() - x * r.GetZ();
			float z_ = z * r.GetW() + w * r.GetZ() + x * r.GetY() - y * r.GetX();

			Set(x_, y_, z_, w_);
			return *this;
		}

		Quaternion& Mult(const Vector3& r)
		{
			float w_ = -x * r.GetX() - y * r.GetY() - z * r.GetZ();
			float x_ = w * r.GetX() + y * r.GetZ() - z * r.GetY();
			float y_ = w * r.GetY() + z * r.GetX() - x * r.GetZ();
			float z_ = w * r.GetZ() + x * r.GetY() - y * r.GetX();

			Set(x_, y_, z_, w_);
			return *this;
		}

		inline bool Equals(const Quaternion& other) const
		{
			return x == other.GetX() && y == other.GetY() && z == other.GetZ() && w == other.GetW();
		}

		inline float Dot(const Quaternion& r) const
		{
			return x * r.GetX() + y * r.GetY() + z * r.GetZ() + w * r.GetW();
		}

		Matrix4& ToRotationMatrix() const
		{
			Vector3 fwd = Vector3(2.0f * (x*z - w*y), 2.0f * (y*z + w*x), 1.0f - 2.0f * (x*x + y*y));
			Vector3 up = Vector3(2.0f * (x*y + w*z), 1.0f - 2.0f * (x*x + z*z), 2.0f * (y*z - w*x));
			Vector3 right = Vector3(1.0f - 2.0f * (y*y + z*z), 2.0f * (x*y - w*z), 2.0f * (x*z + w*y));

			Matrix4 m = Matrix4();
			return m.InitRotation(fwd, up, right);
		}

		Quaternion& nlerp(const Quaternion& dest, const float lerpFactor, const bool shortest)
		{
			Quaternion& correctedDest = dest.Copy();

			if (shortest && Dot(dest) < 0)
				correctedDest =  Quaternion(-dest.GetX(), -dest.GetY(), -dest.GetZ(), -dest.GetW());

			return correctedDest.Sub(*this).Mult(lerpFactor).Add(*this).Normalize();
		}

		Quaternion& slerp(const Quaternion& dest, const float lerpFactor, const bool shortest)
		{
			const float EPSILON = 1e3f;

			float cos = Dot(dest);
			Quaternion& correctedDest = dest.Copy();

			if (shortest && cos < 0)
			{
				cos = -cos;
				correctedDest = Quaternion(-dest.GetX(), -dest.GetY(), -dest.GetZ(), -dest.GetW());
			}

			if (std::abs(cos) >= 1 - EPSILON)
				return nlerp(correctedDest, lerpFactor, false);

			float sin = std::sqrt(1.0f - cos * cos);
			float angle = std::atan2(sin, cos);
			float invSin = 1.0f / sin;

			float srcFactor = std::sin((1.0f - lerpFactor) * angle) * invSin;
			float destFactor = std::sin((lerpFactor)* angle) * invSin;

			return Mult(*this, srcFactor).Add(Mult(correctedDest, destFactor));
		}

		//Static Functions
		inline static Quaternion Normal(const Quaternion& q)
		{
			float l = q.Length();
			return Quaternion(q.GetX() / l, q.GetY() / l, q.GetZ() / l, q.GetW() / l);
		}

		inline static Quaternion Conjugate(const Quaternion& q) {
			return Quaternion(-q.GetX(), -q.GetY(), -q.GetZ(), q.GetW());
		}

		inline static Quaternion Mult(const Quaternion& q, const float r) { return Quaternion(q.GetX() * r, q.GetY() * r, q.GetZ() * r, q.GetX() * r); }
		inline static Quaternion Sub(const Quaternion& q, const Quaternion& r) { return Quaternion(q.GetX() - r.GetX(), q.GetY() - r.GetY(), q.GetZ() - r.GetZ(), q.GetW() - r.GetW()); }
		inline static Quaternion Add(const Quaternion& q, const Quaternion& r) { return Quaternion(q.GetX() + r.GetX(), q.GetY() + r.GetY(), q.GetZ() + r.GetZ(), q.GetW() + r.GetW()); }

		static Quaternion Mult(const Quaternion& q, const Quaternion& r)
		{
			float w_ = q.GetW() * r.GetW() - q.GetX() * r.GetX() - q.GetY() * r.GetY() - q.GetZ() * r.GetZ();
			float x_ = q.GetX() * r.GetW() + q.GetW() * r.GetX() + q.GetY() * r.GetZ() - q.GetZ() * r.GetY();
			float y_ = q.GetY() * r.GetW() + q.GetW() * r.GetY() + q.GetZ() * r.GetX() - q.GetX() * r.GetZ();
			float z_ = q.GetZ() * r.GetW() + q.GetW() * r.GetZ() + q.GetX() * r.GetY() - q.GetY() * r.GetX();

			return Quaternion(x_, y_, z_, w_);
		}

		static Quaternion Mult(const Quaternion& q, const Vector3& r)
		{
			float w_ = -q.GetX() * r.GetX() - q.GetY() * r.GetY() - q.GetZ() * r.GetZ();
			float x_ = q.GetW() * r.GetX() + q.GetY() * r.GetZ() - q.GetZ() * r.GetY();
			float y_ = q.GetW() * r.GetY() + q.GetZ() * r.GetX() - q.GetX() * r.GetZ();
			float z_ = q.GetW() * r.GetZ() + q.GetX() * r.GetY() - q.GetY() * r.GetX();

			return Quaternion(x_, y_, z_, w_);
		}
	};
}