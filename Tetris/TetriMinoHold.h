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
		void UnlockHold() { mIsLockHold = false; }
	private:
		void Hold();
		bool mIsHold = false;
		bool mIsFirstHold = false;
		bool mIsLockHold = false;
		Scene* mScene;
		DXResourceManager* mManager;
		TetriMino* mTetriMino;
		TetriMinoType mHoldType;
		TetriMinoUI* mHoldUI;
	};
}


