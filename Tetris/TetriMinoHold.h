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
		void Hold();
		bool mIsHold = false;
		bool mIsLockHold = false;
		bool mIsFirstHold = false;
		Scene* mScene;
		DXResourceManager* mManager;
		TetriMino* mTetriMino;
		TetriMinoType mHoldType;
		TetriMinoUI* mHoldUI;
	};
}


