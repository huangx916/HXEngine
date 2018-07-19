#pragma once
#include "HXCommon.h"

namespace HX3D
{
	// 行主序
	struct HXMatrix44
	{
		static HXMatrix44 IDENTITY;
		float m[4][4];

		HXMatrix44()
		{
			memset(m, 0, sizeof(float) * 16);
		}

		HXMatrix44(const HXMatrix44& right)
		{
			m[0][0] = right.m[0][0]; m[0][1] = right.m[0][1]; m[0][2] = right.m[0][2]; m[0][3] = right.m[0][3];
			m[1][0] = right.m[1][0]; m[1][1] = right.m[1][1]; m[1][2] = right.m[1][2]; m[1][3] = right.m[1][3];
			m[2][0] = right.m[2][0]; m[2][1] = right.m[2][1]; m[2][2] = right.m[2][2]; m[2][3] = right.m[2][3];
			m[3][0] = right.m[3][0]; m[3][1] = right.m[3][1]; m[3][2] = right.m[3][2]; m[3][3] = right.m[3][3];
		}

		HXMatrix44(float m0_0, float m0_1, float m0_2, float m0_3,
			float m1_0, float m1_1, float m1_2, float m1_3,
			float m2_0, float m2_1, float m2_2, float m2_3,
			float m3_0, float m3_1, float m3_2, float m3_3)
		{
			m[0][0] = m0_0; m[0][1] = m0_1; m[0][2] = m0_2; m[0][3] = m0_3;
			m[1][0] = m1_0; m[1][1] = m1_1; m[1][2] = m1_2; m[1][3] = m1_3;
			m[2][0] = m2_0; m[2][1] = m2_1; m[2][2] = m2_2; m[2][3] = m2_3;
			m[3][0] = m3_0; m[3][1] = m3_1; m[3][2] = m3_2; m[3][3] = m3_3;
		}

