//==========================================================
// Title.cpp
// Auther : 桜井 博之
// Data   : 2002/01/11
//==========================================================

#include "Title.h"

//------------------------------------------------------
//	Name:	CTitle
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3Dデバイス
//	Out:	なし
//------------------------------------------------------
CTitle::CTitle(LPDIRECT3DDEVICE8 d3dDevice)
	  :GameStatus(d3dDevice)
{
	/* タイトルロゴの作成 */
	m_pTitleLogo = new CSprite(m_pd3dDevice, const_cast<TCHAR*>("Data\\Title\\TitleLogo.png"));
	m_pTitleLogo->SetVec(D3DXVECTOR2(64, 50));
	m_pTitleLogo->SetRec(0, 0, 480, 200);

	/* エンター押せの作成 */
	m_pPressEnter = new CSprite(m_pd3dDevice, const_cast<TCHAR*>("Data\\Title\\PressEnter.png"));
	m_pPressEnter->SetVec(D3DXVECTOR2(192, 350));
	m_pPressEnter->SetRec(0, 0, 256, 64);

	/* タイトルキャラクタの作成 */
	m_pTitleChara = new CSprite(m_pd3dDevice, const_cast<TCHAR*>("Data\\Title\\TitleChara.png"));
	m_pTitleChara->SetVec(D3DXVECTOR2(380, 0));
	m_pTitleChara->SetRec(0, 0, 256, 512);

	/* タイトル背景の作成 */
	m_pBackGround = new CScrollBG(m_pd3dDevice, const_cast<TCHAR*>("data\\Title\\TitleBG.png"), 512, 512);
	m_pBackGround->SetVecDir(D3DXVECTOR2(1.0, 1.0));

}
//----------------------------------------------
//	Name:	~CTitle
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CTitle::~CTitle()
{
	/* 使用したメモリの開放 */
	SAFE_DELETE(m_pTitleLogo);
	SAFE_DELETE(m_pPressEnter);
	SAFE_DELETE(m_pTitleChara);
	SAFE_DELETE(m_pBackGround);
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	Out:	なし
//	In:		int = 状態変更識別子
//----------------------------------------------
int CTitle::FrameMove()
{
	/* タイトルロゴ */
	m_pTitleLogo->FrameMove();

	/* エンター押せ */
	m_pPressEnter->FrameMove();

	/* タイトルキャラ */
	m_pTitleChara->FrameMove();

	/* タイトル背景 */
	m_pBackGround->FrameMove();

	/* リターンを押したらメニューへ移行する */
	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
		return CHANGE_MENU;

	return NO_CHANGE;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	Out:	なし
//	In:		なし
//----------------------------------------------
void CTitle::Render()
{
	/* タイトル背景 */
	m_pBackGround->Render();

	/* タイトルキャラ */
	m_pTitleChara->Render();

	/* エンター押せ */
	m_pPressEnter->Render();

	/* タイトルロゴ */
	m_pTitleLogo->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	Out:	なし
//	In:		なし
//----------------------------------------------
void CTitle::UpDate()
{
	/* タイトル背景 */
	m_pBackGround->UpDate();

	/* タイトルキャラ */
	m_pTitleChara->UpDate();

	/* エンター押せ */
	m_pPressEnter->UpDate();

	/* タイトルロゴ */
	m_pTitleLogo->UpDate();
}
