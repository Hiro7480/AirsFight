//==========================================================
// Bullet.cpp
// Auther : ���� ���V
// Data   : 2002/01/11
//==========================================================

#include "Bullet.h"


//----------------------------------------------
//	Name:	CBullet
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3D�f�o�C�X
//			tagBulParam*	  pType		= �e�̃^�C�v
//			D3DXMATRIX		  matBase	= �����}�g���N�X
//			long			  lID		= ���ʔԍ�
//	Out:	�Ȃ�
//----------------------------------------------
CBullet::CBullet(LPDIRECT3DDEVICE8 d3dDevice, tagBulParam* pType, D3DXMATRIX matBase, long lID)
		:C3DGraphicObj(d3dDevice)
{
	/* �p�����[�^�̃|�C���^���i�[ */
	m_pBulStatus = pType;	

	/* �e�̏����s����w��s��� */
	m_matBase = matBase;

	/* ���ւ̃|�C���^�̏����� */
	m_pNext = NULL;

	/* �o�ߎ��Ԃ̏����� */
	m_nTimeCount = 0;

	/* �ړ��x�N�g���̎Z�o */
	m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

	/* ���ʔԍ��̊i�[ */
	m_lID = lID;
}

//----------------------------------------------
//	Name:	~CBullet
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CBullet::~CBullet()
{

}

//------------------------------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		CEffectManage* pEffectManage = �G�t�F�N�g�Ǘ��N���X
//	Out:	�Ȃ�
//------------------------------------------------------------------
void CBullet::FrameMove(CEffectManage* pEffectManage)
{
	/* ���W�l�̍X�V */
	m_matBase._41 += m_vecMove.x * m_pBulStatus->fSpeed;
	m_matBase._42 += m_vecMove.y * m_pBulStatus->fSpeed;
	m_matBase._43 += m_vecMove.z * m_pBulStatus->fSpeed;

	/* �G�t�F�N�g���R��ɂP�񔭐� */
	static int nCnt=0;
	nCnt++;
	if(nCnt % 3 == 0)
		pEffectManage->AddEffect(ORBIT_BUL, m_matBase);

	/* �o�ߎ��Ԃ̃C���N�������g */
	m_nTimeCount++;
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CBullet::Render()
{
	/* ���[���h�ϊ� */
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &m_matStock);
	
	/* �`�� */
	m_pBulStatus->pBulMesh->Render();
}

//----------------------------------------------
//	Name:	IsDelete
//	Func:	�e���������ǂ����𔻒�
//	in:		�Ȃ�
//	Out:	bool
//----------------------------------------------
bool CBullet::IsDelete()
{
	/* �e�̌o�ߎ��Ԃ��������Ԃ��I�[�o�[���Ă���������Ƃ݂Ȃ� */
	if(m_nTimeCount >= m_pBulStatus->nMaxLife)	return	true;

	else	return false;
}