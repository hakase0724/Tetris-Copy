#pragma once
#include "IComponent.h"
#include "MyEnums.h"
#include "DXTexture.h"
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
		PieceState GetPieceState() { return mState; }
		PieceColor GetPieceColor() { return mColor; }
		void Erase();
	private:
		DXTexture* mTexture;
		TextureRenderer* mRenderer;
		PieceState mState;
		PieceColor mColor;
		//�e�F�̃e�N�X�`���p�X
		std::wstring mRedTexturePath;
		std::wstring mBlueTexturePath;
		std::wstring mYellowTexturePath;
		std::wstring mGreenTexturePath;
		std::wstring mOrangeTexturePath;
		std::wstring mPurpleTexturePath;
		std::wstring mLightBlueTexturePath;
		std::wstring mPieceColorPath;
	};
}


