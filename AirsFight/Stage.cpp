//==========================================================
// Stage.cpp
// Auther : ���� ���V
// Data   : 2002/01/14
//==========================================================

#include "Stage.h"

//----------------------------------------------
//	Name:	CStage
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8	d3dDevice
//	Out:	�Ȃ�
//----------------------------------------------
CStage::CStage(LPDIRECT3DDEVICE8 d3dDevice)
{
	m_pd3dDevice = d3dDevice;

	/* ���b�V���̍쐬 */
	m_pMeshObject[0] = new CMeshObject(m_pd3dDevice);
	m_pMeshObject[0]->Create("Data\\Stage\\Wall.x");
	m_pMeshObject[0]->RestoreDeviceObjects();

	m_pMeshObject[1] = new CMeshObject(m_pd3dDevice);
	m_pMeshObject[1]->Create("Data\\Stage\\Block.x");
	m_pMeshObject[1]->RestoreDeviceObjects();

	m_pMeshObject[2] = new CMeshObject(m_pd3dDevice);
	m_pMeshObject[2]->Create("data\\Stage\\Bridge.x");
	m_pMeshObject[2]->RestoreDeviceObjects();

	m_pMeshObject[3] = new CMeshObject(m_pd3dDevice);
	m_pMeshObject[3]->Create("data\\Stage\\Block2.x");
	m_pMeshObject[3]->RestoreDeviceObjects();

	m_pMeshObject[4] = new CMeshObject(m_pd3dDevice);
	m_pMeshObject[4]->Create("data\\Stage\\Block3.x");
	m_pMeshObject[4]->RestoreDeviceObjects();

	int i;
	for(i=5; i<10; i++)		m_pMeshObject[i] = NULL;

	/* �u���b�N���̐ݒ� */
	m_nBlockNum = 17;

	/* �u���b�N�^�C�v�̍쐬 */

	/* ���ɂ���S�̑傫�ȃu���b�N */
	m_pBlock[0] = new CBlockA(m_pd3dDevice);
	m_pBlock[0]->LoadMesh(m_pMeshObject[1]);
	m_pBlock[0]->InitMatrix(D3DXVECTOR3(-100.0f,-100.0f,-100.0f), 90,0,0);

	m_pBlock[1] = new CBlockA(m_pd3dDevice);
	m_pBlock[1]->LoadMesh(m_pMeshObject[1]);
	m_pBlock[1]->InitMatrix(D3DXVECTOR3( 100.0f,-100.0f,-100.0f), 0,0,0);

	m_pBlock[2] = new CBlockA(m_pd3dDevice);
	m_pBlock[2]->LoadMesh(m_pMeshObject[1]);
	m_pBlock[2]->InitMatrix(D3DXVECTOR3(-100.0f,-100.0f, 100.0f), 180,0,0);

	m_pBlock[3] = new CBlockA(m_pd3dDevice);
	m_pBlock[3]->LoadMesh(m_pMeshObject[1]);
	m_pBlock[3]->InitMatrix(D3DXVECTOR3( 100.0f,-100.0f, 100.0f), 270,0,0);

	/* ���̃u���b�N�̏�ɂ���A���������ȃu���b�N */
	m_pBlock[4] = new CBlockA(m_pd3dDevice);
	m_pBlock[4]->LoadMesh(m_pMeshObject[3]);
	m_pBlock[4]->InitMatrix(D3DXVECTOR3(-100.0f,-50.0f,-100.0f), 90,0,0);

	m_pBlock[5] = new CBlockA(m_pd3dDevice);
	m_pBlock[5]->LoadMesh(m_pMeshObject[3]);
	m_pBlock[5]->InitMatrix(D3DXVECTOR3( 100.0f,-50.0f,-100.0f), 0,0,0);

	m_pBlock[6] = new CBlockA(m_pd3dDevice);
	m_pBlock[6]->LoadMesh(m_pMeshObject[3]);
	m_pBlock[6]->InitMatrix(D3DXVECTOR3(-100.0f,-50.0f, 100.0f), 180,0,0);

	m_pBlock[7] = new CBlockA(m_pd3dDevice);
	m_pBlock[7]->LoadMesh(m_pMeshObject[3]);
	m_pBlock[7]->InitMatrix(D3DXVECTOR3( 100.0f,-50.0f, 100.0f), 270,0,0);

	/* ���������ȃu���b�N���Ȃ��� */
	m_pBlock[8] = new CBlockA(m_pd3dDevice);
	m_pBlock[8]->LoadMesh(m_pMeshObject[2]);
	m_pBlock[8]->InitMatrix(D3DXVECTOR3( 100.0f,-40.0f, 0.0f), 0,0,0);

	m_pBlock[9] = new CBlockA(m_pd3dDevice);
	m_pBlock[9]->LoadMesh(m_pMeshObject[2]);
	m_pBlock[9]->InitMatrix(D3DXVECTOR3( -100.0f,-40.0f, 0.0f), 0,0,0);

	m_pBlock[10] = new CBlockA(m_pd3dDevice);
	m_pBlock[10]->LoadMesh(m_pMeshObject[2]);
	m_pBlock[10]->InitMatrix(D3DXVECTOR3( 0.0f,-40.0f, 100.0f), 90,0,0);

	m_pBlock[11] = new CBlockA(m_pd3dDevice);
	m_pBlock[11]->LoadMesh(m_pMeshObject[2]);
	m_pBlock[11]->InitMatrix(D3DXVECTOR3( 0.0f,-40.0f, -100.0f), 90,0,0);

	/* �󒆂ɕ����Ă��鏬���ȃu���b�N */
	m_pBlock[12] = new CBlockA(m_pd3dDevice);
	m_pBlock[12]->LoadMesh(m_pMeshObject[4]);
	m_pBlock[12]->InitMatrix(D3DXVECTOR3( 0.0f,-20.0f, 0.0f), 90,0,0);

	m_pBlock[13] = new CBlockA(m_pd3dDevice);
	m_pBlock[13]->LoadMesh(m_pMeshObject[4]);
	m_pBlock[13]->InitMatrix(D3DXVECTOR3( 120.0f,30.0f, 120.0f), 270,0,0);

	m_pBlock[14] = new CBlockA(m_pd3dDevice);
	m_pBlock[14]->LoadMesh(m_pMeshObject[4]);
	m_pBlock[14]->InitMatrix(D3DXVECTOR3( -120.0f,30.0f, 120.0f), 270,0,0);

	m_pBlock[15] = new CBlockA(m_pd3dDevice);
	m_pBlock[15]->LoadMesh(m_pMeshObject[4]);
	m_pBlock[15]->InitMatrix(D3DXVECTOR3( 120.0f,30.0f, -120.0f), 270,0,0);

	m_pBlock[16] = new CBlockA(m_pd3dDevice);
	m_pBlock[16]->LoadMesh(m_pMeshObject[4]);
	m_pBlock[16]->InitMatrix(D3DXVECTOR3( -120.0f,30.0f, -120.0f), 270,0,0);

	for(i=m_nBlockNum; i<32; i++)
		m_pBlock[i] = NULL;

	/* �ǃ^�C�v���̐ݒ� */
	m_nWallNum = 1;

	/* �E�H�[���^�C�v�̍쐬 */

	/* �S�̂��͂��� */
	m_pWall[0]	= new CBlockA(m_pd3dDevice);
	m_pWall[0]->LoadMesh(m_pMeshObject[0]);
	m_pWall[0]->InitMatrix(D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 0,0,0);

	for(i=m_nWallNum; i<32; i++)
		m_pWall[i] = NULL;
}

