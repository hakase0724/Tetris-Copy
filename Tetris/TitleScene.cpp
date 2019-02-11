#include "stdafx.h"
#include "TitleScene.h"
#include "DXText.h"
#include "DXTexture.h"

using namespace DirectX;
using namespace MyDirectX;

void TitleScene::Init()
{
	//タイトル
	auto title = Instantiate();
	auto tex = title->AddComponent<DXTexture>();
	tex->SetTexture(_T("Texture/Title.png"));
	auto transform = title->GetTransform();
	transform->Scale = XMFLOAT3(5.5f, 4.0f, 3.5f);
	transform->Position.y += 0.3f;
	auto texRenderer = title->GetComponent<TextureRenderer>();
	texRenderer->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	title->SetEnable(true);

	////説明テキスト
	//auto titleMessage = Instantiate();
	//auto message = titleMessage->AddComponent<DXText>();
	//auto transform2 = titleMessage->GetTransform();
	//transform2->Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	//transform2->Position.x -= 1.1f;
	//transform2->Position.y -= 0.5f;
	//transform2->Position.z -= 0.1f;
	//message->UpdateText(L"PRESS ENTER: GAME START");
	//titleMessage->SetEnable(true);
}

bool TitleScene::IsSceneEnd()
{
	//エンター押されたら
	if (mDXRescourceManager->GetKeyDown(DIK_RETURN))return true;
	return false;
}
