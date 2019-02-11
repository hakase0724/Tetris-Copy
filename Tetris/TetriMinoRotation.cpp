#include "stdafx.h"
#include "TetriMinoRotation.h"

using namespace MyDirectX;
TetriMinoRotation::TetriMinoRotation(DXResourceManager* manager, TetriMino* tetrimino)
{
	mManager = manager;
	mTetriMino = tetrimino;
}

void TetriMinoRotation::Update()
{
	if (mManager->GetKeyDown(DIK_Z))
	{
		mTetriMino->LeftRotation();
	}
	if (mManager->GetKeyDown(DIK_X))
	{
		mTetriMino->RightRotation();
	}
}
