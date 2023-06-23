#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>
#include "DebugCamera.h"

class Calc
{
};

Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

//内積
float Dot(const Vector3& v1, const Vector3& v2);

//長さ
float Length(const Vector3& v);

//正規化
Vector3 Normalize(const Vector3& v);

Vector3 Scaler(float scaler, const Vector3& v);


Matrix4x4 MakeAffinMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeTranslateMatrix(Vector3& translate);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);

Matrix4x4 MakeRatateXMatrix(float radian);

Matrix4x4 MakeRatateYMatrix(float radian);

Matrix4x4 MakeRatateZMatrix(float radian);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Inverse(const Matrix4x4& m);

Vector3 Transform(const Vector3& vector, const Matrix4x4 matrix);

Vector3 Cross(const Vector3& v1, const Vector3& v2);

//正射影行列
Matrix4x4 MakeOrthograhicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);