//==========================================================
// Stage.h
// Auther : 桜井 博之
// Data   : 2002/01/14
//==========================================================

#if !defined(AFX_STAGE_H__7D0F984D_3093_434A_90B1_4101C9D48CF9__INCLUDED_)
#define AFX_STAGE_H__7D0F984D_3093_434A_90B1_4101C9D48CF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include <d3dx8.h>
#include "StageObj.h"
#include "BlockA.h"

//----------------------------------------------
//	Name:	CStage
//	Func:	ステージのオブジェクトの管理
//----------------------------------------------
class CStage
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3Dデバイス
	char			m_cStageName[256];	// ステージの名前

	CStageObj*		m_pBlock[32];		// ブロックタイプ
	int				m_nBlockNum;		// ブロックタイプの数

	CStageObj*		m_pWall[32];		// 壁タイプ
	int				m_nWallNum;			// 壁タイプの数

	CMeshObject*	m_pMeshObject[10];	// メッシュ

public:
	void FrameMove();					// オブジェクトの移動等
	void Render();						// 画面描画
	void UpDate();						// 描画用マトリクスの更新

	/* アクセス関数 */
	CStageObj*		GetBlockObj(int n){return m_pBlock[n];};// ブロックのメッシュを返す
	CStageObj*		GetWallObj(int n){return m_pWall[n];};	// 壁のメッシュを返す

	int				GetBlockNum(){return m_nBlockNum;};	// ブロック数を返す
	int				GetWallNum(){return m_nWallNum;};	// ウォール数を返す


	CStage(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CStage();
};

#endif // !defined(AFX_STAGE_H__7D0F984D_3093_434A_90B1_4101C9D48CF9__INCLUDED_)
