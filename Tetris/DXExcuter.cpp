#include "stdafx.h"
#include "DXExcuter.h"
#include "FuctionCountTimer.h"
#include <thread>

using namespace MyDirectX;
DXExcuter::DXExcuter()
{
	//シーンの登録を解除する
	mScene = nullptr;
}

void DXExcuter::SetScene(Scene * scene)
{
	auto isThread = false;
	std::thread preSceneThread;
	//シーンが登録されていたらシーンの終了メソッドを呼び出す
	if (mScene != nullptr) 
	{
		auto preScene = mScene;
		isThread = true;
		preSceneThread = std::thread([&] 
		{
			preScene->SceneEnd();
		});
	}
	//シーンの開始メソッドを呼ぶ
	scene->SceneStart();
	//実行ゲームオブジェクト管理配列にシーン上のゲームオブジェクトを追加する
	mExcuteObjectsList = scene->GetGameObjects();
	//前のシーンの終了メソッドの完了を待つ
	if (isThread) preSceneThread.join();
	//シーンを登録する
	mScene = scene;
}

void DXExcuter::Excute()
{
	//シーンが登録されて無ければ処理しない
	if (!mScene) return;
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
