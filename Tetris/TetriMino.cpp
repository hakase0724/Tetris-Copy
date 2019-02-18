#include "stdafx.h"
#include "TetriMino.h"
#include <algorithm>
#include <sstream>

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
	mIsTspin = false;
	mIsTspinMini = false;
}

void TetriMino::TetriMinoPreUpdate()
{
	//次出すなら何もしない
	if (mIsNext) return;
	//着地判定
	mIsLanding = IsLanding();
	//着地していれば
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
}

void TetriMino::TetriMinoUpdate()
{
	//ゴースト位置の計算
	CalcGhostPosition();
	//ゴーストを削除
	mFieldManager->ChangePieceStateToSpace(Ghost);
	//ゴーストを表示
	for (auto ghostPos : mGhostPositions)
	{
		mFieldManager->UpdatePiece(ghostPos.x, ghostPos.y, Ghost, mColor);
	}
	//テトリミノを削除
	mFieldManager->ChangePieceStateToSpace(PlayerControll);
	//現在位置のピースを表示
	for (auto piecePos : mPiecePositions)
	{
		mFieldManager->UpdatePiece(piecePos.x, piecePos.y, PlayerControll, mColor);
	}
}

bool TetriMino::MoveTetriMino(int rowMove, int columnMove)
{
	//移動後の位置を計算
	for(int i = 0;i < 4;i++)
	{
		mPiecePositions[i].x += rowMove;
		mPiecePositions[i].y += columnMove;
	}
	//重複しているか
	if (IsDuplication()) return false;
	else return true;
}

bool TetriMino::MoveTetriMinoSafe(int rowMove, int columnMove)
{
	if (!MoveTetriMino(rowMove, columnMove)) 
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
	//重複しているか
	if (IsDuplication()) return false;
	else return true;
}

