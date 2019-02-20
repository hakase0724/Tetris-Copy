#pragma once
#include <vector>
#include <memory>
#include "DirLoder.h"
#include "DXSound.h"
namespace MyDirectX 
{
	//音の管理クラス
	class DXSoundManager
	{
	public:
		DXSoundManager(HWND hwnd);
		~DXSoundManager() {};
		//BGM取得
		//path = 取得したい音源ファイルのパス
		DXSound* GetBGMSound(std::wstring path);
		//SE取得
		//path = 取得したい音源ファイルのパス
		DXSound* GetSESound(std::wstring path);
	private:
		//BGM
		std::vector<std::unique_ptr<DXSound>> mBGMSounds;
		//SE
		std::vector<std::unique_ptr<DXSound>> mSESounds;
	};
}


