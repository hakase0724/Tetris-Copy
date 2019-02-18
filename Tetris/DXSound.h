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
		//âπó ê›íË
		void SetVolume(LONG volume) { mDsBuffer->SetVolume(volume); }
		//âπÇç≈èâÇ©ÇÁçƒê∂Ç≈Ç´ÇÈÇÊÇ§Ç…Ç∑ÇÈ
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


