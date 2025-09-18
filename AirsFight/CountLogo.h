//==========================================================
// CountLogo.h
// Auther : 桜井 博之
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_COUNTLOGO_H__6D215A4F_5EA3_45A9_B975_2B25158689FA__INCLUDED_)
#define AFX_COUNTLOGO_H__6D215A4F_5EA3_45A9_B975_2B25158689FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "ListSprite.h"

//----------------------------------------------
//	Name:	CCountLogo
//	Func:	スタートする時のカウンター
//----------------------------------------------
class CCountLogo : public CListSprite  
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

	CCountLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture);
	virtual ~CCountLogo();

};

#endif // !defined(AFX_COUNTLOGO_H__6D215A4F_5EA3_45A9_B975_2B25158689FA__INCLUDED_)
