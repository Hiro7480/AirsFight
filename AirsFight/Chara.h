//==========================================================
// Chara.h
// Auther : ���� ���V
// Data   : 2002/02/26
//==========================================================

#if !defined(AFX_Chara_H__0BF69BE4_6286_400C_B667_F7658AF7BE57__INCLUDED_)
#define AFX_Chara_H__0BF69BE4_6286_400C_B667_F7658AF7BE57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "MyFunction.h"
#include "3DGraphicObj.h"
#include "ActiveMotion.h"

#include "Stage.h"
#include "BulManage.h"
#include "SpriteManage.h"
#include "EffectManage.h"

#include "time.h"

//------------------------------
//	�萔��`
//------------------------------

/* �L�����N�^�[�̏�Ԏ��ʎq */
enum{
	START,		// �Q�[���J�n�O
	WALK,		// �����Ă���
	DASH,		// �����Ă���
	ATTACK_S,	// �U���\��
	ATTACK,		// �U��

	JUMP_START,	// �W�����v�J�n
	JUMP_MAIN,	// �W�����v��
	JUMP_END,	// �W�����v�I��

	FLYGHT,		// ��s��

	DAMAGE_LAND,// �n�ʂɂ��ă_���[�W
	DAMAGE_AIR,	// �󒆂ɂ��ă_���[�W

	DEAD_LAND,	// �n�ʂɂ��Ď��S
	DEAD_AIR	// �󒆂ɂ��Ď��S
};

/* �A�j���[�V�����̎��ʎq(�A�ԕK�{) */
#define ANI_STOP		0	// �~�܂��Ă���
#define ANI_FORWARD		1	// �����Ă���
#define ANI_BACK		2	// ��ނ��Ă���
#define ANI_DASH_F		3	// �O���Ƀ_�b�V��
#define ANI_DASH_B		4	// ����Ƀ_�b�V��
#define ANI_DASH_R		5	// �E�Ƀ_�b�V��
#define ANI_DASH_L		6	// ���Ƀ_�b�V��
#define ANI_ATAS		7	// �U���\��
#define ANI_ATA 		8	// �U���A�j���[�V����

#define ANI_JUMP_N		9	// �����ɃW�����v
#define ANI_JUMP_F		10	// �O���ɃW�����v
#define ANI_JUMP_B		11	// ����ɃW�����v
#define ANI_JUMP_S		12	// �W�����v�J�n��
#define ANI_JUMP_E		13	// �W�����v�I����
#define ANI_DAM_L		14	// �n�ʂŃ_���[�W
#define ANI_DAM_A		15	// �󒆂Ń_���[�W
#define ANI_DEAD_L		16	// �n��Ŏ��S
#define ANI_DEAD_A		17	// �󒆂Ŏ��S

#define MAX_MOTION		18	// ���[�V�����ő吔

/* �ʂƂ̓����蔻�苗�� */
#define HIT_GROUND		5.0f// �n�ʂƂ̓����蔻�苗��
#define HIT_WALL		3.0f// �ǂƂ̓����蔻�苗��
#define HIT_CEILING		5.0f// �V��Ƃ̓����蔻�苗��

/* �G�l���M�[�̎g�p�ʁA�񕜗� */
#define USE_ENERGY_DASH 3	// �_�b�V�����Ɏg���G�l���M�[�l
#define USE_ENERGY_FLY	3	// ��s���Ɏg���G�l���M�[�l
#define REST_ENERGY		2	// ���t���[���񕜂���G�l���M�[�l

/* �_���[�W�̌�̖��G���� */
#define DAMAGE_CNT		20

/* �G�t�F�N�g�̔�������Ԋu */
#define EFFECT_DASH		4	// �_�b�V�����ɏo��u�[�X�g�G�t�F�N�g
#define EFFECT_FLY		4	// ��s���ɂł�u�[�X�g�G�t�F�N�g
#define EFFECT_BUL		3	// �e���΂��Ă��鎞�ɂł�O���G�t�F�N�g

