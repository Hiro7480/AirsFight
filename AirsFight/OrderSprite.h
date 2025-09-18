//==========================================================
// OrderSprite.h
// Auther : ���� ���V
// Data   : 2002/05/20
//==========================================================

#if !defined(AFX_ORDERSPRITE_H__C1694154_9DD2_4D55_B76A_1DE5550F410B__INCLUDED_)
#define AFX_ORDERSPRITE_H__C1694154_9DD2_4D55_B76A_1DE5550F410B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "CompatiDX8.h"
#include "Sprite.h"
#include "Font.h"

//----------------------------------------------
//	Name:	COrderSprite
//	Func:	���ʂ�\������N���X
//----------------------------------------------
class COrderSprite  
{
private:
	CSprite*	m_pFormat;	// ���ʃt�H�[�}�b�g
	CFont*		m_pName;	// ���O�t�H���g
	CFont*		m_pDeadNum;	// ���񂾐��t�H���g

	int			m_nOrder;		// ����
	TCHAR		m_strName[256];	// ���O
	int			m_nDeadNum;		// ���񂾐�

	D3DXVECTOR2	m_vecBase;		// ��{�`��ʒu

public:
	void	FrameMove();	// ���t���[���̏���
	void	Render();		// �`�揈��
	void	UpDate();		// �f�[�^�X�V

	COrderSprite(LPDIRECT3DDEVICE8 d3dDevice, int nOrder, TCHAR* strName, int nDeadNum);
	virtual ~COrderSprite();
};

#endif // !defined(AFX_ORDERSPRITE_H__C1694154_9DD2_4D55_B76A_1DE5550F410B__INCLUDED_)
