//==========================================================
// MyPlayer.h
// Auther : ���� ���V
// Data   : 2002/05/05
//==========================================================

#if !defined(AFX_MYPLAYER_H__19EDB939_22CA_4E75_8FDA_48CB7706909A__INCLUDED_)
#define AFX_MYPLAYER_H__19EDB939_22CA_4E75_8FDA_48CB7706909A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include "Chara.h"
#include "LockOnMarker.h"
#include "Font.h"

//----------------------------------------------
//	Name:	CMyPlayer
//	Func:	�����̃L�����𑀍삷��N���X
//----------------------------------------------
class CMyPlayer : public CChara  
{
private:
	int				m_nCnt;				// �ėp�J�E���^

	/* ���b�N�I���֌W�̕ϐ� */
	D3DXVECTOR3		m_vecView[3];		// �r���[�ϊ��������̍��W�l
	D3DXVECTOR2		m_vecProject[3];	// �����ϊ��������̍��W�l

	CLockOnMarker*	m_pLockMarker[3];	// ���b�N�I���}�[�J�[
	CFont*			m_pCharaName[3];	// �L�����N�^�[��
	CFont*			m_pCharaLife[3];	// ���C�t�l

	bool			m_bCanLock[3];		// ���b�N�I�����\���H
	bool			m_bNowLock;			// ���݃��b�N�I�����Ă��邩�H
	int				m_nLockTarget;		// ���b�N�I���̑Ώ�
										// ���Ă��Ȃ������邢�͂ł��Ȃ�����-1

	/* �L�����N�^�[�̏�Ԃɂ�蕪�򂷂�֐� */
	void	Start(CSpriteManage* pSpriteManage);
	void	Walk(CStage* pStage);
	void	Dash(CStage* pStage, CEffectManage* pEffectManage);

	void	Attack_S();
	void	Attack(CBulManage* pBulManage);

	void	JumpStart(CStage* pStage, CEffectManage* pEffectManage);
	void	JumpMain(CStage* pStage);
	void	JumpEnd();

	void	Flyght(CStage* pStage, CEffectManage* pEffectManage);

	void	DamageLand(CStage* pStage, CEffectManage* pEffectManage);
	void	DamageAir(CStage* pStage, CEffectManage* pEffectManage);

	void	DeadLand(CStage* pStage, CEffectManage* pEffectManage);
	void	DeadAir(CStage* pStage, CEffectManage* pEffectManage);

	/* ���b�N�I���Ɋւ���v���C�x�[�g���\�b�h */
	void	LockOn(CStage* pStage);		// ���b�N�I���Ɋւ�����̂��L�q
	void	IsLockON(CStage* pStage);	// ���b�N�I���ł��邩�ǂ������ׂ�
	void	SelectTarget();				// �^�[�Q�b�g�ƂȂ�L�����N�^��I��
	void	ComputProject();			// �v���W�F�N�V�������W�l�̌v�Z
	void	ComputView();				// �r���[���W�l�̌v�Z

public:
	/* �Q�[�����̃t���[���̏��� */
	void FrameMoveGame(CStage* pStage, CBulManage* pBulManage, CSpriteManage* pSpriteManage, CEffectManage* pEffectManage);

	/* �`�揈�� */
	void Render();

	/* �f�[�^�X�V */
	void UpDate();

	/* �L�����N�^�̖��O�t�H���g���쐬 */
	void CreateCharaName();

	/* �L�����N�^�̃��C�t�t�H���g���쐬 */
	void CreateCharaLife();

	/* �A�N�Z�X�֐� */
	bool			GetLockFlg(){return m_bNowLock;};		// ���݃��b�N�I�����Ă��邩���擾
	D3DXVECTOR3		GetLockVec();							// ���݂̃��b�N�I�����W�l�̎擾

	CMyPlayer(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CMyPlayer();

};

//----------------------------------------------------------------------
//	Name:	GetLockVec
//	Func:	���݃��b�N�I�����Ă���L�����N�^�̍��W�l���擾
//			���b�N�I�����Ă��Ȃ��Ȃ�NULL��Ԃ�
//	In:		�Ȃ�
//	Out:	D3DXVECTOR3	= ���b�N�I�����Ă��鑊��̍��W�l
//----------------------------------------------------------------------
inline D3DXVECTOR3 CMyPlayer::GetLockVec()
{
	/* ���b�N�I�����Ă��Ȃ��Ȃ�NULL��Ԃ� */
	if(!m_bNowLock)	return NULL;

	/* �f�[�^���Ȃ��Ƃ���NULL��Ԃ��i�O�̂��߁j */
	if(m_tagEnemyData[m_nLockTarget].pMatrix == NULL)	return NULL;

	/* ���b�N�I�����Ă���ꍇ�͂��̃}�g���N�X���܂��o�� */
	D3DXMATRIX	matTmp = *m_tagEnemyData[m_nLockTarget].pMatrix;

	/* �}�g���N�X���x�N�g���ɕϊ����ĕԂ� */
	return D3DXVECTOR3(matTmp._41, matTmp._42, matTmp._43);
}


#endif // !defined(AFX_MYPLAYER_H__19EDB939_22CA_4E75_8FDA_48CB7706909A__INCLUDED_)
