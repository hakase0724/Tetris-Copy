#pragma once
#include <mmsystem.h>
#include <dsound.h>
#include <windows.h>
#include <tchar.h>
#include <string>
namespace MyDirectX
{
	class DXSound
	{
	public:
		DXSound(HWND hwnd, LPWSTR sourcePath);
		~DXSound() {};
		//音量設定
		void SetVolume(LONG volume) { mDsBuffer->SetVolume(volume); }
		//音を最初から再生できるようにする
		void ResetSound();
		void Play(bool isLoop = true);
		void Stop();
		std::wstring GetSourcePath() { return mSourcePath; }
	private:
		std::wstring mSourcePath;
		IDirectSound8* mDirectSound;
		IDirectSoundBuffer8* mDsBuffer;
		bool OpenWave(TCHAR *filepath, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize);
	};

}


