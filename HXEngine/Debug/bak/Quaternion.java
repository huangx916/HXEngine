package engine;

public strictfp final class Quaternion {

	public float x;
	public float y;
	public float z;
	public float w;

	public static Quaternion identity() {
		return new Quaternion(0, 0, 0, 1);
	}

	private static Quaternion zero() {
		return new Quaternion(0, 0, 0, 0);
	}

	private Quaternion(float x, float y, float z, float w) {
		this.x = x;
		this.y = y;
		this.z = z;
		this.w = w;
	}

	public float getX() {
		return x;
	}

	public float getY() {
		return y;
	}

	public float getZ() {
		return z;
	}

	public float getW() {
		return w;
	}

	public float magnitude() {
		return GameMath.sqrt(sqrMagnitude());
	}

	public float sqrMagnitude() {
		return x * x + y * y + z * z + w * w;
	}

	public Quaternion normalized() {
		float length = magnitude();
		return length < GameMath.EPSILON ? Quaternion.zero() : new Quaternion(x / length, y / length, z / length, w / length);
	}

	public Quaternion negative() {
		return new Quaternion(-x, -y, -z, -w);
	}

	public Quaternion inverse() {
		float sqrLength = sqrMagnitude();
		return sqrLength < GameMath.EPSILON ? Quaternion.zero() : new Quaternion(-x / sqrLength, -y / sqrLength, -z / sqrLength, w / sqrLength);
	}

	public boolean equals(Quaternion q) {
		return (x == q.x) && (y == q.y) && (z == q.z) && (w == q.w);
	}

	public Quaternion plus(Quaternion q) {
		return new Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	public Quaternion multiply(float number) {
		return new Quaternion(x * number, y * number, z * number, w * number);
	}

	@Deprecated
	public Vector3 multiplyByVector(Vector3 v3) {
		Vector3 uv, uuv;
		Vector3 qvec = new Vector3(x, y, z);

		uv = qvec.cross(v3);
		uuv = qvec.cross(uv);
		uv = uv.multiply(w * 2);
		uuv = uuv.multiply(2);

		return v3.plus(uv).plus(uuv);
	}
	
	public Vector3 multiply(Vector3 point) {
		float tX = x * 2f, tY = y * 2f, tZ = z * 2f;
		float tXX = x * tX, tYY = y * tY, tZZ = z * tZ;
		float tXY = x * tY, tXZ = x * tZ, tYZ = y * tZ;
		float tWX = w * tX, tWY = w * tY, tWZ = w * tZ;
		Vector3 result = Vector3.zero();
		result.x = (1f - (tYY + tZZ)) * point.x + (tXY - tWZ) * point.y + (tXZ + tWY) * point.z;
		result.y = (tXY + tWZ) * point.x + (1f - (tXX + tZZ)) * point.y + (tYZ - tWX) * point.z;
		result.z = (tXZ - tWY) * point.x + (tYZ + tWX) * point.y + (1f - (tXX + tYY)) * point.z;
		return result;
	}

	public Quaternion multiply(Quaternion q) {
		Quaternion quaternion = Quaternion.zero();
		quaternion.x = w * q.x + x * q.w + y * q.z - z * q.y;
		quaternion.y = w * q.y + y * q.w + z * q.x - x * q.z;
		quaternion.z = w * q.z + z * q.w + x * q.y - y * q.x;
		quaternion.w = w * q.w - x * q.x - y * q.y - z * q.z;
		return quaternion;
	}

	public float dot(Quaternion q) {
		return x * q.x + y * q.y + z * q.z + w * q.w;
	}

	public float getPitch() {
		return GameMath.asin((x * w - y * z) * 2) * GameMath.RAD_TO_DEG;
	}

	public float getYaw() {
		return GameMath.atan2(2 * (x * z + y * w), 1 - 2 * (x * x + (y * y))) * GameMath.RAD_TO_DEG;
	}

	public float getRoll() {
		return GameMath.atan2(2 * (x * y + z * w), 1 - 2 * (x * x + (z * z))) * GameMath.RAD_TO_DEG;
	}
	
	public Vector3 eulerAngles() {
		return new Vector3(getPitch(), getYaw(), getRoll());
	}

	public float getAngle() {
		return 2 * GameMath.acos(w) * GameMath.RAD_TO_DEG;
	}

	public Vector3 getAxis() {
		return new Vector3(x, y, z).normalized();
	}

	public float[][] toRotationMatrix3x3() {
		float tX = x * 2f, tY = y * 2f, tZ = z * 2f;
		float tXX = x * tX, tYY = y * tY, tZZ = z * tZ;
		float tXY = x * tY, tXZ = x * tZ, tYZ = y * tZ;
		float tWX = w * tX, tWY = w * tY, tWZ = w * tZ;

		float[][] rotation = new float[3][3];
		rotation[0][0] = 1f - (tYY + tZZ);
		rotation[0][1] = tXY - tWZ;
		rotation[0][2] = tXZ + tWY;
		rotation[1][0] = tXY + tWZ;
		rotation[1][1] = 1f - (tXX + tZZ);
		rotation[1][2] = tYZ - tWX;
		rotation[2][0] = tXZ - tWY;
		rotation[2][1] = tYZ + tWX;
		rotation[2][2] = 1f - (tXX + tYY);

		return rotation;
	}
	
	public Quaternion log() {
		// BLACKBOX: Learn this
		// If q = cos(A)+sin(A)*(X*i+Y*j+Z*k) Where (X,Y,Z) is unit length, then
		// log(q) = A*(X*i+Y*j+Z*k).  If sin(A) is near Zero, use log(q) =
		// sin(A)*(X*i+Y*j+Z*k) since sin(A)/A has limit 1.

		Quaternion returnvalue = Quaternion.zero();

		if (GameMath.abs(w) < 1) {
			float angle = GameMath.acos(w);
			float sin = GameMath.sin(angle);

			if (GameMath.abs(sin) >= GameMath.EPSILON) {
				float coeff = angle / sin;
				returnvalue.x = coeff * x;
				returnvalue.y = coeff * y;
				returnvalue.z = coeff * z;
			} else {
				returnvalue.x = x;
				returnvalue.y = y;
				returnvalue.z = z;
			}
		}

		return returnvalue;
	}

	public Quaternion exp() {
		// If q = A*(X*i+Y*j+Z*k) Where (X,Y,Z) is unit length, then eXp(q) = cos(A)+sin(A)*(X*i+Y*j+Z*k).
		// If sin(A) is near Zero, use eXp(q) = cos(A)+A*(X*i+Y*j+Z*k) since A/sin(A) has limit 1.

		float angle = GameMath.sqrt(x * x + y * y + z * z);
		float sin = GameMath.sin(angle);

		Quaternion returnvalue = Quaternion.zero();

		returnvalue.w = GameMath.cos(angle);

		if (GameMath.abs(sin) >= GameMath.EPSILON) {
			float coeff = sin / angle;
			returnvalue.x = coeff * x;
			returnvalue.y = coeff * y;
			returnvalue.z = coeff * z;
		} else {
			returnvalue.x = x;
			returnvalue.y = y;
			returnvalue.z = z;
		}

		return returnvalue;
	}
	
	public Quaternion clone() {
		return new Quaternion(x, y, z, w);
	}

	@Override
	public String toString() {
		float _x = GameMath.round(x * 10) / 10f;
		float _y = GameMath.round(y * 10) / 10f;
		float _z = GameMath.round(z * 10) / 10f;
		float _w = GameMath.round(w * 10) / 10f;
		return "[" + _x + ", " + _y + ", " + _z + ", " + _w + "]";
	}

	public static Quaternion euler(Vector3 v3) {
		return Quaternion.euler(v3.x, v3.y, v3.z);
	}

	public static Quaternion euler(float pitch, float yaw, float roll) {
		//Yaw > Pitch > Roll

		float halfPitch = 0.5f * pitch * GameMath.DEG_TO_RAD;
		float halfYaw = 0.5f * yaw * GameMath.DEG_TO_RAD;
		float halfRoll = 0.5f * roll * GameMath.DEG_TO_RAD;

		float chp = GameMath.cos(halfPitch);
		float shp = GameMath.sin(halfPitch);

		float chy = GameMath.cos(halfYaw);
		float shy = GameMath.sin(halfYaw);

		float chr = GameMath.cos(halfRoll);
		float shr = GameMath.sin(halfRoll);

		float x = chy * shp * chr + shy * chp * shr;
		float y = shy * chp * chr - chy * shp * shr;
		float z = chy * chp * shr - shy * shp * chr;
		float w = chy * chp * chr + shy * shp * shr;

		return new Quaternion(x, y, z, w);
	}

    public static Quaternion angleAxis(float angle, Vector3 axis) {
    	
        float halfAngle = 0.5f * angle * GameMath.DEG_TO_RAD;
        float cos = GameMath.cos(halfAngle);
        float sin = GameMath.sin(halfAngle);
        
        axis = axis.normalized();
        float x = sin * axis.x;
        float y = sin * axis.y;
        float z = sin * axis.z;
        float w = cos;
        
        return new Quaternion(x, y, z, w);
    }

	public static Quaternion lerp(Quaternion from, Quaternion to, float t) {
		t = GameMath.clamp01(t);
		return new Quaternion(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t, from.w + (to.w - from.w) * t);
	}

	public static Quaternion slerp(Quaternion from, Quaternion to, float t) {
		return slerp(from, to, t, false);
	}

	public static Quaternion slerp(Quaternion from, Quaternion to, float t, boolean useShortestPath) {
		float cos = from.dot(to);

		float angle = GameMath.acos(cos);

		if (GameMath.abs(angle) < GameMath.EPSILON) {
			return from;
		}

		float sin = GameMath.sin(angle);
		float inverseSin = 1 / sin;
		float coeff0 = GameMath.sin((1 - t) * angle) * inverseSin;
		float coeff1 = GameMath.sin(t * angle) * inverseSin;

		Quaternion returnvalue;

		if (cos < 0 && useShortestPath) {
			coeff0 = -coeff0;
			Quaternion q = from.multiply(coeff0).plus(to.multiply(coeff1));
			returnvalue = q.normalized();
		} else {
			returnvalue = from.multiply(coeff0).plus(to.multiply(coeff1));;
		}

		return returnvalue;
	}
}