#include "stdafx.h"
#include "TetriMinoRotation.h"

using namespace MyDirectX;
TetriMinoRotation::TetriMinoRotation(DXResourceManager* manager, TetriMino* tetrimino)
{
	mManager = manager;
	mTetriMino = tetrimino;
	mSuperRotationState = Zero;
}

void TetriMinoRotation::Update()
{
	//O�e�g���~�m�ł���Ή�]�����͍s��Ȃ�
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
	//���݂̉�]��Ԃ��擾
	auto rotationState = mTetriMino->GetRotationState();
	return IsSuperRotationCheck(mTetriMinoRotationState, rotationState);
}

bool TetriMinoRotation::IsSuperRotationCheck(TetriMinoRotationState preState, TetriMinoRotationState state)
{
	if(mTetriMinoType == I)
	{
		return false;
		/*switch (mSuperRotationState)
		{
		case One:
			switch (preState)
			{
			case A:
				break;
			case B:
				break;
			case C:
				break;
			case D:
				break;
			default:
				break;
			}
			break;
		case Two:
			switch (preState)
			{
			case A:
				break;
			case B:
				break;
			case C:
				break;
			case D:
				break;
			default:
				break;
			}
			break;
		case Three:
			switch (preState)
			{
			case A:
				break;
			case B:
				break;
			case C:
				break;
			case D:
				break;
			default:
				break;
			}
			break;
		case Four:
			switch (preState)
			{
			case A:
				break;
			case B:
				break;
			case C:
				break;
			case D:
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}*/
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
	//�ړ��o������true
	if (mTetriMino->MoveTetriMinoSafe(mMovePosition.x, mMovePosition.y)) return true;
	//�o�����ɃX�[�p�[���[�e�[�V�������肪�I����false
	else if (mSuperRotationState == Four) return false;
	//�X�[�p�[���[�e�[�V�������肪�c���Ă���Ύ��̔����
	else return IsSuperRotationCheck(preState, state);
}
