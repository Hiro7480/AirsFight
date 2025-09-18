//==========================================================
// GameStatus.h
// Auther : 桜井 博之
// Data   : 2002/01/11
//==========================================================

#if !defined(AFX_GAMESTATUS_H__263F63A0_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_)
#define AFX_GAMESTATUS_H__263F63A0_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------
#include "CompatiDX8.h"
#include <d3dx8.h>

//----------------------
//	定数定義
//----------------------
/* 状態変化識別子 */
enum{
	NO_CHANGE,		// 変えない
	CHANGE_TITLE,	// タイトルへ移行
	CHANGE_MENU,	// メニューへ移行
	CHANGE_GAME,	// ゲームへ移行
	CHANGE_ENDING	// エンディングへ移行
};

//----------------------------------------------
//	Name:	GameStatus
//	Func:	ゲームの状態を管理する基底クラス
//----------------------------------------------
class GameStatus  
{
protected:
	LPDIRECT3DDEVICE8	m_pd3dDevice; 	// D3Dデバイス

public:
	virtual int  FrameMove(){return 0;};
	virtual void Render(){};
	virtual void UpDate(){};

	GameStatus(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~GameStatus();
};

#endif // !defined(AFX_GAMESTATUS_H__263F63A0_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_)
