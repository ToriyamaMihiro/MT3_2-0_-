#include"Calc.h"
#include<assert.h>



Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 Add;
	Add.x = v1.x + v2.x;
	Add.y = v1.y + v2.y;
	Add.z = v1.z + v2.z;

	return Add;
}
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 Subtract;
	Subtract.x = v1.x - v2.x;
	Subtract.y = v1.y - v2.y;
	Subtract.z = v1.z - v2.z;

	return Subtract;
}

//正規化

float Dot(const Vector3& v1, const Vector3& v2)
{
	float dot;
	dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return dot;
}
float Length(const Vector3& v)
{
	float Length;
	Length = sqrtf(Dot(v, v));
	return Length;
}
Vector3 Normalize(const Vector3& v)
{
	Vector3 Normalize;
	Normalize.x = v.x / Length(v);
	Normalize.y = v.y / Length(v);
	Normalize.z = v.z / Length(v);

	return Normalize;
}
Vector3 Scaler(float scaler, const Vector3& v)
{
	Vector3 Multiply;
	Multiply.x = scaler * v.x;
	Multiply.y = scaler * v.y;
	Multiply.z = scaler * v.z;

	return Multiply;
}
//アフィン変換
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 MakeTranslateMatrix;
	//3行1列に格納
	MakeTranslateMatrix.m[0][0] = 1;
	MakeTranslateMatrix.m[0][1] = 0;
	MakeTranslateMatrix.m[0][2] = 0;
	MakeTranslateMatrix.m[0][3] = 0;
	MakeTranslateMatrix.m[1][0] = 0;
	MakeTranslateMatrix.m[1][1] = 1;
	MakeTranslateMatrix.m[1][2] = 0;
	MakeTranslateMatrix.m[1][3] = 0;
	MakeTranslateMatrix.m[2][0] = 0;
	MakeTranslateMatrix.m[2][1] = 0;
	MakeTranslateMatrix.m[2][2] = 1;
	MakeTranslateMatrix.m[2][3] = 0;
	MakeTranslateMatrix.m[3][0] = translate.x;
	MakeTranslateMatrix.m[3][1] = translate.y;
	MakeTranslateMatrix.m[3][2] = translate.z;
	MakeTranslateMatrix.m[3][3] = 1;
	return MakeTranslateMatrix;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 MakeScaleMatrix;
	MakeScaleMatrix.m[0][0] = scale.x;
	MakeScaleMatrix.m[0][1] = 0;
	MakeScaleMatrix.m[0][2] = 0;
	MakeScaleMatrix.m[0][3] = 0;
	MakeScaleMatrix.m[1][0] = 0;
	MakeScaleMatrix.m[1][1] = scale.y;
	MakeScaleMatrix.m[1][2] = 0;
	MakeScaleMatrix.m[1][3] = 0;
	MakeScaleMatrix.m[2][0] = 0;
	MakeScaleMatrix.m[2][1] = 0;
	MakeScaleMatrix.m[2][2] = scale.z;
	MakeScaleMatrix.m[2][3] = 0;
	MakeScaleMatrix.m[3][0] = 0;
	MakeScaleMatrix.m[3][1] = 0;
	MakeScaleMatrix.m[3][2] = 0;
	MakeScaleMatrix.m[3][3] = 1;

	return MakeScaleMatrix;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4 matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);//wは0にならない
	//0ではないwの値で割るので0ではない
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Matrix4x4 MakeRatateXMatrix(float radian)
{
	Matrix4x4 MakeRatateXMatrix;
	MakeRatateXMatrix.m[0][0] = 1;
	MakeRatateXMatrix.m[0][1] = 0;
	MakeRatateXMatrix.m[0][2] = 0;
	MakeRatateXMatrix.m[0][3] = 0;
	MakeRatateXMatrix.m[1][0] = 0;
	MakeRatateXMatrix.m[1][1] = std::cos(radian);
	MakeRatateXMatrix.m[1][2] = std::sin(radian);
	MakeRatateXMatrix.m[1][3] = 0;
	MakeRatateXMatrix.m[2][0] = 0;
	MakeRatateXMatrix.m[2][1] = -std::sin(radian);
	MakeRatateXMatrix.m[2][2] = std::cos(radian);
	MakeRatateXMatrix.m[2][3] = 0;
	MakeRatateXMatrix.m[3][0] = 0;
	MakeRatateXMatrix.m[3][1] = 0;
	MakeRatateXMatrix.m[3][2] = 0;
	MakeRatateXMatrix.m[3][3] = 1;

	return MakeRatateXMatrix;
}

