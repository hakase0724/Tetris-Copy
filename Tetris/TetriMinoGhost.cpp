#include "stdafx.h"
#include "TetriMinoGhost.h"

using namespace MyDirectX;
TetriMinoGhost::TetriMinoGhost(FieldManager* manager)
{
	mFieldManager = manager;
}

void TetriMinoGhost::SetPosition(PiecePosition * piecePositions)
{
	mTetriMinoPositions = piecePositions;
	for(int i = 0;i < 4;i++)
	{
		mGhostPositions[i] = mTetriMinoPositions[i];
	}
}
