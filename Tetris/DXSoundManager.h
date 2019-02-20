#pragma once
#include <vector>
#include <memory>
#include "DirLoder.h"
#include "DXSound.h"
namespace MyDirectX 
{
	//���̊Ǘ��N���X
	class DXSoundManager
	{
	public:
		DXSoundManager(HWND hwnd);
		~DXSoundManager() {};
		//BGM�擾
		//path = �擾�����������t�@�C���̃p�X
		DXSound* GetBGMSound(std::wstring path);
		//SE�擾
		//path = �擾�����������t�@�C���̃p�X
		DXSound* GetSESound(std::wstring path);
	private:
		//BGM
		std::vector<std::unique_ptr<DXSound>> mBGMSounds;
		//SE
		std::vector<std::unique_ptr<DXSound>> mSESounds;
	};
}


