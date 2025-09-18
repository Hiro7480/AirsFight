//==========================================================
// ScrollBG.h
// Auther : 桜井 博之
// Data   : 2002/05/01
//==========================================================

#if !defined(AFX_SCROLLBG_H__F5145635_6BAE_4616_83A7_3F3B4AE64F89__INCLUDED_)
#define AFX_SCROLLBG_H__F5145635_6BAE_4616_83A7_3F3B4AE64F89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------
#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CScrollBG
//	Func:	スクロールする背景の管理
//----------------------------------------------
class CScrollBG : public C2DGraphicObj
{
private:
	LPDIRECT3DTEXTURE8	m_pTexture;		// テクスチャ
	float				m_fHeight;		// テクスチャの高さ
	float				m_fWidth;		// テクスチャの幅

	LPD3DXSPRITE		m_pSprite;		// スプライト

	D3DXVECTOR2			m_vecDir;		// 移動ベクトル

public:
	void	FrameMove();		// 毎フレームの処理
	void	Render();			// 描画処理

	/* アクセス関数 */
	void	SetVecDir(D3DXVECTOR2 vecDir){m_vecDir = vecDir;};	// 移動ベクトルのセット

	CScrollBG(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFileName, float fHeight, float fWidth);
	virtual ~CScrollBG();

};

#endif // !defined(AFX_SCROLLBG_H__F5145635_6BAE_4616_83A7_3F3B4AE64F89__INCLUDED_)
