#pragma once
#include "DXResourceManager.h"
#include "TetriMino.h"
#include "TetriMinoNextUI.h"

namespace MyDirectX
{
	class TetriMinoHold
	{
	public:
		TetriMinoHold(DXResourceManager* manager, TetriMino* tetrimino,Scene* scene);
		~TetriMinoHold() {};
		void Start();
		void Update();
		bool IsFirstHold() { return mIsFirstHold; }
		bool IsHoldLock() { return mIsLockHold; }
		void UnlockHold() { mIsLockHold = false; }
	private:
		//�z�[���h����
		void Hold();
		//�z�[���h���Ă��邩
		bool mIsHold = false;
		//�z�[���h����������Ă��邩
		bool mIsLockHold = false;
		//�ŏ��̃z�[���h��
		bool mIsFirstHold = false;
		Scene* mScene;
		DXResourceManager* mManager;
		TetriMino* mTetriMino;
		TetriMinoType mHoldType;
		TetriMinoUI* mHoldUI;
		DXSound* mHoldSE;
	};
}


