#include "..\include\HXMatrix4x4.h"
#include "MathUtils3D.h"

namespace HX3D
{
	HXMatrix4x4::HXMatrix4x4()
	{
	}


	HXMatrix4x4::~HXMatrix4x4()
	{
	}

	void HXMatrix4x4::createRotationX(float rad, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* oe = out.elements;
		float s = sin(rad), c = cos(rad);

		oe[1] = oe[2] = oe[3] = oe[4] = oe[7] = oe[8] = oe[11] = oe[12] = oe[13] = oe[14] = 0;
		oe[0] = oe[15] = 1;
		oe[5] = oe[10] = c;
		oe[6] = s;
		oe[9] = -s;
	}

	void HXMatrix4x4::createRotationY(float rad, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* oe = out.elements;
		float s = sin(rad), c = cos(rad);

		oe[1] = oe[3] = oe[4] = oe[6] = oe[7] = oe[9] = oe[11] = oe[12] = oe[13] = oe[14] = 0;
		oe[5] = oe[15] = 1;
		oe[0] = oe[10] = c;
		oe[2] = -s;
		oe[8] = s;
	}

	void HXMatrix4x4::createRotationZ(float rad, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* oe = out.elements;
		float s = sin(rad), c = cos(rad);

		oe[2] = oe[3] = oe[6] = oe[7] = oe[8] = oe[9] = oe[11] = oe[12] = oe[13] = oe[14] = 0;
		oe[10] = oe[15] = 1;
		oe[0] = oe[5] = c;
		oe[1] = s;
		oe[4] = -s;
	}

	void HXMatrix4x4::createRotationYawPitchRoll(float yaw, float pitch, float roll, HXMatrix4x4& result)
	{
		HXQuaternion::createFromYawPitchRoll(yaw, pitch, roll, _tempQuaternion);
		createRotationQuaternion(_tempQuaternion, result);
	}

	void HXMatrix4x4::createRotationAxis(const HXVector3& axis, float angle, HXMatrix4x4& result)
	{
		const float* axisE = axis.elements;
		float x = axisE[0];
		float y = axisE[1];
		float z = axisE[2];
		float _cos = cos(angle);
		float _sin = sin(angle);
		float xx = x * x;
		float yy = y * y;
		float zz = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;

		float* resultE = result.elements;
		resultE[3] = resultE[7] = resultE[11] = resultE[12] = resultE[13] = resultE[14] = 0;
		resultE[15] = 1.0;
		resultE[0] = xx + (_cos * (1.0 - xx));
		resultE[1] = (xy - (_cos * xy)) + (_sin * z);
		resultE[2] = (xz - (_cos * xz)) - (_sin * y);
		resultE[4] = (xy - (_cos * xy)) - (_sin * z);
		resultE[5] = yy + (_cos * (1.0 - yy));
		resultE[6] = (yz - (_cos * yz)) + (_sin * x);
		resultE[8] = (xz - (_cos * xz)) + (_sin * y);
		resultE[9] = (yz - (_cos * yz)) - (_sin * x);
		resultE[10] = zz + (_cos * (1.0 - zz));
	}

	void HXMatrix4x4::createRotationQuaternion(const HXQuaternion& rotation, HXMatrix4x4& result)
	{
		const float* rotationE = rotation.elements;
		float* resultE = result.elements;
		float rotationX = rotationE[0];
		float rotationY = rotationE[1];
		float rotationZ = rotationE[2];
		float rotationW = rotationE[3];
		
		float xx = rotationX * rotationX;
		float yy = rotationY * rotationY;
		float zz = rotationZ * rotationZ;
		float xy = rotationX * rotationY;
		float zw = rotationZ * rotationW;
		float zx = rotationZ * rotationX;
		float yw = rotationY * rotationW;
		float yz = rotationY * rotationZ;
		float xw = rotationX * rotationW;

		resultE[3] = resultE[7] = resultE[11] = resultE[12] = resultE[13] = resultE[14] = 0;
		resultE[15] = 1.0;
		resultE[0] = 1.0 - (2.0 * (yy + zz));
		resultE[1] = 2.0 * (xy + zw);
		resultE[2] = 2.0 * (zx - yw);
		resultE[4] = 2.0 * (xy - zw);
		resultE[5] = 1.0 - (2.0 * (zz + xx));
		resultE[6] = 2.0 * (yz + xw);
		resultE[8] = 2.0 * (zx + yw);
		resultE[9] = 2.0 * (yz - xw);
		resultE[10] = 1.0 - (2.0 * (yy + xx));
	}

