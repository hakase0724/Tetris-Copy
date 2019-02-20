#pragma once
#include<memory>
#include "DXManager.h"
#include "FPSCountor.h"
#include "DXSoundManager.h"

namespace MyDirectX
{
	class DXGameObject;

	class DXResourceManager
	{
	public:
		DXResourceManager(HWND hwnd);
		~DXResourceManager() {};
		//オブジェクトを生成する
		DXGameObject* Instantiate();
		//DirectXリソース管理クラスを返す
		DXManager* GetDXManager() const { return mDXManager.get(); }
		//指定したキーが入力されたタイミングか
		bool GetKeyDown(int key) { return mDXManager->GetDXInput()->GetKeyDown(key); }
		//指定したキーが入力されているか
		bool GetKey(int key) { return mDXManager->GetDXInput()->GetKey(key); }
		//音管理クラスを返す
		DXSoundManager* GetSoundManager() { return mDXSoundManager.get(); }
		//FPSを返す
		double GetFPS() const { return mFPS; }
		//現在の入力状況を取得
		void SetInputState() { mDXManager->GetDXInput()->SetInputState(); }
		//次のフレームへ行く前に現在の入力状況を記録する
		void SetPreBuffer() { mDXManager->GetDXInput()->SetPreBuffer(); }
		//FPSを計算する
		void UpdateFPS() { mFPS = mFPSCountor->GetFPS(); }
		void SetVsyncIntarval(int intarval) { mDXManager->SetVsyncIntarval(intarval); }
	private:
		//FPS計算結果を保持
		double mFPS;
		//生成したオブジェクト数
		UINT mGameObjectCount;
		//FPS計測クラス
		std::unique_ptr<FPSCountor> mFPSCountor;
		//DirectXリソース生成管理クラス
		std::unique_ptr<DXManager> mDXManager;
		//音管理クラス
		std::unique_ptr<DXSoundManager> mDXSoundManager;
	};
}