		// 转置矩阵
		inline HXMatrix44 Transpose() const
		{
			HXMatrix44 temp;	//如果返回指针就有问题，调用其他函数后，指针所指对象错乱。此处不是指针直接拷贝了没关系
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp.m[i][j] = m[j][i];
				}
			}
			return temp;
		}

		// 逆矩阵
		/*inline HXMatrix44 Inverse() const
		{
			float Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			float Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
			float Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

			float Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			float Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
			float Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

			float Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			float Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
			float Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

			float Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			float Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
			float Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

			float Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			float Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
			float Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

			float Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
			float Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
			float Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

			const HXVector4D SignA = HXVector4D(1.0, -1.0, 1.0, -1.0);
			const HXVector4D SignB = HXVector4D(-1.0, 1.0, -1.0, 1.0);

			HXVector4D Fac0 = HXVector4D(Coef00, Coef00, Coef02, Coef03);
			HXVector4D Fac1 = HXVector4D(Coef04, Coef04, Coef06, Coef07);
			HXVector4D Fac2 = HXVector4D(Coef08, Coef08, Coef10, Coef11);
			HXVector4D Fac3 = HXVector4D(Coef12, Coef12, Coef14, Coef15);
			HXVector4D Fac4 = HXVector4D(Coef16, Coef16, Coef18, Coef19);
			HXVector4D Fac5 = HXVector4D(Coef20, Coef20, Coef22, Coef23);

			HXVector4D Vec0 = HXVector4D(m[1][0], m[0][0], m[0][0], m[0][0]);
			HXVector4D Vec1 = HXVector4D(m[1][1], m[0][1], m[0][1], m[0][1]);
			HXVector4D Vec2 = HXVector4D(m[1][2], m[0][2], m[0][2], m[0][2]);
			HXVector4D Vec3 = HXVector4D(m[1][3], m[0][3], m[0][3], m[0][3]);

			HXVector4D Inv0 = SignA * (Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			HXVector4D Inv1 = SignB * (Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			HXVector4D Inv2 = SignA * (Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			HXVector4D Inv3 = SignB * (Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			HXMatrix44 temp = HXMatrix44(Inv0, Inv1, Inv2, Inv3);

			HXVector4D Row0 = HXVector4D(temp.m[0][0], temp.m[1][0], temp.m[2][0], temp.m[3][0]);
			HXVector4D Column0 = HXVector4D(temp.m[0][0], temp.m[0][1], temp.m[0][2], temp.m[0][3]);

			float Determinant = Column0.dotProduct(Row0);

			temp = temp / Determinant;

			return temp;
		}*/

		inline HXMatrix44 operator+(const HXMatrix44& right) const
		{
			return HXMatrix44(m[0][0] + right.m[0][0], m[0][1] + right.m[0][1], m[0][2] + right.m[0][2], m[0][3] + right.m[0][3],
				m[1][0] + right.m[1][0], m[1][1] + right.m[1][1], m[1][2] + right.m[1][2], m[1][3] + right.m[1][3],
				m[2][0] + right.m[2][0], m[2][1] + right.m[2][1], m[2][2] + right.m[2][2], m[2][3] + right.m[2][3],
				m[3][0] + right.m[3][0], m[3][1] + right.m[3][1], m[3][2] + right.m[3][2], m[3][3] + right.m[3][3]);
		}

		inline HXMatrix44 operator-(const HXMatrix44& right)
		{
			return HXMatrix44(m[0][0] - right.m[0][0], m[0][1] - right.m[0][1], m[0][2] - right.m[0][2], m[0][3] - right.m[0][3],
				m[1][0] - right.m[1][0], m[1][1] - right.m[1][1], m[1][2] - right.m[1][2], m[1][3] - right.m[1][3],
				m[2][0] - right.m[2][0], m[2][1] - right.m[2][1], m[2][2] - right.m[2][2], m[2][3] - right.m[2][3],
				m[3][0] - right.m[3][0], m[3][1] - right.m[3][1], m[3][2] - right.m[3][2], m[3][3] - right.m[3][3]);
		}

		inline HXMatrix44 operator*(float factor) const
		{
			return HXMatrix44(m[0][0] * factor, m[0][1] * factor, m[0][2] * factor, m[0][3] * factor,
				m[1][0] * factor, m[1][1] * factor, m[1][2] * factor, m[1][3] * factor,
				m[2][0] * factor, m[2][1] * factor, m[2][2] * factor, m[2][3] * factor,
				m[3][0] * factor, m[3][1] * factor, m[3][2] * factor, m[3][3] * factor);
		}

		inline HXMatrix44 operator/(float factor) const
		{
			return HXMatrix44(m[0][0] / factor, m[0][1] / factor, m[0][2] / factor, m[0][3] / factor,
				m[1][0] / factor, m[1][1] / factor, m[1][2] / factor, m[1][3] / factor,
				m[2][0] / factor, m[2][1] / factor, m[2][2] / factor, m[2][3] / factor,
				m[3][0] / factor, m[3][1] / factor, m[3][2] / factor, m[3][3] / factor);
		}

		inline HXMatrix44 operator*(const HXMatrix44& right) const
		{
			HXMatrix44 temp;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						temp.m[i][j] += m[i][k] * right.m[k][j];
					}
				}
			}
			return temp;
		}

		inline HXMatrix44& operator=(const HXMatrix44& right)
		{
			m[0][0] = right.m[0][0], m[0][1] = right.m[0][1], m[0][2] = right.m[0][2], m[0][3] = right.m[0][3];
			m[1][0] = right.m[1][0], m[1][1] = right.m[1][1], m[1][2] = right.m[1][2], m[1][3] = right.m[1][3];
			m[2][0] = right.m[2][0], m[2][1] = right.m[2][1], m[2][2] = right.m[2][2], m[2][3] = right.m[2][3];
			m[3][0] = right.m[3][0], m[3][1] = right.m[3][1], m[3][2] = right.m[3][2], m[3][3] = right.m[3][3];

			return *this;
		}

		inline bool operator==(const HXMatrix44& right) const
		{
			if (   m[0][0] != right.m[0][0] || m[0][1] != right.m[0][1] || m[0][2] != right.m[0][2] || m[0][3] != right.m[0][3]
				|| m[1][0] != right.m[1][0] || m[1][1] != right.m[1][1] || m[1][2] != right.m[1][2] || m[1][3] != right.m[1][3]
				|| m[2][0] != right.m[2][0] || m[2][1] != right.m[2][1] || m[2][2] != right.m[2][2] || m[2][3] != right.m[2][3]
				|| m[3][0] != right.m[3][0] || m[3][1] != right.m[3][1] || m[3][2] != right.m[3][2] || m[3][3] != right.m[3][3])
			{
				return false;
			}
			return true;
		}		
	};

	struct HXMatrix33
	{
		static HXMatrix33 IDENTITY;
		float m[3][3];

		HXMatrix33()
		{
			memset(m, 0, sizeof(float) * 9);
		}

		HXMatrix33(HXMatrix44 mat)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m[i][j] = mat.m[i][j];
				}
			}
		}

		HXMatrix33(float m0_0, float m0_1, float m0_2,
				   float m1_0, float m1_1, float m1_2,
				   float m2_0, float m2_1, float m2_2)
		{
			m[0][0] = m0_0; m[0][1] = m0_1; m[0][2] = m0_2;
			m[1][0] = m1_0; m[1][1] = m1_1; m[1][2] = m1_2;
			m[2][0] = m2_0; m[2][1] = m2_1; m[2][2] = m2_2;
		}

		// 转置矩阵
		inline HXMatrix33 Transpose() const
		{
			HXMatrix33 temp;	//如果返回指针就有问题，调用其他函数后，指针所指对象错乱。此处不是指针直接拷贝了没关系
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					temp.m[i][j] = m[j][i];
				}
			}
			return temp;
		}

		// 逆矩阵 待测试
		inline HXMatrix33 Inverse() const
		{
			float Determinant =
				m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
				- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
				+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
			HXMatrix33 temp;
			temp.m[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]);
			temp.m[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);
			temp.m[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]);
			temp.m[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]);
			temp.m[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]);
			temp.m[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]);
			temp.m[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]);
			temp.m[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]);
			temp.m[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]);
			temp = temp / Determinant;
			return temp;
		}

		inline HXMatrix33 operator*(float factor) const
		{
			return HXMatrix33(m[0][0] * factor, m[0][1] * factor, m[0][2] * factor,
							  m[1][0] * factor, m[1][1] * factor, m[1][2] * factor,
							  m[2][0] * factor, m[2][1] * factor, m[2][2] * factor);
		}

		inline HXMatrix33 operator/(float factor) const
		{
			return HXMatrix33(m[0][0] / factor, m[0][1] / factor, m[0][2] / factor,
				m[1][0] / factor, m[1][1] / factor, m[1][2] / factor,
				m[2][0] / factor, m[2][1] / factor, m[2][2] / factor);
		}
	};
}

