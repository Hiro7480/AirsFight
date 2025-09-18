//==========================================================
// Font.h
// Auther : ���� ���V
// Data   : 2002/05/06
//==========================================================

#if !defined(AFX_FONT_H__9506607E_7BFE_4882_BCFB_B2050C777F33__INCLUDED_)
#define AFX_FONT_H__9506607E_7BFE_4882_BCFB_B2050C777F33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CFont
//	Func:	�����̕`����Ǘ�����
//----------------------------------------------
class CFont : public C2DGraphicObj  
{
private:
	LPD3DXFONT		m_pFont;	// �t�H���g
	TCHAR			m_str[256];	// �`�敶����
	DWORD			m_dwFormat;	// �`��I�v�V����

	unsigned char	m_cRed;		// �ԐF�̒l�i0�`255�j
	unsigned char	m_cGreen;	// �ΐF�̒l�i0�`255�j
	unsigned char	m_cBlue;	// �F�̒l�i0�`255�j

public:

	void	Render();			// �`�揈��

	/* �A�N�Z�X�֐� */
	void SetString(TCHAR* str);						// ������̃Z�b�g
	void SetString(int nNum);	
	void SetFormat(DWORD dwFormat);					// �`��I�v�V�����̃Z�b�g

	void SetColor(unsigned char cRed, unsigned char cGreen, unsigned char cBlue);	// �F�̃Z�b�g

	CFont(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFontName, int nSize=0);
	virtual ~CFont();
};

//----------------------------------------------
//	Name:	SetString
//	Func:	�`�敶����̃Z�b�g
//	in:		TCHAR* str = �w�蕶����
//	out:	�Ȃ�
//----------------------------------------------
inline void CFont::SetString(TCHAR* str)
{
	//strcpy(m_str, str);
	_tcscpy_s(m_str, _countof(m_str), str);
}

//----------------------------------------------
//	Name:	SetString
//	Func:	�`�敶����̃Z�b�g
//	in:		int	nNum = �w�萔�l
//	out:	�Ȃ�
//----------------------------------------------
inline void CFont::SetString(int nNum)
{
	wsprintf(m_str, "%d", nNum);
}

//----------------------------------------------
//	Name:	SetFormat
//	Func:	�`��t�H�[�}�b�g�̃Z�b�g
//	in:		DWORD dwFormat = �`��t�H�[�}�b�g
//	out:	�Ȃ�
//----------------------------------------------
inline void CFont::SetFormat(DWORD dwFormat)
{
	m_dwFormat = dwFormat;
}

//----------------------------------------------
//	Name:	SetColor
//	Func:	�����̐F���Z�b�g����
//	in:		unsigned char cRed = �ԐF
//			unsigned char cRed = �ԐF
//			unsigned char cRed = �ԐF
//	out:	�Ȃ�
//----------------------------------------------
inline void CFont::SetColor(unsigned char cRed, unsigned char cGreen, unsigned char cBlue)
{
	m_cRed	 = cRed;
	m_cGreen = cGreen;
	m_cBlue	 = cBlue;
}



#endif // !defined(AFX_FONT_H__9506607E_7BFE_4882_BCFB_B2050C777F33__INCLUDED_)
