//==========================================================
// StageObj.cpp
// Auther : 桜井 博之
// Data   : 2002/04/16
//==========================================================

#include "StageObj.h"

//----------------------------------------------
//	Name:	CStageObj
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3Dデバイス
//	Out:	なし
//----------------------------------------------
CStageObj::CStageObj(LPDIRECT3DDEVICE8 d3dDevice)
		  :C3DGraphicObj(d3dDevice)
{
	m_pMeshObject = NULL;
	m_fLength = 0;
}

//----------------------------------------------
//	Name:	~CStageObj
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CStageObj::~CStageObj()
{

}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CStageObj::FrameMove()
{

}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CStageObj::Render()
{
	/* メッシュの描画 */
	m_pMeshObject->Render();
}

//--------------------------------------------------
//	Name:	InitMatrix
//	Func:	マトリクスの初期化
//	in:		D3DXVECTOR3	vecIn	= オブジェクトの位置
//			float		fYaw	= Yaw回転角度
//			float		fPitch	= Pitch回転角度
//			float		fRoll	= Roll回転角度
//	Out:	なし
//--------------------------------------------------
void CStageObj::InitMatrix(D3DXVECTOR3 vecPos,
				float fYaw, float fPitch, float fRoll)
{
	D3DXMATRIX matTmp;

	/* 指定した回転角に回転させる */
	D3DXMatrixRotationYawPitchRoll(&matTmp, 
		D3DXToRadian(fYaw), D3DXToRadian(fPitch), D3DXToRadian(fRoll));

	/* 指定した座標値に平行移動させる */
	matTmp._41 = vecPos.x;
	matTmp._42 = vecPos.y;
	matTmp._43 = vecPos.z;

	/* マトリクスのセット */
	m_matBase = matTmp;
}

//--------------------------------------------------
//	Name:	LoadMesh
//	Func:	メッシュの読み込み
//	in:		CMeshObjcet* pMesh	 = メッシュポインタ
//			float		 fLength = オブジェクトサイズ
//	Out:	なし
//--------------------------------------------------
void CStageObj::LoadMesh(CMeshObject* pMesh)
{
	m_pMeshObject = pMesh;
	m_fLength = m_pMeshObject->GetLength();
}
