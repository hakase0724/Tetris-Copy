#include "stdafx.h"
#include "FieldManager.h"
#include "Scene.h"
#include "DXTexture.h"
#include "CommonValues.h"
#include <sstream>
#include <iomanip>
#include "LightMove.h"
#include <algorithm>

using namespace MyDirectX;
FieldManager::FieldManager(Scene* scene)
{
	mScene = scene;

	mOneLineEffect = mScene->Instantiate();
	auto lightTex = mOneLineEffect->AddComponent<DXTexture>();
	lightTex->SetTexture(_T("Texture/Light.png"));
	mOneLineEffect->AddComponent<LightMove>();
	auto renderer = mOneLineEffect->GetComponent<TextureRenderer>();
	renderer->SetAlphaBlendingFlg(true);

	mOneLineEffect2 = mScene->Instantiate();
	auto lightTex2 = mOneLineEffect2->AddComponent<DXTexture>();
	lightTex2->SetTexture(_T("Texture/Light.png"));
	mOneLineEffect2->AddComponent<LightMove>();
	auto renderer2 = mOneLineEffect2->GetComponent<TextureRenderer>();
	renderer2->SetAlphaBlendingFlg(true);

	mLevelUI = mScene->Instantiate();
	mLevelUIText = mLevelUI->AddComponent<DXText>();
	auto levelUITransform = mLevelUI->GetTransform();
	levelUITransform->Position = DirectX::XMFLOAT3(1.0f, 0.15f, -1.1f);
	levelUITransform->Scale = DirectX::XMFLOAT3(0.07f, 0.07f, 1.0f);

	mLevelRP = 
		std::unique_ptr<ReactiveProperty<int>, Deleter>
		(new ReactiveProperty<int>(),Deleter());
	mLevelRP->Subscribe
	(
	[&](int value)->void 
	{
		std::wostringstream wos;
		wos << std::setw(8) << value;
		mLevelUIText->UpdateText(wos.str().c_str());
	}
	);

	mEraseLineCountUI = mScene->Instantiate();
	mEraseLineCountUIText = mEraseLineCountUI->AddComponent<DXText>();
	auto eraseLineCountUITransform = mEraseLineCountUI->GetTransform();
	eraseLineCountUITransform->Position = DirectX::XMFLOAT3(1.0f, 0.42f, -1.1f);
	eraseLineCountUITransform->Scale = DirectX::XMFLOAT3(0.07f, 0.07f, 1.0f);

	mEraseLineCountRP =
		std::unique_ptr<ReactiveProperty<int>, Deleter>
		(new ReactiveProperty<int>(), Deleter());
	mEraseLineCountRP->Subscribe
	(
	[&](int value)->void
	{
		std::wstringstream wos;
		wos << std::setw(8) << value;
		mEraseLineCountUIText->UpdateText(wos.str().c_str());
	}
	);

	//配列の初期化
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
			pieceCom->SetDebugFlg(false);
			pieces.push_back(pieceCom);
			counts.push_back(0);
		}
		mPieces.push_back(pieces);
		mDropCounts.push_back(counts);
	}
}

void FieldManager::UpdatePiece(int i, int j, PieceState state, PieceColor color)
{
	if (!IsWidthInTheFieldRange(i, j)) return;
	auto piece = mPieces[i][j];
	piece->SetPieceState(state);
	piece->SetPieceColor(color);
}

void FieldManager::CheckErase()
{
	mEraseLine.clear();
	auto eraseNum = 0;
	auto eraseJudgeNum = ROWNUM - 2;
	//列→行と見ていく
	for (int j = 1; j < COLUMNNUM - 3; j++)
	{
		eraseNum = 0;
		for (int i = 1; i < ROWNUM - 1; i++) 
		{
			//盤面に固定されているピースの数を数える
			if (mPieces[i][j]->GetPieceState() == FieldLock) 
			{
				eraseNum++;
			}
		}
		//固定されているピースが消去判定数以上であれば消去
		if(eraseNum >= eraseJudgeNum)
		{
			//消去した列を格納
			mEraseLine.push_back(j);
			for (int i = 1; i < ROWNUM - 1; i++)
			{
				mPieces[i][j]->SetPieceState(PieceState::Erase);
			}
		}
	}

	//消去していれば
	if (!mEraseLine.empty())
	{
		*mEraseLineCountRP + mEraseLine.size();
		if (mEraseLineCountRP->GetValue() / 10 == mLevelRP->GetValue())
		{
			if (mLevelRP->GetValue() < mMaxLevel) *mLevelRP + 1;
			mFreeFallFrame = mDefaultFreeFallFrame - (mLevelRP->GetValue() * (mDefaultFreeFallFrame / mMaxLevel));
			if (mFreeFallFrame <= 0) mFreeFallFrame = 1;
		}
		EraseEffect();
	}
	
}

