#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"

//void CScene::BuildObjects()
//{
//	CCubeMesh* pCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
//	CMapMesh* pMapMesh = new CMapMesh(80.0f, 80.0f, 15.0f);
//	CCubeMesh* pBulletMesh = new CCubeMesh(0.8f, 0.8f, 0.8f);
//
//	m_nObjects = 25;
//	m_ppObjects = new CGameObject * [m_nObjects + m_nBullets];
//
//	m_ppObjects[0] = new CGameObject();
//	m_ppObjects[0]->SetMesh(pCubeMesh);
//	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
//	m_ppObjects[0]->SetPosition(-13.5f, 25.0f, +90.0f);
//	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
//	m_ppObjects[0]->SetRotationSpeed(90.0f);
//	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
//	m_ppObjects[0]->SetMovingSpeed(4.0f);
//
//	m_ppObjects[1] = new CGameObject();
//	m_ppObjects[1]->SetMesh(pCubeMesh);
//	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
//	m_ppObjects[1]->SetPosition(+13.5f, -20.0f, +100.0f);
//	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
//	m_ppObjects[1]->SetRotationSpeed(180.0f);
//	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
//	m_ppObjects[1]->SetMovingSpeed(1.5f);
//
//	m_ppObjects[2] = new CGameObject();
//	m_ppObjects[2]->SetMesh(pCubeMesh);
//	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
//	m_ppObjects[2]->SetPosition(10.0f, +5.0f, 95.0f);
//	m_ppObjects[2]->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 1.0f));
//	m_ppObjects[2]->SetRotationSpeed(30.15f);
//	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
//	m_ppObjects[2]->SetMovingSpeed(2.0f);
//
//	m_ppObjects[3] = new CGameObject();
//	m_ppObjects[3]->SetMesh(pCubeMesh);
//	m_ppObjects[3]->SetColor(RGB(0, 255, 255));
//	m_ppObjects[3]->SetPosition(0.0f, 0.0f, 80.0f);
//	m_ppObjects[3]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 1.0f));
//	m_ppObjects[3]->SetRotationSpeed(40.6f);
//	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(1.0f, 1.0f, 0.0f));
//	m_ppObjects[3]->SetMovingSpeed(2.0f);
//
//	m_ppObjects[4] = new CGameObject();
//	m_ppObjects[4]->SetMesh(pCubeMesh);
//	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
//	m_ppObjects[4]->SetPosition(10.0f, 10.0f, 90.0f);
//	m_ppObjects[4]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
//	m_ppObjects[4]->SetRotationSpeed(50.06f);
//	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(-1.0f, 1.0f, 0.0f));
//	m_ppObjects[4]->SetMovingSpeed(1.5f);
//
//	for (int i = 5; i < m_nObjects; i++) {
//		m_ppObjects[i] = new CGameObject();
//		m_ppObjects[i]->SetMesh(pMapMesh);
//		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
//		m_ppObjects[i]->SetPosition(0.0f, 0.0f, (i - 4) * 15.0f);
//		m_ppObjects[i]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
//		m_ppObjects[i]->SetRotationSpeed(0.0f);
//		m_ppObjects[i]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
//		m_ppObjects[i]->SetMovingSpeed(0.0f);
//	}
//
//	for (int i = 0; i < m_nBullets; i++) {
//		m_ppObjects[m_nObjects + i] = new CGameObject();
//		m_ppObjects[m_nObjects + i]->bBulletcheck = true;
//		m_ppObjects[m_nObjects + i]->SetMesh(pBulletMesh);
//		m_ppObjects[m_nObjects + i]->SetColor(RGB(255, 0, 0));
//		m_ppObjects[m_nObjects + i]->SetPosition(0.0f, 0.0f, 10.0f);
//		m_ppObjects[m_nObjects + i]->SetRotationAxis(XMFLOAT3(0.0f, .0f, 1.0f));
//		m_ppObjects[m_nObjects + i]->SetRotationSpeed(200.0f);
//		m_ppObjects[m_nObjects + i]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
//		m_ppObjects[m_nObjects + i]->SetMovingSpeed(50.0f);
//	}
//}		//BuildObject ¿øº»

