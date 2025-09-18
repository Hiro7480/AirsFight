//==========================================================
// BulManage.h
// Auther : ���� ���V
// Data   : 2002/01/11
//==========================================================

#if !defined(AFX_BULMANAGE_H__7E4D9C63_06AE_11D6_AE81_0000F4905862__INCLUDED_)
#define AFX_BULMANAGE_H__7E4D9C63_06AE_11D6_AE81_0000F4905862__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//------------------------------
//	�C���N���[�h
//------------------------------
#include <d3dx8.h>
#include "MyFunction.h"

#include "Bullet.h"
#include "Stage.h"
#include "EffectManage.h"

//------------------------------
//		�萔��`
//------------------------------
#define HIT_WALL_LENGTH		2.0f	// �ǂƂ̂����蔻�肷�鋗��
#define HIT_CHARA_LENGTH	5.0f	// �L�����N�^�[�Ƃ̓����蔻�苗��

//--------------------------------------------------
//		�f�[�^���M�p�\����
//--------------------------------------------------
/* �e�̔��˂����� */
struct TBullet{
	DWORD		dwDpnType;		// ���b�Z�[�W�^�C�v
	D3DXMATRIX	matBase;		// �e���ˈʒu�A�p�x
	int			nType;			// �e�̃^�C�v
	int			nCharaID;		// �e���o�����L�����N�^
};

//----------------------------------------------
//	Name:	BulManage
//	Func:	�e�Ǘ��N���X
//----------------------------------------------
class CBulManage
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;				// D3D�f�o�C�X

	CBullet*			m_pListTop;					// �͂��߂̒e�ւ̃|�C���^
	tagBulParam			m_tagParam[3];				// �e�p�����[�^

	CRITICAL_SECTION	m_cs;						// �N���e�B�J���Z�N�V�����I�u�W�F�N�g

public:
	void FrameMove(CStage* pStage, 					// ���t���[���̏���
		CEffectManage* pEffectManage);			
	void Render();									// ��ʕ`��
	void UpDate();									// �`��p���W�l�X�V

	void AddBullet(int nType, D3DXMATRIX matBase, int nCharaNum);	// �e�̒ǉ�
	void SubBullet();												// �e�̏�������

	CBullet* SearchBullet(long lID);				// ���ʔԍ�����e��{��

	void HitPlane(CStage* pStage,					// �e�̕ǂƂ̓����蔻��
		CEffectManage* pEffectManage);

	float SearchAllPlane(CStage* pStage,			// �ʂƂ̓����蔻��
		D3DXVECTOR3 vecPos, D3DXVECTOR3 vecMove); 

	/* �A�N�Z�X�֐� */
	tagBulParam*	GetBulStatus(int nType){return &m_tagParam[nType];};	// �e�Œ�X�e�[�^�X�l�̃|�C���^��Ԃ�
	CBullet*		GetListTop(){return m_pListTop;};						// �͂��߂̒e�ւ̃|�C���^��Ԃ�

	CBulManage(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CBulManage();
};

#endif // !defined(AFX_BULMANAGE_H__7E4D9C63_06AE_11D6_AE81_0000F4905862__INCLUDED_)
