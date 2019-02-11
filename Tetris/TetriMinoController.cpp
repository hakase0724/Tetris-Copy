#include "stdafx.h"
#include "TetriMinoController.h"

using namespace MyDirectX;
TetriMinoController::TetriMinoController(DXResourceManager* manager,FieldManager* fieldManager)
{
	mManager = manager;
	mTetriMino = std::make_unique<TetriMino>(fieldManager);
	mMove = std::make_unique<TetriMinoMove>(mManager,mTetriMino.get());
	mRotation = std::make_unique<TetriMinoRotation>(mManager, mTetriMino.get());
	mHold = std::make_unique<TetriMinoHold>(mManager, mTetriMino.get());
}

void TetriMinoController::Start()
{
	mMove->Start();
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
	if (mTetriMino->GetIsNext()) return false;
	mMove->Update();
	mRotation->Update();
	mHold->Update();
	mTetriMino->TetriMinoUpdate();
	return true;
}
