//==========================================================
// MyPlayer.cpp
// Auther : ���� ���V
// Data   : 2002/05/05
//==========================================================
#include "MyPlayer.h"

//------------------------------------------------------
//	Name:	MyPlayer
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3D�f�o�C�X
//	Out:	�Ȃ�
//------------------------------------------------------
CMyPlayer::CMyPlayer(LPDIRECT3DDEVICE8 d3dDevice):CChara(d3dDevice)
{
	/* ���b�N�I���֌W�̕ϐ��̏����� */
	for(int i=0; i<3; i++)
	{
		m_bCanLock[i]	= false;
		m_vecProject[i] *= 0;
		m_vecView[i]	*= 0;

		/* ���b�N�I���}�[�J�[�̍쐬 */
		m_pLockMarker[i] = new CLockOnMarker(m_pd3dDevice, const_cast<TCHAR*>("data\\Game\\LockOn.png"));
		m_pLockMarker[i]->SetRec(0,0, 64, 64);

		/* �L�����N�^���C�t�t�H���g�̏����� */
		m_pCharaLife[i] = NULL;

		/* �L�����N�^���O�t�H���g�̏����� */
		m_pCharaName[i] = NULL;
	}

	m_bNowLock = false;
 	m_nLockTarget = -1;

	/* �ėp�J�E���^�̏����� */
	m_nCnt = 0;

	/* �s���̏����� */
	m_nNowAction = WALK;
}

