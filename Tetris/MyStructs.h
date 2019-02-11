#pragma once
#include <string>
#include <memory>
#include <d3d11.h>
#include <DirectXMath.h>
#include "MyEnums.h"
#include "AlignedAllocationPolicy.h"
namespace MyDirectX
{
	//�s�[�X�̍��W
	struct PiecePosition 
	{
		//�s
		int x;
		//��
		int y;
	};

	//�F����ێ�����\����
	struct COLOR
	{
		//��
		float r = 1.0f;
		//��
		float g = 1.0f;
		//��
		float b = 1.0f;
		//�A���t�@�l
		float a = 1.0f;

		void SetWhite()
		{
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
		}

		void SetBlack()
		{
			r = 0.0f;
			g = 0.0f;
			b = 0.0f;
		}

		void SetRed()
		{
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
		}

		void SetBlue()
		{
			r = 0.0f;
			g = 0.0f;
			b = 1.0f;
		}

		void SetGreen()
		{
			r = 0.0f;
			g = 1.0f;
			b = 0.0f;
		}
	};

	//�萔�o�b�t�@
	struct TEXTURE_CONSTANT_BUFFER
	{
		DirectX::XMMATRIX mWVP;
		DirectX::XMVECTOR mColor;
	};

	//�J�������
	struct CAMERA_PARAM:public AlignedAllocationPolicy<16>
	{
		DirectX::XMVECTOR mPos;
		DirectX::XMVECTOR mLookup;
		DirectX::XMVECTOR mUp;
		float mRatio;
		float mXRote;
		float mYRote;
		CAMERA_PARAM()
		{
			mPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			mLookup = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			mUp = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			mRatio = 0.0f;
			mXRote = 0.0f;
			mYRote = 0.0f;
		}

		CAMERA_PARAM(DirectX::XMVECTOR pos, DirectX::XMVECTOR lookup, DirectX::XMVECTOR up, float ratio)
		{
			mPos = pos;
			mLookup = lookup;
			mUp = up;
			mRatio = ratio;
			mXRote = 0.0f;
			mYRote = 0.0f;
		}
	};

	//�I�u�W�F�N�g�����ʒu��]�X�P�[�����
	struct TRANSFORM
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Rotation;
		DirectX::XMFLOAT3 Scale;

		TRANSFORM()
		{
			Position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			Rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			Scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}

		TRANSFORM(DirectX::XMFLOAT3 pos)
		{
			Position = pos;
			Rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			Scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}

		TRANSFORM(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rote)
		{
			Position = pos;
			Rotation = rote;
			Scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}

		TRANSFORM(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rote, DirectX::XMFLOAT3 scale)
		{
			Position = pos;
			Rotation = rote;
			Scale = scale;
		}
	};

	//���_���\����
	struct TEXTURE_VERTEX_DATA
	{
		DirectX::XMFLOAT3 V;
		DirectX::XMFLOAT2 T;
		TEXTURE_VERTEX_DATA() = default;
		TEXTURE_VERTEX_DATA(DirectX::XMFLOAT3 v, DirectX::XMFLOAT2 t)
		{
			V = v;
			T = t;
		}
	};

	//�V�F�[�_�[�ɐݒ肷��f�[�^
	struct SHADER_DATA
	{
		LPCWSTR VertexName;
		LPCWSTR PixelName;
		LPCSTR VertexEntry;
		LPCSTR PixelEntry;
		LPCSTR VertexVersion;
		LPCSTR PixelVersion;
		D3D11_INPUT_ELEMENT_DESC* InputLayout;
		int LayoutNum;
	};

	//�e�N�X�`������ێ�
	struct TEXTURE_DATA
	{
		std::wstring fileName;
		ID3D11Resource* texture;
		ID3D11ShaderResourceView* shaderView;
		~TEXTURE_DATA()
		{
			if(texture)texture->Release();
			if(shaderView)shaderView->Release();
		}
	};
}
