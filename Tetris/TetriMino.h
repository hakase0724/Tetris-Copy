#pragma once
#include "FieldManager.h"
#include "MyEnums.h"
#include "MyStructs.h"

namespace MyDirectX
{
	class TetriMino
	{
	public:
		TetriMino(FieldManager* field);
		~TetriMino() {};
		//プレイヤーが操作するテトリミノをセットする
		//row = 行番号
		//column = 列番号
		//type = 形
		//color = 色
		void TetriMinoPreUpdate();
		void TetriMinoUpdate();
		bool MoveTetriMino(int rowMove, int columnMove);
		bool RightRotation();
		bool LeftRotation();
		void SetPlayerTetriMino(int row, int column,TetriMinoType type);
		TetriMinoType GetTetriMinoType() { return mType; }
		void ErasePiece() { mFieldManager->ErasePiece(); }
		void SetIsLanding(bool isLanding) { mIsLanding = isLanding; }
		bool GetIsNext() { return mIsNext; }
	private:
		//回転状態列挙体の要素数
		const int ROTATIONSTATENUM = 4;
		//中心座標をもとに各ピースの座標を計算する
		void CalcPiecePosition();
		//重複しているか
		bool IsDuplication();
		//現在保有しているピースの上下左右の最大
		PiecePosition mMinPosition;
		//現在保有しているピースの上下左右の最小
		PiecePosition mMaxPosition;
		//盤面
		FieldManager* mFieldManager;
		//形
		TetriMinoType mType;
		//色
		PieceColor mColor;
		//回転状態
		TetriMinoRotationState mRotationState;
		//前回の回転状態
		TetriMinoRotationState mPreRotationState;
		//保有するピース
		//0番目が中心
		PiecePosition mPiecePositions[4];
		//フレーム開始時のピースの位置
		PiecePosition mPrePiecePositions[4];
		//着地しているか
		bool mIsLanding = false;
		int mLandingFrame = 0;
		int mLandingJudgeFrame = 60;
		bool mIsNext = false;
	};
}


