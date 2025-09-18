//==========================================================
// EnemyCPU.h
// Auther : ���� ���V
// Data   : 2002/05/05
//==========================================================

#if !defined(AFX_ENEMYCPU_H__63357F8F_C02D_4E56_B282_F5DCA3A8EC96__INCLUDED_)
#define AFX_ENEMYCPU_H__63357F8F_C02D_4E56_B282_F5DCA3A8EC96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//--------------------------
//	�C���N���[�h
//--------------------------
#include "Chara.h"
#include <time.h>

//----------------------------------------------
//	Name:	CCEnemuCPU
//	Func:	�G�L�����R���s���[�^
//----------------------------------------------
class CEnemyCPU : public CChara  
{
private:
	/* ���z�L�[��������Ă��邩�ǂ������i�[����\���� */
	struct TVirtualKey
	{
		bool	Up;		// ��L�[
		bool	Down;	// ���L�[
		bool	Left;	// ���L�[
		bool	Right;	// �E�L�[
	};

	int				m_nNextStatus;		// �����_���Ō��߂����ɋN�����s��
	int				m_nActionCount;		// �s���𑱂���J�E���^�[
	TVirtualKey		m_tagVirtualKey;	// ���z�L�[

	int				m_nCnt;				// �ėp�J�E���^

	/* �R���s���[�^�̎��̍s�������߂� */
	void	ComputNextAction(CEffectManage* pEffectManage);

	/* �L�����N�^�[�̏�Ԃɂ�蕪�򂷂�֐� */
	void	Start();
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

public:
	/* �Q�[�����̖��t���[���̏��� */
	void FrameMoveGame(CStage* pStage, CBulManage* pBulManage, CSpriteManage* pSpriteManage,
		CEffectManage* pEffectManage);

	CEnemyCPU(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEnemyCPU();

};

#endif // !defined(AFX_ENEMYCPU_H__63357F8F_C02D_4E56_B282_F5DCA3A8EC96__INCLUDED_)
