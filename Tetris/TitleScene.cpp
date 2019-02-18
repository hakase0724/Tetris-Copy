#include "stdafx.h"
#include "TitleScene.h"
#include "DXText.h"
#include "DXTexture.h"
#include "LightMove.h"

using namespace DirectX;
using namespace MyDirectX;

void TitleScene::Init()
{
	//タイトル
	auto title = Instantiate();
	auto tex = title->AddComponent<DXTexture>();
	tex->SetTexture(_T("Texture/Title.png"));
	auto transform = title->GetTransform();
	transform->Scale = XMFLOAT3(5.5f, 4.0f, 1.0f);
	transform->Position = DirectX::XMFLOAT3(0.0f,0.3f,0.0f);
	auto texRenderer = title->GetComponent<TextureRenderer>();
	texRenderer->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	title->SetEnable(true);
	//タイトルBGM取得
	mBGM = mDXRescourceManager->GetSoundManager()->GetBGMSound(_T("Sound/BGM/Title.wav"));
	//音量下げる
	mBGM->SetVolume(-1000);
}

void TitleScene::SceneStart()
{
	mBGM->Play();
}

bool TitleScene::IsSceneEnd()
{
	//エンター押されたら
	if (mDXRescourceManager->GetKeyDown(DIK_RETURN)) 
	{
		mBGM->Stop();
		return true;
	}
	return false;
}
