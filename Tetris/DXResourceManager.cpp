#include "stdafx.h"
#include "DXResourceManager.h"
#include "DXGameObject.h"

using namespace MyDirectX;

DXResourceManager::DXResourceManager(HWND hwnd)
{
	//DirectX���\�[�X�Ǘ�
	mDXManager = std::make_unique<DXManager>(hwnd);
	//FPS�J�E���^�[�𐶐�
	mFPSCountor = std::make_unique<FPSCountor>();
	//���Ǘ��N���X����
	mDXSoundManager = std::make_unique<DXSoundManager>(hwnd);
}

DXGameObject * DXResourceManager::Instantiate()
{
	DXGameObject* game = new DXGameObject(this);
	//�e�I�u�W�F�N�g��ID���~��
	game->SetID(mGameObjectCount);
	mGameObjectCount++;
	return game;
}

