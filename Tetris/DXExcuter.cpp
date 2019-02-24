#include "stdafx.h"
#include "DXExcuter.h"
#include "FuctionCountTimer.h"
#include <thread>

using namespace MyDirectX;
DXExcuter::DXExcuter()
{
	//�V�[���̓o�^����������
	mScene = nullptr;
}

void DXExcuter::SetScene(Scene * scene)
{
	auto isThread = false;
	std::thread preSceneThread;
	//�V�[�����o�^����Ă�����V�[���̏I�����\�b�h���Ăяo��
	if (mScene != nullptr) 
	{
		auto preScene = mScene;
		isThread = true;
		preSceneThread = std::thread([&] 
		{
			preScene->SceneEnd();
		});
	}
	//�V�[���̊J�n���\�b�h���Ă�
	scene->SceneStart();
	//���s�Q�[���I�u�W�F�N�g�Ǘ��z��ɃV�[����̃Q�[���I�u�W�F�N�g��ǉ�����
	mExcuteObjectsList = scene->GetGameObjects();
	//�O�̃V�[���̏I�����\�b�h�̊�����҂�
	if (isThread) preSceneThread.join();
	//�V�[����o�^����
	mScene = scene;
}

void DXExcuter::Excute()
{
	//�V�[�����o�^����Ė�����Ώ������Ȃ�
	if (!mScene) return;
	/*���t���[���̏������s��*/
	//�V�[���̍X�V����
	mScene->SceneUpdate();
	//�Q�[���I�u�W�F�N�g�̍X�V����
	Update();
	//�S�Ă̍X�V�������I�������̍X�V����
	mScene->SceneLateUpdate();
	//�Q�[���I�u�W�F�N�g�̌�X�V����
	LateUpdate();
	//�`�揈��
	Render();
	//1�t���[���I�����̏���
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
	//�[�x�o�b�t�@��Ԃ�ݒ�
	auto depth = mDXRescourceManager->GetDXManager()->GetDepthStencilState();
	mDXRescourceManager->GetDXManager()->GetDeviceContext()->OMSetDepthStencilState(depth, 0);
	for (auto &game : *mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->Render();
	}
	mDXRescourceManager->GetDXManager()->EndScene();
}