	void HXMatrix4x4::createTranslate(const HXVector3& trans, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		const float* te = trans.elements;
		float* oe = out.elements;
		oe[4] = oe[8] = oe[1] = oe[9] = oe[2] = oe[6] = oe[3] = oe[7] = oe[11] = 0;
		oe[0] = oe[5] = oe[10] = oe[15] = 1;
		oe[12] = te[0];
		oe[13] = te[1];
		oe[14] = te[2];
	}

	void HXMatrix4x4::createScaling(const HXVector3& scale, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		const float* se = scale.elements;
		float* oe = out.elements;
		oe[0] = se[0];
		oe[5] = se[1];
		oe[10] = se[2];
		oe[1] = oe[4] = oe[8] = oe[12] = oe[9] = oe[13] = oe[2] = oe[6] = oe[14] = oe[3] = oe[7] = oe[11] = 0;
		oe[15] = 1;
	}

	void HXMatrix4x4::multiply(HXMatrix4x4& left, HXMatrix4x4& right, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		int i; float* e; float* a; float* b; float ai0; float ai1; float ai2; float ai3;

		e = out.elements;
		a = left.elements;
		b = right.elements;
		if (e == b) {
			float temp[16];
			b = temp;
			for (i = 0; i < 16; ++i) {
				b[i] = e[i];
			}
		}

		for (i = 0; i < 4; i++) {
			ai0 = a[i];
			ai1 = a[i + 4];
			ai2 = a[i + 8];
			ai3 = a[i + 12];
			e[i] = ai0 * b[0] + ai1 * b[1] + ai2 * b[2] + ai3 * b[3];
			e[i + 4] = ai0 * b[4] + ai1 * b[5] + ai2 * b[6] + ai3 * b[7];
			e[i + 8] = ai0 * b[8] + ai1 * b[9] + ai2 * b[10] + ai3 * b[11];
			e[i + 12] = ai0 * b[12] + ai1 * b[13] + ai2 * b[14] + ai3 * b[15];
		}
	}

	void HXMatrix4x4::createFromQuaternion(const HXQuaternion& rotation, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* e = out.elements;
		const float* q = rotation.elements;
		float x = q[0], y = q[1], z = q[2], w = q[3];
		float x2 = x + x;
		float y2 = y + y;
		float z2 = z + z;
		
		float xx = x * x2;
		float yx = y * x2;
		float yy = y * y2;
		float zx = z * x2;
		float zy = z * y2;
		float zz = z * z2;
		float wx = w * x2;
		float wy = w * y2;
		float wz = w * z2;

		e[0] = 1 - yy - zz;
		e[1] = yx + wz;
		e[2] = zx - wy;
		e[3] = 0;

		e[4] = yx - wz;
		e[5] = 1 - xx - zz;
		e[6] = zy + wx;
		e[7] = 0;

		e[8] = zx + wy;
		e[9] = zy - wx;
		e[10] = 1 - xx - yy;
		e[11] = 0;

		e[12] = 0;
		e[13] = 0;
		e[14] = 0;
		e[15] = 1;
	}

	void HXMatrix4x4::createAffineTransformation(const HXVector3& trans, const HXQuaternion& rot, const HXVector3& scale, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		const float* te = trans.elements;
		const float* re = rot.elements;
		const float* se = scale.elements;
		float* oe = out.elements;

		float x = re[0], y = re[1], z = re[2], w = re[3], x2 = x + x, y2 = y + y, z2 = z + z;
		float xx = x * x2, xy = x * y2, xz = x * z2, yy = y * y2, yz = y * z2, zz = z * z2;
		float wx = w * x2, wy = w * y2, wz = w * z2, sx = se[0], sy = se[1], sz = se[2];

		oe[0] = (1 - (yy + zz)) * sx;
		oe[1] = (xy + wz) * sx;
		oe[2] = (xz - wy) * sx;
		oe[3] = 0;
		oe[4] = (xy - wz) * sy;
		oe[5] = (1 - (xx + zz)) * sy;
		oe[6] = (yz + wx) * sy;
		oe[7] = 0;
		oe[8] = (xz + wy) * sz;
		oe[9] = (yz - wx) * sz;
		oe[10] = (1 - (xx + yy)) * sz;
		oe[11] = 0;
		oe[12] = te[0];
		oe[13] = te[1];
		oe[14] = te[2];
		oe[15] = 1;
	}

