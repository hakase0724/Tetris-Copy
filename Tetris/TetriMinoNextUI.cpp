#include "stdafx.h"
#include "TetriMinoNextUI.h"

using namespace MyDirectX;

void TetriMinoUI::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mTexture = mGameObject->AddComponent<DXTexture>();
	mITexturePath = _T("Texture/ITetriMino.png");
	mOTexturePath = _T("Texture/OTetriMino.png");
	mTTexturePath = _T("Texture/TTetriMino.png");
	mJTexturePath = _T("Texture/JTetriMino.png");
	mLTexturePath = _T("Texture/LTetriMino.png");
	mSTexturePath = _T("Texture/STetriMino.png");
	mZTexturePath = _T("Texture/ZTetriMino.png");
}

void TetriMinoUI::Initialize()
{
	if (mTexture == nullptr) mGameObject->GetComponent<DXTexture>();
	mTexture->SetTexture(_T(""));
}

void TetriMinoUI::SetTetriMinoType(TetriMinoType type)
{
	mType = type;
	switch (mType)
	{
	case I:
		mTexture->SetTexture(mITexturePath.c_str());
		break;
	case O:
		mTexture->SetTexture(mOTexturePath.c_str());
		break;
	case T:
		mTexture->SetTexture(mTTexturePath.c_str());
		break;
	case J:
		mTexture->SetTexture(mJTexturePath.c_str());
		break;
	case L:
		mTexture->SetTexture(mLTexturePath.c_str());
		break;
	case S:
		mTexture->SetTexture(mSTexturePath.c_str());
		break;
	case Z:
		mTexture->SetTexture(mZTexturePath.c_str());
		break;
	default:
		break;
	}
}
