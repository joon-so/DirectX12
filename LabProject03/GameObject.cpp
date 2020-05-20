#include "stdafx.h"
#include "GameObject.h"
#include "GraphicsPipeline.h"

CGameObject::~CGameObject()
{
	if (m_pMesh) m_pMesh->Release();
}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}
void CGameObject::SetPosition(XMFLOAT3& xmf3Position)
{
	m_xmf4x4World._41 = xmf3Position.x;
	m_xmf4x4World._42 = xmf3Position.y;
	m_xmf4x4World._43 = xmf3Position.z;
}

void CGameObject::SetMovingDirection(const XMFLOAT3& xmf3MovingDirection)
{
	XMStoreFloat3(&m_xmf3MovingDirection, XMVector3Normalize(XMLoadFloat3(&xmf3MovingDirection)));
}

//void CGameObject::BulletDirection()
//{
//	XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
//	XMStoreFloat3(&xmf3Shift, XMVectorAdd(XMLoadFloat3(&xmf3Shift), XMVectorScale(XMLoadFloat3(&m_xmf3BulletLook), 50.0f)));
//	BulletDirection(xmf3Shift);
//}
//
//void CGameObject::BulletDirection(const XMFLOAT3& xmf3Shift)
//{
//	XMFLOAT3 m_xmf3Position{ m_xmf4x4World._41, m_xmf4x4World._42 ,m_xmf4x4World._43 };
//	XMStoreFloat3(&m_xmf3Position, XMVectorAdd(XMLoadFloat3(&m_xmf3Position), XMLoadFloat3(&xmf3Shift)));
//	SetPosition(m_xmf3Position);
//}

void CGameObject::SetRotationAxis(const XMFLOAT3& xmf3RotationAxis)
{
	XMStoreFloat3(&m_xmf3RotationAxis, XMVector3Normalize(XMLoadFloat3(&xmf3RotationAxis)));
}

void CGameObject::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX xmmtxRotate =
		XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch), XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixMultiply(xmmtxRotate, XMLoadFloat4x4(&m_xmf4x4World)));
}

void CGameObject::Rotate(XMFLOAT3& xmf3RotationAxis, float fAngle)
{
	XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&xmf3RotationAxis), XMConvertToRadians(fAngle));
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixMultiply(xmmtxRotate, XMLoadFloat4x4(&m_xmf4x4World)));
}

void CGameObject::Move(XMFLOAT3& vDirection, float fSpeed)
{
	SetPosition(m_xmf4x4World._41 + vDirection.x * fSpeed, m_xmf4x4World._42 + vDirection.y * fSpeed, m_xmf4x4World._43 + vDirection.z * fSpeed);

	// ���� �Ѿ�� �ʱ�ȭ
	if (bBulletcheck == true) {
		if (m_xmf4x4World._43 > 250.0f) {
			SetPosition(0.0f, -100000.0f, 0.0f);
			SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
			SetRotationSpeed(0.0f);
			SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
			SetMovingSpeed(0.0f);
		}
	}
}

void CGameObject::Animate(float fElapsedTime)
{
	if (m_fRotationSpeed != 0.0f) 
		Rotate(m_xmf3RotationAxis, m_fRotationSpeed * fElapsedTime);
	if (m_fMovingSpeed != 0.0f)
		Move(m_xmf3MovingDirection,	m_fMovingSpeed * fElapsedTime);
}


void CGameObject::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	if (m_pMesh)
	{
		CGraphicsPipeline::SetWorldTransform(&m_xmf4x4World);

		HPEN hPen = ::CreatePen(PS_SOLID, 0, m_dwColor);
		HPEN hOldPen = (HPEN)::SelectObject(hDCFrameBuffer, hPen);
		m_pMesh->Render(hDCFrameBuffer);
		::SelectObject(hDCFrameBuffer, hOldPen);
		::DeleteObject(hPen);
	}
}