void FieldManager::DropPiece()
{
	if (!mEraseLine.empty()) PieceDrop();
}

void FieldManager::ChangeDebugMode()
{
	if (mIsDebug)mIsDebug = false;
	else mIsDebug = true;
	for(auto pieces:mPieces)
	{
		for(auto piece:pieces)
		{
			piece->SetDebugFlg(mIsDebug);
		}
	}
}

void FieldManager::ChangePieceStateToSpace(PieceState state)
{
	for(auto pieces:mPieces)
	{
		for(auto piece:pieces)
		{
			if(piece->GetPieceState() == state)
			{
				piece->SetPieceState(Space);
			}
		}
	}
}

PieceState FieldManager::GetPieceState(int i, int j)
{
	if (IsWidthInTheFieldRange(i, j)) 
	{
		return mPieces[i][j]->GetPieceState();
	}
	else return Wall;
}

bool FieldManager::IsWidthInTheFieldRange(int i, int j)
{
	if(0 < i && i < ROWNUM - 1)
	{
		if (0 < j && j < COLUMNNUM) return true;
	}
	return false;
}

void FieldManager::EraseEffect()
{
	//消去したラインを照準に並び替え
	std::sort(mEraseLine.begin(), mEraseLine.end());
	//最初のラインを格納
	auto startLine = mEraseLine.front();
	//連続している段数
	auto linkLineCount = 1;
	auto linkLineCount2 = 1;
	//段飛びしているか
	auto isJumpLine = false;
	auto noLinkLine = 0;
	auto preLine = startLine;
	
	for (auto line : mEraseLine)
	{
		//ひとつ前の判定と同じ値なら無視
		if (preLine == line) continue;
		//ひとつ前の値と連続しているか
		if (preLine + 1 == line)
		{
			//段飛びしていれば
			if (isJumpLine)linkLineCount2++;
			else linkLineCount++;
		}
		else
		{
			isJumpLine = true;
			noLinkLine = line;
		}
		preLine = line;
	}
	auto lineEffect = mOneLineEffect->GetTransform();
	auto lineYPos = cBottomPos + cPieceHeightOffset * ((float)startLine + (float)linkLineCount / 4);
	lineEffect->Position = DirectX::XMFLOAT3(-1.7f, lineYPos, -0.1f);
	lineEffect->Scale = DirectX::XMFLOAT3(0.1f, 0.1f * linkLineCount, 1.0f);
	mOneLineEffect->SetEnable(true);
	if(isJumpLine)
	{
		auto lineYPos2 = cBottomPos + cPieceHeightOffset * ((float)noLinkLine + (float)linkLineCount2 / 4);
		auto lineEffect2 = mOneLineEffect2->GetTransform();
		lineEffect2->Position = DirectX::XMFLOAT3(-1.7f, lineYPos2, -0.1f);
		lineEffect2->Scale = DirectX::XMFLOAT3(0.1f, 0.1f * linkLineCount2, 1.0f);
		mOneLineEffect2->SetEnable(true);
	}
}

void FieldManager::PieceDrop()
{
	//落下する段数計算
	for (auto line : mEraseLine)
	{
		//消去した列の1列上から見ていく
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
	//落下
	for (int j = 1; j < COLUMNNUM; j++)
	{
		for (int i = 1; i < ROWNUM; i++)
		{
			if (mDropCounts[i][j] <= 0) continue;
			auto color = mPieces[i][j]->GetPieceColor();
			mPieces[i][j]->SetPieceState(Space);
			UpdatePiece(i, j - mDropCounts[i][j], FieldLock, color);
			mDropCounts[i][j] = 0;
		}
	}
}

void FieldManager::Start()
{
	//スペースを空ける
	for (int i = 1; i < ROWNUM - 1; i++)
	{
		for (int j = 1; j < COLUMNNUM; j++)
		{
			mPieces[i][j]->SetPieceState(Space);
		}
	}
	mLevelUI->SetEnable(true);
	mEraseLineCountUI->SetEnable(true);
	*mLevelRP = 1;
	*mEraseLineCountRP = 0;
	mFreeFallFrame = mDefaultFreeFallFrame;
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
