#include "stdafx.h"
#include "TetriMinoController.h"

using namespace MyDirectX;
TetriMinoController::TetriMinoController(DXResourceManager* manager,FieldManager* fieldManager,Scene* scene)
{
	mManager = manager;
	mScene = scene;
	mTetriMino = std::make_unique<TetriMino>(fieldManager);
	mMove = std::make_unique<TetriMinoMove>(mManager,mTetriMino.get(),fieldManager);
	mRotation = std::make_unique<TetriMinoRotation>(mManager, mTetriMino.get());
	mHold = std::make_unique<TetriMinoHold>(mManager, mTetriMino.get(),mScene);
}

void TetriMinoController::Start()
{
	mMove->Start();
	mTetriMino->Start();
	mHold->Start();
	mRotation->Start();
}

void TetriMinoController::SetTetriMino(int i, int j, TetriMinoType type)
{
	mTetriMino->SetPlayerTetriMino(i, j, type);
	mMove->Start();
}

void TetriMinoController::PreUpdate()
{
	mTetriMino->TetriMinoPreUpdate();
}

bool TetriMinoController::Update()
{
	//次のテトリミノを出すなら
	if (mTetriMino->GetIsNext())
	{
		//位置を確定し表示
		mTetriMino->TetriMinoUpdate();
		mHold->UnlockHold();
		//以後の処理をしない
		return false;
	}
	//移動
	mMove->Update();
	//回転
	mRotation->Update();
	//ホールド
	mHold->Update();
	if (mHold->IsFirstHold()) return false;
	//位置を確定し表示
	mTetriMino->TetriMinoUpdate();
	return true;
}

int TetriMinoController::GetMoveScore()
{
	return mMove->GetMoveScore();
}
