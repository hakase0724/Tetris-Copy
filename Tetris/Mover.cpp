#include "stdafx.h"
#include "Mover.h"
#include <sstream>
using namespace MyDirectX;

void Mover::Initialize(DXGameObject * gameObject)
{
	mDXInput = gameObject->GetDXInput();
	mGameObject = gameObject;
}

void Mover::Update()
{
	auto transform = mGameObject->GetTransform();
	//移動前の座標保持
	auto prePos = transform->Position;
	//入力を受けて移動
	if (mDXInput->GetKeyDown(DIK_LEFTARROW)) transform->Position.x -= mMoveSpeed;
	if (mDXInput->GetKeyDown(DIK_RIGHTARROW)) transform->Position.x += mMoveSpeed;
	if (mDXInput->GetKeyDown(DIK_UPARROW)) transform->Position.y += mMoveSpeed;
	if (mDXInput->GetKeyDown(DIK_DOWNARROW)) transform->Position.y -= mMoveSpeed;
}