#pragma once
#include "TetriMino.h"
#include "TetriMinoMove.h"
#include "TetriMinoRotation.h"
#include "TetriMinoHold.h"
#include "DXResourceManager.h"

namespace MyDirectX 
{
	class TetriMinoController
	{
	public:
		TetriMinoController(DXResourceManager* manager,FieldManager* fieldManager);
		~TetriMinoController() {};
		void Start();
		void SetTetriMino(int i, int j, TetriMinoType type);
		void PreUpdate();
		bool Update();
	private:
		std::unique_ptr<TetriMinoMove> mMove;
		std::unique_ptr<TetriMinoRotation> mRotation;
		std::unique_ptr<TetriMinoHold> mHold;
		std::unique_ptr<TetriMino> mTetriMino;
		DXResourceManager* mManager;
	};
}


