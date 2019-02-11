#include "stdafx.h"
#include "PlayScene.h"
#include <DirectXMath.h>
#include <sstream>
#include <random>

using namespace MyDirectX;

void PlayScene::Init()
{
	mFieldManager = std::make_unique<FieldManager>(this);
	mTetriMinoController = std::make_unique<TetriMinoController>(mDXRescourceManager,mFieldManager.get());
	CreateUIItem();
	//全てのオブジェクトの初期位置を設定する
	for(auto &game: mGameObjectsList)
	{
		game->SetDefaultTransform();
	}
}

void PlayScene::SceneStart()
{
	//全てのオブジェクトの初期化
	for(auto &game:mGameObjectsList)
	{
		game->InitializeComponent();
	}
	//最初からいるオブジェクトのアクティブ化
	for(auto game:mAwakeObject)
	{
		game->SetEnable(true);
	}
	mFieldManager->Start();
	mTetriMinoController->Start();
	mTetriMinoController->SetTetriMino(5, 20, I);
	//曲再生
	//mDXRescourceManager->GetBGMDXSound()->Play();
}

void PlayScene::SceneUpdate()
{
	mFrameCount++;
	//FPSを計算し出力する
	//毎フレーム出すと変化が激しすぎるので一定間隔で更新
	if (mFrameCount % FPS_CHEACK_FRAME_COUNT == 0)
	{
		*mFPSRP = mDXRescourceManager->GetFPS();
	}
	mTetriMinoController->PreUpdate();
	auto isPlaying = mTetriMinoController->Update();
	if(!isPlaying)
	{
		mFieldManager->LockPiece();
		auto type = static_cast<TetriMinoType>(GetRandRange(0, 6));
		mTetriMinoController->SetTetriMino(5, 20, type);
	}
	mFieldManager->CheckErase();
}

void PlayScene::SceneEnd()
{
	//mDXRescourceManager->SetScore((float)mScoreRP->GetValue());
	//全てのオブジェクトのアクティブを切る
	for (auto &game : mGameObjectsList)
	{
		game->SetEnable(false);
	}
	//アイテムのアクティブを切る
	for(auto &game :mGameObjectsList)
	{
		if(game->GetTag() == StaticInstantiateItem)
		{
			game->SetEnable(false);
		}
	}
	//動的生成アイテムがあれば削除
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end();)
	{
		if (itr->get()->GetTag() == DynamicInstantiateItem)
		{
			itr->reset();
			itr = mGameObjectsList.erase(itr);
			continue;
		}
		else ++itr;
	}
	//曲を止める
	//mDXRescourceManager->GetBGMDXSound()->Stop();
}

bool PlayScene::IsSceneEnd()
{
	if (mDXRescourceManager->GetKeyDown(DIK_RETURN)) return true;
	return false;
}

int PlayScene::GetRandRange(int min, int max)
{
	//シード値乱数生成器
	std::random_device rnd;
	//メルセンヌ・ツイスタ方を使って乱数を作る
	std::mt19937_64 mt64(rnd());
	//範囲内の離散分布を作る
	std::uniform_int_distribution<int> genRandInt(min, max);
	//分布の中から生成した乱数を使って1つだけ値を取り出す
	return genRandInt(mt64);
}

void PlayScene::CreateUIItem()
{
	//タイトル
	auto layout = Instantiate();
	auto tex = layout->AddComponent<DXTexture>();
	tex->SetTexture(_T("Texture/Layout.png"));
	auto transform = layout->GetTransform();
	transform->Scale = DirectX::XMFLOAT3(5.5f, 3.0f, 1.0f);
	mAwakeObject.push_back(layout);

	//タイトル
	auto field = Instantiate();
	auto tex2 = field->AddComponent<DXTexture>();
	tex2->SetTexture(_T("Texture/Field.png"));
	auto transform2 = field->GetTransform();
	transform2->Scale = DirectX::XMFLOAT3(1.1f, 2.1f, 1.0f);
	transform2->Position.x -= 1.35f;
	transform2->Position.y += 0.07f;
	transform2->Position.z += 0.01f;
	mAwakeObject.push_back(field);

	//FPS表示テキスト
	auto fps = Instantiate();
	mFPSText = fps->AddComponent<DXText>();
	auto transform3 = fps->GetTransform();
	//位置と大きさ
	transform3->Scale = DirectX::XMFLOAT3(0.07f, 0.07f, 1.0f);
	transform3->Position = DirectX::XMFLOAT3(1.2f, -0.8f, -1.1f);
	mAwakeObject.push_back(fps);

	//FPS表示に使う変数
	mFPSRP =
		std::unique_ptr<Property, Deleter>
		(new Property(), Deleter());

	//変数に変化があった時に表示する処理を登録
	mFPSRP->Subscribe
	(
	[&](double value)->void
	{
		mFrameCount = 0;
		//メンバ変数に持つと値が固定されてしまう・・・
		std::wstringstream ws;
		//有効桁数指定
		ws.precision(6);
		ws << value;
		mFPSText->UpdateText(ws.str().c_str());
		//中身をクリアする
		ws.clear();
	}
	);
}

