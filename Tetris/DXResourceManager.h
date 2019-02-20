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
		//�I�u�W�F�N�g�𐶐�����
		DXGameObject* Instantiate();
		//DirectX���\�[�X�Ǘ��N���X��Ԃ�
		DXManager* GetDXManager() const { return mDXManager.get(); }
		//�w�肵���L�[�����͂��ꂽ�^�C�~���O��
		bool GetKeyDown(int key) { return mDXManager->GetDXInput()->GetKeyDown(key); }
		//�w�肵���L�[�����͂���Ă��邩
		bool GetKey(int key) { return mDXManager->GetDXInput()->GetKey(key); }
		//���Ǘ��N���X��Ԃ�
		DXSoundManager* GetSoundManager() { return mDXSoundManager.get(); }
		//FPS��Ԃ�
		double GetFPS() const { return mFPS; }
		//���݂̓��͏󋵂��擾
		void SetInputState() { mDXManager->GetDXInput()->SetInputState(); }
		//���̃t���[���֍s���O�Ɍ��݂̓��͏󋵂��L�^����
		void SetPreBuffer() { mDXManager->GetDXInput()->SetPreBuffer(); }
		//FPS���v�Z����
		void UpdateFPS() { mFPS = mFPSCountor->GetFPS(); }
		void SetVsyncIntarval(int intarval) { mDXManager->SetVsyncIntarval(intarval); }
	private:
		//FPS�v�Z���ʂ�ێ�
		double mFPS;
		//���������I�u�W�F�N�g��
		UINT mGameObjectCount;
		//FPS�v���N���X
		std::unique_ptr<FPSCountor> mFPSCountor;
		//DirectX���\�[�X�����Ǘ��N���X
		std::unique_ptr<DXManager> mDXManager;
		//���Ǘ��N���X
		std::unique_ptr<DXSoundManager> mDXSoundManager;
	};
}


