#include "stdafx.h"
#include "LightMove.h"
#include "DXGameObject.h"

using namespace MyDirectX;

void LightMove::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	auto transform = mGameObject->GetTransform();
	mDefaultPos = transform->Position;
	mDefaultScale = transform->Scale;
}

void LightMove::Initialize()
{
	auto transform = mGameObject->GetTransform();
	transform->Position = mDefaultPos;
	transform->Scale = mDefaultScale;
	mIsEffectPlay = false;
}

void LightMove::OnEnable()
{
	mIsEffectPlay = true;
}

void LightMove::OnDisable()
{
	mIsEffectPlay = false;
	mFrameCount = 0;
	auto transform = mGameObject->GetTransform();
	transform->Position = mDefaultPos;
	transform->Scale = mDefaultScale;
}

void LightMove::Update()
{
	if (!mIsEffectPlay) return;
	mFrameCount++;
	auto transform = mGameObject->GetTransform();
	auto move = 0.1f;
	auto scaleXUp = 0.01f;
	auto scaleYUp = 0.01f;
	if(mFrameCount > mEffectEndFrame / 2)
	{
		move = 0.05f;
		scaleXUp = 0.2f;
		scaleYUp = 0.1f;
	}
	transform->Position.x += move;
	transform->Scale.x += scaleXUp;
	transform->Scale.y += scaleYUp;
	if (mFrameCount >= mEffectEndFrame) mGameObject->SetEnable(false);
}
