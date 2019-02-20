#pragma once
#include "Scene.h"
#include "DXText.h"
#include "DXTexture.h"
#include "ReactiveProperty.h"
#include "FieldManager.h"
#include "TetriMinoController.h"
#include "ScoreManager.h"
#include "TetriMinoNext.h"

using namespace MyObservarPattern;

namespace MyDirectX
{
	class PlayScene :public Scene
	{
	public:
		PlayScene() {};
		~PlayScene() {};
		virtual void Init() override;
		virtual void SceneStart() override;
		virtual void SceneUpdate() override;
		virtual void SceneEnd() override;
		virtual bool IsSceneEnd() override;
	private:
		//�G�t�F�N�g�ҋ@�t���[��
		const int cWaitFrame = 60;
		//�ҋ@���n�߂��t���[�������i�[���邽�߂̕ϐ�
		int mWaitStartFrame;
		//UI�v�f����
		void CreateUIItem();
		//�t���[���v���p
		int mFrameCount;
		//FPS�\���X�V�t���[����
		const int FPS_CHEACK_FRAME_COUNT = 60;
		//FPS�\���e�L�X�g
		DXText* mFPSText;
		//T�X�s�����ɕ\������UI
		DXGameObject* mTspinUI;
		//T�X�s���~�j���ɕ\������UI
		DXGameObject* mTspinMiniUI;
		//�V�[���J�n���ɃA�N�e�B�u�ɂ���I�u�W�F�N�g
		std::vector<DXGameObject*> mAwakeObject;
		//�t�B�[���h�Ǘ�
		std::unique_ptr<FieldManager> mFieldManager;
		//�Ֆʑ���
		std::unique_ptr<TetriMinoController> mTetriMinoController;
		//�X�R�A�Ǘ�
		std::unique_ptr<ScoreManager> mScoreManager;
		//Next�\��
		std::unique_ptr<TetriMinoNext> mNext;
		//�G�C���A�X�e���v���[�g���g���Ė��O��Z�k
		using Property = ReactiveProperty<double>;
		//FPS�\���Ɏg���ϐ�
		std::unique_ptr<Property, Deleter> mFPSRP;
		//BGM
		DXSound* mBGM;
		//�������̉�
		DXSound* mDeleteSound;
		//�����݂̃v���C�V�[���̏��
		PlaySceneState mState = Play;
	};
}


