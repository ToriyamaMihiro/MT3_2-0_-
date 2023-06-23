#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>
#include"Calc.h"
#include <Novice.h>
#include<numbers>

struct Sphere
{
	Vector3 center; //中心点
	float radius;   //半径
};

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);