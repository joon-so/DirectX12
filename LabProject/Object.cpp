//-----------------------------------------------------------------------------
// File: CGameObject.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Object.h"
#include "Shader.h"

CGameObject::CGameObject()
{
	random_device rd;
	mt19937 mersenne(rd());
	uniform_int_distribution<> die;

	m_xmf4x4World = Matrix4x4::Identity();
	iMoveDirection = die(mersenne) % 6;
	fEnemySpeed = (die(mersenne) % 6 + 1) / (float)70;
}

CGameObject::~CGameObject()
{
	if (m_pMesh) m_pMesh->Release();
	if (m_pShader) m_pShader->Release();
}

void CGameObject::SetMesh(CMesh *pMesh)
{
	if (m_pMesh) m_pMesh->Release();
	m_pMesh = pMesh;
	if (m_pMesh) m_pMesh->AddRef();
}

void CGameObject::SetShader(CShader *pShader)
{
	if (m_pShader) m_pShader->Release();
	m_pShader = pShader;
	if (m_pShader) m_pShader->AddRef();
}

void CGameObject::Animate(float fTimeElapsed)
{
}

void CGameObject::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
}

void CGameObject::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(1, 16, &xmf4x4World, 0);

	pd3dCommandList->SetGraphicsRoot32BitConstants(1, 3, &m_xmf3Color, 16);
}

void CGameObject::ReleaseShaderVariables()
{
}

void CGameObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	OnPrepareRender();

	if (m_pShader) m_pShader->Render(pd3dCommandList, pCamera);

	UpdateShaderVariables(pd3dCommandList);

	if (m_pMesh) m_pMesh->Render(pd3dCommandList);
}

void CGameObject::ReleaseUploadBuffers()
{
	if (m_pMesh) m_pMesh->ReleaseUploadBuffers();
}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}

void CGameObject::SetPosition(XMFLOAT3 xmf3Position)
{
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}

XMFLOAT3 CGameObject::GetPosition()
{
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}

XMFLOAT3 CGameObject::GetLook()
{
	return(Vector3::Normalize((XMFLOAT3&)XMFLOAT3(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33)));
}

XMFLOAT3 CGameObject::GetUp()
{
	return(Vector3::Normalize((XMFLOAT3&)XMFLOAT3(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23)));
}

XMFLOAT3 CGameObject::GetRight()
{
	return(Vector3::Normalize((XMFLOAT3&)XMFLOAT3(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13)));
}

void CGameObject::MoveStrafe(float fDistance)
{
	if (GetPosition().x > LEFT&& GetPosition().x < RIGHT) {
		XMFLOAT3 xmf3Position = GetPosition();
		XMFLOAT3 xmf3Right = GetRight();
		xmf3Position = Vector3::Add(xmf3Position, xmf3Right, fDistance);
		CGameObject::SetPosition(xmf3Position);
	}
}

void CGameObject::MoveUp(float fDistance)
{
	if (GetPosition().y > BOTTOM&& GetPosition().y < TOP) {
		XMFLOAT3 xmf3Position = GetPosition();
		XMFLOAT3 xmf3Up = GetUp();
		xmf3Position = Vector3::Add(xmf3Position, xmf3Up, fDistance);
		CGameObject::SetPosition(xmf3Position);
	}
}

void CGameObject::MoveForward(float fDistance)
{
	if (GetPosition().z > BACK&& GetPosition().z < FORWARD) {
		XMFLOAT3 xmf3Position = GetPosition();
		XMFLOAT3 xmf3Look = GetLook();
		xmf3Position = Vector3::Add(xmf3Position, xmf3Look, fDistance);
		CGameObject::SetPosition(xmf3Position);
	}
}

void CGameObject::MoveRandom()
{
	iDirectionChange--;
	int range = 3.0f;
	// top = 65.0f, bottom = 15.0f, left = -100.0f, right = 100.0f, forward = 200.0f, back = -200.0f
	// 0 : left ,  1 : right , 2: down , 3: up , 4: back , 5: forward
	if (GetPosition().x < LEFT + range || GetPosition().x > RIGHT - range ||
		GetPosition().y <BOTTOM + range || GetPosition().y > TOP - range ||
		GetPosition().z < BACK + range || GetPosition().z > FORWARD - range||
		iDirectionChange == 0) 
	{
		random_device rd;
		mt19937 mersenne(rd());
		uniform_int_distribution<> die;

		if (iDirectionChange == 0)
			iDirectionChange = 500;
		else if (iMoveDirection == 0)
			MoveStrafe(fEnemySpeed);
		else if (iMoveDirection == 1)
			MoveStrafe(-fEnemySpeed);
		else if (iMoveDirection == 2)
			MoveUp(-fEnemySpeed);
		else if (iMoveDirection == 3)
			MoveUp(+fEnemySpeed);
		else if (iMoveDirection == 4)
			MoveForward(+fEnemySpeed);
		else if (iMoveDirection == 5)
			MoveForward(-fEnemySpeed);

		iMoveDirection = die(rd) % 6;
	}

	if (iMoveDirection == 0)
		MoveStrafe(-fEnemySpeed);
	else if (iMoveDirection == 1)
		MoveStrafe(+fEnemySpeed);
	else if (iMoveDirection == 2)
		MoveUp(+fEnemySpeed);
	else if (iMoveDirection == 3)
		MoveUp(-fEnemySpeed);
	else if (iMoveDirection == 4)
		MoveForward(-fEnemySpeed);
	else if (iMoveDirection == 5)
		MoveForward(+fEnemySpeed);
}

void CGameObject::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch), XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Rotate(XMFLOAT3 *pxmf3Axis, float fAngle)
{
	XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(pxmf3Axis), XMConvertToRadians(fAngle));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CUfoObject::CUfoObject()
{

}

CUfoObject::~CUfoObject()
{

}


CCubeRotatingObject::CCubeRotatingObject()
{
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 90.0f;
}

void CCubeRotatingObject::Animate(float fTimeElapsed)
{
	CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
}

CCubeRotatingObject::~CCubeRotatingObject()
{
}