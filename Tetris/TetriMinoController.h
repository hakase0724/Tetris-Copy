#pragma once
#include "TetriMino.h"
#include "TetriMinoMove.h"
#include "TetriMinoRotation.h"
#include "TetriMinoHold.h"
#include "DXResourceManager.h"
#include "Scene.h"

namespace MyDirectX 
{
	class TetriMinoController
	{
	public:
		TetriMinoController(DXResourceManager* manager,FieldManager* fieldManager,Scene* scene);
		~TetriMinoController() {};
		//������
		void Start();
		//�e�g���~�m���Z�b�g����
		void SetTetriMino(int i, int j, TetriMinoType type);
		//�t���[���J�n���̏���
		void PreUpdate();
		//���ۂ̍X�V����
		bool Update();
		//�Q�[���I�[�o�[�ɂȂ��Ă��邩
		bool IsGameOver() { return mTetriMino->GetIsGameOver(); }
		//�ړ��̎d���ɂ���Ēǉ��X�R�A����������
		int GetMoveScore();
		bool GetIsTspin() { return mTetriMino->GetIsTspin(); }
		bool GetIsTspinMini() { return mTetriMino->GetIsTspinMini(); }
	private:
		Scene* mScene;
		//�ړ��Ǘ�
		std::unique_ptr<TetriMinoMove> mMove;
		//��]�Ǘ�
		std::unique_ptr<TetriMinoRotation> mRotation;
		//�z�[���h�Ǘ�
		std::unique_ptr<TetriMinoHold> mHold;
		//�e�g���~�m
		std::unique_ptr<TetriMino> mTetriMino;
		DXResourceManager* mManager;
		DXSound* mSoftLandingSE;
	};
}