/* �f�[�^�𑗐M����Ԋu */
#define SEND_CHARA		4	// �L�����N�^�̍��W�l�Ȃǂ̍X�V�Ԋu

/* �L�[������@�̒�` */
#define KEY_FORWARD			VK_UP		// �O�i�L�[
#define KEY_BACK			VK_DOWN		// ��ރL�[
#define KEY_RIGHT			VK_RIGHT	// �E����
#define KEY_LEFT			VK_LEFT		// ������

#define KEY_LOCK			VK_SPACE	// ���b�N�I��
#define KEY_ATAS			'A'			// �U���\��
#define KEY_ATTACK			'S'			// �U��
#define KEY_DASH			'Z'			// �_�b�V��
#define KEY_JUMP			'X'			// �W�����v

#define KEY_ANGLE_CONTROL	VK_SHIFT	// �A���O������
#define KEY_ANGLE_FORMAT	VK_CONTROL	// �A���O��������
#define KEY_ANGLE_UP		VK_NUMPAD0	// �������
#define KEY_ANGLE_DOWN		VK_NUMPAD1	// ��������


//----------------------------------------------
//	Name:	tagCharaParam
//	Func:	�L�����N�^�p�����[�^�\����
//----------------------------------------------
typedef	struct {
	CMeshData*		pMeshData;		// �K�w�\���������b�V���f�[�^

//	BulStatus*		pBulStatus;		// ���ڂ���Ă���e�X�e�[�^�X�f�[�^

	int				nMaxLife;		// �ő�g�o
	int				nMaxEnergy;		// �ő�G�l���M�[�l

	float			fWalkSpeed;		// ���s���x
	float			fBackSpeed;		// ��ޑ��x
	float			fDashSpeed;		// �_�b�V�����x

	float			fJumpUp;		// �W�����v�����u�Ԃ̂x���ړ���
	float			fJumpDown;		// �W�����v���̍~����
	float			fJumpForward;	// �W�����v���̑O�i�ړ����x
	float			fJumpBack;		// �W�����v���̌�ވړ����x

	float			fFlyForward;	// ��s���̑O�i�ړ����x
	float			fFlyBack;		// ��s���̌�ވړ����x
	float			fFlyPlumb;		// ��s���̏㏸���x

	float			fTurn;			// ���񑬓x

	float			fLockLength;	// ���b�N�I���ł��钷��

	float			fBrakes;		// �_���[�W���ɖ���X�s�[�h�����炵�Ă����l

} tagCharaParam;

//----------------------------------------------
//	Name:	TEnemyData
//	Func:	�G�L�����N�^�[�̏��
//----------------------------------------------
struct TEnemyData
{
	D3DXMATRIX*	pMatrix;		// �}�g���N�X�ւ̃|�C���^
	int*		pNowLife;		// ���C�t�ւ̃|�C���^
	TCHAR		Name[256];		// ���O�ւ̃|�C���^
};

//--------------------------------------------------
//		�f�[�^���M�p�\����
//--------------------------------------------------
/* ����OK���b�Z�[�W */
struct TReady{
	DWORD		dwDpnType;		// ���b�Z�[�W�^�C�v
	int			nCharaNum;		// �L�����N�^�ԍ�
};

/* �L�����Ɋւ���f�[�^ ���t���[������I�ɓ]������ */
struct TChara{
	DWORD		dwDpnType;		// ���b�Z�[�W�^�C�v
	int			nCharaNum;		// �L�����N�^�ԍ�
	int			nNowLife;		// �c�胉�C�t
	int			nDeadNum;		// ���񂾉�
	int			nAction;		// �s��
	D3DXMATRIX	matBase;		// ���[���h�ϊ��}�g���N�X
	D3DXMATRIX	matMotion[16];	// ���[�V�����}�g���N�X
};

/* ��e���b�Z�[�W */
struct THitBullet{
	DWORD		dwDpnType;		// ���b�Z�[�W�^�C�v
	long		lID;			// �e���ʔԍ�
};

