#include "stdafx.h"
#include "DXResourceManager.h"
#include "DXGameObject.h"

using namespace MyDirectX;

DXResourceManager::DXResourceManager(HWND hwnd)
{
	//DirectXリソース管理
	mDXManager = std::make_unique<DXManager>(hwnd);
	//FPSカウンターを生成
	mFPSCountor = std::make_unique<FPSCountor>();
	//音管理クラス生成
	mDXSoundManager = std::make_unique<DXSoundManager>(hwnd);
}

DXGameObject * DXResourceManager::Instantiate()
{
	DXGameObject* game = new DXGameObject(this);
	//各オブジェクトにIDを降る
	game->SetID(mGameObjectCount);
	mGameObjectCount++;
	return game;
}

