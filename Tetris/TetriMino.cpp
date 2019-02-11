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

void TetriMino::TetriMinoPreUpdate()
{
	if(mIsLanding)
	{
		mLandingFrame++;
		if(mLandingFrame >= mLandingJudgeFrame)
		{
			mIsNext = true;
			mLandingFrame = 0;
			mIsLanding = false;
			return;
		}
	}
	else 
	{
		mIsNext = false;
		mLandingFrame = 0;
	}
	for(int i = 0;i < 4;i++)
	{
		mPrePiecePositions[i] = mPiecePositions[i];
	}
}

void TetriMino::TetriMinoUpdate()
{
	for(auto piecePos:mPrePiecePositions)
	{
		mFieldManager->ErasePiece(piecePos.x, piecePos.y);
	}
	for (auto piecePos : mPiecePositions)
	{
		mFieldManager->UpdatePiece(piecePos.x, piecePos.y, PlayerControll, mColor);
	}
}

bool TetriMino::MoveTetriMino(int rowMove, int columnMove)
{
	//�ړ���̈ʒu���v�Z
	mPiecePositions[0].x += rowMove;
	mPiecePositions[0].y += columnMove;
	CalcPiecePosition();
	//�d�����Ă���΋t�����Ɉړ�����
	if (IsDuplication()) 
	{
		MoveTetriMino(-rowMove, -columnMove);
		return false;
	}
	else return true;
}

bool TetriMino::RightRotation()
{
	auto rotationStateNum = static_cast<int>(mRotationState);
	rotationStateNum = (++rotationStateNum) % ROTATIONSTATENUM;
	mRotationState = static_cast<TetriMinoRotationState>(rotationStateNum);
	CalcPiecePosition();
	//�d�����Ă���΋t��]
	if (IsDuplication()) 
	{
		LeftRotation();
		return false;
	}
	else return true;
}

bool TetriMino::LeftRotation()
{
	auto rotationStateNum = static_cast<int>(mRotationState);
	rotationStateNum = (rotationStateNum + ROTATIONSTATENUM - 1) % ROTATIONSTATENUM;
	mRotationState = static_cast<TetriMinoRotationState>(rotationStateNum);
	CalcPiecePosition();
	//�d�����Ă���΋t��]
	if (IsDuplication()) 
	{
		RightRotation();
		return false;
	}
	else return true;
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
		
	case S:
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

	case Z:
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
	//���݂̃s�[�X�̏㉺���E�̍ő�ŏ������߂�
	mMinPosition = mPiecePositions[0];
	mMaxPosition = mPiecePositions[0];
	for (auto piecePos : mPiecePositions)
	{
		if (mMinPosition.x > piecePos.x) mMinPosition.x = piecePos.x;
		if (mMinPosition.y > piecePos.y) mMinPosition.y = piecePos.y;
		if (mMaxPosition.x < piecePos.x) mMaxPosition.x = piecePos.x;
		if (mMaxPosition.y < piecePos.y) mMaxPosition.y = piecePos.y;
	}
}

bool TetriMino::IsDuplication()
{
	for(auto piece:mPiecePositions)
	{
		auto state = mFieldManager->GetPieceState(piece.x, piece.y);
		//�v���C���[�����삷��s�[�X�������牽����������
		if (state == PlayerControll) continue;
		//�󔒂łȂ���Ώd�����Ă���
		if (state != Space)
			return true;
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
	TetriMinoPreUpdate();
}
