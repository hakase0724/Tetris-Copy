#include "stdafx.h"
#include "Piece.h"

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
}
void Piece::Initialize()
{
	mState = Wall;
	if (mTexture == nullptr) mTexture = mGameObject->GetComponent<DXTexture>();
	if (mRenderer == nullptr) mRenderer = mGameObject->GetComponent<TextureRenderer>();
}
void Piece::SetPieceState(PieceState state)
{
	mState = state;
	switch (mState)
	{
	case Space:
		mGameObject->SetEnable(false);
		mRenderer->SetEnable(false);
		break;
	case PlayerControll:
		mGameObject->SetEnable(true);
		mRenderer->SetEnable(true);
		break;
	case FieldLock:
		mGameObject->SetEnable(true);
		mRenderer->SetEnable(true);
		break;
	case Wall:
		mGameObject->SetEnable(true);
		mRenderer->SetEnable(true);
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
void Piece::Erase() 
{
	SetPieceState(Space);
};