//------------------------------------------------------
//	Name:	~MyPlayer
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------
CMyPlayer::~CMyPlayer()
{
	/* �g�p�����������̊J�� */
	for(int i=0; i<3; i++)
	{
		SAFE_DELETE(m_pLockMarker[i]);
		SAFE_DELETE(m_pCharaName[i]);
		SAFE_DELETE(m_pCharaLife[i]);
	}
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
void CMyPlayer::FrameMoveGame(CStage* pStage, CBulManage* pBulManage, 
			CSpriteManage* pSpriteManage,CEffectManage* pEffectManage)
{
	int i;

	/* �A���O���t�o�ƃA���O���c�n�v�m�𓯎��ɉ����A�܂���	 */
	/* �p�x�������L�[�������Ɗp�x������������				 */
	if( ( GetAsyncKeyState(KEY_ANGLE_UP)&0x8000 ) &&  ( GetAsyncKeyState(KEY_ANGLE_DOWN)&0x8000 ) ||
		GetAsyncKeyState(KEY_ANGLE_FORMAT) & 0x8000)
		m_fCharaPitch = 0.0f;


	/* �A���O���t�o�܂��̓A���O������{���������Ə������ */
	else if	(GetAsyncKeyState(KEY_ANGLE_UP) & 0x8000 || 
			(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) && (GetAsyncKeyState(VK_DOWN)&0x8000) )
		m_fCharaPitch += m_pParam->fTurn/2;

	/* �A���O���c�n�v�m�܂��̓A���O������{���������Ɖ������� */
	else if	(GetAsyncKeyState(KEY_ANGLE_DOWN) & 0x8000 || 
			(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) && (GetAsyncKeyState(VK_UP)&0x8000) )
		m_fCharaPitch -= m_pParam->fTurn/2;

	/* �p�x��-60�`60�̊ԂŔ��� */
	if(m_fCharaPitch < -60.0f)		m_fCharaPitch = -60.0f;
	else if(m_fCharaPitch > 60.0f)	m_fCharaPitch = 60.0f;	


	/* ���b�N�I���Ɋւ��鏈�� */
	LockOn(pStage);

	/* �e�Ƃ̓����蔻�� */
	IsHitBullet(pBulManage, pEffectManage);

	/* �L�����N�^�[�̍s���ɂ�菈���𕪂��� */
	switch(m_nNowAction)
	{
	case START:			Start(pSpriteManage);						break;
	case WALK:			Walk(pStage);								break;
	case DASH:			Dash(pStage, pEffectManage);				break;

	case JUMP_MAIN:		JumpMain(pStage);							break;
	case JUMP_START:	JumpStart(pStage, pEffectManage);			break;
	case JUMP_END:		JumpEnd();									break;
	case FLYGHT:		Flyght(pStage, pEffectManage);				break;

	case ATTACK_S:		Attack_S();									break;
	case ATTACK:		Attack(pBulManage);							break;

	case DAMAGE_LAND:	DamageLand(pStage, pEffectManage);			break;
	case DAMAGE_AIR:	DamageAir(pStage, pEffectManage);			break;

	case DEAD_LAND:		DeadLand(pStage, pEffectManage);			break;
	case DEAD_AIR:		DeadAir(pStage, pEffectManage);				break;

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

	/* �G�L�����̃��C�t�t�H���g�̍X�V */
	for(i=0; i<3; i++)
	{
		m_pCharaLife[i]->SetString(*m_tagEnemyData[i].pNowLife);
	}

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
//	Name:	Start
//	Func:	�Q�[�����J�n����
//	in:		CSpriteManage* pSpriteManage = �X�v���C�g�Ǘ��N���X
//	Out:	�Ȃ�
//------------------------------------------------------------------
void CMyPlayer::Start(CSpriteManage* pSpriteManage)
{
	/* �Ă΂�Ȃ�����Ӗ����Ȃ� */
	/* ���݂܂�������Y��Ă��܂��� */
}

//------------------------------------------------------
//	Name:	Walk
//	Func:	�����Ă���s��
//	in:		CStage* pStage = �X�e�[�W�N���X�ւ̃|�C���^
//	Out:	�Ȃ�
//------------------------------------------------------
void CMyPlayer::Walk(CStage* pStage)
{
	//--------------------------
	//	���͊֌W�̏���
	//--------------------------
	/* ���ɐ��񂷂� */
	if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* �E�ɐ��񂷂� */
	else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* �O�ɐi�� */
	if(	GetAsyncKeyState(KEY_FORWARD)&0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )	
	{
		m_fSpeed = m_pParam->fWalkSpeed;
		m_fMoveYaw = m_fCharaYaw;
		m_pActiveMotion->ChangeMotion(ANI_FORWARD);
	}

	/* ���֌�ނ��� */
	else if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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

	/* �G�l���M�[��1/3�ȏ�c���Ă���ꍇ�̓_�b�V������ */
	if(	GetAsyncKeyState(KEY_DASH) & 0x8000 &&
		(float)m_nNowEnergy / (float)m_pParam->nMaxEnergy > 0.35f)
	{
		/* ���ݑ��x�����������ă_�b�V���s���Ɉڍs */
		m_fSpeed = 0;
		m_nNowAction = DASH;
		m_nCnt = 0;
	}

	/* �W�����v���� */
	else if(GetAsyncKeyState(KEY_JUMP) & 0x8000)
	{
		/* �J�E���g�l���i�[���ăW�����v�J�n�s���Ɉڍs */
		m_nCnt = 15;
		m_nNowAction = JUMP_START;
	}

	/* ������\���� */
	if(GetAsyncKeyState(KEY_ATAS) & 0x8000)
	{
		// �L�����N�^�[���Ƃ߂�
		m_fSpeed = 0;

		// ����\���s���Ɉڍs
		m_nNowAction = ATTACK_S;
	}

	/* �G�l���M�[�̉� */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

	//--------------------------
	//	�Ǌ֌W�̏���
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* �����̒n�ʂ𒲂ׁA�������ʂ���苗���i�������߁j�ȏ�A*/
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
	}
}

//--------------------------------------------------------------------------
//	Name:	Dash
//	Func:	�_�b�V���s��
//	in:		CStage*			pStage			= �X�e�[�W�N���X�|�C���^
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X�|�C���^
//	Out:	�Ȃ�
//--------------------------------------------------------------------------
void CMyPlayer::Dash(CStage* pStage, CEffectManage* pEffectManage )
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
	if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.x = -1.0f;
		nLR = ANI_DASH_L;
	}
	/* �E�Ƀ_�b�V������ */
	else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.x = 1.0f;
		nLR = ANI_DASH_R;
	}

	/* �O���Ƀ_�b�V������ */
	if(GetAsyncKeyState(KEY_FORWARD) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.z = 1.0f;
		nFB = ANI_DASH_F;
	}
	/* ����Ƀ_�b�V������ */
	else if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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

	/* SHIFT�𗣂��A�܂��G�l���M�[�������ꍇ��WALK�Ɉڍs���� */
	if(!(GetAsyncKeyState(KEY_DASH)&0x8000) || m_nNowEnergy <= 0)
	{
		m_nNowAction = WALK;
	}

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
	/* �����̒n�ʂ𒲂ׁA�������ʂ���苗���i�������߁j�ȏ�A*/
	/* ���邢�͌�����Ȃ�������W�����v�ֈڍs */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) >HIT_GROUND + 1.5f)
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
	}
}

