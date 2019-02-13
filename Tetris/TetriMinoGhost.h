#pragma once
#include "TetriMino.h"

namespace MyDirectX
{
	class TetriMinoGhost
	{
	public:
		TetriMinoGhost(FieldManager* manager);
		~TetriMinoGhost() {};
		void SetPosition(PiecePosition* piecePositions);
	private:
		FieldManager* mFieldManager;
		PiecePosition* mTetriMinoPositions;
		PiecePosition* mGhostPositions;
	};
}


