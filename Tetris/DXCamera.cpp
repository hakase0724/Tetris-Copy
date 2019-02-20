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
	//�J�����̈ʒu�A������A����яœ_���g�p���āA������W�n�̃r���[�s����쐬
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, mParam.mRatio, 0.1f, 110.0f);
	//����Ɋ�Â��āA������W�n�̃p�[�X�y�N�e�B�u�ˉe�s����쐬
	XMMATRIX view = XMMatrixLookAtLH(mParam.mPos, mParam.mLookup, mParam.mUp);
	//x�����S��]
	XMMATRIX worldX = XMMatrixRotationX(ToRadian(transform->Rotation.y));
	//y�����S��]
	XMMATRIX worldY = XMMatrixRotationY(ToRadian(transform->Rotation.x));
	//z�����S��]
	XMMATRIX worldZ = XMMatrixRotationZ(ToRadian(transform->Rotation.z));
	//�ړ��v�Z
	XMMATRIX move = XMMatrixTranslation(transform->Position.x,transform->Position.y,transform->Position.z);
	//�X�P�[���v�Z
	XMMATRIX scale = XMMatrixScalingFromVector(XMVectorSet(transform->Scale.x, transform->Scale.y, transform->Scale.z, 0.0f));
	
	//�]�u�s����v�Z �v�̓J�����̏ꏊ�⎋�E���v�Z������Ă��Ƃ��Ǝv��
	return XMMatrixTranspose(scale * worldX * worldY * worldZ * move * view * proj);
}
