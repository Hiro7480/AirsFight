//==========================================================
// EnemyCPU.cpp
// Auther : ���� ���V
// Data   : 2002/05/05
//==========================================================
#include "EnemyCPU.h"

//------------------------------------------------------
//	Name:	EnemyCPU
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3D�f�o�C�X
//	Out:	�Ȃ�
//------------------------------------------------------
CEnemyCPU::CEnemyCPU(LPDIRECT3DDEVICE8 d3dDevice):CChara(d3dDevice)
{
	/* �ϐ��̏����� */
	m_nCnt = 0;

	/* �s���̏����� */
	m_nNowAction = WALK;
}

//------------------------------------------------------
//	Name:	~EnemyCPU
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------
CEnemyCPU::~CEnemyCPU()
{

}

//----------------------------------------------------------------------
//	Name:	FrameMoveGame
//	Func:	�Q�[�����̖��t���[���̏���
//	in:		CStage*			pStage			= �X�e�[�W�N���X�|�C���^
//			CBulManage*		pBulManage		= �e�Ǘ��N���X�|�C���^
//			CSpriteManage*	pSpriteManage	= �X�v���C�g�Ǘ��N���X�|�C���^
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X�|�C���^
//	Out:	�Ȃ�
//----------------------------------------------------------------------
void CEnemyCPU::FrameMoveGame(CStage* pStage, CBulManage* pBulManage, 
			CSpriteManage* pSpriteManage,CEffectManage* pEffectManage)
{
	/* �s���J�E���^�[���s�������A�L�����N�^�[�̍s�����ω������ꍇ */
	/* ���̍s�������肷�� */
	if(m_nActionCount <= 0 || m_nNowAction != m_nNextStatus)
	{
		ComputNextAction(pEffectManage);			// ���̍s��������
		m_nNowAction = m_nNextStatus;				// ���̍s���ֈڍs
	}

	/* �s�����Ԃ����炵�Ă��� */
	m_nActionCount--;

	/* �e�Ƃ̓����蔻�� */
	IsHitBullet(pBulManage, pEffectManage);

	/* �L�����N�^�[�̍s���ɂ�菈���𕪂��� */
	switch(m_nNowAction)
	{
	case START:			Start();								break;
	case WALK:			Walk(pStage);							break;
	case DASH:			Dash(pStage, pEffectManage);			break;

	case JUMP_MAIN:		JumpMain(pStage);						break;
	case JUMP_START:	JumpStart(pStage, pEffectManage);		break;
	case JUMP_END:		JumpEnd();								break;
	case FLYGHT:		Flyght(pStage, pEffectManage);			break;

	case ATTACK_S:		Attack_S();								break;
	case ATTACK:		Attack(pBulManage);						break;

	case DAMAGE_LAND:	DamageLand(pStage, pEffectManage);		break;
	case DAMAGE_AIR:	DamageAir(pStage, pEffectManage);		break;

	case DEAD_LAND:		DeadLand(pStage, pEffectManage);		break;
	case DEAD_AIR:		DeadAir(pStage, pEffectManage);			break;

	}

	/* ��]�p�x�l�̐��� */
	if(m_fCharaYaw < 0)			m_fCharaYaw += 360.0f;
	else if(m_fCharaYaw > 360)	m_fCharaYaw -= 360.0f;

	/* Yaw�̒l�����]�}�g���N�X���Z�o */
	D3DXMATRIX	matTmp;
	D3DXMatrixRotationY(&matTmp, D3DXToRadian(m_fCharaYaw) );

	/* �P�ʈړ������x�N�g���A�X�s�[�h�l����ړ��x�N�g���̎擾 */
	D3DXVECTOR3	vecMove;
	vecMove = m_vecMove * m_fSpeed;

	/* �L�����N�^�̃}�g���N�X�l�̍X�V */
	m_matBase = MatUpdate(&m_matBase, &matTmp);
	m_matBase._41 += vecMove.x;
	m_matBase._42 += vecMove.y + m_fJump;
	m_matBase._43 += vecMove.z;

	/* ���[�V�����̂��܂��܂ȍX�V */
	m_pActiveMotion->Play();

	/* �_���[�W�J�E���g�̃f�N�������g */
	m_nDamageCnt--;
	if(m_nDamageCnt < 0)	m_nDamageCnt = 0;

	//----------------------------------
	//	�L�����N�^�Ɋւ���f�[�^�̑��M
	//----------------------------------
	/* �J�E���^�[�̃C���N�������g */
	static int nSendCnt=0;
	nSendCnt++;

	/* �E�����U �������� */
	if(m_matBase._42 < -120.0f)
	{
		m_matBase._41 = 0;
		m_matBase._42 = 0;
		m_matBase._43 = 0;
	}

}

