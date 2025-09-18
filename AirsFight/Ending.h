//==========================================================
// Ending.h
// Auther : ���� ���V
// Data   : 2002/05/20
//==========================================================

#if !defined(AFX_ENDING_H__0D5B5B1B_942D_4965_BF52_5D937583A52A__INCLUDED_)
#define AFX_ENDING_H__0D5B5B1B_942D_4965_BF52_5D937583A52A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "GameStatus.h"
#include "OrderSprite.h"
#include "ScrollBG.h"

//----------------------------------------------
//	Name:	CEnding
//	Func:	�G���f�B���O���̊Ǘ�
//----------------------------------------------
class CEnding : public GameStatus  
{
	/* �L�����N�^�̃f�[�^������킷�\���� */
	struct TChara{
		TCHAR	strName[256];		// ���O
		int		nDeadNum;			// ���񂾐�
		int		nOrder;				// ����
	};

	TChara			m_tagChara[4];	// �L�����N�^�f�[�^
	COrderSprite*	m_pOrder[4];	// ���ʃX�v���C�g

	CSprite*		m_pLogo;		// �G���f�B���O���̃��S
	CScrollBG*		m_pBackGround;	// �w�i�̃^�C��

public:
	int		FrameMove();			// ���t���[���̏���
	void	Render();				// ��ʕ`��
	void	UpDate();				// �f�[�^�X�V

	HRESULT	InitOrder(int nDeadNum1, int nDeadNum2, int nDeadNum3, int nDeadNum4);	// ���ʂɊւ��鏉����


	CEnding(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEnding();
};

#endif // !defined(AFX_ENDING_H__0D5B5B1B_942D_4965_BF52_5D937583A52A__INCLUDED_)