	void HXMatrix4x4::createLookAt(const HXVector3& eye, const HXVector3& target, const HXVector3& up, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		//注:WebGL为右手坐标系统
		float* oE = out.elements;
		HXVector3& xaxis = _tempVector0;
		HXVector3& yaxis = _tempVector1;
		HXVector3& zaxis = _tempVector2;
		HXVector3::subtract(eye, target, zaxis);
		HXVector3::normalize(zaxis, zaxis);
		HXVector3::cross(up, zaxis, xaxis);
		HXVector3::normalize(xaxis, xaxis);
		HXVector3::cross(zaxis, xaxis, yaxis);

		out.identity();
		oE[0] = xaxis.x();
		oE[4] = xaxis.y();
		oE[8] = xaxis.z();
		oE[1] = yaxis.x();
		oE[5] = yaxis.y();
		oE[9] = yaxis.z();
		oE[2] = zaxis.x();
		oE[6] = zaxis.y();
		oE[10] = zaxis.z();

		oE[12] = -HXVector3::dot(xaxis, eye);
		oE[13] = -HXVector3::dot(yaxis, eye);
		oE[14] = -HXVector3::dot(zaxis, eye);
	}

	void HXMatrix4x4::createPerspective(float fov, float aspect, float near, float far, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* oe = out.elements;

		float f = 1.0 / tan(fov / 2), nf = 1 / (near - far);
		oe[0] = f / aspect;
		oe[5] = f;
		oe[10] = (far + near) * nf;
		oe[11] = -1;
		oe[14] = (2 * far * near) * nf;
		oe[1] = oe[2] = oe[3] = oe[4] = oe[6] = oe[7] = oe[8] = oe[9] = oe[12] = oe[13] = oe[15] = 0;
	}

	void HXMatrix4x4::createOrthoOffCenterRH(float left, float right, float bottom, float top, float near, float far, HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* oe = out.elements;

		float lr = 1 / (left - right);
		float bt = 1 / (bottom - top);
		float nf = 1 / (near - far);
		oe[1] = oe[2] = oe[3] = oe[4] = oe[6] = oe[7] = oe[8] = oe[9] = oe[11] = 0;
		oe[15] = 1;
		oe[0] = -2 * lr;
		oe[5] = -2 * bt;
		oe[10] = 2 * nf;
		oe[12] = (left + right) * lr;
		oe[13] = (top + bottom) * bt;
		oe[14] = (far + near) * nf;
	}

	HXMatrix4x4::HXMatrix4x4(float m11, float m12, float m13, float m14
		, float m21, float m22, float m23, float m24
		, float m31, float m32, float m33, float m34
		, float m41, float m42, float m43, float m44)
	{
		float* e = this->elements;
		e[0] = m11;
		e[1] = m12;
		e[2] = m13;
		e[3] = m14;
		e[4] = m21;
		e[5] = m22;
		e[6] = m23;
		e[7] = m24;
		e[8] = m31;
		e[9] = m32;
		e[10] = m33;
		e[11] = m34;
		e[12] = m41;
		e[13] = m42;
		e[14] = m43;
		e[15] = m44;
	}

	float HXMatrix4x4::getElementByRowColumn(int row, int column)
	{
		if (row < 0 || row > 3)
			std::cerr << "Rows and columns for matrices run from 0 to 3, inclusive." << std::endl;
		if (column < 0 || column > 3)
			std::cerr << "Rows and columns for matrices run from 0 to 3, inclusive." << std::endl;

		return elements[(row * 4) + column];
	}

	void HXMatrix4x4::setElementByRowColumn(int row, int column, float value)
	{
		if (row < 0 || row > 3)
			std::cerr << "Rows and columns for matrices run from 0 to 3, inclusive." << std::endl;
		if (column < 0 || column > 3)
			std::cerr << "Rows and columns for matrices run from 0 to 3, inclusive." << std::endl;

		elements[(row * 4) + column] = value;
	}

