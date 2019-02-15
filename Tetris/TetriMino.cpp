#include "stdafx.h"
#include "TetriMino.h"
#include <algorithm>

using namespace MyDirectX;
TetriMino::TetriMino(FieldManager* field)
{
	mFieldManager = field;
	mRotationState = A;
	mPreRotationState = mRotationState;
}

void TetriMino::Start()
{
	mIsLanding = false;
	mIsNext = false;
	mIsGameOver = false;
	mLandingFrame = 0;
}

void TetriMino::TetriMinoPreUpdate()
{
	//���o���Ȃ牽�����Ȃ�
	if (mIsNext) return;
	//���n����
	mIsLanding = IsLanding();
	//���n���Ă����
	if(mIsLanding)
	{
		mLandingFrame++;
		if(mLandingFrame >= mLandingJudgeFrame)
		{
			GoNext();
			return;
		}
	}
	else 
	{
		mIsNext = false;
		mLandingFrame = 0;
	}
	MemoryPrePiecePosition();
}

void TetriMino::TetriMinoUpdate()
{
	CalcGhostPosition();
	mFieldManager->ErasePiece(Ghost);
	for (auto ghostPos : mGhostPositions)
	{
		mFieldManager->UpdatePiece(ghostPos.x, ghostPos.y, Ghost, mColor);
	}
	//�J�n���ʒu�̃s�[�X������
	for(auto piecePos:mPrePiecePositions)
	{
		mFieldManager->ErasePiece(piecePos.x, piecePos.y);
	}
	//���݈ʒu�̃s�[�X��\��
	for (auto piecePos : mPiecePositions)
	{
		mFieldManager->UpdatePiece(piecePos.x, piecePos.y, PlayerControll, mColor);
	}
}

bool TetriMino::MoveTetriMino(int rowMove, int columnMove)
{
	//�ړ���̈ʒu���v�Z
	for(int i = 0;i < 4;i++)
	{
		mPiecePositions[i].x += rowMove;
		mPiecePositions[i].y += columnMove;
	}
	//�d�����Ă��邩
	if (IsDuplication()) return false;
	else return true;
}

bool TetriMino::MoveTetriMinoSafe(int rowMove, int columnMove)
{
	if (!MoveTetriMino(rowMove, columnMove)) 
	{
		MoveTetriMino(-rowMove, -columnMove);
		mLandingFrame = 0;
		return false;
	}
	else 
	{
		mLandingFrame = 0;
		return true;
	}
}

bool TetriMino::RightRotation()
{
	auto rotationStateNum = static_cast<int>(mRotationState);
	rotationStateNum = (++rotationStateNum) % ROTATIONSTATENUM;
	mRotationState = static_cast<TetriMinoRotationState>(rotationStateNum);
	CalcPiecePosition();
	//�d�����Ă��邩
	if (IsDuplication()) return false;
	else return true;
}

bool TetriMino::RightRotationSafe()
{
	if(!RightRotation())
	{
		LeftRotation();
		mLandingFrame = 0;
		return false;
	}
	else
	{
		mLandingFrame = 0;
		return true;
	}
}

bool TetriMino::LeftRotation()
{
	auto rotationStateNum = static_cast<int>(mRotationState);
	rotationStateNum = (rotationStateNum + ROTATIONSTATENUM - 1) % ROTATIONSTATENUM;
	mRotationState = static_cast<TetriMinoRotationState>(rotationStateNum);
	CalcPiecePosition();
	//�d�����Ă��邩
	if (IsDuplication()) return false;
	else return true;
}

bool TetriMino::LeftRotationSafe()
{
	if(!LeftRotation())
	{
		RightRotation();
		mLandingFrame = 0;
		return false;
	}
	else
	{
		mLandingFrame = 0;
		return true;
	}
}

void TetriMino::GoNext()
{
	mIsNext = true;
	mLandingFrame = 0;
	mIsLanding = false;
}

