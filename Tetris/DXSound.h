#pragma once
#include <mmsystem.h>
#include <dsound.h>
#include <windows.h>
#include <tchar.h>
#include <string>
namespace MyDirectX
{
	//DirectSound�������N���X
	class DXSound
	{
	public:
		DXSound(HWND hwnd, LPWSTR sourcePath);
		~DXSound() {};
		//���ʐݒ�
		void SetVolume(LONG volume) { mDsBuffer->SetVolume(volume); }
		//�����ŏ�����Đ��ł���悤�ɂ���
		void ResetSound();
		//�����Đ�����
		//isLoop = ���[�v�Đ����邩�@�f�t�H���g�̓��[�v�Đ�
		void Play(bool isLoop = true);
		//�����~�߂�
		void Stop();
		//�����t�@�C���̃p�X��Ԃ�
		std::wstring GetSourcePath() { return mSourcePath; }
	private:
		//�����t�@�C���̃p�X
		std::wstring mSourcePath;
		//DirectSound���������߂ɕK�v�ȃC���^�[�t�F�[�X
		IDirectSound8* mDirectSound;
		IDirectSoundBuffer8* mDsBuffer;
		//Wave�t�@�C�����[�_�[
		bool OpenWave(TCHAR *filepath, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize);
	};

}


