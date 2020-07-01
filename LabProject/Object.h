//------------------------------------------------------- ----------------------
// File: Object.h
//-----------------------------------------------------------------------------

#pragma once

#include "Mesh.h"
#include "Camera.h"

class CShader;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	char							m_pstrName[64] = { '\0' };
	int iMoveDirection;
	float fEnemySpeed;
	int iDirectionChange = 500;

	XMFLOAT4X4						m_xmf4x4World;
	CMesh							*m_pMesh = NULL;

	CShader							*m_pShader = NULL;

	XMFLOAT3						m_xmf3Color = XMFLOAT3(1.0f, 1.0f, 1.0f);

	void SetMesh(CMesh *pMesh);
	void SetShader(CShader *pShader);
	void SetWorldMatrix(XMFLOAT4X4& xmf4x4World) { m_xmf4x4World = xmf4x4World; }

	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual void Animate(float fTimeElapsed);
	virtual void OnPrepareRender() { }
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera = NULL);

	virtual void ReleaseUploadBuffers();

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	void SetColor(XMFLOAT3 xmf3Color) { m_xmf3Color = xmf3Color; }

	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);
	void MoveRandom();

	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	void Rotate(XMFLOAT3 *pxmf3Axis, float fAngle);
};

class CUfoObject : public CGameObject
{
public:
	CUfoObject();
	virtual ~CUfoObject();
};

class CCubeRotatingObject : public CGameObject
{
public:
	CCubeRotatingObject();
	virtual ~CCubeRotatingObject();

private:
	XMFLOAT3 m_xmf3RotationAxis;
	float m_fRotationSpeed;

public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) {
		m_xmf3RotationAxis = xmf3RotationAxis;
	}

	virtual void Animate(float fTimeElapsed);
};