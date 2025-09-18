//==========================================================
// Camera.h
// Auther : ���� ���V
// Data   : 2002/02/20
//==========================================================

#if !defined(AFX_CAMERA_H__E859F97C_FFC1_471D_9A68_CDF90E8FBD4A__INCLUDED_)
#define AFX_CAMERA_H__E859F97C_FFC1_471D_9A68_CDF90E8FBD4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include <d3dx8.h>
#include "MyFunction.h"
#include "3DGraphicObj.h"
#include "MyPlayer.h"

//----------------------------------------------
//	Name:	CCamera
//	Func:	�J�����N���X
//----------------------------------------------
class CCamera:public C3DGraphicObj
{
private:
	D3DXVECTOR3	m_vecPos;				// �J�����̈ʒu
	D3DXVECTOR3	m_vecStock;				// �X�g�b�N�p�J�����ʒu
	float		m_fNowYaw;				// ����Yaw�p�x
	float		m_fNowPitch;			// ����Pitch�p�x
	float		m_fNextYaw;				// �ڕWYaw�p�x
	float		m_fNextPitch;			// �ڕWPitch�p�x

	float		m_fFrameSpeed;			// �J�����̂P�t���[���ړ���
	float		m_fLength;				// �J�����ƖڕW�Ƃ̋���

	/* �J�����̈ʒu�𓮂����֐� */
	void	SetPosition(CChara* pChara);		// �J�����ʒu�̎Z�o
	void	SetNowYaw(CChara* pChara);			// ����Yaw�p�x�̎Z�o
	void	SetNowPitch(CChara* pChara);		// ����Pitch�p�x�̎Z�o
	void	SetNextYaw(D3DXVECTOR3* vecIn);		// �ڕWYaw�p�x�̎Z�o
	void	SetNextPitch(D3DXVECTOR3* vecIn);	// �ڕWPitch�p�x�̎Z�o
	void	SetNextPitch(float fPitch);			// �ڕWPitch�p�x�̒��ڊi�[
	void	MoveYaw();							// ����Yaw�p�x��ڕWYaw�p�x�ɋ߂Â���
	void	MovePitch();						// ����Pitch�p�x��ڕWPitch�p�x�ɋ߂Â���

public:
	void	FrameMove(CMyPlayer* pMyPlayer);	// ���t���[���̏���
	void	Render(CChara* pChara);				// �`�掞�̏���
	void	UpDate();							// �`��p�ϐ��̍X�V

	D3DXVECTOR3	GetPosition(){return m_vecPos;};	// �J�����ʒu��Ԃ�

	CCamera(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CCamera();

};

#endif // !defined(AFX_CAMERA_H__E859F97C_FFC1_471D_9A68_CDF90E8FBD4A__INCLUDED_)
