#include "stdafx.h"
#include "TetriMinoMove.h"

using namespace MyDirectX;
TetriMinoMove::TetriMinoMove(DXResourceManager* manager, TetriMino* tetrimino, FieldManager* fieldManager)
{
	mManager = manager;
	mTetriMino = tetrimino;
	mFieldManager = fieldManager;
	auto soundManager = mManager->GetSoundManager();
	mMoveSE = soundManager->GetSESound(_T("Sound/SE/Move.wav"));
	mMoveSE->SetVolume(DSBVOLUME_MAX);
	mHardDropSE = soundManager->GetSESound(_T("Sound/SE/HardLanding.wav"));
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
		auto isFall = mTetriMino->MoveTetriMinoSafe(0, -1);
		if (isFall) mTetriMino->SetTetriMinoAction(Move);
		//‚‘¬—Ž‰º’†‚©‚Â—Ž‚¿‚ê‚½‚ç
		if (mIsSoftDrop && isFall) 
		{
			mMoveScore++;
			mMoveSE->ResetSound();
			mMoveSE->Play(false);
		}
	}
	if (mManager->GetKeyDown(DIK_LEFTARROW))
	{
		auto isMove = mTetriMino->MoveTetriMinoSafe(1, 0);
		if (isMove) 
		{
			mTetriMino->SetTetriMinoAction(Move);
			mMoveSE->ResetSound();
			mMoveSE->Play(false);
		}
	}
	if (mManager->GetKeyDown(DIK_RIGHTARROW))
	{
		auto isMove = mTetriMino->MoveTetriMinoSafe(-1, 0);
		if (isMove)
		{
			mTetriMino->SetTetriMinoAction(Move);
			mMoveSE->ResetSound();
			mMoveSE->Play(false);
		}
	}
	if (mManager->GetKeyDown(DIK_UPARROW))
	{
		while(mTetriMino->MoveTetriMinoSafe(0,-1))
		{
			mMoveScore++;
		}
		mTetriMino->SetTetriMinoAction(Move);
		mHardDropSE->ResetSound();
		mHardDropSE->Play(false);
		mIsSoftDrop = false;
		mTetriMino->GoNext();
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
