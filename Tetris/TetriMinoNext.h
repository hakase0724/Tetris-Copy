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
		//���̃e�g���~�m���擾
		TetriMinoType GetNextTetriMino();
	private:
		Scene* mScene;
		//�e�g���~�mNext��UI�B
		std::vector<TetriMinoUI*> mTetriMinoNextUIObjects;
		//�\������e�g���~�m�̌`
		std::list<TetriMinoType> mTypeList;
		//���o���e�g���~�m�̌`���擾
		TetriMinoType GetNextTetriMinoType();
		//�w�肵���͈͓��ł̗�����Ԃ�
		//min = �����̍ŏ��l
		//max = �����̍ő�l
		int GetRandRange(int min,int max);
		//���̃e�g���~�m�����X�V����
		void NextUpdate();
	};
}