//------------------------------------------------------------------
//	Name:	ComputNextAction
//	Func:	�R���s���[�^�̎��̍s���������_���Ō��߂�
//	in:		CEffectManage* pEffectManage	= �G�t�F�N�g�Ǘ��N���X
//	Out:	�Ȃ�
//------------------------------------------------------------------
void CEnemyCPU::ComputNextAction(CEffectManage* pEffectManage)
{
	int nTmp;

	/* �s���𑱂��鎞�Ԃ�10�t���[���`30�t���[�����烉���_���Ō��߂� */

	srand((unsigned int)time(NULL));		// �����_���̏�����
	m_nActionCount = rand()%20 + 10;


	/* ���݂̍s���ɂ�莟�̍s���������_���ɂČ��߂� */
	static time_t t;
	srand((unsigned int)(t * time(&t)));		// �����_���̏�����
	switch(m_nNowAction)
	{
	/* �X�^�[�g�� �������Ȃ� */
	case START:
		m_nNextStatus = START;
		break;

	/* �����Ă��鎞 */
	case WALK:
		/* �S���ŕ����B�Q���Ń_�b�V���B�Q���ŃW�����v�B�Q���ōU���\��  */
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 4)	m_nNextStatus = WALK;
		else if	(4 <= nTmp && nTmp < 6)	m_nNextStatus = DASH;
		else if	(6 <= nTmp && nTmp < 8)	m_nNextStatus = JUMP_START;
		else							m_nNextStatus = ATTACK_S;

		/* �_�b�V���Ɉڍs����ۂ̏����� */
		if(m_nNextStatus == DASH)
		{
			/* �G�l���M�[��1/3�ȏ�c���Ă���΃_�b�V���̏����� */
			if( (float)m_nNowEnergy / (float)m_pParam->nMaxEnergy > 0.35f ){
				m_fSpeed = 0;
			}
			/* �����łȂ���΃_�b�V�������� ����ϕ��� */
			else	m_nNextStatus = WALK;
		}

		/* �W�����v�J�n�Ɉڍs����ۂ̏����� */
		if(m_nNextStatus == JUMP_START)
		{
			/* �W�����v�Ɉڍs����܂ł̃J�E���^�[���Z�b�g */
			m_nCnt = 15;
		}

		/* �U���\���Ɉڍs����ۂ̏����� */
		if(m_nNextStatus == ATTACK_S)
		{
			/* �X�s�[�h���O�ɂ��� */
			m_fSpeed = 0;
		}
		break;

	/* �_�b�V�����Ă��鎞 */
	case DASH:
		/* �U���ŕ����B �S���Ń_�b�V���B*/
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 6)		m_nNextStatus = WALK;
		else								m_nNextStatus = DASH;

		/* �_�b�V���𑱂��邽�߂̏��� */
		if(m_nNextStatus = DASH)
			/* �G�l���M�[���Ȃ��ƃ_�� */
			if(m_nNowEnergy <= 0)	m_nNextStatus = WALK;

		break;

	/* �W�����v�J�n��  �������Ȃ� */
	case JUMP_START:
		m_nNextStatus = JUMP_START;
		break;
	
	/* �W�����v�� �U���Ŕ�s�B�S���ŃW�����v */
	case JUMP_MAIN:
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 6)		m_nNextStatus = FLYGHT;
		else								m_nNextStatus = JUMP_MAIN;

		/* ��s�Ɉڍs����ۂ̏���*/
		if(m_nNextStatus == FLYGHT)
		{
			/* �G�l���M�[��1/3�ȏ�c���Ă��Ȃ���΃_�� */
			if( (float)m_nNowEnergy / (float)m_pParam->nMaxEnergy < 0.35f )
				m_nNextStatus = JUMP_MAIN;
		}

		break;

	/* �W�����v�I���� �������Ȃ� */
	case JUMP_END:
		m_nNextStatus = JUMP_START;
		break;

	/* ��s�� �U���ŃW�����v�B�S���Ŕ�s�B */
	case FLYGHT:
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 6)	m_nNextStatus = FLYGHT;
		else							m_nNextStatus = JUMP_MAIN;

		/* ��s�𑱂��邽�߂̏��� */
		if(m_nNextStatus = FLYGHT)
			/* �G�l���M�[���Ȃ��ƃ_�� */
			if(m_nNowEnergy <= 0)	m_nNextStatus = JUMP_MAIN;

		break;

	/* �U���\���� �P���ōU���\�� �V���ōU�� �Q���ŕ��� */
	case ATTACK_S:
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 1)	m_nNextStatus = ATTACK_S;
		else if	(1 <= nTmp && nTmp < 8)	m_nNextStatus = ATTACK;
		else							m_nNextStatus = WALK;

		/* �U���Ɉڍs����ۂ̏����� */
		if(m_nNextStatus == ATTACK)
		{
			m_pActiveMotion->SetBlend(ANI_ATA,  1.0f);			/* �u�����h�W�����i�[ */
			m_pActiveMotion->SetBlend(ANI_ATAS, 0.0f);
			m_nCnt = m_pActiveMotion->GetMaxTime(ANI_ATA);		/* ���[�V�����ő�t���[�����̎擾 */
			m_pActiveMotion->SetActiveTime(ANI_ATA, 0);			/* �A�j���[�V�������ݎ��Ԃ�0�� */
		}
		break;

	/* �U���� �������Ȃ� */
	case ATTACK:
		m_nNextStatus = ATTACK;
		break;

	/* �n��_���[�W�� �������Ȃ� */
	case DAMAGE_LAND:
		m_nNextStatus = DAMAGE_LAND;
		break;

	/* �󒆃_���[�W�� �������Ȃ� */
	case DAMAGE_AIR:
		m_nNextStatus = DAMAGE_AIR;
		break;

	/* �n�㎀�S�� �X���ŉ������Ȃ��B�P���Ő����Ԃ� */
	case DEAD_LAND:
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 9)	m_nNextStatus = DEAD_LAND;
		else							m_nNextStatus = JUMP_MAIN;

		/* �������鎞�̏��� */
		if(m_nNextStatus == JUMP_MAIN)
		{
			m_nNowLife = m_pParam->nMaxLife;				// �g�o���ő�ɉ�
			m_fJump = 0.5f;									// �W�����v�l���i�[
			m_nNowAction = JUMP_MAIN;						// �W�����v�Ɉڍs
			pEffectManage->AddEffect(REVIVAL, m_matBase);	// �����G�t�F�N�g
		}
		break;

	/* �󒆎��S�� �������Ȃ� */
	case DEAD_AIR:
		m_nNextStatus = DEAD_AIR;
		break;
	}

	/* ���ʏ��� ���̍s�����W�����v�̏ꍇ�Ɍ���A�s���J�E���^�[�𔼕��ɂ��� */
	if(m_nNextStatus == JUMP_MAIN)
		m_nActionCount /= 2;

	/* ���z�L�[�������_���Ō��߂� */

	/* ���z�L�[�������� */
	m_tagVirtualKey.Up = false;
	m_tagVirtualKey.Down = false;
	m_tagVirtualKey.Left = false;
	m_tagVirtualKey.Right = false;

	/* �㉺�����߂� �U���ŏ� �P���ŉ� �R���Ŗ���*/
	srand((unsigned int)time(NULL));		// �����_���̏�����
	nTmp = rand()%10;
	if		(0 <= nTmp && nTmp < 6)		m_tagVirtualKey.Up = true;
	else if	(nTmp == 6)					m_tagVirtualKey.Down = true;

	/* ���E�����߂� �U���Ŗ��� �Q���ŉE �Q���ō� */
	srand((unsigned int)time(NULL));		// �����_���̏�����
	nTmp = rand()%10;
	if		(0 <= nTmp && nTmp < 2)	m_tagVirtualKey.Right = true;
	else if	(2 <= nTmp && nTmp < 4)	m_tagVirtualKey.Left = true;

}