void CScene::BuildObjects(CPlayer& pPlayer)
{
	CCubeMesh* pCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	CMapMesh* pMapMesh = new CMapMesh(80.0f, 80.0f, 15.0f);
	CCubeMesh* pBulletMesh = new CCubeMesh(0.8f, 0.8f, 0.8f);

	m_nObjects = 25;
	m_ppObjects = new CGameObject * [200];

	m_ppObjects[0] = new CGameObject();
	m_ppObjects[0]->SetMesh(pCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-13.5f, 25.0f, +90.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[0]->SetRotationSpeed(90.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(4.0f);

	m_ppObjects[1] = new CGameObject();
	m_ppObjects[1]->SetMesh(pCubeMesh);
	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects[1]->SetPosition(+13.5f, -20.0f, +100.0f);
	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[1]->SetRotationSpeed(180.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(1.5f);

	m_ppObjects[2] = new CGameObject();
	m_ppObjects[2]->SetMesh(pCubeMesh);
	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
	m_ppObjects[2]->SetPosition(10.0f, +5.0f, 95.0f);
	m_ppObjects[2]->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_ppObjects[2]->SetRotationSpeed(30.15f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(2.0f);

	m_ppObjects[3] = new CGameObject();
	m_ppObjects[3]->SetMesh(pCubeMesh);
	m_ppObjects[3]->SetColor(RGB(0, 255, 255));
	m_ppObjects[3]->SetPosition(0.0f, 0.0f, 80.0f);
	m_ppObjects[3]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[3]->SetRotationSpeed(40.6f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[3]->SetMovingSpeed(2.0f);

	m_ppObjects[4] = new CGameObject();
	m_ppObjects[4]->SetMesh(pCubeMesh);
	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
	m_ppObjects[4]->SetPosition(10.0f, 10.0f, 90.0f);
	m_ppObjects[4]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[4]->SetRotationSpeed(50.06f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(-1.0f, 1.0f, 0.0f));
	m_ppObjects[4]->SetMovingSpeed(1.5f);

	for (int i = 5; i < m_nObjects; i++) {
		m_ppObjects[i] = new CGameObject();
		m_ppObjects[i]->SetMesh(pMapMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(0.0f, 0.0f, (i - 4) * 15.0f);
		m_ppObjects[i]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
		m_ppObjects[i]->SetRotationSpeed(0.0f);
		m_ppObjects[i]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
		m_ppObjects[i]->SetMovingSpeed(0.0f);
	}

	for (int i = 25; i < 200; i++) {
		m_ppObjects[i] = new CGameObject();
		m_ppObjects[i]->bBulletcheck = true;
		m_ppObjects[i]->SetMesh(pBulletMesh);
		m_ppObjects[i]->SetColor(RGB(255, 0, 0));
		m_ppObjects[i]->SetPosition(0.0f, -100000.0f, 0.0f);
		m_ppObjects[i]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
		m_ppObjects[i]->SetRotationSpeed(0.0f);
		m_ppObjects[i]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 0.0f));
		m_ppObjects[i]->SetMovingSpeed(0.0f);
	}
}

void CScene::BuildBullet(CPlayer& pPlayer, int iChooseBullet)
{
	m_ppObjects[m_nObjects + iChooseBullet]->SetPosition(pPlayer.m_xmf3Position);
	m_ppObjects[m_nObjects + iChooseBullet]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[m_nObjects + iChooseBullet]->SetRotationSpeed(200.0f);
	m_ppObjects[m_nObjects + iChooseBullet]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[m_nObjects + iChooseBullet]->SetMovingSpeed(50.0f);

	//m_ppObjects[m_nObjects + iChooseBullet]->BulletDirection();
}


void CScene::ReleaseObjects()
{
	for (int i = 0; i < 200; i++) 
		if (m_ppObjects[i]) 
			delete m_ppObjects[i];
	if (m_ppObjects) 
		delete[] m_ppObjects;

	if (m_ppObjects) 
		delete[] m_ppObjects;
}

//void CScene::ShootBullets()
//{
//	CCubeMesh* pBulletMesh = new CCubeMesh(0.8f, 0.8f, 0.8f);
//
//	for (int i = 0; i < m_nBullets; i++) {
//		m_ppBullets[i] = new CGameObject();
//		m_ppBullets[i]->SetMesh(pBulletMesh);
//		m_ppBullets[i]->SetColor(RGB(255, 0, 0));
//		m_ppBullets[i]->SetPosition(0.0f, 0.0f, i * 2.0f);
//		m_ppBullets[i]->SetRotationAxis(XMFLOAT3(0.0f, .0f, 1.0f));
//		m_ppBullets[i]->SetRotationSpeed(200.0f);
//		m_ppBullets[i]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
//		m_ppBullets[i]->SetMovingSpeed(30.0f);
//	}
//}
//
//void CScene::ReleaseBullets()
//{
//	for (int i = 0; i < m_nBullets; i++)
//		if (m_ppBullets[i])
//			delete m_ppBullets[i];
//	if (m_ppBullets)
//		delete[] m_ppBullets;
//}


void CScene::Animate(float fElapsedTime)
{
	for (int i = 0; i < 200; i++)
		m_ppObjects[i]->Animate(fElapsedTime);
}

void CScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);
	CGraphicsPipeline::SetViewProjectTransform(&pCamera->m_xmf4x4ViewProject);
	for (int i = 0; i < 200; i++)
		m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
}