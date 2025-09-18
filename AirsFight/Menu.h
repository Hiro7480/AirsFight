//==========================================================
// Menu.h
// Auther : 桜井 博之
// Data   : 2002/05/01
//==========================================================
#if !defined(AFX_MENU_H__EDCC5399_A5D0_40D3_999C_F35246540196__INCLUDED_)
#define AFX_MENU_H__EDCC5399_A5D0_40D3_999C_F35246540196__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "CompatiDX8.h"
#include "GameStatus.h"
#include "Sprite.h"
#include "ScrollBG.h"
#include "Font.h"

#include <time.h>

//------------------------------
//	定数定義
//------------------------------
#define	MAX_CHARA 4

//--------------------------------------------------
//		データ送信用構造体
//--------------------------------------------------
/* 選択しているキャラクタを示す */
struct TSelect{
	DWORD		dwDpnType;		// メッセージタイプ
	int			nChara;			// 指定キャラの添え字
	int			nSelect;		// 選択しているキャラ
	bool		bOK;			// 準備OKかどうか
};

//----------------------------------------------
//	Name:	CMenu
//	Func:	メニュー時の管理
//----------------------------------------------
class CMenu : public GameStatus
{
private:
	/* キャラクタのパラメータを表す */
	struct TParam
	{
		int			nPower;			// パワー
		int			nEnergy;		// エネルギー
		int			nSpeed;			// スピード
	};

	int			m_nSelectChara[4];	// それぞれのプレイヤーが選んでいるキャラクタを示す
	int			m_nMyChara;			// SelectCharaの中の自分の添え字を示す
	bool		m_bOK[4];			// それぞれのプレイヤーの準備完了を示す
	bool		m_bCPUFlg[4];		// コンピュータか否かを示すフラグ

	CSprite*	m_pCharaImage[4];	// キャラクタのイメージ
	CFont*		m_pPlayerName[4];	// プレイヤーの名前
	CSprite*	m_pReady[4];		// OKサインのスプライト

	CSprite*	m_pLogo;			// メニュー時のロゴ
	CScrollBG*	m_pBackGround;		// 背景のタイル
	TParam		m_pParam[MAX_CHARA];// キャラクタパラメータ

public:
	int  FrameMove();			// フレーム毎の処理
	void Render();				// 描画処理
	void UpDate();				// データ更新

	/* アクセス関数 */
	int*		GetSelectChara(){return &m_nSelectChara[0];};
	int			GetSelectChara(int n){return m_nSelectChara[n];};

	CMenu(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CMenu();

};

#endif // !defined(AFX_MENU_H__EDCC5399_A5D0_40D3_999C_F35246540196__INCLUDED_)
