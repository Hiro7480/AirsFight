//==========================================================
// Menu.h
// Auther : ���� ���V
// Data   : 2002/05/01
//==========================================================
#if !defined(AFX_MENU_H__EDCC5399_A5D0_40D3_999C_F35246540196__INCLUDED_)
#define AFX_MENU_H__EDCC5399_A5D0_40D3_999C_F35246540196__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "CompatiDX8.h"
#include "GameStatus.h"
#include "Sprite.h"
#include "ScrollBG.h"
#include "Font.h"

#include <time.h>

//------------------------------
//	�萔��`
//------------------------------
#define	MAX_CHARA 4

//--------------------------------------------------
//		�f�[�^���M�p�\����
//--------------------------------------------------
/* �I�����Ă���L�����N�^������ */
struct TSelect{
	DWORD		dwDpnType;		// ���b�Z�[�W�^�C�v
	int			nChara;			// �w��L�����̓Y����
	int			nSelect;		// �I�����Ă���L����
	bool		bOK;			// ����OK���ǂ���
};

//----------------------------------------------
//	Name:	CMenu
//	Func:	���j���[���̊Ǘ�
//----------------------------------------------
class CMenu : public GameStatus
{
private:
	/* �L�����N�^�̃p�����[�^��\�� */
	struct TParam
	{
		int			nPower;			// �p���[
		int			nEnergy;		// �G�l���M�[
		int			nSpeed;			// �X�s�[�h
	};

	int			m_nSelectChara[4];	// ���ꂼ��̃v���C���[���I��ł���L�����N�^������
	int			m_nMyChara;			// SelectChara�̒��̎����̓Y����������
	bool		m_bOK[4];			// ���ꂼ��̃v���C���[�̏�������������
	bool		m_bCPUFlg[4];		// �R���s���[�^���ۂ��������t���O

	CSprite*	m_pCharaImage[4];	// �L�����N�^�̃C���[�W
	CFont*		m_pPlayerName[4];	// �v���C���[�̖��O
	CSprite*	m_pReady[4];		// OK�T�C���̃X�v���C�g

	CSprite*	m_pLogo;			// ���j���[���̃��S
	CScrollBG*	m_pBackGround;		// �w�i�̃^�C��
	TParam		m_pParam[MAX_CHARA];// �L�����N�^�p�����[�^

public:
	int  FrameMove();			// �t���[�����̏���
	void Render();				// �`�揈��
	void UpDate();				// �f�[�^�X�V

	/* �A�N�Z�X�֐� */
	int*		GetSelectChara(){return &m_nSelectChara[0];};
	int			GetSelectChara(int n){return m_nSelectChara[n];};

	CMenu(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CMenu();

};

#endif // !defined(AFX_MENU_H__EDCC5399_A5D0_40D3_999C_F35246540196__INCLUDED_)
