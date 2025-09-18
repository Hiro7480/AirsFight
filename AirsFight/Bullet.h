//==========================================================
// Bullet.h
// Auther : ���� ���V
// Data   : 2002/01/11
//==========================================================

#if !defined(AFX_BULLET_H__7E4D9C62_06AE_11D6_AE81_0000F4905862__INCLUDED_)
#define AFX_BULLET_H__7E4D9C62_06AE_11D6_AE81_0000F4905862__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include <d3dx8.h>
#include "MyFunction.h"
#include "3DGraphicObj.h"
#include "MeshData.h"

#include "EffectManage.h"

//----------------------------------------------
//	Name:	BulStatus
//	Func:	�e�X�e�[�^�X�\����
//----------------------------------------------
typedef	struct {
	CMeshObject*	pBulMesh;			// �e���b�V���f�[�^
	int				nMaxLife;			// �L���ő厞��(�t���[����)
	int				nShotFrame;			// �A�ː��\(���̒e���o��܂ł̃t���[����)
	float			fSpeed;				// �ړ����x

} tagBulParam;

//----------------------------------------------
//	Name:	CBullet
//	Func:	�e�N���X
//----------------------------------------------
class CBullet: public C3DGraphicObj
{
private:
	long			m_lID;				// ���ʔԍ�
	CBullet*		m_pNext;			// ���̒e�ւ̃|�C���^
	D3DXVECTOR3		m_vecMove;			// �ړ��x�N�g��
	tagBulParam*	m_pBulStatus;		// �Œ�X�e�[�^�X(�|�C���^)
	int				m_nTimeCount;		// ����Ă���̌o�ߎ���

public:
	void FrameMove(CEffectManage* pEffectManage);	// ���t���[���̏���
	void Render();									// ��ʕ`��
	bool IsDelete();								// �e���������ǂ����𔻒�

	void Delete(){m_nTimeCount = m_pBulStatus->nMaxLife;};	// �����I�ɒe������

	/* �A�N�Z�X�֐� */
	CBullet*	GetNext(){return m_pNext;};					// ���̒e�ւ̃|�C���^��Ԃ�
	D3DXVECTOR3	GetMoveVec(){return m_vecMove;};			// �ړ��x�N�g���l��Ԃ�
	int			GetTimeCount(){return m_nTimeCount;};		// ����Ă���̌o�ߎ��Ԃ�Ԃ�
	int			GetID(){return m_lID;};						// ID��Ԃ�

	void		SetNext(CBullet* pNext){m_pNext = pNext;};	// ���̒e�ւ̃|�C���^���Z�b�g

	CBullet(LPDIRECT3DDEVICE8 d3dDevice, tagBulParam* pType, D3DXMATRIX matBase, long lID);
	virtual ~CBullet();
};

#endif // !defined(AFX_Bullet_H__7E4D9C62_06AE_11D6_AE81_0000F4905862__INCLUDED_)
