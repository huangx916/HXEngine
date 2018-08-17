#include "..\include\HXQuaternion.h"
#include "HXMatrix4x4.h"

namespace HX3D
{
	HXQuaternion::HXQuaternion()
	{

	}

	HXQuaternion::~HXQuaternion()
	{

	}

	void HXQuaternion::createFromYawPitchRoll(float yaw, float pitch, float roll, HXQuaternion& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		float halfRoll = roll * 0.5;
		float halfPitch = pitch * 0.5;
		float halfYaw = yaw * 0.5;

		float sinRoll = sin(halfRoll);
		float cosRoll = cos(halfRoll);
		float sinPitch = sin(halfPitch);
		float cosPitch = cos(halfPitch);
		float sinYaw = sin(halfYaw);
		float cosYaw = cos(halfYaw);

		float* oe = out.elements;
		oe[0] = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll);
		oe[1] = (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll);
		oe[2] = (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll);
		oe[3] = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll);
	}

	void HXQuaternion::identity()
	{
		float* e = this->elements;
		e[0] = 0;
		e[1] = 0;
		e[2] = 0;
		e[3] = 1;
	}

	void HXQuaternion::createFromMatrix4x4(const HXMatrix4x4& mat, HXQuaternion& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		const float* me = mat.elements;
		float* oe = out.elements;

		float _sqrt;
		float half;
		float scale = me[0] + me[5] + me[10];

		if (scale > 0.0) {
			_sqrt = sqrt(scale + 1.0);
			oe[3] = _sqrt * 0.5;
			_sqrt = 0.5 / _sqrt;

			oe[0] = (me[6] - me[9]) * _sqrt;
			oe[1] = (me[8] - me[2]) * _sqrt;
			oe[2] = (me[1] - me[4]) * _sqrt;
		}
		else if ((me[0] >= me[5]) && (me[0] >= me[10])) {
			_sqrt = sqrt(1.0 + me[0] - me[5] - me[10]);
			half = 0.5 / _sqrt;

			oe[0] = 0.5 * _sqrt;
			oe[1] = (me[1] + me[4]) * half;
			oe[2] = (me[2] + me[8]) * half;
			oe[3] = (me[6] - me[9]) * half;
		}
		else if (me[5] > me[10]) {
			_sqrt = sqrt(1.0 + me[5] - me[0] - me[10]);
			half = 0.5 / _sqrt;

			oe[0] = (me[4] + me[1]) * half;
			oe[1] = 0.5 * _sqrt;
			oe[2] = (me[9] + me[6]) * half;
			oe[3] = (me[8] - me[2]) * half;
		}
		else {
			_sqrt = sqrt(1.0 + me[10] - me[0] - me[5]);
			half = 0.5 / _sqrt;

			oe[0] = (me[8] + me[2]) * half;
			oe[1] = (me[9] + me[6]) * half;
			oe[2] = 0.5 * _sqrt;
			oe[3] = (me[1] - me[4]) * half;
		}
	}
}
