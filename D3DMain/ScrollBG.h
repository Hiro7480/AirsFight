//==========================================================
// ScrollBG.h
// Auther : ���� ���V
// Data   : 2002/05/01
//==========================================================

#if !defined(AFX_SCROLLBG_H__F5145635_6BAE_4616_83A7_3F3B4AE64F89__INCLUDED_)
#define AFX_SCROLLBG_H__F5145635_6BAE_4616_83A7_3F3B4AE64F89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CScrollBG
//	Func:	�X�N���[������w�i�̊Ǘ�
//----------------------------------------------
class CScrollBG : public C2DGraphicObj
{
private:
	LPDIRECT3DTEXTURE8	m_pTexture;		// �e�N�X�`��
	float				m_fHeight;		// �e�N�X�`���̍���
	float				m_fWidth;		// �e�N�X�`���̕�

	LPD3DXSPRITE		m_pSprite;		// �X�v���C�g

	D3DXVECTOR2			m_vecDir;		// �ړ��x�N�g��

public:
	void	FrameMove();		// ���t���[���̏���
	void	Render();			// �`�揈��

	/* �A�N�Z�X�֐� */
	void	SetVecDir(D3DXVECTOR2 vecDir){m_vecDir = vecDir;};	// �ړ��x�N�g���̃Z�b�g

	CScrollBG(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFileName, float fHeight, float fWidth);
	virtual ~CScrollBG();

};

#endif // !defined(AFX_SCROLLBG_H__F5145635_6BAE_4616_83A7_3F3B4AE64F89__INCLUDED_)
