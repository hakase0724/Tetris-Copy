#include "stdafx.h"
#include "TetriMinoMove.h"

using namespace MyDirectX;
TetriMinoMove::TetriMinoMove(DXResourceManager* manager, TetriMino* tetrimino, FieldManager* fieldManager)
{
	mManager = manager;
	mTetriMino = tetrimino;
	mFieldManager = fieldManager;
}

void TetriMinoMove::Start()
{
	mFrameCount = 0;
}

void TetriMinoMove::Update()
{
	mFrameCount++;
	mMoveScore = 0;
	if(mFrameCount % mFreeFallCount == 0)
	{
		mFrameCount = 0;
		auto isFall = mTetriMino->MoveTetriMino(0, -1);
		//�����������������ꂽ��
		if (mIsSoftDrop && isFall) mMoveScore++;
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
		while(mTetriMino->MoveTetriMino(0,-1))
		{
			mMoveScore++;
		}
	}
	if (mManager->GetKey(DIK_DOWNARROW))
	{
		mFreeFallCount = 2;
		mIsSoftDrop = true;
	}
	else
	{
		mFreeFallCount = mFieldManager->GetFreeFallFrame();
		mIsSoftDrop = false;
	}
}
