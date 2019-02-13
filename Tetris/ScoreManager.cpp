#include "stdafx.h"
#include "ScoreManager.h"
#include <sstream>
#include <iomanip>

using namespace MyDirectX;
ScoreManager::ScoreManager(Scene* scene)
{
	mScene = scene;
	mScoreTextObject = mScene->Instantiate();
	mScoreText = mScoreTextObject->AddComponent<DXText>();
	auto scoreTransform = mScoreTextObject->GetTransform();
	scoreTransform->Scale = DirectX::XMFLOAT3(0.07f, 0.07f, 1.0f);
	scoreTransform->Position = DirectX::XMFLOAT3(1.0f, -0.4f, -1.1f);

	mScoreTextObject2 = mScene->Instantiate();
	mScoreText2 = mScoreTextObject2->AddComponent<DXText>();
	auto scoreTransform2 = mScoreTextObject2->GetTransform();
	scoreTransform2->Scale = DirectX::XMFLOAT3(0.07f, 0.07f, 1.0f);
	scoreTransform2->Position = DirectX::XMFLOAT3(-1.2f, -0.7f, -1.1f);

	mScoreRP =
		std::unique_ptr<ReactiveProperty<int>, Deleter>
		(new ReactiveProperty<int>(), Deleter());

	mScoreRP->Subscribe
	(
	[&](int value)->void
	{
		std::wostringstream wos;
		//8Œ…‚Å‘«‚è‚È‚¢•ª‚Í0–„‚ß‚·‚é
		wos << std::setw(8) << std::setfill(_T('0')) << value;
		mScoreText->UpdateText(wos.str().c_str());
		mScoreText2->UpdateText(wos.str().c_str());
		wos.clear();
	}
	);
}

void ScoreManager::Start()
{
	mScoreTextObject->SetEnable(true);
	mScoreTextObject2->SetEnable(true);
	*mScoreRP = 0;
}