//----------------------------------------------
//	Name:	Attack_S
//	Func:	�U���\���s��
//	in:		�Ȃ�
//	Out:	����
//----------------------------------------------
void CMyPlayer::Attack_S()
{
	static float fNextYaw;		// �ڕWYaw�p�x
	static float fMoveSpeed;	// �J�����ړ����x

	/* ���b�N�I�����Ă���Ƃ� */
	if(m_bNowLock)
	{
		/* ���b�N�I�����Ă���ꍇ�͍\�����Ƃ��ɖڕW�̕��������� */

		/* �ڕW�p�x�̌v�Z */
		D3DXVECTOR3	vecTmp = GetLockVec() - GetPosBase();
		GetVec3Inverce(&vecTmp, &vecTmp);
		fNextYaw = (float)GetAngle(vecTmp.x, vecTmp.z);

		/* 360�𒴂�����C�� */
		if(fNextYaw >= 360.0f)			fNextYaw -= 360.0f;
		else if(fNextYaw < 0.0f)		fNextYaw += 360.0f;

		/* ���݊p�x��ڕW�p�x�ɋ߂Â��� */

		/* ����Yaw�A�ڕWYaw����P�t���[�����Ƃ̕�Ԉړ��ʂ����߂� */
		float fTmp;
		fTmp = m_fCharaYaw - fNextYaw + 180.0f;

		/* 360�𒴂�����C�� */
		if(fTmp >= 360.0f)		fTmp -= 360.0f;
		else if(fTmp < 0.0f)	fTmp += 360.0f;

		/* ���݊p�x�ƖڕW�p�x�����ȓ��Ȃ瓯���ɂ��� */
		if( fTmp <= 4.0f && fTmp >= -4.0f)
			m_fCharaYaw = fNextYaw + 180.0f;	

		/* �����i�}�C�i�X�j�̕����߂��� */
		else if(fTmp < 180.0f)
		{
			// �ړ��ʂ̎Z�o
			fMoveSpeed = fTmp / 10.0f;
			if(fMoveSpeed < 2.0f)	fMoveSpeed = 2.0f;
			// �L�����ʒu�̈ړ�
			m_fCharaYaw -= fMoveSpeed;
		}

		/* �E���i�v���X�j�̕����߂��� */
		else
		{
			// �ړ��ʂ̎Z�o
			fTmp = 360.0f - fTmp;
			fMoveSpeed = fTmp / 10.0f;
			if(fMoveSpeed < 2.0f)	fMoveSpeed = 2.0f;
			// �L�����ʒu�̈ړ�
			m_fCharaYaw += fMoveSpeed;
		}

		/* 360�𒴂�����C��*/
		if(m_fCharaYaw >= 360.0f)	m_fCharaYaw -= 360.0f;
		else if(m_fCharaYaw < 0.0f)	m_fCharaYaw += 360.0f;
	}

	/* ���b�N�I�����Ă��Ȃ��Ƃ� */
	else
	{
		/* ��L�[�Ŏ��������ɉ����� */
		if(GetAsyncKeyState(KEY_FORWARD) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
			if( (m_fCharaPitch-=m_pParam->fTurn/2) < -60.0f)	m_fCharaPitch = -60.0f;

		/* ���L�[�Ŏ�������ɂ����� */
		if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
			if( (m_fCharaPitch+=m_pParam->fTurn/2) > 60.0f)	m_fCharaPitch = 60.0f;

		/* ���ɐ��񂷂� */
		if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
			m_fCharaYaw -= m_pParam->fTurn/2;

		/* �E�ɐ��񂷂� */
		else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
			m_fCharaYaw += m_pParam->fTurn/2;

	}

	/* ���S�ɍ\���Ă���Ȃ�A�U������ */
	if(GetAsyncKeyState(KEY_ATTACK) & 0x8000 && m_pActiveMotion->GetBlend(ANI_ATAS)== 1.0f)
	{
		/* �u�����h�W�����i�[ */
		m_pActiveMotion->SetBlend(ANI_ATA,  1.0f);
		m_pActiveMotion->SetBlend(ANI_ATAS, 0.0f);

		/* ���[�V�����ő�t���[�����̎擾 */
		m_nCnt = m_pActiveMotion->GetMaxTime(ANI_ATA);

		/* �A�j���[�V�������ݎ��Ԃ�0�� */
		m_pActiveMotion->SetActiveTime(ANI_ATA, 0);

		/* �U���s���ֈڍs */
		m_nNowAction = ATTACK;
	}

	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;

	/* ���[�V�����̍X�V */
	m_pActiveMotion->ChangeMotion(ANI_ATAS);

	/* TAB�𗣂���WALK�Ɉڍs���� */
	if(!(GetAsyncKeyState(KEY_ATAS)&0x8000))
	{
		m_nNowAction = WALK;
	}

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
void CMyPlayer::Attack(CBulManage* pBulManage )
{
	static float fNextYaw;		// �ڕWYaw�p�x
	static float fMoveSpeed;	// �J�����ړ����x

	D3DXVECTOR3	vecTmp;

	/* ����̃t���[�������e���o�� */
	if(m_nCnt == m_pActiveMotion->GetMaxTime(ANI_ATA))
	{
		D3DXMATRIX matTmp;
		D3DXMatrixIdentity(&matTmp);

		// ���b�N�I�����Ă��鎞�͂��̑���̕��ɒe������
		if(m_bNowLock)
		{
			float		fTmp;
			float		fPitch;

			/* �L�������ڕW�ւ̃x�N�g���l�����߂� */
			vecTmp = GetLockVec() - GetPosBase();
			/* X,Z���̒��������߂� */
			fTmp = GetLengthEX(&vecTmp, true, false, true);
			/* Pitch��]�p�x�����߂� */
			fPitch = (float)GetAngle(vecTmp.y, fTmp);

			D3DXMatrixRotationX(&matTmp, D3DXToRadian(-fPitch));
		}

		/* ���b�N�I�����Ă��Ȃ����͌����Ă�������ɒe������ */
		else {
			D3DXMatrixRotationX(&matTmp, D3DXToRadian(-m_fCharaPitch));
		}

		// ���W�l��������x��̈ʒu�ɏC��
		matTmp._41 += 0.0f;
		matTmp._42 += 3.5f;
		matTmp._43 += 0.0f;

		// �e���o������
		matTmp = matTmp * m_matBase;
		pBulManage->AddBullet(0, matTmp, m_nNum);

		//----------------------------------
		//	�e�̔��˂������f�[�^�̑��M
		//----------------------------------

	}

	/* ���b�N�I�����Ă���Ƃ��͖ڕW�̕��������� */
	if(m_bNowLock)
	{

		/* �ڕW�p�x�̌v�Z */
		vecTmp = GetLockVec() - GetPosBase();
		GetVec3Inverce(&vecTmp, &vecTmp);
		fNextYaw = (float)GetAngle(vecTmp.x, vecTmp.z);

		/* 360�𒴂�����C�� */
		if(fNextYaw >= 360.0f)			fNextYaw -= 360.0f;
		else if(fNextYaw < 0.0f)		fNextYaw += 360.0f;

		/* ���݊p�x��ڕW�p�x�ɋ߂Â��� */

		/* ����Yaw�A�ڕWYaw����P�t���[�����Ƃ̕�Ԉړ��ʂ����߂� */
		float fTmp;
		fTmp = m_fCharaYaw - fNextYaw + 180.0f;

		/* 360�𒴂�����C�� */
		if(fTmp >= 360.0f)		fTmp -= 360.0f;
		else if(fTmp < 0.0f)	fTmp += 360.0f;

		/* ���݊p�x�ƖڕW�p�x�����ȓ��Ȃ瓯���ɂ��� */
		if( fTmp <= 4.0f && fTmp >= -4.0f)
			m_fCharaYaw = fNextYaw + 180.0f;	

		/* �����i�}�C�i�X�j�̕����߂��� */
		else if(fTmp < 180.0f)
		{
			// �ړ��ʂ̎Z�o
			fMoveSpeed = fTmp / 10.0f;
			if(fMoveSpeed < 2.0f)	fMoveSpeed = 2.0f;
			// �L�����ʒu�̈ړ�
			m_fCharaYaw -= fMoveSpeed;
		}

		/* �E���i�v���X�j�̕����߂��� */
		else
		{
			// �ړ��ʂ̎Z�o
			fTmp = 360.0f - fTmp;
			fMoveSpeed = fTmp / 10.0f;
			if(fMoveSpeed < 2.0f)	fMoveSpeed = 2.0f;
			// �L�����ʒu�̈ړ�
			m_fCharaYaw += fMoveSpeed;
		}

		/* 360�𒴂�����C��*/
		if(m_fCharaYaw >= 360.0f)	m_fCharaYaw -= 360.0f;
		else if(m_fCharaYaw < 0.0f)	m_fCharaYaw += 360.0f;
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
void CMyPlayer::JumpStart(CStage* pStage, CEffectManage* pEffectManage)
{
	/* �J�E���^�[�������ԁA�W�����v�J�n�s�������� */
	if(m_nCnt>0)
	{
		/* ���[�V�����̕ω� */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_S);

		// �J�E���^�[�����炵�Ă���
		m_nCnt--;

		/* �n�ʂ𒲂ׁA�������ʂ���苗���ȉ��Ȃ璅�n���� */
		D3DXVECTOR3	vecTmp;
		if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND)
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
		}

		/* �V��𒲂ׁA�V�䂪����������W�����v�l���Ȃ��� */
		if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
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
void CMyPlayer::JumpMain(CStage* pStage)
{
	/* ���ɐ��񂷂� */
	if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* �E�ɐ��񂷂� */
	else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* �O�Ɉړ����� */
	if(GetAsyncKeyState(KEY_FORWARD) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
	{
		m_fSpeed = m_pParam->fJumpForward;

		/* �P�ʕ����x�N�g���̎擾 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

		/* ���[�V�����̕ω� */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_F);
	}

	/* ���Ɉړ����� */
	else if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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

	/* �G�l���M�[��1/3�ȏ�c���Ă����� */
	/* ��эs���Ɉڍs���� */
	if(GetAsyncKeyState(KEY_JUMP) & 0x8000 && m_nCnt < 0 && 
		(float)m_nNowEnergy/(float)m_pParam->nMaxEnergy > 0.35f)
	{
		m_nNowAction = 	FLYGHT;
	}

	/* ���ɔ�s�ł���܂ł̃J�E���^�[���f�N�������g */
	m_nCnt--;

	/* ���񂾂�n�ʂɗ����� */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* �G�l���M�[�̉� */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

	//------------------
	//	�Ǌ֌W�̏���
	//------------------
	/* �n�ʂ𒲂ׁA�������ʂ���苗���i�������Ȃ߁j�ȉ��Ȃ璅�n���� */
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
void CMyPlayer::JumpEnd()
{

}

//------------------------------------------------------------------
//	Name:	Flyght
//	Func:	���ł���s��
//	in:		CStage*			pStage		  = �X�e�[�W�N���X
//			CEffectManage*	pEffectManage = �G�t�F�N�g�Ǘ��N���X
//	Out:	����
//------------------------------------------------------------------
void CMyPlayer::Flyght(CStage* pStage, CEffectManage* pEffectManage)
{
	/* ���ɐ��񂷂� */
	if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* �E�ɐ��񂷂� */
	else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* �O�Ɉړ����� */
	if(GetAsyncKeyState(KEY_FORWARD) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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
	else if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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

	/* �W�����v�L�[�𗣂��A�܂��G�l���M�[�������ꍇ�� */
	/* �J�E���g�l���i�[���W�����v�Ɉڍs���� */
	if(!(GetAsyncKeyState(KEY_JUMP) & 0x8000) || m_nNowEnergy <= 0)
	{
		m_nCnt = 20;
		m_nNowAction = 	JUMP_MAIN;
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
void CMyPlayer::DamageLand(CStage* pStage, CEffectManage* pEffectManage)
{
	/* ���삷�鎖�͈�؏o���Ȃ� */

	/* �X�s�[�h�l�����炵�Ă��� */
	m_fSpeed -= m_pParam->fBrakes;

	/* �X�s�[�h�l���O�ɂȂ����猳�ɖ߂� */
	if(m_fSpeed < 0)
	{
		m_nNowAction = WALK;
		/* �߂�����������̊Ԗ��G */
		m_nDamageCnt = DAMAGE_CNT;
	}

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
void CMyPlayer::DamageAir(CStage* pStage, CEffectManage* pEffectManage)
{
	/* ���삷�鎖�͈�؏o���Ȃ� */

	/* �X�s�[�h�l�����炵�Ă��� */
	m_fSpeed -= m_pParam->fBrakes;

	/* ���񂾂�n�ʂɗ����� */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* �X�s�[�h�l���O�ɂȂ����猳�ɖ߂� */
	if(m_fSpeed < 0)
	{
		m_nNowAction = JUMP_MAIN;
		/* �߂�����������̊Ԗ��G */
		m_nDamageCnt = DAMAGE_CNT;
	}

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
void CMyPlayer::DeadLand(CStage* pStage, CEffectManage* pEffectManage )
{
	/* ���삷�鎖�͈�؏o���Ȃ� */

	/* �X�s�[�h�l�����炵�Ă��� */
	m_fSpeed -= m_pParam->fBrakes;
	if(m_fSpeed < 0)	m_fSpeed = 0;

	/* �G���^�[�������Ɛ����Ԃ� */
	if(GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		pEffectManage->AddEffect(REVIVAL, m_matBase);
		m_nNowLife = m_pParam->nMaxLife;
		m_fJump = 0.5f;
		m_nNowAction = JUMP_MAIN;
	}

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
void CMyPlayer::DeadAir(CStage* pStage, CEffectManage* pEffectManage)
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

//----------------------------------------------
//	Name:	LockOn
//	Func:	���b�N�I���Ɋւ���L�q
//	in:		CStage* pStage = �X�e�[�W�N���X
//	Out:	����
//----------------------------------------------
void CMyPlayer::LockOn(CStage* pStage)
{
	int i;

	/* ���b�N�I�����t���O�̍X�V */
	IsLockON(pStage);

	/* �S�Ăɑ΂��čs������ */
	for(i=0; i<3; i++)
	{
		/* ���b�N�I���}�[�J�[�̉�ʂɕ\������ʒu��ݒ肷�� */
		m_pLockMarker[i]->SetVec(D3DXVECTOR2(m_vecProject[i].x, m_vecProject[i].y));

		/* �L�����N�^�[���O�t�H���g����ʂɕ\������ʒu��ݒ肷�� */
		m_pCharaName[i]->SetRec((int)m_vecProject[i].x - 64,(int)m_vecProject[i].y - 80,
								(int)m_vecProject[i].x + 64,(int)m_vecProject[i].y - 50);

		/* �L�����N�^�[���C�t�t�H���g����ʂɕ\������ʒu��ݒ肷�� */
		m_pCharaLife[i]->SetRec((int)m_vecProject[i].x - 64,(int)m_vecProject[i].y - 60,
								(int)m_vecProject[i].x + 64,(int)m_vecProject[i].y - 30);

		/* ���b�N�I���̍s�����X�V���� */
		if(!m_bCanLock[i])			m_pLockMarker[i]->SetStatus(NOT_LOCK);	// ���b�N�I���o���Ȃ��Ȃ�NOT_LOCK��
		else if(m_nLockTarget != i)	m_pLockMarker[i]->SetStatus(CAN_LOCK);	// ���b�N�I���o���邯�ǃ^�[�Q�b�g����Ȃ��Ȃ�CAN_LOCK��
		else if(!m_bNowLock)		m_pLockMarker[i]->SetStatus(TAG_LOCK);	// �^�[�Q�b�g�����ǃ��b�N�I�����Ă��Ȃ�����TAG_LOCK��
		else						m_pLockMarker[i]->SetStatus(NOW_LOCK);	// �S�ăN���A������NOW_LOCK�ł�

		/* ���t���[���̏��� */
		m_pLockMarker[i]->FrameMove();
	}

	/* ���b�N�I�������Ă��鎞�̓��͏���*/
	if(m_bNowLock){
		/* �X�y�[�X�������ƃ��b�N���� */
		if(GetAsyncKeyState(KEY_LOCK) & 0x0001)
			m_bNowLock = false;

		/* ���݂̑Ώۂ����b�N�I���s�ɂȂ����� */
		if(!m_bCanLock[m_nLockTarget])
			m_bNowLock = false;
	}

	/* ���b�N�I�����Ă��Ȃ����̓��͏��� */
	else{
		/* �^�[�Q�b�g�ƂȂ�L�����N�^��I�� */
		SelectTarget();

		/* �X�y�[�X�������A�\�ł���΃��b�N�I������ */
		if(GetAsyncKeyState(KEY_LOCK) & 0x0001 && m_nLockTarget != -1)
		{
			m_bNowLock = true;
			m_fCharaPitch = 0;
		}
	}
}


//----------------------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CMyPlayer::Render()
{

	for(int i=0; i<3; i++)
	{
		if(m_bCanLock[i]){
			/* ���b�N�I���}�[�J�[�̕`�� */
			m_pLockMarker[i]->Render();	
			/* �L�����N�^�[���̕`�� */
			m_pCharaName[i]->Render();
			/* �L�����N�^�[���C�t�̕`�� */
			m_pCharaLife[i]->Render();
		}
	}

	/* �L�����N�^�̕`�� */
	CChara::Render();
}

//----------------------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CMyPlayer::UpDate()
{
	CChara::UpDate();


	for(int i=0; i<3; i++)
	{
		/* ���b�N�I���}�[�J�[�̍X�V */
		m_pLockMarker[i]->UpDate();	
		/* �L�����N�^�[�l�[���̍X�V */
		m_pCharaName[i]->UpDate();
		/* �L�����N�^�[���C�t�̍X�V */
		m_pCharaLife[i]->UpDate();

	}
}

//--------------------------------------------------
//	Name:	ComputProject
//	Func:	�S�Ă̓G�L�������W���A�v���W�F�N�V�������e����
//	in:		�Ȃ�
//	Out:	�Ȃ�
//--------------------------------------------------
void CMyPlayer::ComputProject()
{
	D3DXVECTOR3	vecTmp;
	vecTmp*=0;

	/* �S�Ă̓G�̍��W�l���v���W�F�N�V�������e���� */
	for(int i=0; i<3; i++)
	{
		/* �f�[�^���Ȃ����͎��̃f�[�^�� */
		if(!m_tagEnemyData[i].pMatrix)	continue;

		/* �G�̍��W�l���x�N�g���ɕϊ����� */
		vecTmp.x = m_tagEnemyData[i].pMatrix->_41;
		vecTmp.y = m_tagEnemyData[i].pMatrix->_42;
		vecTmp.z = m_tagEnemyData[i].pMatrix->_43;

		/* �v���W�F�N�V�����ɓ��e���� */
		TransProject(m_pd3dDevice, &vecTmp, &vecTmp);
		m_vecProject[i].x = vecTmp.x;
		m_vecProject[i].y = vecTmp.y;
	}
}

//--------------------------------------------------
//	Name:	ComputView
//	Func:	�S�Ă̓G�L�������W���A�r���[�ϊ�����
//	in:		�Ȃ�
//	Out:	�Ȃ�
//--------------------------------------------------
void CMyPlayer::ComputView()
{
	D3DXVECTOR3	vecTmp;	vecTmp*=0;
	D3DXMATRIX	matView;

	/* �r���[�}�g���N�X�̎擾 */
	m_pd3dDevice->GetTransform( D3DTS_VIEW, &matView );

	/* �S�Ă̓G�̍��W�l���v���W�F�N�V�������e���� */
	for(int i=0; i<3; i++)
	{
		/* �f�[�^���Ȃ����͎��̃f�[�^�� */
		if(!m_tagEnemyData[i].pMatrix)	continue;

		/* �G�̍��W�l���x�N�g���ɕϊ����� */
		vecTmp.x = m_tagEnemyData[i].pMatrix->_41;
		vecTmp.y = m_tagEnemyData[i].pMatrix->_42;
		vecTmp.z = m_tagEnemyData[i].pMatrix->_43;

		/* �r���[���W�n�ɕϊ����� */
		D3DXVec3TransformCoord(&m_vecView[i], &vecTmp, &matView);
	}
}

//--------------------------------------------------
//	Name:	IsLockOn
//	Func:	���b�N�I���ł��邩�ǂ����𒲂ׂ�
//	in:		CStage* pStage = �X�e�[�W�N���X
//	Out:	�Ȃ�
//--------------------------------------------------
void CMyPlayer::IsLockON(CStage* pStage)
{
	RECT		rcTmp;
	D3DXVECTOR3	vecTmp, vecTmp2;
	int i;

	/* �L�����N�^�̃v���W�F�N�V�������W�̎Z�o */
	ComputProject();

	/* �L�����N�^�̃r���[���W�̎Z�o */
	ComputView();

	/* ����̈�̐ݒ� */
	SetRect(&rcTmp, 80, 80, 520, 400);

	/* ���b�N�I���t���O������ */
	for(i=0; i<3; i++)	m_bCanLock[i] = false;

	/* �S�Ă̍��W�l�ɑ΂��Ĕ��� */
	for(i=0; i<3; i++)
	{
		/* �f�[�^���Ȃ���Γ��R�_�� */
		if(!D3DXVec2LengthSq(&m_vecProject[i]))	continue;

		/* �Ώۂ��J�������O�ɂ��Ȃ���΃_�� */
		if(!(m_vecView[i].z > 0))
			continue;

		/* �v���W�F�N�V�������W�l���̈�̒��ɂȂ���΃_�� */
		if(!(m_vecProject[i].x > rcTmp.left  && m_vecProject[i].x < rcTmp.right &&
			 m_vecProject[i].y > rcTmp.top   && m_vecProject[i].y < rcTmp.bottom  ) )
			continue;

		/* �����Ƃ̋��������ȓ��łȂ��ƃ_�� */
		vecTmp.x = m_tagEnemyData[i].pMatrix->_41;
		vecTmp.y = m_tagEnemyData[i].pMatrix->_42;
		vecTmp.z = m_tagEnemyData[i].pMatrix->_43;
		vecTmp2 = CChara::GetPosBase() - vecTmp;
		if (D3DXVec3LengthSq(&vecTmp2) >
			(m_pParam->fLockLength * m_pParam->fLockLength))
			continue;

		/* ��̍��W�Ԃɖʂ�����������_�� */
		if(SearchAllPlane(pStage, CChara::GetPosBase(), vecTmp))
		{
			m_bCanLock[i] = false;
			continue;
		}

		/* ���b�N�I�����\�Ƃ݂Ȃ� */
		m_bCanLock[i] = true;
	}
}

//--------------------------------------------------------------
//	Name:	SelectTarget
//	Func:	���b�N�I���ł���L�����N�^�̒�����A
//			��ʂ̒��S�Ɉ�ԋ߂����̂�T���āA�^�[�Q�b�g�Ƃ���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//--------------------------------------------------------------
void CMyPlayer::SelectTarget()
{
	float		fLen;
	float		fLenMin = 99999;
	int			nAdop = -1;

	D3DXVECTOR2	vecTmp;

	for(int i=0; i<3; i++)
	{
		/* ���b�N�I�����ł��Ȃ��̂Ȃ珜�O */
		if(!m_bCanLock[i])	continue;

		/* ��ʂ̒��S�_����̋��������߂� */
		vecTmp = D3DXVECTOR2(320, 240) - m_vecProject[i];
		fLen = D3DXVec2LengthSq(&vecTmp);

		/* ���ׂ���������ԏ�����������̗p */
		if(fLen < fLenMin)
		{
			fLenMin = fLen;
			nAdop	= i;
		}
	}

	/* ���ʂ������o�Ɋi�[���� */
	m_nLockTarget = nAdop;

}

//----------------------------------------------------------
//	Name:	CreateCharaName
//	Func:	�L�����N�^�̖��O�t�H���g�̍쐬
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CMyPlayer::CreateCharaName()
{
	for(int i=0; i<3; i++)
	{
		m_pCharaName[i] = new CFont(m_pd3dDevice, const_cast<TCHAR*>("�l�r �S�V�b�N"));
		m_pCharaName[i]->SetString(m_tagEnemyData[i].Name);
		m_pCharaName[i]->SetFormat(DT_CENTER);
		m_pCharaName[i]->SetColor(0, 255, 0);
	}
}

//----------------------------------------------------------
//	Name:	CreateCharaName
//	Func:	�L�����N�^�̖��O�t�H���g�̍쐬
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CMyPlayer::CreateCharaLife()
{
	for(int i=0; i<3; i++)
	{
		m_pCharaLife[i] = new CFont(m_pd3dDevice, const_cast<TCHAR*>("�l�r �S�V�b�N"));
		m_pCharaLife[i]->SetString(*m_tagEnemyData[i].pNowLife);
		m_pCharaLife[i]->SetFormat(DT_CENTER);
		m_pCharaLife[i]->SetColor(0, 255, 0);
	}
}