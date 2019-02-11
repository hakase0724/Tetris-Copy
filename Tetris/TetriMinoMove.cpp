#include "stdafx.h"
#include "TetriMinoMove.h"

using namespace MyDirectX;
TetriMinoMove::TetriMinoMove(DXResourceManager* manager, TetriMino* tetrimino)
{
	mManager = manager;
	mTetriMino = tetrimino;
}

void TetriMinoMove::Start()
{
	mFrameCount = 0;
}

void TetriMinoMove::Update()
{
	mFrameCount++;
	if(mFrameCount % mFreeFallCount == 0)
	{
		mFrameCount = 0;
		auto isFall = mTetriMino->MoveTetriMino(0, -1);
		if (!isFall) mTetriMino->SetIsLanding(true);
		else mTetriMino->SetIsLanding(false);
	}
	if (mManager->GetKeyDown(DIK_LEFTARROW))
	{
		mTetriMino->MoveTetriMino(1, 0);
	}
	if (mManager->GetKeyDown(DIK_RIGHTARROW))
	{
		mTetriMino->MoveTetriMino(-1, 0);
	}
	if (mManager->GetKeyDown(DIK_UPARROW))
	{
		while(mTetriMino->MoveTetriMino(0,-1)){}
	}
	if (mManager->GetKey(DIK_DOWNARROW))
	{
		mFreeFallCount = 5;
	}
	else
	{
		mFreeFallCount = 60;
	}
}
