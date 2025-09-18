//==========================================================
// Title.h
// Auther : 桜井 博之
// Data   : 2002/01/11
//==========================================================

#if !defined(AFX_TITLE_H__263F63A1_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_)
#define AFX_TITLE_H__263F63A1_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------
//	インクルード
//--------------------------
#include "GameStatus.h"

#include "Sprite.h"
#include "ScrollBG.h"

//----------------------------------------------
//	Name:	CTitle
//	Func:	タイトル時の管理
//----------------------------------------------
class CTitle : public GameStatus  
{
private:
	CSprite*		m_pTitleLogo;	// タイトルロゴ
	CSprite*		m_pPressEnter;	// エンター押せ
	CSprite*		m_pTitleChara;	// キャラクタ	
	CScrollBG*		m_pBackGround;	// タイトル背景

public:
	int  FrameMove();			// フレーム毎の処理
	void Render();				// 画面描画処理
	void UpDate();				// データ更新

	CTitle(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CTitle();
};

#endif // !defined(AFX_TITLE_H__263F63A1_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_)
