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
		//��ʕ`��̂��߂ɕK�v�ȍs����v�Z���Ԃ�
		DirectX::XMMATRIX GetDXCameraParam(TRANSFORM* transform);
	private:
		//�x���@�\�L�̊p�x���ʓx�@�\�L�̊p�x�ɕϊ�����
		float ToRadian(float angle) { return angle * (float)(acos(-1.0f) / 180.0f); }
		CAMERA_PARAM mParam;	
	};
}


