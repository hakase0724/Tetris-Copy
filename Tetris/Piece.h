#pragma once
#include "Component.h"
#include "MyEnums.h"
#include "DXTexture.h"
#include "DXText.h"

namespace MyDirectX
{
	class Piece :public Component
	{
	public:
		Piece() {};
		~Piece() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		void SetPieceState(PieceState state);
		void SetPieceColor(PieceColor color);
		void SetDebugFlg(bool flg);
		PieceState GetPieceState() { return mState; }
		PieceColor GetPieceColor() { return mColor; }
	private:
		DXGameObject* mDebugTextObject;
		DXText* mDebugText;
		DXTexture* mTexture;
		TextureRenderer* mRenderer;
		PieceState mState;
		PieceColor mColor;
		COLOR mRenderingColor;
		//各色のテクスチャパス
		std::wstring mRedTexturePath;
		std::wstring mBlueTexturePath;
		std::wstring mYellowTexturePath;
		std::wstring mGreenTexturePath;
		std::wstring mOrangeTexturePath;
		std::wstring mPurpleTexturePath;
		std::wstring mLightBlueTexturePath;
		std::wstring mPieceColorPath;
		std::wstring mEraseColorPath;
		bool mIsDebug = true;
	};
}


