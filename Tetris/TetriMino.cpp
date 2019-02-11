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
	//ˆÚ“®Œã‚ÌˆÊ’u‚ğŒvZ
	mPiecePositions[0].x += rowMove;
	mPiecePositions[0].y += columnMove;
	CalcPiecePosition();
	//d•¡‚µ‚Ä‚¢‚ê‚Î‹t•ûŒü‚ÉˆÚ“®‚·‚é
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
	//d•¡‚µ‚Ä‚¢‚ê‚Î‹t‰ñ“]
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
	//d•¡‚µ‚Ä‚¢‚ê‚Î‹t‰ñ“]
	if (IsDuplication()) 
	{
		RightRotation();
		return false;
	}
	else return true;
}

void TetriMino::CalcPiecePosition()
{
	//‚Ü‚¸’†SÀ•W‚ğƒRƒs[
	for(int i = 1;i < 4;i++)
	{
		mPiecePositions[i] = mPiecePositions[0];
	}
	//Œ`‚É‰‚¶‚Ä’†SÀ•W‚ğ‚à‚Æ‚ÉŠeƒs[ƒX‚ÌˆÊ’u‚ğŒˆ’è‚·‚é
	switch (mType)
	{
	//‰ñ“]ˆ—‚ª‘¼‚Æ‚Íˆá‚¤
	case I:
		//‘O‰ñ‚©‚ç‰ñ“]‚µ‚Ä‚¢‚ê‚Î
		if(mPreRotationState != mRotationState)
		{
			//‘O‰ñ‚©‚ç‚Ì‰ñ“]‚É‰‚¶‚Ä’†SÀ•W‚ğˆÚ“®‚³‚¹‚é
			switch (mRotationState)
			{
			case A:
				//¶‰ñ“]‚µ‚Ä‚«‚½
				if(mPreRotationState == B)
				{
					mPiecePositions[0].x += 1;
				}
				//‰E‰ñ“]‚µ‚Ä‚«‚½
				if(mPreRotationState == D)
				{
					mPiecePositions[0].y += 1;
				}
				break;
			case B:
				//¶‰ñ“]‚µ‚Ä‚«‚½
				if (mPreRotationState == C)
				{
					mPiecePositions[0].y += 1;
				}
				//‰E‰ñ“]‚µ‚Ä‚«‚½
				if (mPreRotationState == A)
				{
					mPiecePositions[0].x -= 1;
				}
				break;
			case C:
				//¶‰ñ“]‚µ‚Ä‚«‚½
				if (mPreRotationState == D)
				{
					mPiecePositions[0].x -= 1;
				}
				//‰E‰ñ“]‚µ‚Ä‚«‚½
				if (mPreRotationState == B)
				{
					mPiecePositions[0].y -= 1;
				}
				break;
			case D:
				//¶‰ñ“]‚µ‚Ä‚«‚½
				if (mPreRotationState == A)
				{
					mPiecePositions[0].y -= 1;
				}
				//‰E‰ñ“]‚µ‚Ä‚«‚½
				if (mPreRotationState == C)
				{
					mPiecePositions[0].x += 1;
				}
				break;
			default:
				break;
			}
			//’†SÀ•W‚ğˆÚ“®‚³‚¹‚½‚Ì‚ÅÄ“xƒRƒs[
			for (int i = 1; i < 4; i++)
			{
				mPiecePositions[i] = mPiecePositions[0];
			}
		}
		switch (mRotationState)
		{
		/*

		ZœZZ


		*/
		case A:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].x -= 2;
			break;
		/*
		@@Z
		@@œ
		  @Z
		@@Z
		*/
		case B:
			mPiecePositions[1].y += 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].y -= 2;
			break;
		/*
		@
		 @
		ZZœZ

		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x += 2;
			break;
		/*
		Z
		Z
		œ
		Z
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
		
	//‰ñ“]ˆ—‚Í‚µ‚È‚¢
	case O:
		/*
		ZZ
		œZ
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
		@Z
		ZœZ
		*/
		case A:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		@Z
		@œZ
		@Z
		*/
		case B:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		@
		ZœZ
		@Z
		*/
		case C:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		@Z
		Zœ
		@Z
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
		Z
		ZœZ
		*/
		case A:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		@ZZ
		@œ
		@Z
		*/
		case B:
			mPiecePositions[1].y += 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		
		ZœZ
		@@Z
		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		@Z
		@œ
		ZZ
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
		@@Z
		ZœZ
		*/
		case A:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		@Z
		@œ
		@ZZ
		*/
		case B:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		@@
		ZœZ
		Z
		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		ZZ
		@œ
		@Z
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
		ZZ
		@œZ
		*/
		case A:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		@@Z
		@œZ
		@Z
		*/
		case B:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		@@
		Zœ
		@ZZ
		*/
		case C:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		@Z
		Zœ
		Z
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
		@ZZ
		Zœ
		*/
		case A:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		@Z
		@œZ
		@@Z
		*/
		case B:
			mPiecePositions[1].y += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		@
		@œZ
		ZZ
		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		Z
		Zœ
		@Z
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
	//‰ñ“]ó‘Ô‚ğXV
	mPreRotationState = mRotationState;
	//Œ»İ‚Ìƒs[ƒX‚Ìã‰º¶‰E‚ÌÅ‘åÅ¬‚ğ‹‚ß‚é
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
		//ƒvƒŒƒCƒ„[‚ª‘€ì‚·‚éƒs[ƒX‚¾‚Á‚½‚ç‰½‚à‚¹‚¸Ÿ‚Ö
		if (state == PlayerControll) continue;
		//‹ó”’‚Å‚È‚¯‚ê‚Îd•¡‚µ‚Ä‚¢‚é
		if (state != Space)
			return true;
	}
	return false;
}

void TetriMino::SetPlayerTetriMino(int row, int column, TetriMinoType type)
{
	mType = type;
	//Œ`‚É‰‚¶‚ÄF‚ğİ’è‚·‚é
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
	//ƒs[ƒX‚ÌÀ•Wˆ—
	mPiecePositions[0].x = row;
	mPiecePositions[0].y = column;
	//ƒs[ƒX‚Ì‰ñ“]ó‘Ô‰Šú‰»
	mRotationState = A;
	mPreRotationState = A;
	//ƒs[ƒX‚ÌˆÊ’uŒvZ
	CalcPiecePosition();
	TetriMinoPreUpdate();
}