void TetriMino::MemoryPrePiecePosition()
{
	//�t���[���J�n���̈ʒu���L��
	for (int i = 0; i < 4; i++)
	{
		mPrePiecePositions[i] = mPiecePositions[i];
	}
}

void TetriMino::CalcPiecePosition()
{
	//�܂����S���W���R�s�[
	for(int i = 1;i < 4;i++)
	{
		mPiecePositions[i] = mPiecePositions[0];
	}
	//�`�ɉ����Ē��S���W�����ƂɊe�s�[�X�̈ʒu�����肷��
	switch (mType)
	{
	//��]���������Ƃ͈Ⴄ
	case I:
		//�O�񂩂��]���Ă����
		if(mPreRotationState != mRotationState)
		{
			//�O�񂩂�̉�]�ɉ����Ē��S���W���ړ�������
			switch (mRotationState)
			{
			case A:
				//����]���Ă���
				if(mPreRotationState == B)
				{
					mPiecePositions[0].x += 1;
				}
				//�E��]���Ă���
				if(mPreRotationState == D)
				{
					mPiecePositions[0].y += 1;
				}
				break;
			case B:
				//����]���Ă���
				if (mPreRotationState == C)
				{
					mPiecePositions[0].y += 1;
				}
				//�E��]���Ă���
				if (mPreRotationState == A)
				{
					mPiecePositions[0].x -= 1;
				}
				break;
			case C:
				//����]���Ă���
				if (mPreRotationState == D)
				{
					mPiecePositions[0].x -= 1;
				}
				//�E��]���Ă���
				if (mPreRotationState == B)
				{
					mPiecePositions[0].y -= 1;
				}
				break;
			case D:
				//����]���Ă���
				if (mPreRotationState == A)
				{
					mPiecePositions[0].y -= 1;
				}
				//�E��]���Ă���
				if (mPreRotationState == C)
				{
					mPiecePositions[0].x += 1;
				}
				break;
			default:
				break;
			}
			//���S���W���ړ��������̂ōēx�R�s�[
			for (int i = 1; i < 4; i++)
			{
				mPiecePositions[i] = mPiecePositions[0];
			}
		}
		switch (mRotationState)
		{
		/*

		�Z���Z�Z


		*/
		case A:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].x -= 2;
			break;
		/*
		�@�@�Z
		�@�@��
		  �@�Z
		�@�@�Z
		*/
		case B:
			mPiecePositions[1].y += 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].y -= 2;
			break;
		/*
		�@
		 �@
		�Z�Z���Z

		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x += 2;
			break;
		/*
		�Z
		�Z
		��
		�Z
		*/
		case D:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].y += 2;
			break;
		default:
			break;
		}
		break;
		
	//��]�����͂��Ȃ�
	case O:
		/*
		�Z�Z
		���Z
		*/
		mPiecePositions[1].y += 1;
		mPiecePositions[2].x -= 1;
		mPiecePositions[3].x -= 1;
		mPiecePositions[3].y += 1;
		break;
		
	case T:
		switch (mRotationState)
		{
		/*
		�@�Z
		�Z���Z
		*/
		case A:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		�@�Z
		�@���Z
		�@�Z
		*/
		case B:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		�@
		�Z���Z
		�@�Z
		*/
		case C:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		�@�Z
		�Z��
		�@�Z
		*/
		case D:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].y += 1;
			break;
		default:
			break;
		}
		break;
		
	case J:
		switch (mRotationState)
		{
		/*
		�Z
		�Z���Z
		*/
		case A:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		�@�Z�Z
		�@��
		�@�Z
		*/
		case B:
			mPiecePositions[1].y += 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		
		�Z���Z
		�@�@�Z
		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		�@�Z
		�@��
		�Z�Z
		*/
		case D:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y -= 1;
			break;
		default:
			break;
		}
		break;
		
	case L:
		switch (mRotationState)
		{
		/*
		�@�@�Z
		�Z���Z
		*/
		case A:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		�@�Z
		�@��
		�@�Z�Z
		*/
		case B:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		�@�@
		�Z���Z
		�Z
		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		�Z�Z
		�@��
		�@�Z
		*/
		case D:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y += 1;
			break;
		default:
			break;
		}
		break;
		
	case Z:
		switch (mRotationState)
		{
		/*
		�Z�Z
		�@���Z
		*/
		case A:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		�@�@�Z
		�@���Z
		�@�Z
		*/
		case B:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		�@�@
		�Z��
		�@�Z�Z
		*/
		case C:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		�@�Z
		�Z��
		�Z
		*/
		case D:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y -= 1;
			break;
		default:
			break;
		}
		break;

	case S:
		switch (mRotationState)
		{
		/*
		�@�Z�Z
		�Z��
		*/
		case A:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		�@�Z
		�@���Z
		�@�@�Z
		*/
		case B:
			mPiecePositions[1].y += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		�@
		�@���Z
		�Z�Z
		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		�Z
		�Z��
		�@�Z
		*/
		case D:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y += 1;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
	//��]��Ԃ��X�V
	mPreRotationState = mRotationState;
}

