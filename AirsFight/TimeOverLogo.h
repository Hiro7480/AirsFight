//==========================================================
// TimeOverLogo.h
// Auther : 桜井 博之
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_TIMEOVERLOGO_H__4018A837_4748_4EBB_AFD4_EBE6B0E68DE8__INCLUDED_)
#define AFX_TIMEOVERLOGO_H__4018A837_4748_4EBB_AFD4_EBE6B0E68DE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "ListSprite.h"

//----------------------------------------------
//	Name:	CTimeOverLogo
//	Func:	スタートする時のロゴ
//----------------------------------------------
class CTimeOverLogo : public CListSprite  
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

	CTimeOverLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture);
	virtual ~CTimeOverLogo();

};

#endif // !defined(AFX_TIMEOVERLOGO_H__4018A837_4748_4EBB_AFD4_EBE6B0E68DE8__INCLUDED_)
