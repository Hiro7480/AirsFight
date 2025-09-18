//==========================================================
// LockOnMarker.h
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_LOCKONMARKER_H__BDEA9907_A551_40BC_856E_92D4D9955DBE__INCLUDED_)
#define AFX_LOCKONMARKER_H__BDEA9907_A551_40BC_856E_92D4D9955DBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include "Sprite.h"

//----------------------
//	��Ԏ��ʎq�̒�`
//----------------------
enum{
	NOT_LOCK,		// ���b�N�I���o���Ȃ�
	CAN_LOCK,		// ���b�N�I���o����
	TAG_LOCK,		// �^�[�Q�b�g�Ƃ��ă��b�N�I�����o����
	NOW_LOCK		// ���b�N�I�����Ă���
};

//--------------------------------------------------
//	Name:	CLockOnMarker
//	Func:	���b�N�I���}�[�J�[�̃X�v���C�g���Ǘ�
//--------------------------------------------------
class CLockOnMarker : public CSprite  
{
private:
	DWORD	m_dwStatus;		// ���݂̏�Ԃ�\��

	float	m_fScale;		// �X�P�[���l
	float	m_fAlpha;		// �A���t�@�l

public:
	void FrameMove();		// ���t���[���̏���
	void Render();			// �`�揈��

	/* �A�N�Z�X�֐� */
	void SetStatus(DWORD dwStatus){m_dwStatus = dwStatus;};	// ��Ԃ��i�[

	CLockOnMarker(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName);
	virtual ~CLockOnMarker();

};

#endif // !defined(AFX_LOCKONMARKER_H__BDEA9907_A551_40BC_856E_92D4D9955DBE__INCLUDED_)
