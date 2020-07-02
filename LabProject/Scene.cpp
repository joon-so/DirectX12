//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::LoadSceneObjectsFromFile(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, char *pstrFileName)
{
	FILE *pFile = NULL;
	::fopen_s(&pFile, pstrFileName, "rb");
	::rewind(pFile);

	CPseudoLightingShader *pShader = new CPseudoLightingShader();
	pShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	pShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);

	char pstrToken[64] = { '\0' };
	char pstrGameObjectName[64] = { '\0' };

	UINT nReads = 0, nObjectNameLength = 0;
	BYTE nStrLength = 0;

	nReads = (UINT)::fread(&nStrLength, sizeof(BYTE), 1, pFile);
	nReads = (UINT)::fread(pstrToken, sizeof(char), 14, pFile); //"<GameObjects>:"
	nReads = (UINT)::fread(&m_nObjects, sizeof(int), 1, pFile);

	m_nObjects += m_nEnemyObjects;
	m_ppObjects = new CGameObject*[m_nObjects + mBulletCount + iParticleCube];

	CGameObject *pGameObject = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		pGameObject = new CGameObject();

		nReads = (UINT)::fread(&nStrLength, sizeof(BYTE), 1, pFile);
		nReads = (UINT)::fread(pstrToken, sizeof(char), 13, pFile); //"<GameObject>:"
		nReads = (UINT)::fread(&nObjectNameLength, sizeof(UINT), 1, pFile);
		nReads = (UINT)::fread(&nStrLength, sizeof(BYTE), 1, pFile);
		nReads = (UINT)::fread(pstrGameObjectName, sizeof(char), nObjectNameLength, pFile);
		nReads = (UINT)::fread(&pGameObject->m_xmf4x4World, sizeof(float), 16, pFile);

		pstrGameObjectName[nObjectNameLength] = '\0';
		strcpy_s(pGameObject->m_pstrName, 64, pstrGameObjectName);

		CMesh *pMesh = NULL;
		for (int j = 0; j < i; j++)
		{
			if (!strcmp(pstrGameObjectName, m_ppObjects[j]->m_pstrName))
			{
				pMesh = m_ppObjects[j]->m_pMesh;
				break;
			}
		}
		if (!pMesh)
		{
			char pstrFilePath[64] = { '\0' };
			strcpy_s(pstrFilePath, 64, "Models/");
			strcpy_s(pstrFilePath + 7, 64 - 7, pstrGameObjectName);
			strcpy_s(pstrFilePath + 7 + nObjectNameLength, 64 - 7 - nObjectNameLength, ".bin");
			pMesh = new CMesh(pd3dDevice, pd3dCommandList, pstrFilePath);
		}

		pGameObject->SetMesh(pMesh);
		pGameObject->SetShader(pShader);

		m_ppObjects[i] = pGameObject;
	}

	::fclose(pFile);

	CMesh* pUfoMesh = new CMesh(pd3dDevice, pd3dCommandList, "Models/UFO.txt");
	CMesh* pFlyerMesh = new CMesh(pd3dDevice, pd3dCommandList, "Models/FlyerPlayership.txt");

	m_ppObjects[m_nObjects - 11] = new CGameObject();
	m_ppObjects[m_nObjects - 11]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 11]->SetShader(pShader);
	m_ppObjects[m_nObjects - 11]->SetPosition(6.0f, 30.0f, 13.0f);
	m_ppObjects[m_nObjects - 11]->SetColor(XMFLOAT3(0.7f, 0.0f, 0.0f));

	m_ppObjects[m_nObjects - 10] = new CGameObject();
	m_ppObjects[m_nObjects - 10]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 10]->SetShader(pShader);
	m_ppObjects[m_nObjects - 10]->SetPosition(10.0f, 60.0f, 8.0f);
	m_ppObjects[m_nObjects - 10]->SetColor(XMFLOAT3(0.0f, 0.7f, 0.0f));

	m_ppObjects[m_nObjects - 9] = new CGameObject();
	m_ppObjects[m_nObjects - 9]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 9]->SetShader(pShader);
	m_ppObjects[m_nObjects - 9]->SetPosition(-95.0f, 55.0f, 11.0f);
	m_ppObjects[m_nObjects - 9]->SetColor(XMFLOAT3(0.0f, 0.0f, 0.7f));

	m_ppObjects[m_nObjects - 8] = new CGameObject();
	m_ppObjects[m_nObjects - 8]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 8]->SetShader(pShader);
	m_ppObjects[m_nObjects - 8]->SetPosition(90.0f, 50.0f, 8.0f);
	m_ppObjects[m_nObjects - 8]->SetColor(XMFLOAT3(0.0f, 0.7f, 0.7f));

	m_ppObjects[m_nObjects - 7] = new CGameObject();
	m_ppObjects[m_nObjects - 7]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 7]->SetShader(pShader);
	m_ppObjects[m_nObjects - 7]->SetPosition(0.0f, 20.0f, 190.0f);
	m_ppObjects[m_nObjects - 7]->Rotate(0.0f, 180.0f, 0.0f);
	m_ppObjects[m_nObjects - 7]->SetColor(XMFLOAT3(0.25f, 0.75f, 0.65f));

	m_ppObjects[m_nObjects - 6] = new CGameObject();
	m_ppObjects[m_nObjects - 6]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 6]->SetShader(pShader);
	m_ppObjects[m_nObjects - 6]->SetPosition(-10.0f, 20.0f, -180.0f);
	m_ppObjects[m_nObjects - 6]->Rotate(0.0f, 180.0f, 0.0f);
	m_ppObjects[m_nObjects - 6]->SetColor(XMFLOAT3(0.25f, 0.75f, 0.65f));

	m_ppObjects[m_nObjects - 5] = new CGameObject();
	m_ppObjects[m_nObjects - 5]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 5]->SetShader(pShader);
	m_ppObjects[m_nObjects - 5]->SetPosition(10.0f, 31.0f, 20.0f);
	m_ppObjects[m_nObjects - 5]->Rotate(0.0f, 180.0f, 0.0f);
	m_ppObjects[m_nObjects - 5]->SetColor(XMFLOAT3(0.25f, 0.75f, 0.65f));

	m_ppObjects[m_nObjects - 4] = new CGameObject();
	m_ppObjects[m_nObjects - 4]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 4]->SetShader(pShader);
	m_ppObjects[m_nObjects - 4]->SetPosition(-20.0f, 31.0f, 20.0f);
	m_ppObjects[m_nObjects - 4]->Rotate(0.0f, 180.0f, 0.0f);
	m_ppObjects[m_nObjects - 4]->SetColor(XMFLOAT3(0.25f, 0.75f, 0.65f));

	m_ppObjects[m_nObjects - 3] = new CGameObject();
	m_ppObjects[m_nObjects - 3]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 3]->SetShader(pShader);
	m_ppObjects[m_nObjects - 3]->SetPosition(20.0f, 31.0f, 20.0f);
	m_ppObjects[m_nObjects - 3]->Rotate(0.0f, 180.0f, 0.0f);
	m_ppObjects[m_nObjects - 3]->SetColor(XMFLOAT3(0.25f, 0.75f, 0.65f));

	m_ppObjects[m_nObjects - 2] = new CGameObject();
	m_ppObjects[m_nObjects - 2]->SetMesh(pUfoMesh);
	m_ppObjects[m_nObjects - 2]->SetShader(pShader);
	m_ppObjects[m_nObjects - 2]->SetPosition(-25.0f, 31.0f, 20.0f);
	m_ppObjects[m_nObjects - 2]->Rotate(0.0f, 180.0f, 0.0f);
	m_ppObjects[m_nObjects - 2]->SetColor(XMFLOAT3(0.25f, 0.75f, 0.65f));

	//Cube
	CMesh* pCubeMesh = new CMesh(pd3dDevice, pd3dCommandList, "Models/Cube.txt");

	for (int i = m_nObjects - 1; i < m_nObjects + mBulletCount; i++) {
		m_ppObjects[i] = new CGameObject();
		m_ppObjects[i]->bBulletcheck = true;
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(XMFLOAT3(1.0f, 0.0f, 0.0f));
		m_ppObjects[i]->SetPosition(0.0f, -1000000.0f, 0.0f);
	}

	for (int i = m_nObjects + mBulletCount - 1; i < m_nObjects + mBulletCount + iParticleCube; i++) {
		m_ppObjects[i] = new CGameObject();
		m_ppObjects[i]->bParticlecheck = true;
		m_ppObjects[i]->iParticleNum = i - m_nObjects - mBulletCount + 1;
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(XMFLOAT3(1.0f, 1.0f, 0.0f));
		m_ppObjects[i]->SetPosition(0.0f, -100000.0f, 0.0f);
	}
}