//------------------------------------------------------------------
//	Name:	Start
//	Func:	�Q�[���X�^�[�g��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------------------
void CEnemyCPU::Start()
{
//	static nCnt = 0;

	/* �R�b�ԑ҂� */
//	m_nCnt++;
	/* �R�b��������WALK�Ɉڍs���� */
//	if(m_nCnt>180)	m_nNowAction = WALK;
}

//------------------------------------------------------
//	Name:	Walk
//	Func:	�����Ă���s��
//	in:		CStage* pStage = �X�e�[�W�N���X�ւ̃|�C���^
//	Out:	�Ȃ�
//------------------------------------------------------
void CEnemyCPU::Walk(CStage* pStage)
{
	//--------------------------
	//	���͊֌W�̏���
	//--------------------------
	/* ���ɐ��񂷂� */
	if(m_tagVirtualKey.Left)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* �E�ɐ��񂷂� */
	else if(m_tagVirtualKey.Right)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* �O�ɐi�� */
	if(m_tagVirtualKey.Up)	
	{
		m_fSpeed = m_pParam->fWalkSpeed;
		m_fMoveYaw = m_fCharaYaw;
		m_pActiveMotion->ChangeMotion(ANI_FORWARD);
	}

	/* ���֌�ނ��� */
	else if(m_tagVirtualKey.Down)
	{
		m_fSpeed = m_pParam->fBackSpeed;
		m_fMoveYaw = m_fCharaYaw-180.0f;
		m_pActiveMotion->ChangeMotion(ANI_BACK);
	}

	/* �O�ɂ����ɂ��i�܂Ȃ� */
	else
	{
		m_fSpeed = 0;
		m_fMoveYaw = m_fCharaYaw;
		m_pActiveMotion->ChangeMotion(ANI_STOP);
	}

	/* �G�l���M�[�̉� */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

	//--------------------------
	//	�Ǌ֌W�̏���
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* �����̒n�ʂ𒲂ׁA�������ʂ���苗��(��������)�ȏ�A*/
	/* ���邢�͌�����Ȃ�������W�����v�ֈڍs */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) > HIT_GROUND+1.5f)
	{
		m_nNowAction = JUMP_MAIN;
	}
	// �ʂ���苗���ȓ��Ɍ��������ꍇ�i�����Ă���ƌ��Ȃ��ꂽ�ꍇ�j
	else
	{
		m_matBase._42 = vecTmp.y + 5.0f;				// �L�����̑����n�ʂɂ��Ă���悤�ɏC��
		m_vecMove = GetVecToPlane(&plaTmp, m_fMoveYaw);	// �ړ��p�x�ƒn�ʂ���P�ʕ����x�N�g���̎擾
	}

	/* �ǂ𒲂ׁA�������ʂ���苗�����Ȃ�ǂɉ����Đi�� */
	D3DXVECTOR3 vecCross1,vecCross2;
	if(SearchAllWall(pStage, &vecCross1, &vecCross2) < HIT_WALL)
	{
		m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
		if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);

		m_nActionCount = 0;		// �����ɁA���̍s���Ɉڂ�
	}
}

