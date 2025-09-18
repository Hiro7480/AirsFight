//==========================================================
// Title.h
// Auther : ���� ���V
// Data   : 2002/01/11
//==========================================================

#if !defined(AFX_TITLE_H__263F63A1_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_)
#define AFX_TITLE_H__263F63A1_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------
//	�C���N���[�h
//--------------------------
#include "GameStatus.h"

#include "Sprite.h"
#include "ScrollBG.h"

//----------------------------------------------
//	Name:	CTitle
//	Func:	�^�C�g�����̊Ǘ�
//----------------------------------------------
class CTitle : public GameStatus  
{
private:
	CSprite*		m_pTitleLogo;	// �^�C�g�����S
	CSprite*		m_pPressEnter;	// �G���^�[����
	CSprite*		m_pTitleChara;	// �L�����N�^	
	CScrollBG*		m_pBackGround;	// �^�C�g���w�i

public:
	int  FrameMove();			// �t���[�����̏���
	void Render();				// ��ʕ`�揈��
	void UpDate();				// �f�[�^�X�V

	CTitle(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CTitle();
};

#endif // !defined(AFX_TITLE_H__263F63A1_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_)
