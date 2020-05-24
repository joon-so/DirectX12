#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Player.h"

class CScene
{
public:
	CScene(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
	virtual ~CScene() { }

public:
	int mObjectCount = 200;
	int m_nObjects = 0;
	CGameObject** m_ppObjects = NULL;
	CPlayer* m_pPlayer = NULL;

	//
	int m_nBullets = 0;

	virtual void BuildObjects(CPlayer& pPlayer);
	virtual void ReleaseObjects();

	virtual void BuildBullet(CPlayer& PlayerPosition, int iChooseBullet);

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) { }
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) { }
};