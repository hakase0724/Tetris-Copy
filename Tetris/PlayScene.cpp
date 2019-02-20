#include "stdafx.h"
#include "PlayScene.h"
#include <DirectXMath.h>
#include <sstream>
#include <random>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "LightMove.h"

using namespace MyDirectX;

void PlayScene::Init()
{
	//UI要素を作る
	CreateUIItem();
	//盤面管理
	mFieldManager = std::make_unique<FieldManager>(this);
	//スコア管理
	mScoreManager = std::make_unique<ScoreManager>(this);
	//ネクスト表示
	mNext = std::make_unique<TetriMinoNext>(this);
	//テトリミノ操作
	mTetriMinoController = std::make_unique<TetriMinoController>(mDXRescourceManager,mFieldManager.get(),this);
	
	
	//全てのオブジェクトの初期位置を設定する
	for(auto &game: mGameObjectsList)
	{
		game->SetDefaultTransform();
	}
	//プレイシーンのBGM取得
	mBGM = mDXRescourceManager->GetSoundManager()->GetBGMSound(_T("Sound/BGM/TetrisTheme.wav"));
	//音量下げる
	mBGM->SetVolume(-1000);
	//消去時の音
	mDeleteSound = mDXRescourceManager->GetSoundManager()->GetSESound(_T("Sound/SE/Delete.wav"));
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
	//各種初期化
	mFieldManager->Start();
	mScoreManager->Start();
	mNext->Start();
	mTetriMinoController->Start();
	//最初のテトリミノを出す
	mTetriMinoController->SetTetriMino(5, 20, mNext->GetNextTetriMino());
	//曲再生
	mBGM->Play();
}

void PlayScene::SceneUpdate()
{
	mFrameCount++;
#if _DEBUG
	//FPSを計算し出力する
	//毎フレーム出すと変化が激しすぎるので一定間隔で更新
	if (mFrameCount % FPS_CHEACK_FRAME_COUNT == 0)
	{
		*mFPSRP = mDXRescourceManager->GetFPS();
	}
	if(mDXRescourceManager->GetKeyDown(DIK_NUMPAD0))
	{
		mFieldManager->ChangeDebugMode();
	}
#endif
	auto isPlaying = true;
	switch (mState)
	{
	//テトリミノを操作している時
	case Play:
		mTetriMinoController->PreUpdate();
		isPlaying = mTetriMinoController->Update();
		//移動のスコアを加算する
		mScoreManager->AddScore(mTetriMinoController->GetMoveScore());
		if (!isPlaying) 
		{
			//ピースを盤面に固定
			mFieldManager->LockPiece();
			//Tスピン判定
			auto isTspin = mTetriMinoController->GetIsTspin();
			//Tスピンミニ判定
			auto isTspinMini = mTetriMinoController->GetIsTspinMini();
			//Tスピン成功UIの表示切替
			if (isTspinMini)mTspinMiniUI->SetEnable(true);
			else if (isTspin) mTspinUI->SetEnable(true);
			else
			{
				mTspinMiniUI->SetEnable(false);
				mTspinUI->SetEnable(false);
			}
			//消去
			mFieldManager->CheckErase();
			//消したライン数
			auto eraseLine = mFieldManager->GetEraseLineCount();
			//消していなければ以後の処理をしない
			if (eraseLine <= 0) 
			{
				mState = Next;
				break;
			}
			//現在のレベル
			auto level = mFieldManager->GetLevel();
			//消去した時のスコアを加算
			mScoreManager->AddScore(eraseLine, level, isTspin, isTspinMini);
			mDeleteSound->ResetSound();
			mDeleteSound->Play(false);
			mWaitStartFrame = mFrameCount;
			mState = Wait;
		}
		break;
	//消去後の待ち
	case Wait:
		//フレームで待機
		if((mFrameCount - mWaitStartFrame) % cWaitFrame == 0)
		{
			mState = Next;
			mFieldManager->ChangePieceStateToSpace(PieceState::Erase);
			mFieldManager->DropPiece();
		}
		break;
	//次へ
	case Next:
		//次のテトリミノを出す
		mTetriMinoController->SetTetriMino(5, 20, mNext->GetNextTetriMino());
		mState = Play;
		break;
	default:
		break;
	}
}

void PlayScene::SceneEnd()
{
	//全てのオブジェクトのアクティブを切る
	for (auto &game : mGameObjectsList)
	{
		game->SetEnable(false);
	}
	//曲を止める
	mBGM->Stop();
}

bool PlayScene::IsSceneEnd()
{
	if (mTetriMinoController->IsGameOver()) return true;
	return false;
}

void PlayScene::CreateUIItem()
{
	//プレイシーン大枠
	auto layout = Instantiate();
	auto tex = layout->AddComponent<DXTexture>();
	tex->SetTexture(_T("Texture/Layout.png"));
	auto transform = layout->GetTransform();
	transform->Scale = DirectX::XMFLOAT3(5.5f, 3.0f, 1.0f);
	mAwakeObject.push_back(layout);

	//プレイシーンの盤面
	auto field = Instantiate();
	auto tex2 = field->AddComponent<DXTexture>();
	tex2->SetTexture(_T("Texture/Field.png"));
	auto transform2 = field->GetTransform();
	transform2->Scale = DirectX::XMFLOAT3(1.1f, 2.1f, 1.0f);
	transform2->Position.x -= 1.35f;
	transform2->Position.y += 0.07f;
	transform2->Position.z += 0.01f;
	mAwakeObject.push_back(field);

	//Tスピンしたとき表示するUI
	mTspinUI = Instantiate();
	auto tspinText = mTspinUI->AddComponent<DXText>();
	auto tspinTransform = mTspinUI->GetTransform();
	tspinTransform->Scale = DirectX::XMFLOAT3(0.07f,0.07f,1.0f);
	tspinTransform->Position = DirectX::XMFLOAT3(-1.7f, -0.7f, -1.1f);
	tspinText->UpdateText(_T("TSpin"));
	//Tスピンミニしたとき表示するUI
	mTspinMiniUI = Instantiate();
	auto tspinMiniText = mTspinMiniUI->AddComponent<DXText>();
	auto tspinMiniTransform = mTspinMiniUI->GetTransform();
	tspinMiniTransform->Scale = DirectX::XMFLOAT3(0.07f, 0.07f, 1.0f);
	tspinMiniTransform->Position = DirectX::XMFLOAT3(-1.7f, -0.7f, -1.1f);
	tspinMiniText->UpdateText(_T("TSpinMini"));

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

