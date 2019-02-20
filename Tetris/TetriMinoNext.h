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
		//次のテトリミノを取得
		TetriMinoType GetNextTetriMino();
	private:
		Scene* mScene;
		//テトリミノNextのUI達
		std::vector<TetriMinoUI*> mTetriMinoNextUIObjects;
		//表示するテトリミノの形
		std::list<TetriMinoType> mTypeList;
		//次出すテトリミノの形を取得
		TetriMinoType GetNextTetriMinoType();
		//指定した範囲内での乱数を返す
		//min = 乱数の最小値
		//max = 乱数の最大値
		int GetRandRange(int min,int max);
		//次のテトリミノ情報を更新する
		void NextUpdate();
	};
}


