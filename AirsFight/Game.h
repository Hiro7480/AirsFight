//==========================================================
// Game.h
// Auther : ���� ���V
// Data   : 2002/01/10
//==========================================================

#if !defined(AFX_Game_H__FD56F37B_91FF_467E_AAFB_D4571886E6D9__INCLUDED_)
#define AFX_Game_H__FD56F37B_91FF_467E_AAFB_D4571886E6D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "CompatiDX8.h"
#include "GameStatus.h"

#include "Chara.h"
#include "MyPlayer.h"
#include "EnemyPlayer.h"
#include "EnemyCPU.h"

#include "Stage.h"
#include "Camera.h"
#include "BulManage.h"
#include "SpriteManage.h"
#include "EffectManage.h"

#include "EnergyGauge.h"
#include "LifeGraphic.h"
#include "TimeGraphic.h"

//------------------------------
//	�萔��`
//------------------------------
/* �Q�[���̏�Ԏ��ʎq */
enum{
	GAME_START,		// �Q�[���J�n
	GAME_MAIN,		// �Q�[�����C��
	GAME_END		// �Q�[���I��
};

//----------------------------------------------
//	Name:	CGame
//	Func:	�Q�[�����̊Ǘ�
//----------------------------------------------
class CGame : public GameStatus
{
private:
	CChara*			m_pChara[4];				// �L�����N�^�[�f�[�^
	tagCharaParam	m_CharaParam[4];			// �L�����N�^�p�����[�^
	CMotionData*	m_pMotionData[MAX_MOTION];	// ���[�V�����f�[�^�z��
	int				m_nMyChara;					// �L�����z��ł̎����̓Y����������

	CStage*			m_pStage;					// �X�e�[�W�N���X
	CCamera*		m_pCamera;					// �J�����N���X
	CBulManage*		m_pBulManage;				// �e�Ǘ��N���X
	CSpriteManage*	m_pSpriteManage;			// �X�v���C�g�Ǘ��N���X
	CEffectManage*	m_pEffectManage;			// �G�t�F�N�g�Ǘ��N���X

	CEnergyGauge*	m_pEnergyGauge;				// �G�l���M�[�Q�[�W�X�v���C�g
	CLifeGraphic*	m_pLifeGraphic;				// ���C�t�X�v���C�g
	CTimeGraphic*	m_pTimeGraphic;				// �c�莞�Ԃ�\��

	DWORD			m_dwNowStatus;				// ���݂̏��

	bool			m_bReady[4];				// ����OK�t���O

	/* �Q�[���̏�Ԃɂ���ĕ��򂷂�֐� */
	void	Start();
	void	Game();
	bool	End();

public:
	int		FrameMove();			// �t���[�����̏���
	void	Render();				// ��ʕ`�揈��
	void	UpDate();				// �`��p�}�g���N�X�̍X�V

	HRESULT	CreateChara(int SelectChara[]);		// �L�����N�^�̍쐬

	/* �A�N�Z�X�֐� */
	int		GetDeadNum(int n){return m_pChara[n]->GetDeadNum();};		// ���񂾐��z��̎擾

	CGame(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CGame();

};
#endif // !defined(AFX_Game_H__FD56F37B_91FF_467E_AAFB_D4571886E6D9__INCLUDED_)
