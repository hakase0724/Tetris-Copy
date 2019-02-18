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
		void DropPiece();
		void ChangeDebugMode();
		void ChangePieceStateToSpace(PieceState state = PlayerControll);
		int GetFreeFallFrame() const { return mFreeFallFrame; }
		PieceState GetPieceState(int i, int j);
		int GetROWNUM() const { return ROWNUM; }
		int GetCOLUMNNUM() const { return COLUMNNUM; }
		int GetEraseLineCount() { return mEraseLine.size(); }
		int GetLevel() { return mLevelRP->GetValue(); }
	private:
		bool IsWidthInTheFieldRange(int i, int j);
		std::vector <std::vector<Piece*>> mPieces;
		std::vector <std::vector<int>> mDropCounts;
		void EraseEffect();
		void PieceDrop();
		Scene* mScene;
		const int ROWNUM = 12;
		const int COLUMNNUM = 24;
		std::vector<int> mEraseLine;
		std::unique_ptr<ReactiveProperty<int>, Deleter> mLevelRP;
		std::unique_ptr<ReactiveProperty<int>, Deleter> mEraseLineCountRP;
		int mFreeFallFrame = mDefaultFreeFallFrame;
		DXGameObject* mLevelUI;
		DXText* mLevelUIText;
		DXGameObject* mEraseLineCountUI;
		DXText* mEraseLineCountUIText;
		bool mIsDebug = false;
		//‰Šú—‰ºƒtƒŒ[ƒ€
		int mDefaultFreeFallFrame = 60;
		//Å‘åƒŒƒxƒ‹
		int mMaxLevel = 15;
		DXGameObject* mOneLineEffect;
		DXGameObject* mOneLineEffect2;
	};
}