//--------------------------------------------------------------------------
//	Name:	Dash
//	Func:	�_�b�V���s��
//	in:		CStage*			pStage			= �X�e�[�W�N���X�|�C���^
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X�|�C���^
//	Out:	�Ȃ�
//--------------------------------------------------------------------------
void CEnemyCPU::Dash(CStage* pStage, CEffectManage* pEffectManage)
{
	//--------------------------
	//	���͊֌W�̏���
	//--------------------------
	D3DXVECTOR3	vecNew;		// ����ł̕����x�N�g��
	vecNew *= 0;
	int		nFB=0, nLR=0;	// ���͕��������[�V���������̈׊i�[����

	/* �Ƃ肠��������̃X�s�[�h������������ */
	m_fSpeed = 0.0f;

	/* ���Ƀ_�b�V������ */
	if(m_tagVirtualKey.Left)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.x = -1.0f;
		nLR = ANI_DASH_L;
	}
	/* �E�Ƀ_�b�V������ */
	else if(m_tagVirtualKey.Right)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.x = 1.0f;
		nLR = ANI_DASH_R;
	}

	/* �O���Ƀ_�b�V������ */
	if(m_tagVirtualKey.Up)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.z = 1.0f;
		nFB = ANI_DASH_F;
	}
	/* ����Ƀ_�b�V������ */
	else if(m_tagVirtualKey.Down)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.z = -1.0f;
		nFB = ANI_DASH_B;
	}

	/* �L�����N�^�[�̌����Ă�������ɏC�� */
	D3DXMATRIX	matTmp;
	D3DXMatrixRotationY(&matTmp, D3DXToRadian(m_fCharaYaw) );
	D3DXVec3TransformCoord(&vecNew, &vecNew, &matTmp);
	/* ����̕����x�N�g������ړ������p�x�����߂� */
	m_fMoveYaw = (float)GetAngle((double)vecNew.x, (double)vecNew.z);

	/* �G�l���M�[�̌��� */
	m_nNowEnergy -= USE_ENERGY_DASH;

	/* �G�t�F�N�g�����t���[�����ɂP�񔭐� */
	if(m_nCnt%EFFECT_DASH == 0)
	{
		pEffectManage->AddEffect(BOOST_A, m_matBase);
	}
	m_nCnt++;

	//--------------------------
	//	���[�V�����̕ύX
	//--------------------------
	/* �c������������Ă���Ƃ� */
	if(nFB && nLR)	m_pActiveMotion->ChangeMotion(nFB, nLR, 0.1f);

	/* �c����������Ă���Ƃ� */
	else if(nFB)	m_pActiveMotion->ChangeMotion(nFB, 0.05f);
	/* ������������Ă���Ƃ� */
	else if(nLR)	m_pActiveMotion->ChangeMotion(nLR, 0.05f);
	/* ����������Ă��Ȃ��Ƃ� */
	else			m_pActiveMotion->ChangeMotion(ANI_DASH_F, 0.05f);

	//--------------------------
	//	�Ǌ֌W�̏���
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* �����̒n�ʂ𒲂ׁA�������ʂ���苗��(��������)�ȏ�A*/
	/* ���邢�͌�����Ȃ�������W�����v�ֈڍs */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) > HIT_GROUND+1.5f)
		m_nNowAction = JUMP_MAIN;

	/* �ʂ���苗���ȓ��Ɍ��������ꍇ�i�����Ă���ƌ��Ȃ��ꂽ�ꍇ�j*/
	else
	{
		m_matBase._42 = vecTmp.y + 5.0f;				// �L�����̑����n�ʂɂ��Ă���悤�ɏC��
		m_vecMove = GetVecToPlane(&plaTmp, m_fMoveYaw);	// �ړ��p�x�ƒn�ʂ���P�ʕ����x�N�g���̎擾
	}

	/* �ǂ𒲂ׁA�������ʂ���苗�����Ȃ�ǂɉ����Đi�� */

	D3DXVECTOR3 vecCross1,vecCross2;
	if(SearchAllWall(pStage, &vecCross1, &vecCross2) < HIT_WALL)
	{
		m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
		if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);


		m_nActionCount = 0;		// �����ɁA���̍s���Ɉڂ�
	}
}

