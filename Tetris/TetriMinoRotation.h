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
		void Update();
	private:
		DXResourceManager* mManager;
		TetriMino* mTetriMino;
	};
}


