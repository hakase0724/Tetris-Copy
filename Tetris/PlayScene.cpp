#include "stdafx.h"
#include "PlayScene.h"
#include <DirectXMath.h>
#include <sstream>
#include <random>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace MyDirectX;

void PlayScene::Init()
{
	mFieldManager = std::make_unique<FieldManager>(this);
	mScoreManager = std::make_unique<ScoreManager>(this);
	mNext = std::make_unique<TetriMinoNext>(this);
	mTetriMinoController = std::make_unique<TetriMinoController>(mDXRescourceManager,mFieldManager.get(),this);
	CreateUIItem();
	//�S�ẴI�u�W�F�N�g�̏����ʒu��ݒ肷��
	for(auto &game: mGameObjectsList)
	{
		game->SetDefaultTransform();
	}
}

void PlayScene::SceneStart()
{
	//�S�ẴI�u�W�F�N�g�̏�����
	for(auto &game:mGameObjectsList)
	{
		game->InitializeComponent();
	}
	//�ŏ����炢��I�u�W�F�N�g�̃A�N�e�B�u��
	for(auto game:mAwakeObject)
	{
		game->SetEnable(true);
	}
	mFieldManager->Start();
	mScoreManager->Start();
	mNext->Start();
	mTetriMinoController->Start();
	mTetriMinoController->SetTetriMino(5, 20, mNext->GetNextTetriMino());
	//�ȍĐ�
	//mDXRescourceManager->GetBGMDXSound()->Play();
}

void PlayScene::SceneUpdate()
{
	mFrameCount++;
	//FPS���v�Z���o�͂���
	//���t���[���o���ƕω�������������̂ň��Ԋu�ōX�V
	if (mFrameCount % FPS_CHEACK_FRAME_COUNT == 0)
	{
		*mFPSRP = mDXRescourceManager->GetFPS();
	}
#if _DEBUG
	if(mDXRescourceManager->GetKeyDown(DIK_NUMPAD0))
	{
		mFieldManager->ChangeDebugMode();
	}
#endif
	mTetriMinoController->PreUpdate();
	auto isPlaying = mTetriMinoController->Update();
	//�ړ��̃X�R�A�����Z����
	mScoreManager->AddScore(mTetriMinoController->GetMoveScore());
	//���̃e�g���~�m���o���Ȃ�
	if(!isPlaying)
	{		
		//�s�[�X��ՖʂɌŒ�
		mFieldManager->LockPiece();
		//T�X�s������
		auto isTspin = mTetriMinoController->GetIsTspin();
		//T�X�s���~�j����
		auto isTspinMini = mTetriMinoController->GetIsTspinMini();
		//T�X�s������UI�̕\���ؑ�
		if (isTspinMini)mTspinMiniUI->SetEnable(true);
		else if (isTspin) mTspinUI->SetEnable(true);
		else 
		{
			mTspinMiniUI->SetEnable(false);
			mTspinUI->SetEnable(false);
		}
		//����
		mFieldManager->CheckErase();
		//���������C����
		auto eraseLine = mFieldManager->GetEraseLineCount();
		//���݂̃��x��
		auto level = mFieldManager->GetLevel();
		
		//�����������̃X�R�A�����Z
		mScoreManager->AddScore(eraseLine, level, isTspin, isTspinMini);
		//���̃e�g���~�m���o��
		mTetriMinoController->SetTetriMino(5, 20, mNext->GetNextTetriMino());
	}	
	
}

void PlayScene::SceneEnd()
{
	//mDXRescourceManager->SetScore((float)mScoreRP->GetValue());
	//�S�ẴI�u�W�F�N�g�̃A�N�e�B�u��؂�
	for (auto &game : mGameObjectsList)
	{
		game->SetEnable(false);
	}
	//�A�C�e���̃A�N�e�B�u��؂�
	for(auto &game :mGameObjectsList)
	{
		if(game->GetTag() == StaticInstantiateItem)
		{
			game->SetEnable(false);
		}
	}
	//���I�����A�C�e��������΍폜
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
	//�Ȃ��~�߂�
	//mDXRescourceManager->GetBGMDXSound()->Stop();
}

