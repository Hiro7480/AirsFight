//==========================================================
// TimeGraphic.h
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_TIMEGRAPHIC_H__EB7CCC7F_E765_4021_9E56_1F8028076E6D__INCLUDED_)
#define AFX_TIMEGRAPHIC_H__EB7CCC7F_E765_4021_9E56_1F8028076E6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------
//	�C���N���[�h
//--------------------------
#include "CompatiDX8.h"
#include <time.h>
#include "Sprite.h"

//------------------------------------------
//	Name:	CTimeGraphic
//	Func:	�c�莞�Ԃ�\��
//------------------------------------------
class CTimeGraphic : public CSprite
{
private:
	long	m_lStartTime;		// �J�n����
	long	m_lNowTime;			// ���ݎ���

	long	m_lMaxTime;			// �ő吧������
	long	m_lLimitTime;		// �c�萧������

	bool	m_bPlay;			// ���Ԍv�������H

	RECT	m_rcBase[5];		// �����pRECT
	RECT	m_rcStock[5];		// �`��pRECT

	D3DXVECTOR2		m_vecPos;	// ��{�`��ʒu

public:
	void	FrameMove();		// ���t���[���̏���
	void	Render();			// �`�揈��
	void	UpDate();			// �f�[�^�X�V

	void	Start();			// ���Ԍv���J�n
	bool	IsEnd();			// �c�萧�����Ԃ��Ȃ��Ȃ������H

	/* �A�N�Z�X�֐� */
	long GetLimitTime(){return m_lLimitTime;};				// �c�萧�����Ԃ̎擾

	void SetStartTime(long lTime){m_lStartTime = lTime;};	// �J�n���Ԃ̃Z�b�g
	void SetNowTime(long lTime){m_lNowTime = lTime;};		// ���ݎ��Ԃ̃Z�b�g
	void SetMaxTime(long lTime){m_lMaxTime = lTime;};		// �ő吧�����Ԃ̃Z�b�g

	CTimeGraphic(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CTimeGraphic();
};

#endif // !defined(AFX_TIMEGRAPHIC_H__EB7CCC7F_E765_4021_9E56_1F8028076E6D__INCLUDED_)