//----------------------------------------------
//	Name:	Attack_S
//	Func:	�U���\���s��
//	in:		�Ȃ�
//	Out:	����
//----------------------------------------------
void CEnemyCPU::Attack_S()
{
	static float fNextYaw;		// �ڕWYaw�p�x
	static float fMoveSpeed;	// �J�����ړ����x

	/* ���ɐ��񂷂� */
	if(m_tagVirtualKey.Left)
		m_fCharaYaw -= m_pParam->fTurn/2;

	/* �E�ɐ��񂷂� */
	else if(m_tagVirtualKey.Right)
		m_fCharaYaw += m_pParam->fTurn/2;

	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;

	/* ���[�V�����̍X�V */
	m_pActiveMotion->ChangeMotion(ANI_ATAS);

	/* �G�l���M�[�̉� */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

}

//------------------------------------------------------
//	Name:	Attack
//	Func:	�U���s��
//	in:		CBulManage* pBulManage = �e�Ǘ��N���X�|�C���^
//	Out:	�Ȃ�
//------------------------------------------------------
void CEnemyCPU::Attack(CBulManage* pBulManage)
{
	/* ����̃t���[�������e���o�� */
	if(m_nCnt == m_pActiveMotion->GetMaxTime(ANI_ATA))
	{
		D3DXMATRIX matTmp;
		D3DXMatrixIdentity(&matTmp);

		/* �����Ă�������ɒe������ */
		D3DXMatrixRotationX(&matTmp, D3DXToRadian(-m_fCharaPitch));

		/* ���W�l��������x��̈ʒu�ɏC�� */
		matTmp._41 += 0.0f;
		matTmp._42 += 3.5f;
		matTmp._43 += 0.0f;

		/* �e���o������ */
		matTmp = matTmp * m_matBase;
		pBulManage->AddBullet(0, matTmp, m_nNum);

	}

	// �A�j���[�V�������̏���
	if(m_nCnt > 0)
	{
		/* �A�j���[�V�����J�E���^�[�����炷 */
		m_nCnt--;
	}

	// �A�j���[�V�����I��
	// �u�����h�W�������ɖ߂��AATTACK_S�Ɉڍs����
	else
	{
		/* �u�����h�W�������ɖ߂� */
		m_pActiveMotion->SetBlend(ANI_ATAS, 1.0f);
		m_pActiveMotion->SetBlend(ANI_ATA,	0.0f);
		m_nNowAction = ATTACK_S;
	}

	/* �G�l���M�[�̉� */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

}

//------------------------------------------------------------------
//	Name:	JumpStart
//	Func:	�W�����v�J�n�s��
//	in:		CStage*			pStage		  = �X�e�[�W�N���X
//			CEffectManage*	pEffectManage = �G�t�F�N�g�Ǘ��N���X
//	Out:	����
//------------------------------------------------------------------
void CEnemyCPU::JumpStart(CStage* pStage, CEffectManage* pEffectManage)
{
	/* �J�E���^�[�������ԁA�W�����v�J�n�s�������� */
	if(m_nCnt>0)
	{
		/* ���[�V�����̕ω� */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_S);

		// �J�E���^�[�����炵�Ă���
		m_nCnt--;

		/* �n�ʂ𒲂ׁA�������ʂ���苗��(�������Ȃ�)�ȉ��Ȃ璅�n���� */
		D3DXVECTOR3	vecTmp;
		if (SearchAllGround(pStage, NULL, &vecTmp) < 4.5f)
		{
			m_fJump = 0;
			m_matBase._42 = vecTmp.y + 5.0f;
			m_nNowAction = WALK;
		}

		/* �ǂ𒲂ׁA�������ʂ���苗�����Ȃ�ǂɉ����Đi�� */
		D3DXVECTOR3 vecCross1,vecCross2;
		if(SearchAllWall(pStage, &vecCross1, &vecCross2) < 2.0f)
		{
			m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
			if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);
		}

		/* �V��𒲂ׁA�V�䂪����������W�����v�l���Ȃ��� */
		if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < 4.0f)
		{
			m_fJump = 0;
		}

		/* �G�l���M�[�̉� */
		if(m_nNowEnergy < m_pParam->nMaxEnergy)
			m_nNowEnergy+=REST_ENERGY;

	}

	// �J�E���^�[���I�������玟�ɃW�����v�ł���܂ł̃J�E���g�l���Z�b�g���W�����v�Ɉڍs����
	else
	{
		m_nNowAction = JUMP_MAIN;
		m_fJump = m_pParam->fJumpUp;
		m_nCnt = 30;
	}

}

