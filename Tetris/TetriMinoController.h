#pragma once
#include "TetriMino.h"
#include "TetriMinoMove.h"
#include "TetriMinoRotation.h"
#include "TetriMinoHold.h"
#include "DXResourceManager.h"
#include "Scene.h"

namespace MyDirectX 
{
	class TetriMinoController
	{
	public:
		TetriMinoController(DXResourceManager* manager,FieldManager* fieldManager,Scene* scene);
		~TetriMinoController() {};
		//初期化
		void Start();
		//テトリミノをセットする
		void SetTetriMino(int i, int j, TetriMinoType type);
		//フレーム開始時の処理
		void PreUpdate();
		//実際の更新処理
		bool Update();
		//ゲームオーバーになっているか
		bool IsGameOver() { return mTetriMino->GetIsGameOver(); }
		//移動の仕方によって追加スコアが発生する
		int GetMoveScore();
		bool GetIsTspin() { return mTetriMino->GetIsTspin(); }
		bool GetIsTspinMini() { return mTetriMino->GetIsTspinMini(); }
	private:
		Scene* mScene;
		//移動管理
		std::unique_ptr<TetriMinoMove> mMove;
		//回転管理
		std::unique_ptr<TetriMinoRotation> mRotation;
		//ホールド管理
		std::unique_ptr<TetriMinoHold> mHold;
		//テトリミノ
		std::unique_ptr<TetriMino> mTetriMino;
		DXResourceManager* mManager;
		DXSound* mSoftLandingSE;
	};
}


