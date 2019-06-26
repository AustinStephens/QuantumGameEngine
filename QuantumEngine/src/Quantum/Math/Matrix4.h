#pragma once

#include "Quantum\Core.h"
#include "Vector3.h"

namespace Quantum {

	class QUANTUM_API Matrix4 {
		float m[4][4];
	public:
		// INITS
		Matrix4& InitIdentity()
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if (j == i) m[i][j] = 1;
					else m[i][j] = 0;
				}
			}

			return *this;
		}

		Matrix4& InitTranslation(const float x, const float y, const float z)
		{
			m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = x;
			m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = y;
			m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = z;
			m[1][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;

			return *this;
		}

		Matrix4& InitScale(const float x, const float y, const float z)
		{
			m[0][0] = x; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
			m[1][0] = 0; m[1][1] = y; m[1][2] = 0; m[1][3] = 0;
			m[2][0] = 0; m[2][1] = 0; m[2][2] = z; m[2][3] = 0;
			m[1][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;

			return *this;
		}

		Matrix4& InitRotation(const Vector3& fwd, const Vector3& up)
		{
			Vector3& f = Vector3::Normal(fwd); // forward

			Vector3& r = Vector3::Normal(up); // right
			r = r.Cross(f);

			Vector3& u = f.Cross(r);

			return InitRotation(f, u, r);
		}

		Matrix4& InitRotation(float x, float y, float z)
		{
			Matrix4 rx = Matrix4();
			Matrix4 ry = Matrix4();
			Matrix4 rz = Matrix4();

			x = (PI / 180) * x;
			y = (PI / 180) * y;
			z = (PI / 180) * z;

			rz.m[0][0] = std::cos(z); rz.m[0][1] = -std::sin(z); rz.m[0][2] = 0; rz.m[0][3] = 0;
			rz.m[1][0] = std::sin(z); rz.m[1][1] = std::cos(z); rz.m[0][2] = 0; rz.m[1][3] = 0;
			rz.m[2][0] = 0; rz.m[2][1] = 0; rz.m[2][2] = 1; rz.m[2][3] = 0;
			rz.m[3][0] = 0; rz.m[3][1] = 0; rz.m[3][2] = 0; rz.m[3][3] = 1;

			rx.m[0][0] = 1; rx.m[0][1] = 0; rx.m[0][2] = 0; rx.m[0][3] = 0;
			rx.m[1][0] = 0; rx.m[1][1] = std::cos(x); rx.m[1][2] = -std::sin(x); rx.m[1][3] = 0;
			rx.m[2][0] = 0; rx.m[2][1] = std::sin(x); rx.m[2][2] = std::cos(x); rx.m[2][3] = 0;
			rx.m[3][0] = 0; rx.m[3][1] = 0; rx.m[3][2] = 0; rx.m[3][3] = 1;

			ry.m[0][0] = std::cos(y); ry.m[0][1] = 0; ry.m[0][2] = -std::sin(y); ry.m[0][3] = 0;
			ry.m[1][0] = 0; ry.m[1][1] = 1; ry.m[1][2] = 0; ry.m[1][3] = 0;
			ry.m[2][0] = std::sin(y); ry.m[2][1] = 0; ry.m[2][2] = std::cos(y); ry.m[2][3] = 0;
			ry.m[3][0] = 0; ry.m[3][1] = 0; ry.m[3][2] = 0; ry.m[3][3] = 1;

			SetM(rz.Mult(ry.Mult(rx)));

			return *this;
		}

		Matrix4& InitRotation(const Vector3& forward, const Vector3& up, const Vector3& right)
		{
			Vector3 f = forward;
			Vector3 r = right;
			Vector3 u = up;

			m[0][0] = r.GetX();	m[0][1] = r.GetY();	m[0][2] = r.GetZ();	m[0][3] = 0;
			m[1][0] = u.GetX();	m[1][1] = u.GetY();	m[1][2] = u.GetZ();	m[1][3] = 0;
			m[2][0] = f.GetX();	m[2][1] = f.GetY();	m[2][2] = f.GetZ();	m[2][3] = 0;
			m[3][0] = 0;		m[3][1] = 0;		m[3][2] = 0;		m[3][3] = 1;

			return *this;
		}

		// METHODS
		Vector3& Transform(const Vector3& r)
		{
			return Vector3(m[0][0] * r.GetX() + m[0][1] * r.GetY() + m[0][2] * r.GetZ() + m[0][3],
				m[1][0] * r.GetX() + m[1][1] * r.GetY() + m[1][2] * r.GetZ() + m[1][3],
				m[2][0] * r.GetX() + m[2][1] * r.GetY() + m[2][2] * r.GetZ() + m[2][3]);
		}

		Matrix4& Mult(const Matrix4& r)
		{
			Matrix4 res = Matrix4();

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					res.Set(i, j, m[i][0] * r.Get(0, j) + m[i][1] * r.Get(1, j) +
						m[i][2] * r.Get(2, j) + m[i][3] * r.Get(3, j));
				}
			}

			return res;
		}

		// GETTERS
		inline float Get(int x, int y) const {
			return m[x][y];
		}

		// SETTERS
		inline void Set(int x, int y, float val) {
			m[x][y] = val;
		}

		inline void SetM(float _m[4][4]) {
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					Set(i, j, _m[i][j]);
				}
			}
		}

		inline void SetM(const Matrix4& _m) {
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					Set(i, j, _m.Get(i,j));
				}
			}
		}
	};
}