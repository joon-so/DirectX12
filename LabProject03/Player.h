#pragma once

#include "GameObject.h"
#include "Camera.h"

class CPlayer : public CGameObject
{
public:
	CPlayer() { }
	virtual ~CPlayer() { if (m_pCamera) delete m_pCamera; }
public:
	XMFLOAT3 m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3 m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3 m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	XMFLOAT3 m_xmf3CameraOffset = XMFLOAT3(0.0f, 0.0f, 0.0f);
	
	XMFLOAT3 m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	
	float m_fFriction = 125.0f;
	
	float m_fPitch = 0.0f;
	float m_fYaw = 0.0f;
	float m_fRoll = 0.0f;

	CCamera* m_pCamera = NULL;

public:
	void SetPosition(float x, float y, float z);
	//void SetRotation(float x, float y, float z);
	
	void LookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);
	
	void Move(const DWORD dwDirection, float fDistance);
	void Move(const XMFLOAT3& xmf3Shift, bool bUpdateVelocity);
	void Move(float x, float y, float z);
	
	void Rotate(float fPitch, float fYaw, float fRoll);
	void SetCameraOffset(const XMFLOAT3& xmf3CameraOffset);
	
	void Update(float fTimeElapsed = 0.016f);
	
	virtual void OnUpdateTransform();
	virtual void Animate(float fElapsedTime);

	void SetCamera(CCamera* pCamera) { m_pCamera = pCamera; }
	CCamera* GetCamera() { return(m_pCamera); }
};

class CAirplanePlayer : public CPlayer
{
public:
	CAirplanePlayer();
	virtual ~CAirplanePlayer();
	virtual void OnUpdateTransform();
};