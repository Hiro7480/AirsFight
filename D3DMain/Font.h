//==========================================================
// Font.h
// Auther : 桜井 博之
// Data   : 2002/05/06
//==========================================================

#if !defined(AFX_FONT_H__9506607E_7BFE_4882_BCFB_B2050C777F33__INCLUDED_)
#define AFX_FONT_H__9506607E_7BFE_4882_BCFB_B2050C777F33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------
#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CFont
//	Func:	文字の描画を管理する
//----------------------------------------------
class CFont : public C2DGraphicObj  
{
private:
	LPD3DXFONT		m_pFont;	// フォント
	TCHAR			m_str[256];	// 描画文字列
	DWORD			m_dwFormat;	// 描画オプション

	unsigned char	m_cRed;		// 赤色の値（0～255）
	unsigned char	m_cGreen;	// 緑色の値（0～255）
	unsigned char	m_cBlue;	// 青色の値（0～255）

public:

	void	Render();			// 描画処理

	/* アクセス関数 */
	void SetString(TCHAR* str);						// 文字列のセット
	void SetString(int nNum);	
	void SetFormat(DWORD dwFormat);					// 描画オプションのセット

	void SetColor(unsigned char cRed, unsigned char cGreen, unsigned char cBlue);	// 色のセット

	CFont(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFontName, int nSize=0);
	virtual ~CFont();
};

//----------------------------------------------
//	Name:	SetString
//	Func:	描画文字列のセット
//	in:		TCHAR* str = 指定文字列
//	out:	なし
//----------------------------------------------
inline void CFont::SetString(TCHAR* str)
{
	//strcpy(m_str, str);
	_tcscpy_s(m_str, _countof(m_str), str);
}

//----------------------------------------------
//	Name:	SetString
//	Func:	描画文字列のセット
//	in:		int	nNum = 指定数値
//	out:	なし
//----------------------------------------------
inline void CFont::SetString(int nNum)
{
	wsprintf(m_str, "%d", nNum);
}

//----------------------------------------------
//	Name:	SetFormat
//	Func:	描画フォーマットのセット
//	in:		DWORD dwFormat = 描画フォーマット
//	out:	なし
//----------------------------------------------
inline void CFont::SetFormat(DWORD dwFormat)
{
	m_dwFormat = dwFormat;
}

//----------------------------------------------
//	Name:	SetColor
//	Func:	文字の色をセットする
//	in:		unsigned char cRed = 赤色
//			unsigned char cRed = 赤色
//			unsigned char cRed = 赤色
//	out:	なし
//----------------------------------------------
inline void CFont::SetColor(unsigned char cRed, unsigned char cGreen, unsigned char cBlue)
{
	m_cRed	 = cRed;
	m_cGreen = cGreen;
	m_cBlue	 = cBlue;
}



#endif // !defined(AFX_FONT_H__9506607E_7BFE_4882_BCFB_B2050C777F33__INCLUDED_)
