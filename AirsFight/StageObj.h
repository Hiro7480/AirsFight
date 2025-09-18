//==========================================================
// StageObj.h
// Auther : 桜井 博之
// Data   : 2002/04/16
//==========================================================

#if !defined(AFX_StageObj_H__9DD608E0_1C33_4378_95B2_1BD0186E0ECF__INCLUDED_)
#define AFX_StageObj_H__9DD608E0_1C33_4378_95B2_1BD0186E0ECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include <d3dx8.h>
#include "3DGraphicObj.h"
#include "MeshData.h"

//----------------------------------------------
//	Name:	CStageObj
//	Func:	ステージオブジェクトの基底クラス
//----------------------------------------------
class CStageObj:public C3DGraphicObj
{
private:
	CMeshObject*		m_pMeshObject;	// メッシュへのポインタ
	float				m_fLength;		// バウンディングスフィアのサイズ

public:

	virtual	void FrameMove();			// 毎フレームの処理
	virtual void Render();				// 画面描画

	/* 初期化関数 */
	void	LoadMesh(CMeshObject* pMesh);					// メッシュのロード
	void	InitMatrix(D3DXVECTOR3 vecPos,					// マトリクスの初期化
			float fYaw, float fPitch, float fRoll);

	/* アクセス関数 */
	CMeshObject*	GetMesh(){return m_pMeshObject;};	// メッシュを返す
	float			GetLength(){return m_fLength;};		// オブジェクトサイズを返す

	CStageObj(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CStageObj();
};

#endif // !defined(AFX_StageObj_H__9DD608E0_1C33_4378_95B2_1BD0186E0ECF__INCLUDED_)
