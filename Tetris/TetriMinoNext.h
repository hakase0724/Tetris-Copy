#pragma once
#include "Scene.h"
#include "MyEnums.h"
#include "TetriMinoNextUI.h"
#include <random>
#include <queue>

namespace MyDirectX
{
	class TetriMinoNext
	{
	public:
		TetriMinoNext(Scene* scene);
		void Start();
		TetriMinoType GetNextTetriMino();
	private:
		Scene* mScene;
		std::vector<TetriMinoUI*> mTetriMinoNextUIObjects;
		std::queue<TetriMinoType> mTypes;
		std::list<TetriMinoType> mTypeList;
		TetriMinoType GetNextTetriMinoType();
		int GetRandRange(int min,int max);
		void NextUpdate();
	};
}


