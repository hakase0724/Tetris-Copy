#include "stdafx.h"
#include "DXCamera.h"
#include "CommonValues.h"

using namespace DirectX;
using namespace MyDirectX;

DXCamera::DXCamera(CAMERA_PARAM * param)
{
	mParam = *param;
}

XMMATRIX DXCamera::GetDXCameraParam(TRANSFORM* transform)
{
	//カメラの位置、上方向、および焦点を使用して、左手座標系のビュー行列を作成
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, mParam.mRatio, 0.1f, 110.0f);
	//視野に基づいて、左手座標系のパースペクティブ射影行列を作成
	XMMATRIX view = XMMatrixLookAtLH(mParam.mPos, mParam.mLookup, mParam.mUp);
	//x軸中心回転
	XMMATRIX worldX = XMMatrixRotationX(ToRadian(transform->Rotation.y));
	//y軸中心回転
	XMMATRIX worldY = XMMatrixRotationY(ToRadian(transform->Rotation.x));
	//z軸中心回転
	XMMATRIX worldZ = XMMatrixRotationZ(ToRadian(transform->Rotation.z));
	//移動計算
	XMMATRIX move = XMMatrixTranslation(transform->Position.x,transform->Position.y,transform->Position.z);
	//スケール計算
	XMMATRIX scale = XMMatrixScalingFromVector(XMVectorSet(transform->Scale.x, transform->Scale.y, transform->Scale.z, 0.0f));
	
	//転置行列を計算 要はカメラの場所や視界を計算するってことだと思う
	return XMMatrixTranspose(scale * worldX * worldY * worldZ * move * view * proj);
}
