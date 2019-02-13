#pragma once
#include "DXResourceManager.h"
#include "TetriMino.h"

namespace MyDirectX
{
	class TetriMinoMove
	{
	public:
		TetriMinoMove(DXResourceManager* manager, TetriMino* tetrimino,FieldManager* fieldManager);
		~TetriMinoMove() {};
		void Start();
		void Update();
		int GetMoveScore() const { return mMoveScore; }
	private:
		DXResourceManager* mManager;
		FieldManager* mFieldManager;
		TetriMino* mTetriMino;
		int mFrameCount = 0;
		int mFreeFallCount = 60;
		bool mIsLanding = false;
		int mLandingFrame = 0;
		int mLandingJudgeFrame = 60;
		int mMoveScore;
		bool mIsSoftDrop = false;
	};
}