//----------------------------------------------
//	Name:	JumpMain
//	Func:	�W�����v�s��
//	in:		CStage* pStage = �X�e�[�W�N���X�ւ̃|�C���^
//	Out:	�Ȃ�
//----------------------------------------------
void CEnemyCPU::JumpMain(CStage* pStage)
{
	/* ���ɐ��񂷂� */
	if(m_tagVirtualKey.Left)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* �E�ɐ��񂷂� */
	else if(m_tagVirtualKey.Right)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* �O�Ɉړ����� */
	if(m_tagVirtualKey.Up)
	{
		m_fSpeed = m_pParam->fJumpForward;

		/* �P�ʕ����x�N�g���̎擾 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

		/* ���[�V�����̕ω� */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_F);
	}

	/* ���Ɉړ����� */
	else if(m_tagVirtualKey.Down)
	{
		m_fSpeed = m_pParam->fJumpBack;

		/* �P�ʕ����x�N�g���̎擾 */
		m_vecMove = -GetNormalVec3ToMat(NULL, &m_matBase);

		/* ���[�V�����̕ω� */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_B);
	}
	/* ������������Ȃ������ꍇ */
	else
	{
		/* ���x�𗎂Ƃ��Ă��� */
		if((m_fSpeed-=0.05f) < 0.0f)	m_fSpeed = 0.0f;

		/* �P�ʕ����x�N�g���̎擾 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

		/* ���[�V�����̕ω� */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_N);
	}

	/* ���񂾂�n�ʂɗ����� */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* �G�l���M�[�̉� */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

	//------------------
	//	�Ǌ֌W�̏���
	//------------------
	/* �n�ʂ𒲂ׁA�������ʂ���苗��(�������Ȃ�)�ȉ��Ȃ璅�n���� */
	D3DXVECTOR3	vecTmp;
	if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND-0.5f)
	{
		m_fJump = 0;
		m_matBase._42 = vecTmp.y + 5.0f;
		m_nNowAction = WALK;
	}

	/* �ǂ𒲂ׁA�������ʂ���苗�����Ȃ�ǂɉ����Đi�� */
	D3DXVECTOR3 vecCross1,vecCross2;
	if(SearchAllWall(pStage, &vecCross1, &vecCross2) < HIT_WALL)
	{
		m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
		if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);

		m_nActionCount = 0;		// �����ɁA���̍s���Ɉڂ�
	}

	/* �V��𒲂ׁA�V�䂪����������W�����v�l���Ȃ��� */
	if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
	{
		m_fJump = 0;
	}

}

//----------------------------------------------
//	Name:	JumpEnd
//	Func:	�W�����v�I����
//	in:		����
//	Out:	����
//----------------------------------------------
void CEnemyCPU::JumpEnd()
{

}

