#pragma once
#include "Component.h"
namespace MyDirectX
{
	class LightMove :public Component
	{
	public:
		LightMove() {};
		~LightMove() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		virtual void OnEnable() override;
		virtual void OnDisable() override;
		virtual void Update() override;
	private:
		DirectX::XMFLOAT3 mDefaultPos;
		DirectX::XMFLOAT3 mDefaultScale;
		int mFrameCount = 0;
		int mEffectEndFrame = 10;
		bool mIsEffectPlay = false;
	};
}


