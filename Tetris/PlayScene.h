#pragma once
#include "Scene.h"
#include "DXText.h"
#include "DXTexture.h"
#include "ReactiveProperty.h"
#include "FieldManager.h"
#include "TetriMino.h"
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
		int GetRandRange(int min, int max);
		//UI�v�f����
		void CreateUIItem();
		//�t���[���v���p
		int mFrameCount;
		//FPS�\���X�V�t���[����
		const int FPS_CHEACK_FRAME_COUNT = 60;
		//FPS�\���e�L�X�g
		DXText* mFPSText;
		//�V�[���J�n���ɃA�N�e�B�u�ɂ���I�u�W�F�N�g
		std::vector<DXGameObject*> mAwakeObject;
		//�t�B�[���h�Ǘ�
		std::unique_ptr<FieldManager> mFieldManager;
		//�Ֆʑ���
		std::unique_ptr<TetriMinoController> mTetriMinoController;
		std::unique_ptr<TetriMino> mTetriMino;
		std::unique_ptr<ScoreManager> mScoreManager;
		std::unique_ptr<TetriMinoNext> mNext;
		//�G�C���A�X�e���v���[�g���g���Ė��O��Z�k
		using Property = ReactiveProperty<double>;
		//FPS�\���Ɏg���ϐ�
		std::unique_ptr<Property, Deleter> mFPSRP;
	};
}