//------------------------------------------------------------------
//	Name:	Flyght
//	Func:	���ł���s��
//	in:		CStage*			pStage		  = �X�e�[�W�N���X
//			CEffectManage*	pEffectManage = �G�t�F�N�g�Ǘ��N���X
//	Out:	����
//------------------------------------------------------------------
void CEnemyCPU::Flyght(CStage* pStage, CEffectManage* pEffectManage)
{
	/* ���ɐ��񂷂� */
	if(m_tagVirtualKey.Left)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* �E�ɐ��񂷂� */
	else if(m_tagVirtualKey.Right)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* �O�Ɉړ����� */
	if(m_tagVirtualKey.Up)
	{
		/* �O�ɐi�� */
		m_fSpeed = m_pParam->fFlyForward;
		/* ���[�V�����̕ω� */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_F);
		/* �P�ʕ����x�N�g���̎擾 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

		/* �W�����v�l���O�ɋ߂Â��� */
		if(m_fJump>0)		m_fJump -= 0.02f;
		else if(m_fJump<0)	m_fJump += 0.02f; 
	}

	/* ���Ɉړ����� */
	else if(m_tagVirtualKey.Down)
	{
		/* ���ɐi�� */
		m_fSpeed = m_pParam->fFlyBack;
		/* ���[�V�����̕ω� */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_B);
		/* �P�ʕ����x�N�g���̎擾 */
		m_vecMove = -GetNormalVec3ToMat(NULL, &m_matBase);

		/* �W�����v�l���O�ɋ߂Â��� */
		if(m_fJump>0)		m_fJump -= 0.02f;
		else if(m_fJump<0)	m_fJump += 0.02f; 
	}

	/* ������������Ȃ������ꍇ */
	else
	{
		/* ���񂾂�㏸���Ă��� */
		if( (m_fJump+=m_pParam->fFlyPlumb) > 0.8f)	m_fJump = 0.8f;

		/* �ړ��̑��x�𗎂Ƃ��Ă��� */
		if((m_fSpeed-=0.03f) < 0.0f)	m_fSpeed = 0.0f;
		/* ���[�V�����̕ω� */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_N);
		/* �P�ʕ����x�N�g���̎擾 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);
	}

	/* �G�l���M�[�̌��� ��s���͂Q�����炷 */
	m_nNowEnergy -= USE_ENERGY_FLY;

	/* �G�t�F�N�g�����t���[���Ɉ�񔭐� */
	static int nCnt = 0;
	if(nCnt%EFFECT_FLY == 0)
	{
		pEffectManage->AddEffect(BOOST_B, m_matBase);
	}
	nCnt++;

	//------------------
	//	�Ǌ֌W�̏���
	//------------------
	/* �n�ʂ𒲂ׁA�������ʂ���苗���ȉ��Ȃ璅�n���� */
	D3DXVECTOR3	vecTmp;
	if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND)
	{
		m_fJump = 0;
		m_matBase._42 = vecTmp.y + 5.0f;
		m_nNowAction = WALK;
	}

	/* �ǂ𒲂ׁA�������ʂ���苗�����i�������߁j�Ȃ�ǂɉ����Đi�� */
	D3DXVECTOR3 vecCross1,vecCross2;
	if(SearchAllWall(pStage, &vecCross1, &vecCross2) < HIT_WALL+1.0f)
	{
		m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
		if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);

		m_nActionCount = 0;		// �����ɁA���̍s���Ɉڂ�
	}

	/* �V��𒲂ׁA�V�䂪����������W�����v�l���Ȃ��� */
	if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
	{
		m_fJump = 0;
	}
}

//------------------------------------------------------------------
//	Name:	DamageLand
//	Func:	�_���[�W������L�������n�ʂɂ���
//	in:		CStage*			pStage			= �X�e�[�W�N���X
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X
//	Out:	����
//------------------------------------------------------------------
void CEnemyCPU::DamageLand(CStage* pStage, CEffectManage* pEffectManage)
{
	/* ���삷�鎖�͈�؏o���Ȃ� */

	/* �X�s�[�h�l�����炵�Ă��� */
	m_fSpeed -= m_pParam->fBrakes;

	/* �X�s�[�h�l���O�ɂȂ����猳�ɖ߂� */
	if(m_fSpeed < 0)
		m_nNowAction = WALK;

	/* ���[�V�����̕ω� */
	m_pActiveMotion->ChangeMotion(ANI_DAM_L);

	//--------------------------
	//	�Ǌ֌W�̏���
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* �����̒n�ʂ𒲂ׁA�������ʂ���苗���i�������߁j�ȏ�A*/
	/* ���邢�͌�����Ȃ�������󒆃_���[�W�ֈڍs */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) > HIT_GROUND+1.0f)
	{
		m_nNowAction = DAMAGE_AIR;
	}

	// �ʂ���苗���ȓ��Ɍ��������ꍇ�i�����Ă���ƌ��Ȃ��ꂽ�ꍇ�j
	else
	{
		m_matBase._42 = vecTmp.y + 5.0f;				// �L�����̑����n�ʂɂ��Ă���悤�ɏC��
		m_vecMove = GetVecToPlane(&plaTmp, m_fMoveYaw);	// �ړ��p�x�ƒn�ʂ���P�ʕ����x�N�g���̎擾
	}

	/* �ǂ𒲂ׁA�������ʂ���苗�����i�������߁j�Ȃ�i�܂Ȃ��i�I�j */
	if(SearchAllWall(pStage, NULL, NULL) < HIT_WALL+1.0f)
		m_vecMove *= 0;
}

