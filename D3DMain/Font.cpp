//==========================================================
// Font.cpp
// Auther : 桜井 博之
// Data   : 2002/05/06
//==========================================================
#include "Font.h"

//------------------------------------------------------------------
//	Name:	CFont
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice		= D3Dデバイス
//			TCHAR*			  strFontName	= フォント名
//			int				  nSize			= フォントサイズ
//	Out:	なし
//------------------------------------------------------------------
CFont::CFont(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFontName, int nSize)
	  :C2DGraphicObj(d3dDevice) 
{
	/* 一時的に使うフォントの作成 */
	HFONT hFontTmp;
	hFontTmp = CreateFont(	nSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET,
							OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
							DEFAULT_PITCH, strFontName);

	/* フォントの作成 */
	D3DXCreateFont(m_pd3dDevice, hFontTmp, &m_pFont);

	/* 一時的なフォントの削除 */
	DeleteObject(hFontTmp);

	/* 描画文字列の初期化 */
	//strcpy(m_str, "Default");
	_tcscpy_s(m_str, sizeof(m_str), _T("Default"));

	/* 描画フォーマットの初期化 */
	m_dwFormat = DT_LEFT;

	/* 色の初期化 */
	m_cRed = 255;
	m_cGreen = 255;
	m_cBlue = 255;
}

//------------------------------------------------------------------
//	Name:	~CFont
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//------------------------------------------------------------------
CFont::~CFont()
{
	/* 使用したメモリの解放 */
	SAFE_RELEASE(m_pFont);
}

//------------------------------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//------------------------------------------------------------------
void CFont::Render()
{
	/* 描画 */
	m_pFont->Begin();
	m_pFont->DrawTextA(m_str, -1, &m_rectStock, m_dwFormat, D3DCOLOR_XRGB(m_cRed, m_cGreen, m_cBlue));
	m_pFont->End();
}