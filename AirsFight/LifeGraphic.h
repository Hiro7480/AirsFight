//==========================================================
// LifeGraphic.h
// Auther : 桜井 博之
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_LIFEGRAPHIC_H__EF23A023_3B1C_4A88_AB23_EF85E3DA2D01__INCLUDED_)
#define AFX_LIFEGRAPHIC_H__EF23A023_3B1C_4A88_AB23_EF85E3DA2D01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------
//	インクルード
//--------------------------
#include "CompatiDX8.h"
#include "Sprite.h"

//------------------------------------------
//	Name:	CLifeGraphic
//	Func:	ライフを数字で描画
//------------------------------------------
class CLifeGraphic : public CSprite  
{
private:
	int		m_nMaxLife;			// 最大LIFE値
	int		m_nNextLife;		// 目標LIFE値
	int		m_nNowLife;			// 現在LIFE値

	RECT	m_rcBase[4];		// 処理用RECT
	RECT	m_rcStock[4];		// 描画用RECT

	D3DXVECTOR2		m_vecPos;	// 基本描画位置

public:

	void	FrameMove();		// 毎フレームの処理
	void	Render();			// 描画処理
	void	UpDate();			// データ更新

	void	InitLife(int nLife);// ライフの値の初期化

	/* アクセス関数 */
	void SetLife(int nLife){m_nNextLife = nLife;};	// LIFE値のセット

	CLifeGraphic(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName);
	virtual ~CLifeGraphic();
};

#endif // !defined(AFX_LIFEGRAPHIC_H__EF23A023_3B1C_4A88_AB23_EF85E3DA2D01__INCLUDED_)