//------------------------------------------------------------------
//	Name:	DamageAir
//	Func:	�_���[�W������L�������󒆂ɂ���
//	in:		CStage*			pStage			= �X�e�[�W�N���X
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X
//	Out:	����
//------------------------------------------------------------------
void CEnemyCPU::DamageAir(CStage* pStage, CEffectManage* pEffectManage)
{
	/* ���삷�鎖�͈�؏o���Ȃ� */

	/* �X�s�[�h�l�����炵�Ă��� */
	m_fSpeed -= m_pParam->fBrakes;

	/* ���񂾂�n�ʂɗ����� */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* �X�s�[�h�l���O�ɂȂ����猳�ɖ߂� */
	if(m_fSpeed < 0)
		m_nNowAction = JUMP_MAIN;

	/* ���[�V�����̕ω� */
	m_pActiveMotion->ChangeMotion(ANI_DAM_A);

	//------------------
	//	�Ǌ֌W�̏���
	//------------------
	/* �n�ʂ𒲂ׁA�������ʂ���苗���ȉ��Ȃ�n�ʃ_���[�W�ֈڍs���� */
	D3DXVECTOR3	vecTmp;
	if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND)
	{
		m_fJump = 0;
		m_matBase._42 = vecTmp.y + 5.0f;
		m_nNowAction = DAMAGE_LAND;
	}

	/* �ǂ𒲂ׁA�������ʂ���苗�����i�������߁j�Ȃ�i�܂Ȃ��i�I�j */
	if(SearchAllWall(pStage, NULL, NULL) < HIT_WALL+1.0f)
		m_vecMove *= 0;

	/* �V��𒲂ׁA�V�䂪����������W�����v�l���Ȃ��� */
	if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
	{
		m_fJump = 0;
	}

}

//------------------------------------------------------------------
//	Name:	DeadLand
//	Func:	�L�������n�ʂɂ��Ď���ł�����
//	in:		CStage*			pStage			= �X�e�[�W�N���X
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X
//	Out:	����
//------------------------------------------------------------------
void CEnemyCPU::DeadLand(CStage* pStage, CEffectManage* pEffectManage)
{
	/* ���삷�鎖�͈�؏o���Ȃ� */

	/* �X�s�[�h�l�����炵�Ă��� */
	m_fSpeed -= m_pParam->fBrakes;
	if(m_fSpeed < 0)	m_fSpeed = 0;

	/* ���[�V�����̕ω� */
	m_pActiveMotion->ChangeMotion(ANI_DEAD_L, 0.05f);

	//--------------------------
	//	�Ǌ֌W�̏���
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* �����̒n�ʂ𒲂ׁA�������ʂ���苗���i�������߁j�ȏ�A*/
	/* ���邢�͌�����Ȃ�������󒆎��S�ֈڍs */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) > HIT_GROUND+1.0f)
	{
		m_nNowAction = DEAD_AIR;
	}

	/* �ʂ���苗���ȓ��Ɍ��������ꍇ�i�|��Ă���Ƃ݂Ȃ��ꂽ�ꍇ�j */
	else
	{
		m_matBase._42 = vecTmp.y + 5.0f;				// �L�����̑����n�ʂɂ��Ă���悤�ɏC��
		m_vecMove = GetVecToPlane(&plaTmp, m_fMoveYaw);	// �ړ��p�x�ƒn�ʂ���P�ʕ����x�N�g���̎擾
	}

	/* �ǂ𒲂ׁA�������ʂ���苗�����i�������߁j�Ȃ�i�܂Ȃ��i�I�j */
	if(SearchAllWall(pStage, NULL, NULL) < HIT_WALL+1.0f)
		m_vecMove *= 0;
}

//------------------------------------------------------------------
//	Name:	DeadAir
//	Func:	�L�������󒆂ɂ��Ď���ł�����
//	in:		CStage*			pStage			= �X�e�[�W�N���X
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X
//	Out:	����
//------------------------------------------------------------------
void CEnemyCPU::DeadAir(CStage* pStage, CEffectManage* pEffectManage)
{
	/* ���삷�鎖�͈�؏o���Ȃ� */

	/* �X�s�[�h�l�����炵�Ă��� */
	m_fSpeed -= m_pParam->fBrakes;
	if(m_fSpeed < 0)	m_fSpeed = 0;

	/* ���񂾂�n�ʂɗ����� */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* ���[�V�����̕ω� */
	m_pActiveMotion->ChangeMotion(ANI_DEAD_A, 0.05f);

	//------------------
	//	�Ǌ֌W�̏���
	//------------------
	/* �n�ʂ𒲂ׁA�������ʂ���苗���ȉ��Ȃ�n�ʃ_���[�W�ֈڍs���� */
	D3DXVECTOR3	vecTmp;
	if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND)
	{
		m_fJump = 0;
		m_matBase._42 = vecTmp.y + 5.0f;
		m_nNowAction = DEAD_LAND;
	}

	/* �ǂ𒲂ׁA�������ʂ���苗�����i�������߁j�Ȃ�i�܂Ȃ��i�I�j */
	if(SearchAllWall(pStage, NULL, NULL) < HIT_WALL+1.0f)
		m_vecMove *= 0;

	/* �V��𒲂ׁA�V�䂪����������W�����v�l���Ȃ��� */
	if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
	{
		m_fJump = 0;
	}

}