//----------------------------------------------
//	Name:	~CStage
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CStage::~CStage()
{
	int i;
	/* ���b�V���f�[�^�̊J�� */
	for(i=0; i<10; i++)
		SAFE_DELETE(m_pMeshObject[i]);

	/* �p�[�c�f�[�^�̊J�� */
	for(i=0; i<32; i++)
	{
		SAFE_DELETE(m_pBlock[i]);
		SAFE_DELETE(m_pWall[i]);
	}
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CStage::FrameMove()
{
	int i;

	/* ���̃X�e�[�W�ɂ���S�ẴI�u�W�F�N�g���ړ� */
	for(i=0; i<m_nBlockNum; i++)
		m_pBlock[i]->FrameMove();

	for(i=0; i<m_nWallNum; i++)
		m_pWall[i]->FrameMove();

}

//----------------------------------------------
//	Name:	Render
//	Func:	��ʕ`��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CStage::Render()
{
	int i;

	/* ���̃X�e�[�W�ɂ���S�ẴI�u�W�F�N�g��`�� */
	for(i=0; i<m_nBlockNum; i++)
		m_pBlock[i]->Render();

	for(i=0; i<m_nWallNum; i++)
		m_pWall[i]->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�`��p�}�g���N�X�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CStage::UpDate()
{
	int i;

	/* ���̃X�e�[�W�ɂ���S�ẴI�u�W�F�N�g���X�V */
	for(i=0; i<m_nBlockNum; i++)
		m_pBlock[i]->UpDate();

	for(i=0; i<m_nWallNum; i++)
		m_pWall[i]->UpDate();
}
