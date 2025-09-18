//==========================================================
// CountLogo.h
// Auther : ���� ���V
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_COUNTLOGO_H__6D215A4F_5EA3_45A9_B975_2B25158689FA__INCLUDED_)
#define AFX_COUNTLOGO_H__6D215A4F_5EA3_45A9_B975_2B25158689FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "ListSprite.h"

//----------------------------------------------
//	Name:	CCountLogo
//	Func:	�X�^�[�g���鎞�̃J�E���^�[
//----------------------------------------------
class CCountLogo : public CListSprite  
{
private:
	int		m_nAnimeCnt;		// �A�j���J�E���^�[

	int		m_nAlphaBase;		// �����p�����l
	int		m_nAlphaStock;		// �`��p�����l

	float	m_fScaleBase;		// �����p�X�P�[���l
	float	m_fScaleStock;		// �`��p�X�P�[���l

public:
	void	FrameMove();					// ���t���[���̏���
	void	Render(LPD3DXSPRITE pSprite);	// �`�揈��
	void	UpDate();						// �f�[�^�X�V

	CCountLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture);
	virtual ~CCountLogo();

};

#endif // !defined(AFX_COUNTLOGO_H__6D215A4F_5EA3_45A9_B975_2B25158689FA__INCLUDED_)
