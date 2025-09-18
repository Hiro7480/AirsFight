//==========================================================
// OrderSprite.h
// Auther : 桜井 博之
// Data   : 2002/05/20
//==========================================================

#if !defined(AFX_ORDERSPRITE_H__C1694154_9DD2_4D55_B76A_1DE5550F410B__INCLUDED_)
#define AFX_ORDERSPRITE_H__C1694154_9DD2_4D55_B76A_1DE5550F410B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "CompatiDX8.h"
#include "Sprite.h"
#include "Font.h"

//----------------------------------------------
//	Name:	COrderSprite
//	Func:	順位を表示するクラス
//----------------------------------------------
class COrderSprite  
{
private:
	CSprite*	m_pFormat;	// 順位フォーマット
	CFont*		m_pName;	// 名前フォント
	CFont*		m_pDeadNum;	// 死んだ数フォント

	int			m_nOrder;		// 順位
	TCHAR		m_strName[256];	// 名前
	int			m_nDeadNum;		// 死んだ数

	D3DXVECTOR2	m_vecBase;		// 基本描画位置

public:
	void	FrameMove();	// 毎フレームの処理
	void	Render();		// 描画処理
	void	UpDate();		// データ更新

	COrderSprite(LPDIRECT3DDEVICE8 d3dDevice, int nOrder, TCHAR* strName, int nDeadNum);
	virtual ~COrderSprite();
};

#endif // !defined(AFX_ORDERSPRITE_H__C1694154_9DD2_4D55_B76A_1DE5550F410B__INCLUDED_)
