#include "stdafx.h"
#include "DXExcuter.h"
#include "FuctionCountTimer.h"

using namespace MyDirectX;
DXExcuter::DXExcuter()
{
	//シーンの登録を解除する
	mScene = nullptr;
}

void DXExcuter::SetScene(Scene * scene)
{
	//シーンが登録されていたらシーンの終了メソッドを呼び出す
	if (mScene != nullptr) mScene->SceneEnd();
	//シーンを登録する
	mScene = scene;
	//登録シーンの開始メソッドを呼ぶ
	mScene->SceneStart();
	//実行ゲームオブジェクト管理配列にシーン上のゲームオブジェクトを追加する
	mExcuteObjectsList = mScene->GetGameObjects();
}

void DXExcuter::Excute()
{
	//シーンが登録されて無ければ処理しない
	if (!mScene) return;
	//auto timer = new FuctionCountTimer();
	/*毎フレームの処理を行う*/
	//シーンの更新処理
	mScene->SceneUpdate();
	//ゲームオブジェクトの更新処理
	Update();
	//全ての更新処理が終わった後の更新処理
	mScene->SceneLateUpdate();
	//ゲームオブジェクトの後更新処理
	LateUpdate();
	//描画処理
	Render();
	//1フレーム終了時の処理
	mScene->SceneEndFrame();
	//delete timer;
}

void DXExcuter::Update()
{
	for(auto &game:*mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->Update();
	}
}

void DXExcuter::LateUpdate()
{
	for (auto &game : *mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->LateUpdate();
	}
}

void DXExcuter::Render()
{
	mDXRescourceManager->GetDXManager()->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);
	//深度バッファ状態を設定
	auto depth = mDXRescourceManager->GetDXManager()->GetDepthStencilState();
	mDXRescourceManager->GetDXManager()->GetDeviceContext()->OMSetDepthStencilState(depth, 0);
	for (auto &game : *mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->Render();
	}
	mDXRescourceManager->GetDXManager()->EndScene();
}
