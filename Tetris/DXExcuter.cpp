#include "stdafx.h"
#include "DXExcuter.h"
#include "FuctionCountTimer.h"

using namespace MyDirectX;
DXExcuter::DXExcuter()
{
	//�V�[���̓o�^����������
	mScene = nullptr;
}

void DXExcuter::SetScene(Scene * scene)
{
	//�V�[�����o�^����Ă�����V�[���̏I�����\�b�h���Ăяo��
	if (mScene != nullptr) mScene->SceneEnd();
	//�V�[����o�^����
	mScene = scene;
	//�o�^�V�[���̊J�n���\�b�h���Ă�
	mScene->SceneStart();
	//���s�Q�[���I�u�W�F�N�g�Ǘ��z��ɃV�[����̃Q�[���I�u�W�F�N�g��ǉ�����
	mExcuteObjectsList = mScene->GetGameObjects();
}

void DXExcuter::Excute()
{
	//�V�[�����o�^����Ė�����Ώ������Ȃ�
	if (!mScene) return;
	//auto timer = new FuctionCountTimer();
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