void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	LoadSceneObjectsFromFile(pd3dDevice, pd3dCommandList, (char *)"Models/Scene.bin");
}

void CScene::BuildBullet(CPlayer& pPlayer, int iChooseBullet)
{
	m_ppObjects[m_nObjects + iChooseBullet]->SetPosition(pPlayer.GetPosition());
	m_ppObjects[m_nObjects + iChooseBullet]->m_xmf4x4World = pPlayer.m_xmf4x4World;		//플레이어의 벡터 복사 -> 날아가는 방향 조절
	
	m_ppObjects[m_nObjects + iChooseBullet]->m_xmf3BulletLook = pPlayer.GetLookVector();
	m_ppObjects[m_nObjects + iChooseBullet]->m_xmf3BulletUp = pPlayer.GetUpVector();
	m_ppObjects[m_nObjects + iChooseBullet]->m_xmf3BulletRight = pPlayer.GetRightVector();
	m_ppObjects[m_nObjects + iChooseBullet]->bShootcheck = true;
}

ID3D12RootSignature *CScene::CreateGraphicsRootSignature(ID3D12Device *pd3dDevice)
{
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;

	D3D12_ROOT_PARAMETER pd3dRootParameters[3];
	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[0].Constants.Num32BitValues = 4; //Time, ElapsedTime, xCursor, yCursor
	pd3dRootParameters[0].Constants.ShaderRegister = 0; //Time
	pd3dRootParameters[0].Constants.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 19; //16 + 3
	pd3dRootParameters[1].Constants.ShaderRegister = 1; //World
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[2].Constants.Num32BitValues = 35; //16 + 16 + 3
	pd3dRootParameters[2].Constants.ShaderRegister = 2; //Camera
	pd3dRootParameters[2].Constants.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void **)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) delete m_ppObjects[j];
		delete[] m_ppObjects;
	}
}