void TetriMino::CalcGhostPosition()
{
	for(int i = 0; i < 4;i++)
	{
		mGhostPositions[i] = mPiecePositions[i];
	}
	while(!IsGhostDuplication())
	{
		for(int i = 0;i < 4;i++)
		{
			mGhostPositions[i].y -= 1;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		mGhostPositions[i].y += 1;
	}

}

bool TetriMino::IsDuplication()
{
	for(int i = 0;i < 4;i++)
	{
		auto state = mFieldManager->GetPieceState(mPiecePositions[i].x, mPiecePositions[i].y);
		//�v���C���[�����삷��s�[�X�������牽����������
		if (state == PlayerControll) continue;
		if (state == Ghost) continue;
		//�󔒂łȂ���Ώd�����Ă���
		if (state != Space) return true;
	}
	return false;
}

bool TetriMino::IsGhostDuplication()
{
	for (int i = 0; i < 4; i++)
	{
		auto state = mFieldManager->GetPieceState(mGhostPositions[i].x, mGhostPositions[i].y);
		//�v���C���[�����삷��s�[�X�������牽����������
		if (state == PlayerControll) continue;
		if (state == Ghost) continue;
		//�󔒂łȂ���Ώd�����Ă���
		if (state != Space) return true;
	}
	return false;
}

bool TetriMino::IsLanding()
{
	for (auto piece : mPiecePositions)
	{
		auto state = mFieldManager->GetPieceState(piece.x, piece.y - 1);
		//�v���C���[�����삷��s�[�X�������牽����������
		if (state == PlayerControll) continue;
		if (state == Ghost) continue;
		//�󔒂łȂ���Ώd�����Ă���
		if (state != Space) return true;
	}
	return false;
}

void TetriMino::SetPlayerTetriMino(int row, int column, TetriMinoType type)
{
	mType = type;
	//�`�ɉ����ĐF��ݒ肷��
	switch (mType)
	{
	case I:
		mColor = LightBlue;
		break;
	case O:
		mColor = Yellow;
		break;
	case T:
		mColor = Purple;
		break;
	case J:
		mColor = Blue;
		break;
	case L:
		mColor = Orange;
		break;
	case S:
		mColor = Green;
		break;
	case Z:
		mColor = Red;
		break;
	default:
		mColor = Red;
		break;
	}
	//�s�[�X�̍��W����
	mPiecePositions[0].x = row;
	mPiecePositions[0].y = column;
	//�s�[�X�̉�]��ԏ�����
	mRotationState = A;
	mPreRotationState = A;
	//�s�[�X�̈ʒu�v�Z
	CalcPiecePosition();
	if (IsDuplication()) 
	{
		mPiecePositions[0].y += 1;
		CalcPiecePosition();
		if (IsDuplication())
		{
			mIsGameOver = true;
			return;
		}
	}
	mIsNext = false;
	MemoryPrePiecePosition();
}
