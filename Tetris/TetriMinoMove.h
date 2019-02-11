#pragma once
#include "DXResourceManager.h"
#include "TetriMino.h"

namespace MyDirectX
{
	class TetriMinoMove
	{
	public:
		TetriMinoMove(DXResourceManager* manager, TetriMino* tetrimino);
		~TetriMinoMove() {};
		void Start();
		void Update();
	private:
		DXResourceManager* mManager;
		TetriMino* mTetriMino;
		int mFrameCount = 0;
		int mFreeFallCount = 60;
		bool mIsLanding = false;
		int mLandingFrame = 0;
		int mLandingJudgeFrame = 60;
	};
}