bool PlayScene::IsSceneEnd()
{
	if (mTetriMinoController->IsGameOver()) return true;
	//if (mDXRescourceManager->GetKeyDown(DIK_RETURN)) return true;
	return false;
}

int PlayScene::GetRandRange(int min, int max)
{
	//�V�[�h�l����������
	std::random_device rnd;
	//�����Z���k�E�c�C�X�^�����g���ė��������
	std::mt19937_64 mt64(rnd());
	//�͈͓��̗��U���z�����
	std::uniform_int_distribution<int> genRandInt(min, max);
	//���z�̒����琶�������������g����1�����l�����o��
	return genRandInt(mt64);
}

void PlayScene::CreateUIItem()
{
	//�^�C�g��
	auto layout = Instantiate();
	auto tex = layout->AddComponent<DXTexture>();
	tex->SetTexture(_T("Texture/Layout.png"));
	auto transform = layout->GetTransform();
	transform->Scale = DirectX::XMFLOAT3(5.5f, 3.0f, 1.0f);
	mAwakeObject.push_back(layout);

	//�^�C�g��
	auto field = Instantiate();
	auto tex2 = field->AddComponent<DXTexture>();
	tex2->SetTexture(_T("Texture/Field.png"));
	auto transform2 = field->GetTransform();
	transform2->Scale = DirectX::XMFLOAT3(1.1f, 2.1f, 1.0f);
	transform2->Position.x -= 1.35f;
	transform2->Position.y += 0.07f;
	transform2->Position.z += 0.01f;
	mAwakeObject.push_back(field);

	mTspinUI = Instantiate();
	auto tspinText = mTspinUI->AddComponent<DXText>();
	auto tspinTransform = mTspinUI->GetTransform();
	tspinTransform->Scale = DirectX::XMFLOAT3(0.07f,0.07f,1.0f);
	tspinTransform->Position = DirectX::XMFLOAT3(-1.7f, -0.7f, -1.1f);
	tspinText->UpdateText(_T("TSpin"));

	mTspinMiniUI = Instantiate();
	auto tspinMiniText = mTspinMiniUI->AddComponent<DXText>();
	auto tspinMiniTransform = mTspinMiniUI->GetTransform();
	tspinMiniTransform->Scale = DirectX::XMFLOAT3(0.07f, 0.07f, 1.0f);
	tspinMiniTransform->Position = DirectX::XMFLOAT3(-1.7f, -0.7f, -1.1f);
	tspinMiniText->UpdateText(_T("TSpinMini"));

	//FPS�\���e�L�X�g
	auto fps = Instantiate();
	mFPSText = fps->AddComponent<DXText>();
	auto transform3 = fps->GetTransform();
	//�ʒu�Ƒ傫��
	transform3->Scale = DirectX::XMFLOAT3(0.07f, 0.07f, 1.0f);
	transform3->Position = DirectX::XMFLOAT3(1.2f, -0.8f, -1.1f);
	mAwakeObject.push_back(fps);

	//FPS�\���Ɏg���ϐ�
	mFPSRP =
		std::unique_ptr<Property, Deleter>
		(new Property(), Deleter());

	//�ϐ��ɕω������������ɕ\�����鏈����o�^
	mFPSRP->Subscribe
	(
	[&](double value)->void
	{
		mFrameCount = 0;
		//�����o�ϐ��Ɏ��ƒl���Œ肳��Ă��܂��E�E�E
		std::wstringstream ws;
		//�L�������w��
		ws.precision(6);
		ws << value;
		mFPSText->UpdateText(ws.str().c_str());
		//���g���N���A����
		ws.clear();
	}
	);
}

