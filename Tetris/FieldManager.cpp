#include "stdafx.h"
#include "FieldManager.h"
#include "Scene.h"
#include "DXTexture.h"
#include "CommonValues.h"
#include <sstream>
using namespace MyDirectX;
FieldManager::FieldManager(Scene* scene)
{
	mScene = scene;
	//�z��̏�����
	for (int i = 0; i < ROWNUM; i++)
	{
		std::vector<Piece*> pieces;
		std::vector<int> counts;
		for (int j = 0; j < COLUMNNUM; j++)
		{
			auto piece = mScene->Instantiate();
			auto pieceTex = piece->AddComponent<DXTexture>();
			auto pieceTransform = piece->GetTransform();
			pieceTransform->Position = DirectX::XMFLOAT3(cRightEndPos + (cPieceWidthOffset * i), cBottomPos + (cPieceHeightOffset * j), 0.001f);
			pieceTransform->Scale = DirectX::XMFLOAT3(0.1f, 0.1f, 1.0f);
			auto pieceCom = piece->AddComponent<Piece>();
			piece->InitializeComponent();
			pieces.push_back(pieceCom);
			counts.push_back(0);
		}
		mPieces.push_back(pieces);
		mDropCounts.push_back(counts);
	}
}

void FieldManager::UpdatePiece(int i, int j, PieceState state, PieceColor color)
{
	auto piece = mPieces[i][j];
	piece->SetPieceState(state);
	piece->SetPieceColor(color);
}

void FieldManager::CheckErase()
{
	mEraseLine.clear();
	auto eraseNum = 0;
	auto eraseJudgeNum = ROWNUM - 2;
	//�񁨍s�ƌ��Ă���
	for (int j = 1; j < COLUMNNUM - 3; j++)
	{
		eraseNum = 0;
		for (int i = 1; i < ROWNUM - 1; i++) 
		{
			//�ՖʂɌŒ肳��Ă���s�[�X�̐��𐔂���
			if (mPieces[i][j]->GetPieceState() == FieldLock) 
			{
				eraseNum++;
			}
		}
		//�Œ肳��Ă���s�[�X���������萔�ȏ�ł���Ώ���
		if(eraseNum >= eraseJudgeNum)
		{
			//������������i�[
			mEraseLine.push_back(j);
			for (int i = 1; i < ROWNUM - 1; i++)
			{
				ErasePiece(i, j);
			}
		}
	}
	//�������Ă���Η����������s��
	if (!mEraseLine.empty()) PieceDrop();
}

void FieldManager::ErasePiece(int i, int j)
{
	mPieces[i][j]->Erase();
}

void FieldManager::ErasePiece()
{
	for(auto pieces:mPieces)
	{
		for(auto piece:pieces)
		{
			if(piece->GetPieceState() == PlayerControll)
			{
				piece->Erase();
			}
		}
	}
}

void FieldManager::PieceDrop()
{
	//��������i���v�Z
	for (auto line : mEraseLine)
	{
		//�����������1��ォ�猩�Ă���
		for (int j = line + 1; j < COLUMNNUM; j++)
		{
			for (int i = 1; i < ROWNUM - 1; i++)
			{
				auto piece = mPieces[i][j];
				if (piece->GetPieceState() != FieldLock) continue;
				mDropCounts[i][j]++;
			}
		}
	}
	//����
	for (int j = 1; j < COLUMNNUM; j++)
	{
		for (int i = 1; i < ROWNUM; i++)
		{
			if (mDropCounts[i][j] <= 0) continue;
			auto color = mPieces[i][j]->GetPieceColor();
			ErasePiece(i, j);
			UpdatePiece(i, j - mDropCounts[i][j], FieldLock, color);
			mDropCounts[i][j] = 0;
		}
	}
}

void FieldManager::Start()
{
	//�X�y�[�X���󂯂�
	for (int i = 1; i < ROWNUM - 1; i++)
	{
		for (int j = 1; j < COLUMNNUM; j++)
		{
			mPieces[i][j]->SetPieceState(Space);
		}
	}
}

void FieldManager::AllPieceEnable()
{
	for(int i = 0;i < ROWNUM;i++)
	{
		for(int j = 0;j < COLUMNNUM;j++)
		{
			UpdatePiece(i, j, PlayerControll, Red);
		}
	}
}

void FieldManager::AllPieceDisable()
{
	for (int i = 0; i < ROWNUM; i++)
	{
		for (int j = 0; j < COLUMNNUM; j++)
		{
			UpdatePiece(i, j, Space, Red);
		}
	}
}

void FieldManager::LockPiece()
{
	for(auto pieces:mPieces)
	{
		for(auto piece:pieces)
		{
			if(piece->GetPieceState() == PlayerControll)
			{
				piece->SetPieceState(FieldLock);
			}
		}
	}
}
