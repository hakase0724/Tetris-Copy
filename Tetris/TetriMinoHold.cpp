#include "stdafx.h"
#include "TetriMinoHold.h"

using namespace MyDirectX;

TetriMinoHold::TetriMinoHold(DXResourceManager * manager, TetriMino * tetrimino)
{
	mManager = manager;
	mTetriMino = tetrimino;
}

void TetriMinoHold::Update()
{
	if(mManager->GetKeyDown(DIK_SPACE))
	{
		Hold();
		mIsHold = true;
	}
}

void TetriMinoHold::Hold()
{
	mTetriMino->ErasePiece();
	if(mIsHold)
	{
		auto type = mTetriMino->GetTetriMinoType();
		mTetriMino->SetPlayerTetriMino(5, 20, mHoldType);
		mHoldType = type;
	}
	else
	{
		mHoldType = mTetriMino->GetTetriMinoType();
		mTetriMino->SetPlayerTetriMino(5, 20, I);
	}
}
