#include "stdafx.h"
#include "TitleScene.h"
#include "DXText.h"
#include "DXTexture.h"
#include "LightMove.h"

using namespace MyDirectX;

void TitleScene::Init()
{
	line = Instantiate();
	auto lightTex = line->AddComponent<DXTexture>();
	lightTex->SetTexture(_T("Texture/Light.png"));
	line->GetTransform()->Position.z -= 0.1f;
	line->AddComponent<LightMove>();
	auto renderer = line->GetComponent<TextureRenderer>();
	renderer->SetAlphaBlendingFlg(true);

	//タイトル
	auto title = Instantiate();
	auto tex = title->AddComponent<DXTexture>();
	tex->SetTexture(_T("Texture/Title.png"));
	auto transform = title->GetTransform();
	transform->Scale = DirectX::XMFLOAT3(5.5f, 4.0f, 1.0f);
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

void MyDirectX::TitleScene::SceneUpdate()
{
	if(mDXRescourceManager->GetKeyDown(DIK_NUMPAD1))
	{
		line->SetEnable(true);
	}
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
