#pragma once
#include "MeshAndShader.h"
#include <vector>
#include <memory>
#include <typeinfo>
#include "DirLoder.h"
#include <map>

namespace MyDirectX
{
	class DXRenderDataPool
	{
	public:
		DXRenderDataPool(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~DXRenderDataPool() 
		{
			RemoveFontResourceEx(_T("APJapanesefont.ttf"), FR_PRIVATE, NULL);
		};
		//���b�V���f�[�^���擾
		template<typename T>
		T* GetMesh();
		//�V�F�[�_�[�f�[�^���擾
		template<typename T>
		T* GetShader();
		//�e�N�X�`���f�[�^���擾
		//fileName = �e�N�X�`���̃t�@�C���p�X
		TEXTURE_DATA* GetTexture(wchar_t* fileName);
		//�����̃e�N�X�`�����擾�@�Ȃ����nullptr��Ԃ�
		TEXTURE_DATA* GetFontTexture(wchar_t* text, std::wstring fontName = _T("�l�r �o����"));
		
	private:
		//�e�N�X�`���f�[�^��T��������Ȃ����nullptr��Ԃ�
		//text = �T���f�[�^�̖��O
		TEXTURE_DATA* FindTextureData(wchar_t* text);
		TEXTURE_DATA* FindTextureData(wchar_t text);
		TEXTURE_DATA* FindFontTextureData(wchar_t text,std::wstring font);
		//�e�N�X�`�������
		//filePath = �ǂݍ��ރt�@�C���p�X
		TEXTURE_DATA* CreateTexture(std::wstring filePath);
		void LoadTextureInDir();
		ID3D11Device* mDevice;
		ID3D11DeviceContext* mDeviceContext;
		std::unique_ptr<DirLoder> mDirLoder;
		std::vector<std::unique_ptr<MeshInfo>> mMeshInfoList;
		std::vector<std::unique_ptr<ShaderInfo>> mShaderInfoList;
		std::vector<std::unique_ptr<TEXTURE_DATA>> mTextureList;
		std::map<std::wstring, std::vector<std::unique_ptr<TEXTURE_DATA>>> mFontTextureList;
	};
	template<typename T>
	inline T * DXRenderDataPool::GetMesh()
	{
		T* pReturn = nullptr;
		for(auto &mesh:mMeshInfoList)
		{
			pReturn = dynamic_cast<T*>(mesh.get());
			if (pReturn != NULL)
				break;
		}
		if(pReturn == NULL)
		{
			pReturn = new T();
			mMeshInfoList.push_back(std::unique_ptr<T>(pReturn));
		}
		return pReturn;
	}
	template<typename T>
	inline T * DXRenderDataPool::GetShader()
	{
		T* pReturn = nullptr;
		for (auto &shader : mShaderInfoList)
		{
			pReturn = dynamic_cast<T*>(shader.get());
			if (pReturn != NULL)
				break;
		}
		if (pReturn == NULL)
		{
			pReturn = new T();
			mShaderInfoList.push_back(std::unique_ptr<T>(pReturn));
		}
		return pReturn;
	}
}

