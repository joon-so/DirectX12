#pragma once

#include "Shader.h"
#include "Player.h"

class CScene
{
public:
    CScene();
    ~CScene();

	int m_nBullets = 0;

	virtual void BuildBullet(CPlayer& PlayerPosition, int iChooseBullet);

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void LoadSceneObjectsFromFile(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, char *pstrFileName);

	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	void ReleaseObjects();

	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSignature() { return(m_pd3dGraphicsRootSignature); }

	bool ProcessInput();
    void AnimateObjects(float fTimeElapsed);
    void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera=NULL);

	void ReleaseUploadBuffers();
	int GetBulletCount() { return mBulletCount; }

protected:
	ID3D12RootSignature			*m_pd3dGraphicsRootSignature = NULL;
	CGameObject					**m_ppObjects = 0;
	int							m_nObjects = 0;

	int							m_nEnemyObjects = 15;	//적
	int							iParticleCube = 24;		//파티클
	int							mBulletCount = 200;		//총알
};
