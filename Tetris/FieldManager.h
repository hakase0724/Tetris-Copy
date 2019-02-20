#pragma once
#include "DXGameObject.h"
#include "MyStructs.h"
#include "Piece.h"
#include <vector>
#include "ReactiveProperty.h"

using namespace MyObservarPattern;
namespace MyDirectX
{
	class Scene;
	class FieldManager
	{
	public:
		FieldManager(Scene* scene);
		~FieldManager() {};
		//初期化
		void Start();
		//プレイヤーが操作していたテトリミノを盤面に固定する
		void LockPiece();
		//ピース情報を更新する
		void UpdatePiece(int i, int j, PieceState state, PieceColor color);
		//消去判定
		void CheckErase();
		//ピースを落下させる
		void DropPiece();
		//デバッグモードを切り替える
		void ChangeDebugMode();
		//指定した状態のピースを空白ピースに変える
		void ChangePieceStateToSpace(PieceState state = PlayerControll);
		//レベルに応じた落下フレーム数を返す
		int GetFreeFallFrame() const { return mFreeFallFrame; }
		//指定した位置のピース状態を取得する
		PieceState GetPieceState(int i, int j);
		//消去した段数を返す
		int GetEraseLineCount() { return mEraseLine.size(); }
		//現在のレベルを返す
		int GetLevel() { return mLevelRP->GetValue(); }
	private:
		//渡された添え字が配列の範囲内かどうか判定
		bool IsWidthInTheFieldRange(int i, int j);
		//盤面のピース
		std::vector <std::vector<Piece*>> mPieces;
		//どこが何段落下するか記憶する配列
		std::vector <std::vector<int>> mDropCounts;
		//消去エフェクトを出す
		void EraseEffect();
		//ピースの落下
		void PieceDrop();
		Scene* mScene;
		const int ROWNUM = 12;
		const int COLUMNNUM = 24;
		//何列目を消去するか記憶
		std::vector<int> mEraseLine;
		//レベル管理
		//レベルが変更されると対応UIを更新する
		std::unique_ptr<ReactiveProperty<int>, Deleter> mLevelRP;
		//消去した段数管理
		//消去段数が増加すると対応UIを更新する
		std::unique_ptr<ReactiveProperty<int>, Deleter> mEraseLineCountRP;
		//自由落下のフレーム数
		int mFreeFallFrame = mDefaultFreeFallFrame;
		//レベルUI
		DXGameObject* mLevelUI;
		DXText* mLevelUIText;
		//消去列数UI
		DXGameObject* mEraseLineCountUI;
		DXText* mEraseLineCountUIText;
		//デバッグモードであるか
		bool mIsDebug = false;
		//初期落下フレーム
		int mDefaultFreeFallFrame = 60;
		//最大レベル
		int mMaxLevel = 15;
		//消去エフェクト
		DXGameObject* mOneLineEffect;
		DXGameObject* mOneLineEffect2;
	};
}

