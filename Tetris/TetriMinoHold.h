#pragma once
#include "DXResourceManager.h"
#include "TetriMino.h"

namespace MyDirectX
{
	class TetriMinoHold
	{
	public:
		TetriMinoHold(DXResourceManager* manager, TetriMino* tetrimino);
		~TetriMinoHold() {};
		void Update();
	private:
		void Hold();
		bool mIsHold = false;
		DXResourceManager* mManager;
		TetriMino* mTetriMino;
		TetriMinoType mHoldType;
	};
}