/* �G�t�F�N�g�������b�Z�[�W */
struct TEffect{
	DWORD		dwDpnType;		// ���b�Z�[�W�^�C�v
	DWORD		dwEffectType;	// �G�t�F�N�g�^�C�v
	D3DXMATRIX	matBase;		// �G�t�F�N�g�����ʒu
};

//----------------------------------------------
//	Name:	CChara
//	Func:	�L�����N���X
//----------------------------------------------
class CChara:public C3DGraphicObj
{
protected:
	CActiveMotion*	m_pActiveMotion;	// �A�N�e�B�u���[�V�����f�[�^
	tagCharaParam*	m_pParam;			// �p�����[�^�\���̂ւ̃|�C���^

	TEnemyData		m_tagEnemyData[3];	// ���̃L�����N�^�̃}�g���N�X�ւ̃|�C���^

	TCHAR			m_cName[256];		// �v���C���[�̖��O
	int				m_nNum;				// �v���C���[�ԍ�

	int				m_nNowLife;			// ���݂̂g�o
	int				m_nNowEnergy;		// ���݂̃G�l���M�[
	int				m_nDeadNum;			// ���񂾉�
	int				m_nNowAction;		// ���݂̏��

	/* �L�����N�^�̈ړ����Ɋւ��郁���o */
	D3DXVECTOR3		m_vecMove;			// �����Ă�������ւ̒P�ʕ����x�N�g��
	float			m_fCharaYaw;		// �L�����̌����Ă���p�x
	float			m_fMoveYaw;			// �L�����̌����Ă���p�x
	float			m_fCharaPitch;		// �c�����̎����p�x
	float			m_fSpeed;			// ���݂̈ړ����x
	float			m_fJump;			// �W�����v�l
	int				m_nDamageCnt;		// �_���[�W���󂯂���̖��G����

	/* �ʂ𒲂ׂ郁�\�b�h */
	float		SearchAllGround(CStage* pStage, D3DXPLANE* plaOut, D3DXVECTOR3*	vecOut);	// �n�ʂ𒲂ׂ�
	float		SearchAllWall(CStage* pStage, D3DXVECTOR3* vecOut1, D3DXVECTOR3* vecOut2);	// �ǂ𒲂ׂ�
	float		SearchAllCeiling(CStage* pStage, D3DXPLANE* plaOut, D3DXVECTOR3* vecOut);	// �V��𒲂ׂ�
	bool		SearchAllPlane(CStage* pStage, D3DXVECTOR3 vecPos1, D3DXVECTOR3 vecPos2);	// ��̍��W�Ԃł́A�ʂ̗L���𔻒�
	D3DXVECTOR3	GetVecToPlane(D3DXPLANE* plaGround, float fYaw);	// �n�ʂ̎��Ɗp�x��������x�N�g�������߂�

public:
	/* �Q�[�����̖��t���[���̏��� */
	virtual void FrameMoveGame(CStage* pStage, CBulManage* pBulManage, CSpriteManage* pSpriteManage,
		CEffectManage*	pEffectManage){};

	/* �Q�[���J�n���̖��t���[���̏��� */
	void FrameMoveStart();

	/* �Q�[���I�����̖��t���[���̏��� */
	void FrameMoveEnd();

	virtual void Render();					// ��ʕ`��
	virtual void UpDate();					// �f�[�^�X�V

	/* �A�N�e�B�u���[�V�����̍쐬 */
	HRESULT	CreateActive(CMotionData* pMotionData[]);

	/* �L�����N�^�̏������S�� */
	void	AllInit(D3DXVECTOR3 vecPos, float fCharaYaw);

	/* �e�Ƃ̓����蔻�� */
	void	IsHitBullet(CBulManage* pBulManage, CEffectManage* pEffectManage);

	/* ���S���� */
	bool	IsDead();

	/* �L�����N�^�̖��O�t�H���g���쐬 */
	virtual void CreateCharaName(){};

	/* �L�����N�^�̃��C�t�t�H���g���쐬 */
	virtual void CreateCharaLife(){};

