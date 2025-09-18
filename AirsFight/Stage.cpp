//==========================================================
// Stage.cpp
// Auther : 桜井 博之
// Data   : 2002/01/14
//==========================================================

#include "Stage.h"

//----------------------------------------------
//	Name:	CStage
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8	d3dDevice
//	Out:	なし
//----------------------------------------------
CStage::CStage(LPDIRECT3DDEVICE8 d3dDevice)
{
	m_pd3dDevice = d3dDevice;

	/* メッシュの作成 */
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

	/* ブロック数の設定 */
	m_nBlockNum = 17;

	/* ブロックタイプの作成 */

	/* 下にある４つの大きなブロック */
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

	/* 下のブロックの上にある、少し小さなブロック */
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

	/* 少し小さなブロックをつなぐ橋 */
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

	/* 空中に浮いている小さなブロック */
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

	/* 壁タイプ数の設定 */
	m_nWallNum = 1;

	/* ウォールタイプの作成 */

	/* 全体を囲う壁 */
	m_pWall[0]	= new CBlockA(m_pd3dDevice);
	m_pWall[0]->LoadMesh(m_pMeshObject[0]);
	m_pWall[0]->InitMatrix(D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 0,0,0);

	for(i=m_nWallNum; i<32; i++)
		m_pWall[i] = NULL;
}

//----------------------------------------------
//	Name:	~CStage
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CStage::~CStage()
{
	int i;
	/* メッシュデータの開放 */
	for(i=0; i<10; i++)
		SAFE_DELETE(m_pMeshObject[i]);

	/* パーツデータの開放 */
	for(i=0; i<32; i++)
	{
		SAFE_DELETE(m_pBlock[i]);
		SAFE_DELETE(m_pWall[i]);
	}
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CStage::FrameMove()
{
	int i;

	/* そのステージにある全てのオブジェクトを移動 */
	for(i=0; i<m_nBlockNum; i++)
		m_pBlock[i]->FrameMove();

	for(i=0; i<m_nWallNum; i++)
		m_pWall[i]->FrameMove();

}

//----------------------------------------------
//	Name:	Render
//	Func:	画面描画
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CStage::Render()
{
	int i;

	/* そのステージにある全てのオブジェクトを描画 */
	for(i=0; i<m_nBlockNum; i++)
		m_pBlock[i]->Render();

	for(i=0; i<m_nWallNum; i++)
		m_pWall[i]->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	描画用マトリクス更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CStage::UpDate()
{
	int i;

	/* そのステージにある全てのオブジェクトを更新 */
	for(i=0; i<m_nBlockNum; i++)
		m_pBlock[i]->UpDate();

	for(i=0; i<m_nWallNum; i++)
		m_pWall[i]->UpDate();
}