bool TetriMino::RightRotationSafe()
{
	if(!RightRotation())
	{
		LeftRotation();
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
	//重複しているか
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

bool TetriMino::GetIsTspin()
{
	if (mLastAction != Rotation) return false;
	return IsTspin();
}

bool TetriMino::GetIsTspinMini()
{
	if (!mIsTspin) return false;
	return IsTspinMini();
}

bool TetriMino::IsTspin()
{
	//4隅のピース数をカウント
	auto pieceCount = 0;
	//中央のピース
	auto centerPiece = mPiecePositions[0];
	//4隅のピースの状態取得
	auto rightUpState = mFieldManager->GetPieceState(centerPiece.x - 1, centerPiece.y + 1);
	auto leftUpState = mFieldManager->GetPieceState(centerPiece.x + 1, centerPiece.y + 1);
	auto rightDownState = mFieldManager->GetPieceState(centerPiece.x - 1, centerPiece.y - 1);
	auto leftDownState = mFieldManager->GetPieceState(centerPiece.x + 1, centerPiece.y - 1);
	//取得したピースの状態が盤面固定されたピースであればカウントアップ
	if (rightUpState == FieldLock) pieceCount++;
	if (leftUpState == FieldLock) pieceCount++;
	if (rightDownState == FieldLock) pieceCount++;
	if (leftDownState == FieldLock) pieceCount++;
	//4隅のピースが3つ以上あればTスピンである
	if (pieceCount >= 3)
	{
		mIsTspin = true;
		return true;
	}
	else return false;
}

bool TetriMino::IsTspinMini()
{
	//中央のピース
	auto centerPiece = mPiecePositions[0];
	//中央の背後のピースの状態
	auto centerBackPieceState = Space;
	//ピースの回転状態によって背後のピースを求める
	switch (mRotationState)
	{
	case A:
		centerBackPieceState = mFieldManager->GetPieceState(centerPiece.x, centerPiece.y - 1);
		break;
	case B:
		centerBackPieceState = mFieldManager->GetPieceState(centerPiece.x + 1, centerPiece.y);
		break;
	case C:
		centerBackPieceState = mFieldManager->GetPieceState(centerPiece.x, centerPiece.y + 1);
		break;
	case D:
		centerBackPieceState = mFieldManager->GetPieceState(centerPiece.x - 1, centerPiece.y);
		break;
	default:
		break;
	}
	//背後のピースが盤面固定されていれば
	if (centerBackPieceState == FieldLock) 
	{
		mIsTspin = false;
		mIsTspinMini = true;
		return true;
	}
	else return false;
}

void TetriMino::CalcPiecePosition()
{
	//まず中心座標をコピー
	for(int i = 1;i < 4;i++)
	{
		mPiecePositions[i] = mPiecePositions[0];
	}
	//形に応じて中心座標をもとに各ピースの位置を決定する
	switch (mType)
	{
	//回転処理が他とは違う
	case I:
		//前回から回転していれば
		if(mPreRotationState != mRotationState)
		{
			//前回からの回転に応じて中心座標を移動させる
			switch (mRotationState)
			{
			case A:
				//左回転してきた
				if(mPreRotationState == B)
				{
					mPiecePositions[0].x += 1;
				}
				//右回転してきた
				if(mPreRotationState == D)
				{
					mPiecePositions[0].y += 1;
				}
				break;
			case B:
				//左回転してきた
				if (mPreRotationState == C)
				{
					mPiecePositions[0].y += 1;
				}
				//右回転してきた
				if (mPreRotationState == A)
				{
					mPiecePositions[0].x -= 1;
				}
				break;
			case C:
				//左回転してきた
				if (mPreRotationState == D)
				{
					mPiecePositions[0].x -= 1;
				}
				//右回転してきた
				if (mPreRotationState == B)
				{
					mPiecePositions[0].y -= 1;
				}
				break;
			case D:
				//左回転してきた
				if (mPreRotationState == A)
				{
					mPiecePositions[0].y -= 1;
				}
				//右回転してきた
				if (mPreRotationState == C)
				{
					mPiecePositions[0].x += 1;
				}
				break;
			default:
				break;
			}
			//中心座標を移動させたので再度コピー
			for (int i = 1; i < 4; i++)
			{
				mPiecePositions[i] = mPiecePositions[0];
			}
		}
		switch (mRotationState)
		{
		/*

		〇●〇〇


		*/
		case A:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].x -= 2;
			break;
		/*
		　　〇
		　　●
		  　〇
		　　〇
		*/
		case B:
			mPiecePositions[1].y += 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].y -= 2;
			break;
		/*
		　
		 　
		〇〇●〇

		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x += 2;
			break;
		/*
		〇
		〇
		●
		〇
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
		
	//回転処理はしない
	case O:
		/*
		〇〇
		●〇
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
		　〇
		〇●〇
		*/
		case A:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		　〇
		　●〇
		　〇
		*/
		case B:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		　
		〇●〇
		　〇
		*/
		case C:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		　〇
		〇●
		　〇
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
		〇
		〇●〇
		*/
		case A:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		　〇〇
		　●
		　〇
		*/
		case B:
			mPiecePositions[1].y += 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		
		〇●〇
		　　〇
		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		　〇
		　●
		〇〇
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
		　　〇
		〇●〇
		*/
		case A:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		　〇
		　●
		　〇〇
		*/
		case B:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		　　
		〇●〇
		〇
		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		〇〇
		　●
		　〇
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
		〇〇
		　●〇
		*/
		case A:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		　　〇
		　●〇
		　〇
		*/
		case B:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		　　
		〇●
		　〇〇
		*/
		case C:
			mPiecePositions[1].y -= 1;
			mPiecePositions[2].x += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		　〇
		〇●
		〇
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
		　〇〇
		〇●
		*/
		case A:
			mPiecePositions[1].x += 1;
			mPiecePositions[2].y += 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y += 1;
			break;
		/*
		　〇
		　●〇
		　　〇
		*/
		case B:
			mPiecePositions[1].y += 1;
			mPiecePositions[2].x -= 1;
			mPiecePositions[3].x -= 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		　
		　●〇
		〇〇
		*/
		case C:
			mPiecePositions[1].x -= 1;
			mPiecePositions[2].y -= 1;
			mPiecePositions[3].x += 1;
			mPiecePositions[3].y -= 1;
			break;
		/*
		〇
		〇●
		　〇
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
	//回転状態を更新
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
		//プレイヤーが操作するピースだったら何もせず次へ
		if (state == PlayerControll) continue;
		if (state == Ghost) continue;
		//空白でなければ重複している
		if (state != Space) return true;
	}
	return false;
}

bool TetriMino::IsGhostDuplication()
{
	for (int i = 0; i < 4; i++)
	{
		auto state = mFieldManager->GetPieceState(mGhostPositions[i].x, mGhostPositions[i].y);
		//プレイヤーが操作するピースだったら何もせず次へ
		if (state == PlayerControll) continue;
		if (state == Ghost) continue;
		//空白でなければ重複している
		if (state != Space) return true;
	}
	return false;
}

bool TetriMino::IsLanding()
{
	for (auto piece : mPiecePositions)
	{
		auto state = mFieldManager->GetPieceState(piece.x, piece.y - 1);
		//プレイヤーが操作するピースだったら何もせず次へ
		if (state == PlayerControll) continue;
		if (state == Ghost) continue;
		//空白でなければ重複している
		if (state != Space) return true;
	}
	return false;
}

void TetriMino::SetPlayerTetriMino(int row, int column, TetriMinoType type)
{
	mType = type;
	//形に応じて色を設定する
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
	//ピースの座標処理
	mPiecePositions[0].x = row;
	mPiecePositions[0].y = column;
	//ピースの回転状態初期化
	mRotationState = A;
	mPreRotationState = A;
	//ピースの位置計算
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
	//Tスピン判定を初期化
	mIsTspin = false;
	mIsTspinMini = false;
}
