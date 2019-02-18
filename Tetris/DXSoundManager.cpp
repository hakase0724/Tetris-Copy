#include "stdafx.h"
#include "DXSoundManager.h"

using namespace MyDirectX;
DXSoundManager::DXSoundManager(HWND hwnd)
{
	auto loder = std::make_unique<DirLoder>();
	//BGM¶¬
	auto bgmPaths = loder->GetFilePathInDir(_T("Sound/BGM"), _T("wav"));
	for(auto bgmPath:bgmPaths)
	{
		auto bgm = std::make_unique<DXSound>(hwnd, (LPWSTR)bgmPath.c_str());
		mBGMSounds.push_back(std::move(bgm));
	}
	//SE¶¬
	auto sePaths = loder->GetFilePathInDir(_T("Sound/SE"), _T("wav"));
	for(auto sePath:sePaths)
	{
		auto se = std::make_unique<DXSound>(hwnd, (LPWSTR)sePath.c_str());
		mSESounds.push_back(std::move(se));
	}
}

DXSound * DXSoundManager::GetBGMSound(std::wstring path)
{
	DXSound* sound = nullptr;
	for(auto &bgm:mBGMSounds)
	{
		if(bgm->GetSourcePath() == path)
		{
			sound = bgm.get();
			break;
		}
	}
	return sound;
}

DXSound * DXSoundManager::GetSESound(std::wstring path)
{
	DXSound* sound = nullptr;
	for (auto &se : mSESounds)
	{
		if (se->GetSourcePath() == path)
		{
			sound = se.get();
			break;
		}
	}
	return sound;
}

