#include "Distance.h"
#include <cmath>

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	Vector3 v3, v4;
	v3 = Normalize(v2);
	float product = (v1.x * v3.x + v1.y * v3.y + v1.z * v3.z);
	v4 = Scaler(product, v3);
	return v4;
}

Vector3 ClosetPoint(const Vector3& point, const Segment& segment)
{
	Vector3 cp;
	cp = Add(point, segment.origin);
	return cp;
}