void CScene::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::ProcessInput()
{
	return(false);
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	for (int j = m_nObjects - m_nEnemyObjects - 1; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
		//if (m_ppObjects[j]->fEnemyRestart < 0) {
		//	m_ppObjects[j]->SetPosition(XMFLOAT3((float)(rand() % 50 + 40), (float)(rand() % 20 + 20), (float)(rand() % 120 + 50)));
		//}
		//else if(m_ppObjects[j]->fEnemyRestart > 0){
		//	m_ppObjects[j]->fEnemyRestart--;
		//}
	}
	for (int j = m_nObjects - m_nEnemyObjects - 1; j < m_nObjects - 1; j++)
	{
		if (m_ppObjects[j]) {
			m_ppObjects[j]->MoveRandom();
			m_ppObjects[j]->aabb = BoundingBox(m_ppObjects[j]->GetPosition(), XMFLOAT3(3.0f, 2.0f, 3.0f));
		}
		
	}
	for (int i = m_nObjects - 1; i < m_nObjects + mBulletCount; i++)
	{
		m_ppObjects[i]->Animate(fTimeElapsed);
		m_ppObjects[i]->aabb = BoundingBox(m_ppObjects[i]->GetPosition(), XMFLOAT3(1.0f, 1.0f, 1.0f));
	}

	for (int i = m_nObjects + mBulletCount - 1; i < m_nObjects + mBulletCount + iParticleCube; i++)
	{
		m_ppObjects[i]->Animate(fTimeElapsed);
	}
	
	for (int i = m_nObjects - 1; i < m_nObjects + mBulletCount; i++) {
		if (m_ppObjects[i]->bShootcheck == true) {
			for (int j = m_nObjects - m_nEnemyObjects - 1; j < m_nObjects - 1; j++) {
				if (m_ppObjects[i]->aabb.Intersects(m_ppObjects[j]->aabb)) {
					//총알 소멸
					m_ppObjects[i]->SetPosition(0.0f, -1000000.0f, 0.0f);
					m_ppObjects[i]->bShootcheck = false;

					//파티클
					for (int k = m_nObjects + mBulletCount - 1; k < m_nObjects + mBulletCount + iParticleCube; k++) {
						m_ppObjects[k]->SetPosition(m_ppObjects[j]->GetPosition());
						m_ppObjects[k]->fSplashTime = 500;
					}

					//적 소멸
					m_ppObjects[j]->SetPosition(0.0f, 1000000.0f, 0.0f);
					m_ppObjects[j]->fEnemyRestart = 1000;

					break;
				}
			}
		}
	}
}

void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	for (int j = 0; j < m_nObjects + mBulletCount + iParticleCube; j++)
	{
		if (m_ppObjects[j]) m_ppObjects[j]->Render(pd3dCommandList, pCamera);
	}
}

