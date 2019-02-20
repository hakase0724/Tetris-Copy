#include "stdafx.h"
#include "MeshRenderer.h"

using namespace DirectX;
using namespace MyDirectX;

void MeshRenderer::SetDefaultColor(float r, float g, float b, float a)
{
	mDefaultColor.r = r;
	mDefaultColor.g = g;
	mDefaultColor.b = b;
	mDefaultColor.a = a;
	mColor = mDefaultColor;
}

void MeshRenderer::SetColor(float r, float g, float b, float a)
{
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
	mColor.a = a;
}

void MeshRenderer::SetColor()
{
	mColor = mDefaultColor;
}

void MeshRenderer::Initialize(DXGameObject * gameObject)
{
	mDXManager = gameObject->GetDXManager();
	mDXCamera = gameObject->GetDXCamera();
	mDeviceContext = mDXManager->GetDeviceContext();
	mGameObject = gameObject;
	mDXFactory = mDXManager->GetDXFactory();
	mDevice = mDXManager->GetDevice();
	mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	mDefaultColor.r = 0;
	mDefaultColor.g = 1;
	mDefaultColor.b = 0;
	mDefaultColor.a = 1;
	mColor = mDefaultColor;
}

void MeshRenderer::Initialize()
{
	mColor = mDefaultColor;
}

void MeshRenderer::Render()
{
}

void MeshRenderer::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
}