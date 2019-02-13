#include "stdafx.h"
#include "TetriMinoNext.h"

using namespace MyDirectX;
TetriMinoNext::TetriMinoNext(Scene* scene)
{
	mScene = scene;

	auto next1 = mScene->Instantiate();
	auto nextTransform = next1->GetTransform();
	nextTransform->Position = DirectX::XMFLOAT3(-0.56f, 0.95f, -0.01f);
	nextTransform->Scale = DirectX::XMFLOAT3(0.3f,0.3f,1.0f);
	auto ui1 = next1->AddComponent<TetriMinoUI>();
	mTetriMinoNextUIObjects.push_back(ui1);

	auto next2 = mScene->Instantiate();
	auto nextTransform2 = next2->GetTransform();
	nextTransform2->Position = DirectX::XMFLOAT3(-0.58f, 0.61f, -0.01f);
	nextTransform2->Scale = DirectX::XMFLOAT3(0.25f, 0.25f, 1.0f);
	auto ui2 = next2->AddComponent<TetriMinoUI>();
	mTetriMinoNextUIObjects.push_back(ui2);

	auto next3 = mScene->Instantiate();
	auto nextTransform3 = next3->GetTransform();
	nextTransform3->Position = DirectX::XMFLOAT3(-0.58f, 0.34f, -0.01f);
	nextTransform3->Scale = DirectX::XMFLOAT3(0.25f, 0.25f, 1.0f);
	auto ui3 = next3->AddComponent<TetriMinoUI>();
	mTetriMinoNextUIObjects.push_back(ui3);

	auto next4 = mScene->Instantiate();
	auto nextTransform4 = next4->GetTransform();
	nextTransform4->Position = DirectX::XMFLOAT3(-0.58f, 0.07f, -0.01f);
	nextTransform4->Scale = DirectX::XMFLOAT3(0.25f, 0.25f, 1.0f);
	auto ui4 = next4->AddComponent<TetriMinoUI>();
	mTetriMinoNextUIObjects.push_back(ui4);

	auto next5 = mScene->Instantiate();
	auto nextTransform5 = next5->GetTransform();
	nextTransform5->Position = DirectX::XMFLOAT3(-0.58f, -0.2f, -0.01f);
	nextTransform5->Scale = DirectX::XMFLOAT3(0.25f, 0.25f, 1.0f);
	auto ui5 = next5->AddComponent<TetriMinoUI>();
	mTetriMinoNextUIObjects.push_back(ui5);

	for(int i = 0;i < 6;i++)
	{
		mTypeList.push_back(GetNextTetriMinoType());
	}
}

void TetriMinoNext::Start()
{
	auto i = 0;
	for(auto ui:mTetriMinoNextUIObjects)
	{
		ui->SetEnable(true);
		if (!mTypeList.empty())
		{
			ui->SetTetriMinoType(*std::next(mTypeList.begin(),i));
		}
		i++;
	}
}

TetriMinoType TetriMinoNext::GetNextTetriMino()
{
	//�擪�̃e�g���~�m�^�C�v���擾
	auto type = mTetriMinoNextUIObjects.front()->GetTetriMinoType();
	mTypeList.pop_front();
	//�l�N�X�g�X�V
	NextUpdate();
	return type;
}

TetriMinoType TetriMinoNext::GetNextTetriMinoType()
{
	//�V�����e�g���~�m�^�C�v��ǉ�
	auto type = static_cast<TetriMinoType>(GetRandRange(0, 6));
	//�z�񂪋�Ȃ炻�̂܂ܕԂ�
	if (mTypeList.empty()) return type;
	//�����Ɣ���Ă�����Ē��I
	if (type == mTypeList.back())
	{
		type = static_cast<TetriMinoType>(GetRandRange(0, 6));
	}
	return type;
}

int TetriMinoNext::GetRandRange(int min, int max)
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

void TetriMinoNext::NextUpdate()
{
	mTypeList.push_back(GetNextTetriMinoType());
	auto i = 0;
	for (auto ui : mTetriMinoNextUIObjects)
	{
		if (!mTypeList.empty())
		{
			ui->SetTetriMinoType(*std::next(mTypeList.begin(), i));
		}
		i++;
	}
}
