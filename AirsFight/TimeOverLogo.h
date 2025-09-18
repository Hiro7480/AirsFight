//==========================================================
// TimeOverLogo.h
// Auther : ���� ���V
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_TIMEOVERLOGO_H__4018A837_4748_4EBB_AFD4_EBE6B0E68DE8__INCLUDED_)
#define AFX_TIMEOVERLOGO_H__4018A837_4748_4EBB_AFD4_EBE6B0E68DE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "ListSprite.h"

//----------------------------------------------
//	Name:	CTimeOverLogo
//	Func:	�X�^�[�g���鎞�̃��S
//----------------------------------------------
class CTimeOverLogo : public CListSprite  
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

	CTimeOverLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture);
	virtual ~CTimeOverLogo();

};

#endif // !defined(AFX_TIMEOVERLOGO_H__4018A837_4748_4EBB_AFD4_EBE6B0E68DE8__INCLUDED_)
