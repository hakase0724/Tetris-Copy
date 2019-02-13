#include "stdafx.h"
#include "Piece.h"
#include "Scene.h"
using namespace MyDirectX;
void Piece::Initialize(DXGameObject* gameObject)
{
	mGameObject = gameObject;
	mRedTexturePath = _T("Texture/Red.png");
	mBlueTexturePath = _T("Texture/Blue.png");
	mYellowTexturePath = _T("Texture/Yellow.png");
	mOrangeTexturePath = _T("Texture/Orange.png");
	mGreenTexturePath = _T("Texture/Green.png");
	mPurpleTexturePath = _T("Texture/Purple.png");
	mLightBlueTexturePath = _T("Texture/LightBlue.png");

	mDebugTextObject = mGameObject->GetScene()->Instantiate();
	auto debugTransform = mDebugTextObject->GetTransform();
	auto transform = mGameObject->GetTransform();
	debugTransform->Position = transform->Position;
	debugTransform->Scale = transform->Scale;
	debugTransform->Position.z -= 0.01f;
	mDebugText = mDebugTextObject->AddComponent<DXText>();
}
void Piece::Initialize()
{
	mState = Wall;
	if (mIsDebug) mDebugTextObject->SetEnable(true);
	if (mTexture == nullptr) mTexture = mGameObject->GetComponent<DXTexture>();
	if (mRenderer == nullptr) mRenderer = mGameObject->GetComponent<TextureRenderer>();
}
void Piece::SetPieceState(PieceState state)
{
	mState = state;
	mRenderer->SetAlphaBlendingFlg(false);
	mRenderingColor.a = 1.0f;
	switch (mState)
	{
	case Space:
		mGameObject->SetEnable(false);
		mRenderer->SetEnable(false);
		if (mIsDebug) 
		{
			mDebugText->UpdateText(_T("S"));
		}
		break;
	case PlayerControll:
		mGameObject->SetEnable(true);
		mRenderer->SetEnable(true);
		if (mIsDebug)
		{
			mDebugText->UpdateText(_T("P"));
		}
		break;
	case FieldLock:
		mGameObject->SetEnable(true);
		mRenderer->SetEnable(true);
		if (mIsDebug)
		{
			mDebugText->UpdateText(_T("F"));
		}
		break;
	case Wall:
		mGameObject->SetEnable(true);
		mRenderer->SetEnable(true);
		if (mIsDebug)
		{
			mDebugText->UpdateText(_T("W"));
		}
		break;
	case Ghost:
		mGameObject->SetEnable(true);
		mRenderer->SetEnable(true);
		mRenderer->SetAlphaBlendingFlg(true);
		mRenderingColor.a = 0.5f;
		mRenderer->SetColor(mRenderingColor);
		if (mIsDebug)
		{
			mDebugText->UpdateText(_T("G"));
		}
		break;
	default:
		break;
	}
}
void Piece::SetPieceColor(PieceColor color)
{
	mColor = color;
	switch (mColor)
	{
	case Red:
		mPieceColorPath = mRedTexturePath;
		break;
	case Blue:
		mPieceColorPath = mBlueTexturePath;
		break;
	case Yellow:
		mPieceColorPath = mYellowTexturePath;
		break;
	case Orange:
		mPieceColorPath = mOrangeTexturePath;
		break;
	case Purple:
		mPieceColorPath = mPurpleTexturePath;
		break;
	case Green:
		mPieceColorPath = mGreenTexturePath;
		break;
	case LightBlue:
		mPieceColorPath = mLightBlueTexturePath;
		break;
	default:
		break;
	}
	mTexture->SetTexture(mPieceColorPath.c_str());
}
void Piece::SetDebugFlg(bool flg)
{
	mIsDebug = flg;
	if (mIsDebug) mDebugTextObject->SetEnable(true);
	else mDebugTextObject->SetEnable(false);
}
void Piece::Erase() 
{
	SetPieceState(Space);
};