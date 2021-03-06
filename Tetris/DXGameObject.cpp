#include "stdafx.h"
#include "DXGameObject.h"

using namespace DirectX;
using namespace MyDirectX;

DXGameObject::DXGameObject(DXResourceManager* manager)
{
	mTransform = std::make_unique<TRANSFORM>();
	mTransform->Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform->Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform->Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	mDXResourceManager = manager;
	mDXManager = mDXResourceManager->GetDXManager();
	mDXCamera = mDXManager->GetDXCamera();
	mName = "GameObject";
}

DXGameObject::~DXGameObject()
{
	Exit();
}

//自身の初期化
HRESULT DXGameObject::Init(DXManager * dxManager)
{
	mDXManager = dxManager;
	mDXCamera = mDXManager->GetDXCamera();
	return S_OK;
}

//持っているコンポーネントの初期化処理を行う
void DXGameObject::InitializeComponent()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Initialize();
	}
}

//持っているコンポーネントの更新処理を行う
void DXGameObject::Update()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		if (!pItr->GetEnable())continue;
		pItr->Update();
	}
}

//持っているコンポーネントの更新処理が終わった後での更新処理
void DXGameObject::LateUpdate()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		if (!pItr->GetEnable())continue;
		pItr->LateUpdate();
	}
}


//持っているコンポーネントの描画処理を行う
void DXGameObject::Render()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		if (!pItr->GetEnable())continue;
		pItr->Render();
	}
}

//持っているコンポーネントの解放処理を行う
void DXGameObject::Exit()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Exit();
		delete pItr;
	}
}

//アクティブになった時
void DXGameObject::OnEnable()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->OnEnable();
	}
}

//非アクティブになった時
void DXGameObject::OnDisable()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->OnDisable();
	}
}
