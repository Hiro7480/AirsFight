//==========================================================
// LifeGraphic.h
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_LIFEGRAPHIC_H__EF23A023_3B1C_4A88_AB23_EF85E3DA2D01__INCLUDED_)
#define AFX_LIFEGRAPHIC_H__EF23A023_3B1C_4A88_AB23_EF85E3DA2D01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------
//	�C���N���[�h
//--------------------------
#include "CompatiDX8.h"
#include "Sprite.h"

//------------------------------------------
//	Name:	CLifeGraphic
//	Func:	���C�t�𐔎��ŕ`��
//------------------------------------------
class CLifeGraphic : public CSprite  
{
private:
	int		m_nMaxLife;			// �ő�LIFE�l
	int		m_nNextLife;		// �ڕWLIFE�l
	int		m_nNowLife;			// ����LIFE�l

	RECT	m_rcBase[4];		// �����pRECT
	RECT	m_rcStock[4];		// �`��pRECT

	D3DXVECTOR2		m_vecPos;	// ��{�`��ʒu

public:

	void	FrameMove();		// ���t���[���̏���
	void	Render();			// �`�揈��
	void	UpDate();			// �f�[�^�X�V

	void	InitLife(int nLife);// ���C�t�̒l�̏�����

	/* �A�N�Z�X�֐� */
	void SetLife(int nLife){m_nNextLife = nLife;};	// LIFE�l�̃Z�b�g

	CLifeGraphic(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName);
	virtual ~CLifeGraphic();
};

#endif // !defined(AFX_LIFEGRAPHIC_H__EF23A023_3B1C_4A88_AB23_EF85E3DA2D01__INCLUDED_)