	bool HXMatrix4x4::equalsOtherMatrix(const HXMatrix4x4& other) const
	{
		const float* e = this->elements;
		const float* oe = other.elements;

		return (MathUtils3D::nearEqual(e[0], oe[0]) && MathUtils3D::nearEqual(e[1], oe[1]) && MathUtils3D::nearEqual(e[2], oe[2]) && MathUtils3D::nearEqual(e[3], oe[3]) && MathUtils3D::nearEqual(e[4], oe[4]) && MathUtils3D::nearEqual(e[5], oe[5]) && MathUtils3D::nearEqual(e[6], oe[6]) && MathUtils3D::nearEqual(e[7], oe[7]) && MathUtils3D::nearEqual(e[8], oe[8]) && MathUtils3D::nearEqual(e[9], oe[9]) && MathUtils3D::nearEqual(e[10], oe[10]) && MathUtils3D::nearEqual(e[11], oe[11]) && MathUtils3D::nearEqual(e[12], oe[12]) && MathUtils3D::nearEqual(e[13], oe[13]) && MathUtils3D::nearEqual(e[14], oe[14]) && MathUtils3D::nearEqual(e[15], oe[15]));
	}

	bool HXMatrix4x4::decomposeTransRotScale(HXVector3& translation, HXQuaternion& rotation, HXVector3& scale)
	{
		HXMatrix4x4& rotationMatrix = _tempMatrix4x4;
		if (decomposeTransRotMatScale(translation, rotationMatrix, scale))
		{
			HXQuaternion::createFromMatrix4x4(rotationMatrix, rotation);
			return true;
		}
		else
		{
			rotation.identity();
			return false;
		}
		return true;
	}

	bool HXMatrix4x4::decomposeTransRotMatScale(HXVector3& translation, HXMatrix4x4& rotationMatrix, HXVector3& scale)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* e = this->elements;
		float* te = translation.elements;
		float* re = rotationMatrix.elements;
		float* se = scale.elements;

		//Get the translation. 
		te[0] = e[12];
		te[1] = e[13];
		te[2] = e[14];

		//Scaling is the length of the rows. 
		float m11 = e[0], m12 = e[1], m13 = e[2];
		float m21 = e[4], m22 = e[5], m23 = e[6];
		float m31 = e[8], m32 = e[9], m33 = e[10];

		float sX = se[0] = sqrt((m11 * m11) + (m12 * m12) + (m13 * m13));
		float sY = se[1] = sqrt((m21 * m21) + (m22 * m22) + (m23 * m23));
		float sZ = se[2] = sqrt((m31 * m31) + (m32 * m32) + (m33 * m33));

		//If any of the scaling factors are zero, than the rotation matrix can not exist. 
		if (MathUtils3D::isZero(sX) || MathUtils3D::isZero(sY) || MathUtils3D::isZero(sZ)) {
			re[1] = re[2] = re[3] = re[4] = re[6] = re[7] = re[8] = re[9] = re[11] = re[12] = re[13] = re[14] = 0;
			re[0] = re[5] = re[10] = re[15] = 1;
			return false;
		}

		// Calculate an perfect orthonormal matrix (no reflections)
		HXVector3& at = _tempVector0;
		float* atE = at.elements;
		atE[0] = m31 / sZ;
		atE[1] = m32 / sZ;
		atE[2] = m33 / sZ;
		HXVector3& tempRight = _tempVector1;
		float* tempRightE = tempRight.elements;
		tempRightE[0] = m11 / sX;
		tempRightE[1] = m12 / sX;
		tempRightE[2] = m13 / sX;
		HXVector3& up = _tempVector2;
		HXVector3::cross(at, tempRight, up);
		HXVector3& right = _tempVector1;
		HXVector3::cross(up, at, right);

		re[3] = re[7] = re[11] = re[12] = re[13] = re[14] = 0;
		re[15] = 1;
		re[0] = right.x();
		re[1] = right.y();
		re[2] = right.z();

		re[4] = up.x();
		re[5] = up.y();
		re[6] = up.z();

		re[8] = at.x();
		re[9] = at.y();
		re[10] = at.z();

		// In case of reflexions//TODO:是否不用计算dot后的值即为结果
		((re[0] * m11 + re[1] * m12 + re[2] * m13)/*Vector3.dot(right,Right)*/ < 0.0) && (se[0] = -sX);
		((re[4] * m21 + re[5] * m22 + re[6] * m23)/* Vector3.dot(up, Up)*/ < 0.0) && (se[1] = -sY);
		((re[8] * m31 + re[9] * m32 + re[10] * m33)/*Vector3.dot(at, Backward)*/ < 0.0) && (se[2] = -sZ);

