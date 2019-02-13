#pragma once
#include "IComponent.h"
#include "MyEnums.h"
#include "DXTexture.h"

namespace MyDirectX 
{
	class TetriMinoUI :public Component
	{
	public:
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		TetriMinoType GetTetriMinoType() { return mType; }
		void SetTetriMinoType(TetriMinoType type);
		void SetEnable(bool enable) { mGameObject->SetEnable(enable); }
	private:
		DXTexture* mTexture;
		TetriMinoType mType;
		//各色のテクスチャパス
		std::wstring mITexturePath;
		std::wstring mOTexturePath;
		std::wstring mTTexturePath;
		std::wstring mJTexturePath;
		std::wstring mLTexturePath;
		std::wstring mSTexturePath;
		std::wstring mZTexturePath;
		std::wstring mTetriMinoPath;
	};
}