	/* �A�N�Z�X�֐�*/
	CActiveMotion*	GetActiveMotion(){return m_pActiveMotion;};	// �A�N�e�B�u���[�V�����̎擾
	D3DXVECTOR3		GetMoveVec(){return m_vecMove;};			// �ړ��x�N�g���̎擾
	float			GetPitch(){return m_fCharaPitch;};			// �L�����N�^�̎����p�x�̎擾

	TCHAR*			GetName(){return m_cName;};					// ���O�̎擾
	int				GetNum(){return m_nNum;};					// �v���C���[�ԍ��̎擾
	int				GetNowLife(){return m_nNowLife;};			// ���݂̂g�o�̎擾
	int				GetNowEnergy(){return m_nNowEnergy;};		// ���݂̃G�l���M�[�̎擾
	int				GetMaxLife();								// �ő�g�o�̎擾
	int				GetMaxEnergy();								// �ő�G�l���M�[�̎擾
	int 			GetNowAction(){return m_nNowAction;};		// ���݂̏�Ԃ̎擾
	int				GetDeadNum(){return m_nDeadNum;};			// ���񂾐����擾
	int*			GetLifePointer(){return &m_nNowLife;};		// ���݂̃��C�t�̃|�C���^���擾

	void	SetAction(int nAction){m_nNowAction = nAction;};			// �s����Ԃ̊i�[
	void	SetType(tagCharaParam* pType){m_pParam = pType;};			// �L�����N�^�^�C�v�̃Z�b�g
	void	SetName(TCHAR* cName){strcpy(m_cName, cName);};				// ���O�̃Z�b�g
	void	SetNum(int nNum){m_nNum = nNum;};							// �v���C���[�ԍ��̃Z�b�g
	void	SetNowLife(int nNowLife){m_nNowLife = nNowLife;};			// ���݂g�o�̃Z�b�g
	void	SetNowEnergy(int nNowEnergy){m_nNowEnergy = nNowEnergy;};	// ���݃G�l���M�[�l�̃Z�b�g
	void	SetDeadNum(int nDeadNum){m_nDeadNum = nDeadNum;};			// ���񂾉񐔂��Z�b�g

	void SetEnemyData(int n, D3DXMATRIX* pMat, int* pLife, TCHAR* pName);	// �G�L�����̃f�[�^�̃Z�b�g

	CChara(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CChara();
};

//----------------------------------------------
//	Name:	GetMaxLife
//	Func:	�ő�g�o�̎擾
//	In	:	�Ȃ�
//	Out	:	int = �ő�g�o
//----------------------------------------------
inline int CChara::GetMaxLife()
{
	return m_pParam->nMaxLife;
}

//----------------------------------------------
//	Name:	GetMaxEnergy
//	Func:	�ő�G�l���M�[�̎擾
//	In	:	�Ȃ�
//	Out	:	int = �ő�G�l���M�[
//----------------------------------------------
inline int CChara::GetMaxEnergy()
{
	return m_pParam->nMaxEnergy;
}

//----------------------------------------------------------------------
//	Name:	SetEnemyData
//	Func:	�G�L�����f�[�^�̃Z�b�g
//	In:		int			n		= �Z�b�g����L�����N�^������
//			D3DXMATRIX* pMat	= �}�g���N�X
//			int*		pLife	= ���C�t
//			TCHAR*		pName	= ���O
//	Out:	�Ȃ�
//----------------------------------------------------------------------
inline void CChara::SetEnemyData(int n, D3DXMATRIX* pMat, int* pLife, TCHAR* pName)
{
	m_tagEnemyData[n].pMatrix  = pMat;		// �}�g���N�X�̃Z�b�g
	m_tagEnemyData[n].pNowLife = pLife;		// ���C�t�̃Z�b�g
	strcpy(m_tagEnemyData[n].Name, pName);	// �v���C���[���̃Z�b�g
}

#endif // !defined(AFX_Chara_H__0BF69BE4_6286_400C_B667_F7658AF7BE57__INCLUDED_)
