//==========================================================
// D3DMain.h
// Auther : 桜井 博之
// Data   : 2000/12/28
//==========================================================

#if !defined(AFX_D3DMAIN_H__FD26F1E7_215F_48A0_BE96_CA83FB10441A__INCLUDED_)
#define AFX_D3DMAIN_H__FD26F1E7_215F_48A0_BE96_CA83FB10441A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------


#include "CompatiDX8.h"
#include <d3dx8.h>
#include <stdio.h>
#include "resource.h"
#include "define.h"





//----------------------
//	定数定義
//----------------------
#define	STYLE_FULLSCREEN	(WS_POPUP | WS_VISIBLE)
#define	STYLE_WINDOW		((WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU)&~(WS_MAXIMIZEBOX | WS_THICKFRAME))
#define	FLAME_RATE			(16)						// ゲームスピード (秒間60フレーム)
#define RENDER_FLAME_RATE	(16)		
#define	SCREEN_WIDTH		640								// 画面横幅
#define	SCREEN_HEIGHT		480								// 画面縦幅

// {DC132EF5-D673-4021-A72E-041FCA2BF28B}
static const GUID c_guidDXGame = 
{ 0xdc132ef5, 0xd673, 0x4021, { 0xa7, 0x2e, 0x4, 0x1f, 0xca, 0x2b, 0xf2, 0x8b } };

#define MAX_NAME_SESSION		64		// セクション名最大文字数
#define MAX_NAME_PLAYER			64		// プレイヤー名最大文字数
#define MAX_NAME_IP_ADDRESS		15		// ＩＰアドレス名最大文字数
#define INPUT_STRING_MIN		3		// 最低入力文字数

#define MAX_PLAYER				4		//	最大同時接続人数

//----------------------------------------------------------
//		データ送信用構造体
//----------------------------------------------------------
/* チャットメッセージ送信用 */
struct TChat{
	DWORD dwDpnType;		// メッセージタイプ
	char  str[256];			// チャットメッセージ
};

/* 開始信号送信用 意味ないし */
struct TStart{
	DWORD	dwDpnType;		// メッセージタイプ
};

/* 識別番号送信用 */
struct TID{
	DWORD	dwDpnType;		// メッセージタイプ
	//DPNID	dpnID;			// ＩＤ（名前）
	int		nIDNum;			// 連番番号
};

//----------------------------------------------------------
//	Name	: CD3DMain
//	Func	: DirectXを作成する際のベースとなるクラス
//----------------------------------------------------------
class CD3DMain
{
private:
	TCHAR		szTitle[64];			// ウィンドウのタイトルバー テキスト
	TCHAR		szWindowClass[64];		// ウィンドウクラス名
	int			m_nWndWidth;			// ウィンドウの幅サイズ
	int			m_nWndHeight;			// ウィンドウの高さサイズ

	HINSTANCE	m_hInst;				// 現在のインスタンス
	HWND		m_hWnd;					// メインウィンドウのハンドル
	bool		m_bWindowMode;			// TRUE:ウインドウ	FALSE:フルスクリーン

	bool		m_bAppActive;			// ウィンドウがアクティブかどうか
	bool		m_bFpsFlg;				// FPSの表示フラグ
	bool		m_bEndFlg;				// アプリケーションの終了フラグ（動いてる間はfalse）

	DWORD		m_dwThreadID;			// スレッドのＩＤ
	HANDLE		m_hThread;				// スレッドのハンドル
	bool		m_bThread;				// スレッドを行うかどうかのフラグ

	float		m_fFrameFps;			// 処理スレッドのFPS
	float		m_fRenderFps;			// 描画スレッドのFPS
	bool		m_bRenderFlg;			// 描画可能フラグ

	//HWND		m_hDlg;					// チャットダイアログ用ハンドル

	/* プライベートメソッド */
	HRESULT	CleanAppli();				// アプリケーションの後始末
	HRESULT	InitD3D();					// Direct3Dの初期化

protected:

	LPDIRECT3D8 		m_pD3D; 		// D3DDeviceをクリエイトするために使われる
	LPDIRECT3DDEVICE8	m_pd3dDevice; 	// D3Dデバイス
	LPD3DXFONT			m_pd3dXFont;	// デバッグ用フォント

	/* ユーザー情報 */
	//int			m_nPlayerNum;							// プレイヤー識別番号
	//TCHAR		m_strPlayer[MAX_NAME_PLAYER+1];			// プレイヤー名
	//TCHAR		m_strSession[MAX_NAME_PLAYER+1];		// セッション名
	//TCHAR		m_strIPAddress[MAX_NAME_IP_ADDRESS+1];	// ＩＰアドレス

	virtual HRESULT OneTimeInit(void){return S_OK;};	// 一回だけ呼ばれる初期化
	virtual HRESULT FrameMove(void){return S_OK;};		// 毎フレームごとの処理
	virtual HRESULT Render(void){return S_OK;};			// 画面描画
	virtual HRESULT UpDate(void){return S_OK;};			// 描画用情報の更新
	virtual HRESULT CleanUp(void){return S_OK;};		// アプリケーション終了時の処理

public:
	int		Run(void);							// アプリケーションのメインループ
	HRESULT	AllCreate(HINSTANCE hInst);			// 初期化全般
	void	FrameProc();						// 処理用スレッド
	void	RenderProc();						// 描画用スレッド

	/* メインウィンドウのメッセージ処理 */
	LRESULT	MsgProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam);

	CD3DMain();									// コンストラクタ
};

#endif // !defined(AFX_D3DMAIN_H__FD26F1E7_215F_48A0_BE96_CA83FB10441A__INCLUDED_)
