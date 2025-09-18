//==========================================================
// StartLogo.h
// Auther : ���� ���V
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_STARTLOGO_H__91137AFF_C667_4333_BB83_7F7862D57966__INCLUDED_)
#define AFX_STARTLOGO_H__91137AFF_C667_4333_BB83_7F7862D57966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "CompatiDX8.h"
#include "ListSprite.h"

//----------------------------------------------
//	Name:	CStartLogo
//	Func:	�X�^�[�g���鎞�̃��S
//----------------------------------------------
class CStartLogo : public CListSprite  
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

	CStartLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture);
	virtual ~CStartLogo();

};

#endif // !defined(AFX_STARTLOGO_H__91137AFF_C667_4333_BB83_7F7862D57966__INCLUDED_)
