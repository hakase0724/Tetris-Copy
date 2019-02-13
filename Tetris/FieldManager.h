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
		void Start();
		void LockPiece();
		void UpdatePiece(int i, int j, PieceState state, PieceColor color);
		void CheckErase();
		void ErasePiece(int i,int j);
		void ErasePiece(PieceState state = PlayerControll);
		int GetFreeFallFrame() const { return mFreeFallFrame; }
		PieceState GetPieceState(int i, int j) { return mPieces[i][j]->GetPieceState(); }
		int GetROWNUM() const { return ROWNUM; }
		int GetCOLUMNNUM() const { return COLUMNNUM; }
		int GetEraseScore();
	private:
		std::vector <std::vector<Piece*>> mPieces;
		std::vector <std::vector<int>> mDropCounts;
		void PieceDrop();
		Scene* mScene;
		const int ROWNUM = 12;
		const int COLUMNNUM = 24;
		std::vector<int> mEraseLine;
		std::unique_ptr<ReactiveProperty<int>, Deleter> mLevelRP;
		std::unique_ptr<ReactiveProperty<int>, Deleter> mEraseLineCountRP;
		int mLevel = 1;
		int mFreeFallFrame = 60;
		int mTotalEraseLineCount = 0;
		DXGameObject* mLevelUI;
		DXText* mLevelUIText;
		DXGameObject* mEraseLineCountUI;
		DXText* mEraseLineCountUIText;
	};
}

