#pragma once
#include "DXGameObject.h"
#include "MyStructs.h"
#include "Piece.h"
#include <vector>

namespace MyDirectX
{
	class Scene;
	class FieldManager
	{
	public:
		FieldManager(Scene* scene);
		~FieldManager() {};
		void Start();
		void AllPieceEnable();
		void AllPieceDisable();
		void LockPiece();
		void UpdatePiece(int i, int j, PieceState state, PieceColor color);
		void CheckErase();
		void ErasePiece(int i,int j);
		void ErasePiece();
		PieceState GetPieceState(int i, int j) { return mPieces[i][j]->GetPieceState(); }
		int GetROWNUM() const { return ROWNUM; }
		int GetCOLUMNNUM() const { return COLUMNNUM; }
	private:
		std::vector <std::vector<Piece*>> mPieces;
		std::vector <std::vector<int>> mDropCounts;
		void PieceDrop();
		Scene* mScene;
		const int ROWNUM = 12;
		const int COLUMNNUM = 24;
		std::vector<int> mEraseLine;
	};
}

