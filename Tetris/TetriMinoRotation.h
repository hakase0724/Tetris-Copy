#pragma once
#include "DXResourceManager.h"
#include "TetriMino.h"

namespace MyDirectX
{
	class TetriMinoRotation
	{
	public:
		TetriMinoRotation(DXResourceManager* manager, TetriMino* tetrimino);
		~TetriMinoRotation() {};
		void Start();
		void Update();
	private:
		bool IsSuperRotation();
		bool IsSuperRotationCheck(TetriMinoRotationState preState,TetriMinoRotationState state);
		TetriMinoRotationState mTetriMinoRotationState;
		DXResourceManager* mManager;
		TetriMino* mTetriMino;
		SuperRotationState mSuperRotationState;
		PiecePosition mMovePosition;
		TetriMinoType mTetriMinoType;
	};
}


