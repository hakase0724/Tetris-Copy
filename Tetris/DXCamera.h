#pragma once
#include <DirectXMath.h>
#include "MyStructs.h"
#include "AlignedAllocationPolicy.h"
namespace MyDirectX
{
	class DXCamera:public AlignedAllocationPolicy<16>
	{
	public:
		DXCamera(CAMERA_PARAM *param);
		~DXCamera() {};
		//画面描画のために必要な行列を計算し返す
		DirectX::XMMATRIX GetDXCameraParam(TRANSFORM* transform);
	private:
		//度数法表記の角度を弧度法表記の角度に変換する
		float ToRadian(float angle) { return angle * (float)(acos(-1.0f) / 180.0f); }
		CAMERA_PARAM mParam;	
	};
}


