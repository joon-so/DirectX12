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

//mPlayer vector 랑 mObject vector 복사

void CGameObject::BulletMove()
{
	XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
	XMFLOAT3 m_xmf3Position{ m_xmf4x4World._41, m_xmf4x4World._42 ,m_xmf4x4World._43 };
	XMStoreFloat3(&xmf3Shift, XMVectorAdd(XMLoadFloat3(&xmf3Shift), XMVectorScale(XMLoadFloat3(&m_xmf3BulletLook), 1.5f)));
	XMStoreFloat3(&m_xmf3Position, XMVectorAdd(XMLoadFloat3(&m_xmf3Position), XMLoadFloat3(&xmf3Shift)));
	SetPosition(m_xmf3Position);
	//
	SetBoundingBox(0.8f, 0.8f, 0.8f);
}

void CGameObject::SetBoundingBox(float fWidth, float fHeight, float fDepth)
{
	XMVECTOR min = XMVectorSet(-fWidth / 2.0f, -fHeight / 2.0f, -fDepth / 2.0f, 1.0f);
	XMVECTOR max = XMVectorSet(+fWidth / 2.0f, +fHeight / 2.0f, +fDepth / 2.0f, 1.0f);
	BoundingBox::CreateFromPoints(b_bAABB, min, max);
	XMVECTOR point = XMVectorSet(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43, 1.0f);
	b_bAABB.Contains(point);
	BoundingOrientedBox::CreateFromBoundingBox(b_boOOBB, b_bAABB);
}

//void CGameObject::checkOOBB(CGameObject& box)
//{
//	bool check = false;
//	if (bBulletcheck == true) {
//		check = b_boOOBB.Intersects(box.b_boOOBB);
//		if (check == true) {
//			SetPosition(0.0f, -100000.0f, 0.0f);
//			SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
//			SetRotationSpeed(0.0f);
//			SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
//			SetMovingSpeed(0.0f);
//			bShootcheck = false;
//
//			box.SetPosition(0.0f, 100000.0f, 0.0f);
//			box.SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
//			box.SetRotationSpeed(0.0f);
//			box.SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
//			box.SetMovingSpeed(0.0f);
//			return;
//		}
//	}
//}


//

//void CGameObject::LookAt(const CPlayer& pPlayer,XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up)
//{
//	XMFLOAT4X4 xmf4x4View;
//	XMStoreFloat4x4(&xmf4x4View, XMMatrixLookAtLH(XMLoadFloat3(&m_xmf3Position), XMLoadFloat3(&xmf3LookAt), XMLoadFloat3(&xmf3Up)));
//
//	XMVECTORF32 xmf32vRight = { xmf4x4View._11, xmf4x4View._21, xmf4x4View._31, 0.0f };
//	XMVECTORF32 xmf32vUp = { xmf4x4View._12, xmf4x4View._22, xmf4x4View._32, 0.0f };
//	XMVECTORF32 xmf32vLook = { xmf4x4View._13, xmf4x4View._23, xmf4x4View._33, 0.0f };
//
//	XMStoreFloat3(&m_xmf3Right, XMVector3Normalize(xmf32vRight));
//	XMStoreFloat3(&m_xmf3Up, XMVector3Normalize(xmf32vUp));
//	XMStoreFloat3(&m_xmf3Look, XMVector3Normalize(xmf32vLook));
//}
//
//void CGameObject::OnUpdateTransform()
//{
//	m_xmf4x4World._11 = m_xmf3Right.x; m_xmf4x4World._12 = m_xmf3Right.y; m_xmf4x4World._13 = m_xmf3Right.z;
//	m_xmf4x4World._21 = m_xmf3Up.x; m_xmf4x4World._22 = m_xmf3Up.y;
//	m_xmf4x4World._23 = m_xmf3Up.z;
//	m_xmf4x4World._31 = m_xmf3Look.x; m_xmf4x4World._32 = m_xmf3Look.y;
//	m_xmf4x4World._33 = m_xmf3Look.z;
//	//m_xmf4x4World._41 = m_xmf3Position.x; m_xmf4x4World._42 = m_xmf3Position.y; m_xmf4x4World._43 = m_xmf3Position.z;
//}

//까지

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

	// 범위 넘어가면 초기화
	if (bBulletcheck == true) {
		if (m_xmf4x4World._43 > 250.0f) {
			SetPosition(0.0f, -100000.0f, 0.0f);
			SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
			SetRotationSpeed(0.0f);
			SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
			SetMovingSpeed(0.0f);
			bShootcheck = false;
			//
			SetBoundingBox(0.8f, 0.8f, 0.8f);
		}
	}
}

void CGameObject::Animate(float fElapsedTime)
{
	if (bShootcheck == true) {
		BulletMove();
	}
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
