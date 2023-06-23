#pragma once
#include"Vector3.h"
#include"Segment.h"
#include "Grid.h"

class Distance
{
};
struct Line {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};

struct Ray {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};
struct Segment {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};
Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosetPoint(const Vector3& point, const Segment& segment);



