#include "stdafx.h"
#include "TetriMinoRotation.h"

#include <sstream>
#define STRING(var) #var

using namespace MyDirectX;
TetriMinoRotation::TetriMinoRotation(DXResourceManager* manager, TetriMino* tetrimino)
{
	mManager = manager;
	mTetriMino = tetrimino;
	mSuperRotationState = Zero;
}

void TetriMinoRotation::Update()
{
	//Oテトリミノであれば回転処理は行わない
	auto type = mTetriMino->GetTetriMinoType();
	if (type == O) return;
	mMovePosition.x = 0;
	mMovePosition.y = 0;
	mSuperRotationState = Zero;
	mTetriMinoRotationState = mTetriMino->GetRotationState();
	mTetriMinoType = mTetriMino->GetTetriMinoType();
	if (mManager->GetKeyDown(DIK_Z))
	{
		if (!mTetriMino->LeftRotation()) 
		{
			mSuperRotationState = One;
			if(!IsSuperRotation()) mTetriMino->RightRotation();
		}
	}
	if (mManager->GetKeyDown(DIK_X))
	{
		if (!mTetriMino->RightRotation()) 
		{
			mSuperRotationState = One;
			if (!IsSuperRotation()) mTetriMino->LeftRotation();
		}
	}
}

bool TetriMinoRotation::IsSuperRotation()
{
	//現在の回転状態を取得
	auto rotationState = mTetriMino->GetRotationState();
	return IsSuperRotationCheck(mTetriMinoRotationState, rotationState);
}

