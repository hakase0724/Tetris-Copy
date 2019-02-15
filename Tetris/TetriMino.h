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
		//初期化
		void Start();
		//フレーム開始時の操作
		void TetriMinoPreUpdate();
		//テトリミノの更新
		void TetriMinoUpdate();
		//テトリミノを移動させる
		//重複していた場合逆方向に移動させる
		//rowMove = 行移動量
		//columnMove = 列移動量
		bool MoveTetriMino(int rowMove, int columnMove);
		//失敗した場合逆移動する
		bool MoveTetriMinoSafe(int rowMove, int columnMove);
		//右回転
		bool RightRotation();
		//失敗した場合逆移動する
		bool RightRotationSafe();
		//左回転
		bool LeftRotation();
		//失敗した場合逆移動する
		bool LeftRotationSafe();
		//プレイヤーが操作するテトリミノをセットする
		//row = 行番号
		//column = 列番号
		//type = 形
		void SetPlayerTetriMino(int row, int column,TetriMinoType type);
		//今のテトリミノの形を返す
		TetriMinoType GetTetriMinoType() { return mType; }
		//テトリミノを消す
		void ErasePiece() { mFieldManager->ErasePiece(); }
		//着地フラグをセットする
		void SetIsLanding(bool isLanding) { mIsLanding = isLanding; }
		//次のテトリミノを出すか
		bool GetIsNext() { return mIsNext; }
		//ゲームオーバーか
		bool GetIsGameOver() { return mIsGameOver; }
		//次へ行く
		void GoNext();
		//今の回転状態を返す
		TetriMinoRotationState GetRotationState() { return mRotationState; }
	private:
		//ピースの位置を記憶
		void MemoryPrePiecePosition();
		//回転状態列挙体の要素数
		const int ROTATIONSTATENUM = 4;
		//中心座標をもとに各ピースの座標を計算する
		void CalcPiecePosition();
		//ゴーストの位置計算
		void CalcGhostPosition();
		//重複しているか
		bool IsDuplication();
		//ゴーストが重複しているか
		bool IsGhostDuplication();
		//着地しているか
		bool IsLanding();
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
		//ゴーストの位置
		PiecePosition mGhostPositions[4];
		//着地しているか
		bool mIsLanding = false;
		//着地経過フレーム
		int mLandingFrame = 0;
		//着地して固定されるまでのフレーム数
		int mLandingJudgeFrame = 30;
		//次のテトリミノを出すか
		bool mIsNext = false;
		//ゲームオーバー判定
		bool mIsGameOver = false;
	};
}


