#include "Grid.h"

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSubdivision = 30;
	const float kLonEvery = 2.0f * float(std::numbers::pi) / float(kSubdivision);//経度分割1つ分の角度
	const float kLatEvery = float(std::numbers::pi) / float(kSubdivision);//緯度分割1つ分の角度
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -1.0f * float(std::numbers::pi) / 2.0f + kLatEvery * latIndex;//現在の緯度
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {

			float lon = lonIndex * kLonEvery;//現在の経度
			Vector3 a, b, c;

			a = { sphere.radius * cosf(lat) * cosf(lon), sphere.radius * sinf(lat), sphere.radius * cosf(lat) * sinf(lon) };
			a = Add(a, sphere.center);
			b = { sphere.radius * cosf(lat + kLatEvery) * cosf(lon), sphere.radius * sinf(lat + kLatEvery), sphere.radius * cosf(lat + kLatEvery) * sinf(lon) };
			b = Add(b, sphere.center);
			c = { sphere.radius * cosf(lat) * cosf(lon + kLonEvery), sphere.radius * sinf(lat), sphere.radius * cosf(lat) * sinf(lon + kLonEvery) };
			c = Add(c, sphere.center);
			//Screean座標系まで変換
			a = Transform(a, viewProjectionMatrix);
			a = Transform(a, viewportMatrix);
			b = Transform(b, viewProjectionMatrix);
			b = Transform(b, viewportMatrix);
			c = Transform(c, viewProjectionMatrix);
			c = Transform(c, viewportMatrix);

			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y), color);

			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);
		}
	}
};

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const uint32_t kSubdivision = 16;//分割数
	const float kGridHalfWidth = 2.0f;//グリッドの半分
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);//一つ分の長さ

	Vector3 worldVertices[2];
	Vector3 screenVertices[2];
	Vector3 ndcVertex;
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		//ワールド座標系の始点と終点を求める
		worldVertices[0] = { xIndex * kGridEvery - kGridHalfWidth,0.0f,kGridHalfWidth };
		worldVertices[1] = { xIndex * kGridEvery - kGridHalfWidth,0.0f, -kGridHalfWidth };
		//スクリーン座標系まで変換をかける
		for (uint32_t i = 0; i < 2; ++i) {
			ndcVertex = Transform(worldVertices[i], viewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		//変換した座標を使って表示
		if (xIndex * kGridEvery - kGridHalfWidth == 0.0f) {
			Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y),
				int(screenVertices[1].x), int(screenVertices[1].y), 0x000000FF);
		}
		else {
			Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y),
				int(screenVertices[1].x), int(screenVertices[1].y), 0xAAAAAAFF);


		}
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		//ワールド座標系の始点と終点を求める
		worldVertices[0] = { kGridHalfWidth,0.0f, zIndex * kGridEvery - kGridHalfWidth };
		worldVertices[1] = { -kGridHalfWidth,0.0f, zIndex * kGridEvery - kGridHalfWidth };
		//スクリーン座標系まで変換をかける
		for (uint32_t i = 0; i < 2; ++i) {
			ndcVertex = Transform(worldVertices[i], viewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		//変換した座標を使って表示
		if (zIndex * kGridEvery - kGridHalfWidth == 0.0f) {
			Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y),
				int(screenVertices[1].x), int(screenVertices[1].y), 0x000000FF);
		}
		else {
			Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y),
				int(screenVertices[1].x), int(screenVertices[1].y), 0xAAAAAAFF);

		}
	}
};

