#pragma once
#include <vector>
#include <memory>
#include "DirLoder.h"
#include "DXSound.h"
namespace MyDirectX 
{
	class DXSoundManager
	{
	public:
		DXSoundManager(HWND hwnd);
		~DXSoundManager() {};
		DXSound* GetBGMSound(std::wstring path);
		DXSound* GetSESound(std::wstring path);
	private:
		std::vector<std::unique_ptr<DXSound>> mBGMSounds;
		std::vector<std::unique_ptr<DXSound>> mSESounds;
	};
}


