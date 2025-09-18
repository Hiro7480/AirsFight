//==========================================================
// StartLogo.h
// Auther : 桜井 博之
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_STARTLOGO_H__91137AFF_C667_4333_BB83_7F7862D57966__INCLUDED_)
#define AFX_STARTLOGO_H__91137AFF_C667_4333_BB83_7F7862D57966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "CompatiDX8.h"
#include "ListSprite.h"

//----------------------------------------------
//	Name:	CStartLogo
//	Func:	スタートする時のロゴ
//----------------------------------------------
class CStartLogo : public CListSprite  
{
private:
	int		m_nAnimeCnt;		// アニメカウンター

	int		m_nAlphaBase;		// 処理用透明値
	int		m_nAlphaStock;		// 描画用透明値

	float	m_fScaleBase;		// 処理用スケール値
	float	m_fScaleStock;		// 描画用スケール値

public:
	void	FrameMove();					// 毎フレームの処理
	void	Render(LPD3DXSPRITE pSprite);	// 描画処理
	void	UpDate();						// データ更新

	CStartLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture);
	virtual ~CStartLogo();

};

#endif // !defined(AFX_STARTLOGO_H__91137AFF_C667_4333_BB83_7F7862D57966__INCLUDED_)