Matrix4x4 MakeRatateYMatrix(float radian)
{
	Matrix4x4 MakeRatateYMatrix;
	MakeRatateYMatrix.m[0][0] = std::cos(radian);
	MakeRatateYMatrix.m[0][1] = 0;
	MakeRatateYMatrix.m[0][2] = -std::sin(radian);
	MakeRatateYMatrix.m[0][3] = 0;
	MakeRatateYMatrix.m[1][0] = 0;
	MakeRatateYMatrix.m[1][1] = 1;
	MakeRatateYMatrix.m[1][2] = 0;
	MakeRatateYMatrix.m[1][3] = 0;
	MakeRatateYMatrix.m[2][0] = std::sin(radian);
	MakeRatateYMatrix.m[2][1] = 0;
	MakeRatateYMatrix.m[2][2] = std::cos(radian);
	MakeRatateYMatrix.m[2][3] = 0;
	MakeRatateYMatrix.m[3][0] = 0;
	MakeRatateYMatrix.m[3][1] = 0;
	MakeRatateYMatrix.m[3][2] = 0;
	MakeRatateYMatrix.m[3][3] = 1;

	return MakeRatateYMatrix;
}

Matrix4x4 MakeRatateZMatrix(float radian)
{
	Matrix4x4 MakeRatateZMatrix;
	MakeRatateZMatrix.m[0][0] = std::cos(radian);
	MakeRatateZMatrix.m[0][1] = std::sin(radian);
	MakeRatateZMatrix.m[0][2] = 0;
	MakeRatateZMatrix.m[0][3] = 0;
	MakeRatateZMatrix.m[1][0] = -std::sin(radian);
	MakeRatateZMatrix.m[1][1] = std::cos(radian);
	MakeRatateZMatrix.m[1][2] = 0;
	MakeRatateZMatrix.m[1][3] = 0;
	MakeRatateZMatrix.m[2][0] = 0;
	MakeRatateZMatrix.m[2][1] = 0;
	MakeRatateZMatrix.m[2][2] = 1;
	MakeRatateZMatrix.m[2][3] = 0;
	MakeRatateZMatrix.m[3][0] = 0;
	MakeRatateZMatrix.m[3][1] = 0;
	MakeRatateZMatrix.m[3][2] = 0;
	MakeRatateZMatrix.m[3][3] = 1;

	return MakeRatateZMatrix;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 Multiply;
	Multiply.m[0][0] = (m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0]);
	Multiply.m[0][1] = (m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1]);
	Multiply.m[0][2] = (m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2]);
	Multiply.m[0][3] = (m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3]);
	Multiply.m[1][0] = (m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0]);
	Multiply.m[1][1] = (m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1]);
	Multiply.m[1][2] = (m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2]);
	Multiply.m[1][3] = (m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3]);
	Multiply.m[2][0] = (m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0]);
	Multiply.m[2][1] = (m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1]);
	Multiply.m[2][2] = (m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2]);
	Multiply.m[2][3] = (m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3]);
	Multiply.m[3][0] = (m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0]);
	Multiply.m[3][1] = (m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1]);
	Multiply.m[3][2] = (m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2]);
	Multiply.m[3][3] = (m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3]);
	return Multiply;
}

Matrix4x4 MakeAffinMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 rotateXYZMatrix = Multiply(MakeRatateXMatrix(rotate.x), Multiply(MakeRatateYMatrix(rotate.y), MakeRatateZMatrix(rotate.z)));
	Matrix4x4 SRT = Multiply(MakeScaleMatrix(scale), Multiply(rotateXYZMatrix, MakeTranslateMatrix(translate)));


	return SRT;
}

Matrix4x4 Inverse(const Matrix4x4& m)
{
	Matrix4x4 Inverse;
	float deterMinant =
		(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	Inverse.m[0][0] = 1 / deterMinant * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);
	Inverse.m[0][1] = 1 / deterMinant * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);
	Inverse.m[0][2] = 1 / deterMinant * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);
	Inverse.m[0][3] = 1 / deterMinant * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);

	Inverse.m[1][0] = 1 / deterMinant * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);
	Inverse.m[1][1] = 1 / deterMinant * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);
	Inverse.m[1][2] = 1 / deterMinant * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);
	Inverse.m[1][3] = 1 / deterMinant * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);

	Inverse.m[2][0] = 1 / deterMinant * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);
	Inverse.m[2][1] = 1 / deterMinant * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);
	Inverse.m[2][2] = 1 / deterMinant * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);
	Inverse.m[2][3] = 1 / deterMinant * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);

	Inverse.m[3][0] = 1 / deterMinant * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);
	Inverse.m[3][1] = 1 / deterMinant * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);
	Inverse.m[3][2] = 1 / deterMinant * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);
	Inverse.m[3][3] = 1 / deterMinant * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);

	return Inverse;
}

