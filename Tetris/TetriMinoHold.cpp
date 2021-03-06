#include "stdafx.h"
#include "TetriMinoHold.h"
#include "Scene.h"

using namespace MyDirectX;

TetriMinoHold::TetriMinoHold(DXResourceManager * manager, TetriMino * tetrimino, Scene* scene)
{
	mManager = manager;
	mTetriMino = tetrimino;
	mScene = scene;

	auto ui = mScene->Instantiate();
	auto uiTransform = ui->GetTransform();
	uiTransform->Position = DirectX::XMFLOAT3(-2.06f, 0.85f, -0.01f);
	uiTransform->Scale = DirectX::XMFLOAT3(0.3f,0.3f,1.0f);
	mHoldUI = ui->AddComponent<TetriMinoUI>();

	mHoldSE = mManager->GetSoundManager()->GetSESound(_T("Sound/SE/Hold.wav"));
}

void TetriMinoHold::Start()
{
	mHoldUI->SetEnable(true);
	mIsLockHold = false;
	mIsHold = false;
	mIsFirstHold = false;
}

void TetriMinoHold::Update()
{
	mIsFirstHold = false;
	if(mManager->GetKeyDown(DIK_SPACE))
	{
		Hold();
		mIsHold = true;
	}
}

void TetriMinoHold::Hold()
{
	//ロックされていたら
	if (mIsLockHold) return;
	mTetriMino->ChangePieceStateToSpace();
	if(mIsHold)
	{
		auto type = mTetriMino->GetTetriMinoType();
		mTetriMino->SetPlayerTetriMino(5, 20, mHoldType);
		mHoldType = type;
	}
	else
	{
		mHoldType = mTetriMino->GetTetriMinoType();
		mIsFirstHold = true;
	}
	mHoldUI->SetTetriMinoType(mHoldType);
	mIsLockHold = true;
	mHoldSE->ResetSound();
	mHoldSE->Play(false);
}
