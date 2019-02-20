#pragma once
#include <mmsystem.h>
#include <dsound.h>
#include <windows.h>
#include <tchar.h>
#include <string>
namespace MyDirectX
{
	//DirectSoundを扱うクラス
	class DXSound
	{
	public:
		DXSound(HWND hwnd, LPWSTR sourcePath);
		~DXSound() {};
		//音量設定
		void SetVolume(LONG volume) { mDsBuffer->SetVolume(volume); }
		//音を最初から再生できるようにする
		void ResetSound();
		//音を再生する
		//isLoop = ループ再生するか　デフォルトはループ再生
		void Play(bool isLoop = true);
		//音を止める
		void Stop();
		//音源ファイルのパスを返す
		std::wstring GetSourcePath() { return mSourcePath; }
	private:
		//音源ファイルのパス
		std::wstring mSourcePath;
		//DirectSoundを扱うために必要なインターフェース
		IDirectSound8* mDirectSound;
		IDirectSoundBuffer8* mDsBuffer;
		//Waveファイルローダー
		bool OpenWave(TCHAR *filepath, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize);
	};

}