Matrix4x4 MakeOrthograhicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 MakeOrthograhicMatrix;
	MakeOrthograhicMatrix.m[0][0] = 2 / (right - left);
	MakeOrthograhicMatrix.m[0][1] = 0;
	MakeOrthograhicMatrix.m[0][2] = 0;
	MakeOrthograhicMatrix.m[0][3] = 0;
	MakeOrthograhicMatrix.m[1][0] = 0;
	MakeOrthograhicMatrix.m[1][1] = 2 / (top - bottom);
	MakeOrthograhicMatrix.m[1][2] = 0;
	MakeOrthograhicMatrix.m[1][3] = 0;
	MakeOrthograhicMatrix.m[2][0] = 0;
	MakeOrthograhicMatrix.m[2][1] = 0;
	MakeOrthograhicMatrix.m[2][2] = 1 / (farClip - nearClip);
	MakeOrthograhicMatrix.m[2][3] = 0;
	MakeOrthograhicMatrix.m[3][0] = (left + right) / (left - right);
	MakeOrthograhicMatrix.m[3][1] = (top + bottom) / (bottom - top);
	MakeOrthograhicMatrix.m[3][2] = nearClip / (nearClip - farClip);
	MakeOrthograhicMatrix.m[3][3] = 1;
	return MakeOrthograhicMatrix;
}

//修正必要
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 MakePerdpectiveFovMatrix;
	float newfovY = 1 / tan(fovY / 2.0f);

	MakePerdpectiveFovMatrix.m[0][0] = (1 / aspectRatio) * (newfovY);
	MakePerdpectiveFovMatrix.m[0][1] = 0;
	MakePerdpectiveFovMatrix.m[0][2] = 0;
	MakePerdpectiveFovMatrix.m[0][3] = 0;
	MakePerdpectiveFovMatrix.m[1][0] = 0;
	MakePerdpectiveFovMatrix.m[1][1] = (newfovY);
	MakePerdpectiveFovMatrix.m[1][2] = 0;
	MakePerdpectiveFovMatrix.m[1][3] = 0;
	MakePerdpectiveFovMatrix.m[2][0] = 0;
	MakePerdpectiveFovMatrix.m[2][1] = 0;
	MakePerdpectiveFovMatrix.m[2][2] = farClip / (farClip - nearClip);
	MakePerdpectiveFovMatrix.m[2][3] = 1;
	MakePerdpectiveFovMatrix.m[3][0] = 0;
	MakePerdpectiveFovMatrix.m[3][1] = 0;
	MakePerdpectiveFovMatrix.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	MakePerdpectiveFovMatrix.m[3][3] = 0;
	return MakePerdpectiveFovMatrix;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 MakeViewportMatrix;
	MakeViewportMatrix.m[0][0] = width / 2;
	MakeViewportMatrix.m[0][1] = 0;
	MakeViewportMatrix.m[0][2] = 0;
	MakeViewportMatrix.m[0][3] = 0;
	MakeViewportMatrix.m[1][0] = 0;
	MakeViewportMatrix.m[1][1] = -(height / 2);
	MakeViewportMatrix.m[1][2] = 0;
	MakeViewportMatrix.m[1][3] = 0;
	MakeViewportMatrix.m[2][0] = 0;
	MakeViewportMatrix.m[2][1] = 0;
	MakeViewportMatrix.m[2][2] = maxDepth - minDepth;
	MakeViewportMatrix.m[2][3] = 0;
	MakeViewportMatrix.m[3][0] = left + (width / 2);
	MakeViewportMatrix.m[3][1] = top + (height / 2);
	MakeViewportMatrix.m[3][2] = minDepth;
	MakeViewportMatrix.m[3][3] = 1;
	return MakeViewportMatrix;

}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 Cross;
	Cross = { v1.y * v2.z - v1.z * v2.y,v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	return Cross;
}