		return true;
	}

	void HXMatrix4x4::decomposeYawPitchRoll(HXVector3& yawPitchRoll)
	{
		float* yawPitchRollE = yawPitchRoll.elements;
		float pitch = asin(-elements[9]);
		yawPitchRollE[1] = pitch;
		// Hardcoded constant - burn him, he's a witch
		// double threshold = 0.001; 
		float test = cos(pitch);
		if (test > MathUtils3D::zeroTolerance) {
			yawPitchRollE[2] = atan2(elements[1], elements[5]);
			yawPitchRollE[0] = atan2(elements[8], elements[10]);
		}
		else {
			yawPitchRollE[2] = atan2(-elements[4], elements[0]);
			yawPitchRollE[0] = 0.0;
		}
	}

	void HXMatrix4x4::normalize()
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* v = this->elements;
		float c = v[0], d = v[1], e = v[2], g = sqrt(c * c + d * d + e * e);
		if (g) {
			if (g == 1)
				return;
		}
		else {
			v[0] = 0;
			v[1] = 0;
			v[2] = 0;
			return;
		}
		g = 1 / g;
		v[0] = c * g;
		v[1] = d * g;
		v[2] = e * g;
	}

	HXMatrix4x4& HXMatrix4x4::transpose()
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* e; float t;
		e = this->elements;
		t = e[1];
		e[1] = e[4];
		e[4] = t;
		t = e[2];
		e[2] = e[8];
		e[8] = t;
		t = e[3];
		e[3] = e[12];
		e[12] = t;
		t = e[6];
		e[6] = e[9];
		e[9] = t;
		t = e[7];
		e[7] = e[13];
		e[13] = t;
		t = e[11];
		e[11] = e[14];
		e[14] = t;

		return *this;
	}

	void HXMatrix4x4::invert(HXMatrix4x4& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float* ae = this->elements;
		float* oe = out.elements;
		float a00 = ae[0], a01 = ae[1], a02 = ae[2], a03 = ae[3], a10 = ae[4], a11 = ae[5], a12 = ae[6], a13 = ae[7], a20 = ae[8], a21 = ae[9], a22 = ae[10], a23 = ae[11], a30 = ae[12], a31 = ae[13], a32 = ae[14], a33 = ae[15],

			b00 = a00 * a11 - a01 * a10, b01 = a00 * a12 - a02 * a10, b02 = a00 * a13 - a03 * a10, b03 = a01 * a12 - a02 * a11, b04 = a01 * a13 - a03 * a11, b05 = a02 * a13 - a03 * a12, b06 = a20 * a31 - a21 * a30, b07 = a20 * a32 - a22 * a30, b08 = a20 * a33 - a23 * a30, b09 = a21 * a32 - a22 * a31, b10 = a21 * a33 - a23 * a31, b11 = a22 * a33 - a23 * a32,

			// Calculate the determinant 
			det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

		if (abs(det) == 0.0) {
			return;
		}
		det = 1.0 / det;

		oe[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
		oe[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
		oe[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
		oe[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
		oe[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
		oe[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
		oe[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
		oe[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
		oe[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
		oe[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
		oe[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
		oe[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
		oe[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
		oe[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
		oe[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
		oe[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;
	}

	void HXMatrix4x4::identity()
	{
		float* e = this->elements;
		e[1] = e[2] = e[3] = e[4] = e[6] = e[7] = e[8] = e[9] = e[11] = e[12] = e[13] = e[14] = 0;
		e[0] = e[5] = e[10] = e[15] = 1;
	}

	void HXMatrix4x4::translation(const HXVector3& v3, HXMatrix4x4& out)
	{
		const float* ve = v3.elements;
		float* oe = out.elements;
		oe[0] = oe[5] = oe[10] = oe[15] = 1;
		oe[12] = ve[0];
		oe[13] = ve[1];
		oe[14] = ve[2];
	}

	void HXMatrix4x4::getTranslationVector(HXVector3& out) const
	{
		const float* me = this->elements;
		float* te = out.elements;
		te[0] = me[12];
		te[1] = me[13];
		te[2] = me[14];
	}

	void HXMatrix4x4::setTranslationVector(const HXVector3& translate)
	{
		float* me = this->elements;
		const float* ve = translate.elements;
		me[12] = ve[0];
		me[13] = ve[1];
		me[14] = ve[2];
	}

	void HXMatrix4x4::getForward(HXVector3& out) const
	{
		const float* me = this->elements;
		float* te = out.elements;
		te[0] = -me[8];
		te[1] = -me[9];
		te[2] = -me[10];
	}

	void HXMatrix4x4::setForward(const HXVector3& forward)
	{
		float* me = this->elements;
		const float* ve = forward.elements;
		me[8] = -ve[0];
		me[9] = -ve[1];
		me[10] = -ve[2];
	}
}