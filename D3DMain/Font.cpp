//==========================================================
// Font.cpp
// Auther : ���� ���V
// Data   : 2002/05/06
//==========================================================
#include "Font.h"

//------------------------------------------------------------------
//	Name:	CFont
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice		= D3D�f�o�C�X
//			TCHAR*			  strFontName	= �t�H���g��
//			int				  nSize			= �t�H���g�T�C�Y
//	Out:	�Ȃ�
//------------------------------------------------------------------
CFont::CFont(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFontName, int nSize)
	  :C2DGraphicObj(d3dDevice) 
{
	/* �ꎞ�I�Ɏg���t�H���g�̍쐬 */
	HFONT hFontTmp;
	hFontTmp = CreateFont(	nSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET,
							OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
							DEFAULT_PITCH, strFontName);

	/* �t�H���g�̍쐬 */
	D3DXCreateFont(m_pd3dDevice, hFontTmp, &m_pFont);

	/* �ꎞ�I�ȃt�H���g�̍폜 */
	DeleteObject(hFontTmp);

	/* �`�敶����̏����� */
	//strcpy(m_str, "Default");
	_tcscpy_s(m_str, sizeof(m_str), _T("Default"));

	/* �`��t�H�[�}�b�g�̏����� */
	m_dwFormat = DT_LEFT;

	/* �F�̏����� */
	m_cRed = 255;
	m_cGreen = 255;
	m_cBlue = 255;
}

//------------------------------------------------------------------
//	Name:	~CFont
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------------------
CFont::~CFont()
{
	/* �g�p�����������̉�� */
	SAFE_RELEASE(m_pFont);
}

//------------------------------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------------------
void CFont::Render()
{
	/* �`�� */
	m_pFont->Begin();
	m_pFont->DrawTextA(m_str, -1, &m_rectStock, m_dwFormat, D3DCOLOR_XRGB(m_cRed, m_cGreen, m_cBlue));
	m_pFont->End();
}