bool TetriMinoRotation::IsSuperRotationCheck(TetriMinoRotationState preState, TetriMinoRotationState state)
{
	//回転軸の移動量計算
	if(mTetriMinoType == I)
	{
		switch (mSuperRotationState)
		{
		case One:
			mSuperRotationState = Two;
			switch (preState)
			{
			case A:
				if (state == D)
				{
					mMovePosition.x -= 1;
				}
				if (state == B)
				{
					mMovePosition.x -= 2;
				}
				break;
			case B:
				if (state == A)
				{
					mMovePosition.x += 2;
				}
				if (state == C)
				{
					mMovePosition.x += 1;
				}
				break;
			case C:
				if (state == B)
				{
					mMovePosition.x += 1;
				}
				if (state == D)
				{
					mMovePosition.x += 2;
				}
				break;
			case D:
				if (state == C)
				{
					mMovePosition.x += 1;
				}
				if (state == A) 
				{
					mMovePosition.x += 2;
				}
				break;
			default:
				break;
			}
			break;
		case Two:
			mSuperRotationState = Three;
			mMovePosition.x = 0;
			switch (preState)
			{
			case A:
				if (state == D)
				{
					mMovePosition.x += 2;
				}
				if (state == B)
				{
					mMovePosition.x += 1;
				}
				break;
			case B:
				if (state == A)
				{
					mMovePosition.x -= 1;
				}
				if (state == C)
				{
					mMovePosition.x -= 2;
				}
				break;
			case C:
				if (state == B)
				{
					mMovePosition.x -= 2;
				}
				if (state == D)
				{
					mMovePosition.x -= 1;
				}
				break;
			case D:
				if (state == C)
				{
					mMovePosition.x -= 2;
				}
				if (state == A)
				{
					mMovePosition.x -= 1;
				}
				break;
			default:
				break;
			}
			break;
		case Three:
			mSuperRotationState = Four;
			mMovePosition.x = 0;
			switch (preState)
			{
			case A:
				if (state == D)
				{
					mMovePosition.x -= 1;
					mMovePosition.y += 2;
				}
				if (state == B)
				{
					mMovePosition.x -= 2;
					mMovePosition.y -= 1;
				}
				break;
			case B:
				if (state == A)
				{
					mMovePosition.x += 2;
					mMovePosition.y += 1;
				}
				if (state == C)
				{
					mMovePosition.x += 1;
					mMovePosition.y += 2;
				}
				break;
			case C:
				if (state == B)
				{
					mMovePosition.x += 1;
					mMovePosition.y -= 2;
				}
				if (state == D)
				{
					mMovePosition.x += 2;
					mMovePosition.y += 1;
				}
				break;
			case D:
				if (state == C)
				{
					mMovePosition.x += 1;
					mMovePosition.y -= 1;
				}
				if (state == A)
				{
					mMovePosition.x += 2;
					mMovePosition.y -= 2;
				}
				break;
			default:
				break;
			}
			break;
		case Four:
			mSuperRotationState = End;
			mMovePosition.x = 0;
			mMovePosition.y = 0;
			switch (preState)
			{
			case A:
				if (state == D)
				{
					mMovePosition.x += 2;
					mMovePosition.y -= 1;
				}
				if (state == B)
				{
					mMovePosition.x += 1;
					mMovePosition.y += 2;
				}
				break;
			case B:
				if (state == A)
				{
					mMovePosition.x -= 1;
					mMovePosition.y -= 2;
				}
				if (state == C)
				{
					mMovePosition.x -= 2;
					mMovePosition.y -= 1;
				}
				break;
			case C:
				if (state == B)
				{
					mMovePosition.x -= 2;
					mMovePosition.y += 1;
				}
				if (state == D)
				{
					mMovePosition.x -= 1;
					mMovePosition.y -= 2;
				}
				break;
			case D:
				if (state == C)
				{
					mMovePosition.x -= 2;
					mMovePosition.y += 2;
				}
				if (state == A)
				{
					mMovePosition.x -= 1;
					mMovePosition.y += 1;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	else 
	{
		switch (mSuperRotationState)
		{
		case One:
			mSuperRotationState = Two;
			switch (preState)
			{
			case A:
				if(state == D)
				{
					mMovePosition.x -= 1;
				}
				if(state == B)
				{
					mMovePosition.x += 1;
				}
				break;
			case B:
				mMovePosition.x -= 1;
				break;
			case C:
				if (state == B)
				{
					mMovePosition.x += 1;
				}
				if (state == D)
				{
					mMovePosition.x -= 1;
				}
				break;
			case D:
				mMovePosition.x += 1;
				break;
			default:
				break;
			}
			break;
		case Two:
			mSuperRotationState = Three;
			switch (state)
			{
			case A:
				mMovePosition.y -= 1;
				break;
			case B:
				mMovePosition.y += 1;
				break;
			case C:
				mMovePosition.y -= 1;
				break;
			case D:
				mMovePosition.y += 1;
				break;
			default:
				break;
			}
			break;
		case Three:
			mSuperRotationState = Four;
			mMovePosition.x = 0;
			mMovePosition.y = 0;
			switch (state)
			{
			case A:
				mMovePosition.y += 2;
				break;
			case B:
				mMovePosition.y -= 2;
				break;
			case C:
				mMovePosition.y += 2;
				break;
			case D:
				mMovePosition.y -= 2;
				break;
			default:
				break;
			}
			break;
		case Four:
			mSuperRotationState = End;
			switch (preState)
			{
			case A:
				if (state == D)
				{
					mMovePosition.x -= 1;
				}
				if (state == B)
				{
					mMovePosition.x += 1;
				}
				break;
			case B:
				mMovePosition.x -= 1;
				break;
			case C:
				if (state == B)
				{
					mMovePosition.x += 1;
				}
				if (state == D)
				{
					mMovePosition.x -= 1;
				}
				break;
			case D:
				mMovePosition.x += 1;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	//移動出来たらtrue
	if (mTetriMino->MoveTetriMinoSafe(mMovePosition.x, mMovePosition.y)) 
	{
		return true;
	}
	//出来ずにスーパーローテーション判定が終わればfalse
	else if (mSuperRotationState == End) 
	{
		return false;
	}
	//スーパーローテーション判定が残っていれば次の判定へ
	else return IsSuperRotationCheck(preState, state);

	
}
