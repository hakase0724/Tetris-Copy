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
	//UI�v�f�����
	CreateUIItem();
	//�ՖʊǗ�
	mFieldManager = std::make_unique<FieldManager>(this);
	//�X�R�A�Ǘ�
	mScoreManager = std::make_unique<ScoreManager>(this);
	//�l�N�X�g�\��
	mNext = std::make_unique<TetriMinoNext>(this);
	//�e�g���~�m����
	mTetriMinoController = std::make_unique<TetriMinoController>(mDXRescourceManager,mFieldManager.get(),this);
	
	
	//�S�ẴI�u�W�F�N�g�̏����ʒu��ݒ肷��
	for(auto &game: mGameObjectsList)
	{
		game->SetDefaultTransform();
	}
	//�v���C�V�[����BGM�擾
	mBGM = mDXRescourceManager->GetSoundManager()->GetBGMSound(_T("Sound/BGM/TetrisTheme.wav"));
	//���ʉ�����
	mBGM->SetVolume(-1000);
	//�������̉�
	mDeleteSound = mDXRescourceManager->GetSoundManager()->GetSESound(_T("Sound/SE/Delete.wav"));
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
	//�e�평����
	mFieldManager->Start();
	mScoreManager->Start();
	mNext->Start();
	mTetriMinoController->Start();
	//�ŏ��̃e�g���~�m���o��
	mTetriMinoController->SetTetriMino(5, 20, mNext->GetNextTetriMino());
	//�ȍĐ�
	mBGM->Play();
}

void PlayScene::SceneUpdate()
{
	mFrameCount++;
#if _DEBUG
	//FPS���v�Z���o�͂���
	//���t���[���o���ƕω�������������̂ň��Ԋu�ōX�V
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
	//�e�g���~�m�𑀍삵�Ă��鎞
	case Play:
		mTetriMinoController->PreUpdate();
		isPlaying = mTetriMinoController->Update();
		//�ړ��̃X�R�A�����Z����
		mScoreManager->AddScore(mTetriMinoController->GetMoveScore());
		if (!isPlaying) 
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
			//�����Ă��Ȃ���ΈȌ�̏��������Ȃ�
			if (eraseLine <= 0) 
			{
				mState = Next;
				break;
			}
			//���݂̃��x��
			auto level = mFieldManager->GetLevel();
			//�����������̃X�R�A�����Z
			mScoreManager->AddScore(eraseLine, level, isTspin, isTspinMini);
			mDeleteSound->ResetSound();
			mDeleteSound->Play(false);
			mWaitStartFrame = mFrameCount;
			mState = Wait;
		}
		break;
	//������̑҂�
	case Wait:
		//�t���[���őҋ@
		if((mFrameCount - mWaitStartFrame) % cWaitFrame == 0)
		{
			mState = Next;
			mFieldManager->ChangePieceStateToSpace(PieceState::Erase);
			mFieldManager->DropPiece();
		}
		break;
	//����
	case Next:
		//���̃e�g���~�m���o��
		mTetriMinoController->SetTetriMino(5, 20, mNext->GetNextTetriMino());
		mState = Play;
		break;
	default:
		break;
	}
}

void PlayScene::SceneEnd()
{
	//�S�ẴI�u�W�F�N�g�̃A�N�e�B�u��؂�
	for (auto &game : mGameObjectsList)
	{
		game->SetEnable(false);
	}
	//�Ȃ��~�߂�
	mBGM->Stop();
}

bool PlayScene::IsSceneEnd()
{
	if (mTetriMinoController->IsGameOver()) return true;
	return false;
}

void PlayScene::CreateUIItem()
{
	//�v���C�V�[����g
	auto layout = Instantiate();
	auto tex = layout->AddComponent<DXTexture>();
	tex->SetTexture(_T("Texture/Layout.png"));
	auto transform = layout->GetTransform();
	transform->Scale = DirectX::XMFLOAT3(5.5f, 3.0f, 1.0f);
	mAwakeObject.push_back(layout);

	//�v���C�V�[���̔Ֆ�
	auto field = Instantiate();
	auto tex2 = field->AddComponent<DXTexture>();
	tex2->SetTexture(_T("Texture/Field.png"));
	auto transform2 = field->GetTransform();
	transform2->Scale = DirectX::XMFLOAT3(1.1f, 2.1f, 1.0f);
	transform2->Position.x -= 1.35f;
	transform2->Position.y += 0.07f;
	transform2->Position.z += 0.01f;
	mAwakeObject.push_back(field);

	//T�X�s�������Ƃ��\������UI
	mTspinUI = Instantiate();
	auto tspinText = mTspinUI->AddComponent<DXText>();
	auto tspinTransform = mTspinUI->GetTransform();
	tspinTransform->Scale = DirectX::XMFLOAT3(0.07f,0.07f,1.0f);
	tspinTransform->Position = DirectX::XMFLOAT3(-1.7f, -0.7f, -1.1f);
	tspinText->UpdateText(_T("TSpin"));
	//T�X�s���~�j�����Ƃ��\������UI
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

