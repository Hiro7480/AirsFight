//==========================================================
// Chara.cpp
// Auther : ���� ���V
// Data   : 2002/01/10
//==========================================================
#include "Chara.h"

//------------------------------------------------------
//	Name:	CChara
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3D�f�o�C�X
//	Out:	�Ȃ�
//------------------------------------------------------
CChara::CChara(LPDIRECT3DDEVICE8 d3dDevice) :C3DGraphicObj(d3dDevice)
{
	/* �e�ϐ��̏����� */
	m_pActiveMotion = NULL;
	m_pParam = NULL;

	m_vecMove *= 0;
	m_fSpeed = 0;
	m_fCharaYaw = 0;
	m_fCharaPitch = 0;
	m_fJump = 0;

	m_nDamageCnt = 0;

	m_nNowLife = 0;
	m_nNowEnergy = 0;
	m_nDeadNum = 0;

	/* �G�L�����f�[�^�̏����� */
	for(int i=0; i<4; i++)
	{
		m_tagEnemyData[i].pMatrix = NULL;
		strcpy(m_tagEnemyData[i].Name, "Default");
	}
}

//----------------------------------------------
//	Name:	~CChara
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CChara::~CChara()
{

}
//--------------------------------------------------
//	Name:	FrameMoveStart
//	Func:	�Q�[���J�n���̖��t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//--------------------------------------------------
void CChara::FrameMoveStart()
{
	/* ���[�V�����̂��܂��܂ȍX�V */
	m_pActiveMotion->Play();
}

//--------------------------------------------------
//	Name:	FrameMoveEnd
//	Func:	�Q�[���I�����̖��t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//--------------------------------------------------
void CChara::FrameMoveEnd()
{
	/* �������Ȃ� */
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CChara::Render()
{
	D3DXMATRIX	matView;
	D3DXVECTOR3	vecTmp;

	/* �r���[�}�g���N�X�̎擾 */
	m_pd3dDevice->GetTransform( D3DTS_VIEW, &matView );

	/* ���݂̍��W�l���r���[���W�n�ɕϊ����� */
	D3DXVec3TransformCoord(&vecTmp, &CChara::GetPosBase(), &matView);

	/* �L�����N�^���J�����̌��ɂ�����`�悵�Ȃ��I */
	if(vecTmp.z < 0)	return;

	/* �L�����N�^�̕`�� */
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matStock );
	m_pActiveMotion->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�`��p�}�g���N�X�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CChara::UpDate()
{
	C3DGraphicObj::UpDate();

	/* �A�N�e�B�u���[�V�����̍X�V */
	m_pActiveMotion->UpDate();
}

//----------------------------------------------------------
//	Name:	CreateActive
//	Func:	�A�N�e�B�u���[�V�����̍쐬
//	in:		CMotionData* pMotionData[] = ���[�V�����f�[�^�z��
//	Out:	HRESULT
//----------------------------------------------------------
HRESULT CChara::CreateActive(CMotionData* pMotionData[])
{
	/* �A�N�e�B�u���[�V�������������Ɋm�� */
	m_pActiveMotion = new CActiveMotion;

	/* ���b�V���f�[�^�̓ǂݍ��� */
	m_pActiveMotion->LoadMesh(m_pParam->pMeshData);

	/* ���[�V�����f�[�^�̓ǂݍ��� */
	m_pActiveMotion->LoadMotion(pMotionData[ANI_STOP]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_FORWARD]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_BACK]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DASH_F]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DASH_B]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DASH_R]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DASH_L]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_ATAS]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_ATA]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_N]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_F]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_B]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_S]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_E]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DAM_L]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DAM_A]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DEAD_L]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DEAD_A]);

	return S_OK;
}

//--------------------------------------------------------------
//	Name:	AllInit
//	Func:	�L�����N�^�̏������S��
//	in:		D3DXVECTOR3	vecIn		= �I�u�W�F�N�g�̈ʒu
//			float		fCharaYaw	= �L�����N�^��Yaw��]�p�x
//	Out:	�Ȃ�
//--------------------------------------------------------------
void CChara::AllInit(D3DXVECTOR3 vecPos, float fCharaYaw)
{
	D3DXMATRIX matTmp;
	D3DXMatrixIdentity(&matTmp);

	/* �w�肵�����W�l�ɕ��s�ړ������� */
	matTmp._41 = vecPos.x;
	matTmp._42 = vecPos.y;
	matTmp._43 = vecPos.z;

	/* �}�g���N�X�̃Z�b�g */
	m_matBase = matTmp;

	/* �L����Yaw�p�x�l�̃Z�b�g */
	m_fCharaYaw = fCharaYaw;

	/* LIFE�l�ƃG�l���M�[�̏����� */
	m_nNowLife   = m_pParam->nMaxLife;
	m_nNowEnergy = m_pParam->nMaxEnergy;
}

//--------------------------------------------------
//	Name:	IsHitBullet
//	Func:	�e�Ƃ̓����蔻��
//	in:		CBulManage*		pBulManage		= �e�Ǘ��N���X
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X
//	Out:	�Ȃ�
//--------------------------------------------------
void CChara::IsHitBullet(CBulManage* pBulManage,
						 CEffectManage* pEffectManage)
{
	/* �������_���[�W���ł���΁A�����蔻����s��Ȃ� */
	if(m_nNowAction == DAMAGE_LAND || m_nNowAction == DAMAGE_AIR)
		return;

	/* ���G���Ԃł����Ă������蔻����s��Ȃ� */
	else if(m_nDamageCnt > 0)
		return;

	D3DXVECTOR3	vecBulPos;	// �e�̈ʒu������

	/* ���X�g�̍ŏ��̒e���擾 */
	CBullet* pBullet = pBulManage->GetListTop();;

	/* ���X�g�̍Ō�܂ł����蔻����J��Ԃ� */
	while(pBullet)
	{
		vecBulPos = pBullet->GetPosBase();	// �e�̈ʒu�̎擾

		/* �e���������Ă���P�t���[���ȏソ���Ă��鎖�A */
		/* �L�����N�^�Ƃ̋��������ȓ��ł��鎖�̏ꍇ�A���������Ƃ݂Ȃ� */
		if(	pBullet->GetTimeCount() > 1 &&
			D3DXVec3LengthSq( &(C3DGraphicObj::GetPosBase() - vecBulPos) ) < (HIT_CHARA_LENGTH * HIT_CHARA_LENGTH) ) 
			break;

		/* ���̒e�𒲂ׂ� */
		pBullet = pBullet->GetNext();
	}

	/* �ǂ̒e�Ƃ�������Ȃ������ꍇ�͏I������ */
	if(pBullet == NULL)	return;

	/* �e�������������̏��� */
	// ���̕ӂ͕���ɂ���ĕς���i�\��j

	int nDamage;						// �_���[�W�l�̊i�[
	srand((unsigned int)time(NULL));
	nDamage = rand()%500 + 500;
	m_nNowLife  -= nDamage;

	pBullet->Delete();					// �e������

	m_vecMove = pBullet->GetMoveVec();	// �ړ������x�N�g���̊i�[

	/* �e�̕����x�N�g������ړ������p�x�����߂� */
	m_fMoveYaw = (float)GetAngle((double)pBullet->GetMoveVec().x, (double)pBullet->GetMoveVec().z);

	m_fSpeed = 1.5f;					// �X�s�[�h�l�̊i�[	
	m_fJump += 0.2f;					// �W�����v�l�̊i�[

	D3DXMATRIX matTmp;
	/* ���S���� */
	if(IsDead())
	{
		/* ���C�t��0�ɂ��Ƃ� */
		m_nNowLife = 0;

		/* ���񂾉񐔂�����₷ */
		m_nDeadNum++;

		/* ���ʂƋ󒆎��S��ԂɈڍs���A�G�t�F�N�g���O���� */
		for(int i=0; i<3; i++)
		{
			matTmp = m_matBase;
			matTmp._41 += (float)(rand()%10-5) / 1.0f;
			matTmp._42 += (float)(rand()%10-5) / 1.0f;
			matTmp._43 += (float)(rand()%10-5) / 1.0f;

			pEffectManage->AddEffect(EXPLOSION_B, matTmp);
		}
		m_nNowAction = DEAD_AIR;
	}
	else
	{
		/* ���ȂȂ���΋󒆃_���[�W��ԂɈڍs���A�G�t�F�N�g���ЂƂ��� */
		pEffectManage->AddEffect(EXPLOSION_B, m_matBase);
		m_nNowAction = DAMAGE_AIR;
	}
}

//--------------------------------------------------
//	Name:	IsDead
//	Func:	���S����
//	in:		�Ȃ�
//	Out:	bool = ����ł���Ȃ�True
//--------------------------------------------------
bool CChara::IsDead()
{
	/* ����Ȋ֐�����ĈӖ�������̂��ǂ����͋^�� */
	if(m_nNowLife <= 0)	return true;
	return false;
}

//----------------------------------------------
//	Name:	GetVecToPlane
//	Func:	�n�ʂ̖ʂ̎��ƃL�����N�^�̉�]�p�x����
//			�L�����N�^�̒P�ʕ����x�N�g�������߂�
//			�n�ʂ��⓹�ɂȂ��Ă��Ă�������Ƃ��Ɏg�p
//
//	in:		D3DXPLANE	plaGround = �w��n��
//			float		fYaw      = �w���]�p�x
//	Out:	D3DXVECTOR3*
//----------------------------------------------
D3DXVECTOR3 CChara::GetVecToPlane(D3DXPLANE* plaGround, float fYaw)
{
	D3DXVECTOR3	vec3X,vec3Y,vec3Z;
	D3DXVECTOR3	vecAdop;
	D3DXMATRIX	matTmp;

	// �ʂɐ����Ȃx����]�������}�g���b�N�X���쐬��
	// �ړ��x�N�g�����쐬����
	// �x������ݒ�
	vec3Y.x = plaGround->a;
	vec3Y.y = plaGround->b;
	vec3Y.z = plaGround->c;

	// �y������ݒ�
	vec3Z.x = (float)sin( D3DXToRadian(fYaw) );
	vec3Z.y = 0;
	vec3Z.z = (float)cos( D3DXToRadian(fYaw) );

	// �w���������Ƃ߂�
	D3DXVec3Cross(&vec3X, &vec3Y, &vec3Z);
	D3DXVec3Normalize(&vec3X, &vec3X);
	// �y���������Ƃ߂�
	D3DXVec3Cross(&vec3Z, &vec3X, &vec3Y);
	D3DXVec3Normalize(&vec3Z, &vec3Z);

	// �}�g���b�N�X�̒P�ʍs��
	D3DXMatrixIdentity(&matTmp);

	// �e�������}�g���b�N�X�ɔ��f����
	matTmp._11 = vec3X.x;	matTmp._12 = vec3X.y;	matTmp._13 = vec3X.z;
	matTmp._21 = vec3Y.x;	matTmp._22 = vec3Y.y;	matTmp._23 = vec3Y.z;
	matTmp._31 = vec3Z.x;	matTmp._32 = vec3Z.y;	matTmp._33 = vec3Z.z;

	// �悤�₭�P�ʕ����x�N�g���̎擾�I
	D3DXVec3TransformNormal(&vecAdop, &D3DXVECTOR3(0, 0, 1), &matTmp);

	return vecAdop;

}

//----------------------------------------------------------
//	Name:	SearchAllGround
//	Func:	�S�ẴI�u�W�F�N�g�̒n�ʂ𒲂ׁA
//			��ԋ����̒Z���ʂ̎��A��_�A���������߂�
//	in:		CStage*			pStage = �X�e�[�W�N���X�ւ̃|�C���^
//			D3DXPLANE*		plaOut = �o�͗p�ʂ̎�
//			D3DXVECTOR3*	vecOut = �o�͗p�ʂƂ̌�_
//	Out:	float				   = �ʂƂ̋���
//----------------------------------------------------------
float CChara::SearchAllGround(CStage* pStage, D3DXPLANE* plaOut, D3DXVECTOR3* vecOut)
{
	float		fLenAdop,fLen;
	D3DXPLANE	plaTmp,plaAdop;
	D3DXVECTOR3	vecCrossAdop,vecCross;
	float		fTmp1, fTmp2;
	int			i;

	fLenAdop = 99999;


	/* �u���b�N�^�C�v�̃I�u�W�F�N�g�𒲂ׂ� */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		/* �L�����N�^�ƃI�u�W�F�N�g������Ă����璲�ׂȂ� */
		fTmp1 = D3DXVec3LengthSq(&( pStage->GetBlockObj(i)->GetPosBase() - GetPosBase()) );
		fTmp2 = (pStage->GetBlockObj(i)->GetLength() + 5.0f) * (pStage->GetBlockObj(i)->GetLength()+ 5.0f);

		if(fTmp1 < fTmp2)
		{
			if( SearchPlane(pStage->GetBlockObj(i)->GetMesh(), &pStage->GetBlockObj(i)->GetMatBase(),
						&GetPosBase(),&D3DXVECTOR3(0,-1,0), &vecCross, &plaTmp, &fLen))
			{
				if(fLenAdop > fLen)
				{
					/* ���ׂ����ׂẴI�u�W�F�N�g�̒��ň�ԋ������Z���ʂ��̗p */
					fLenAdop = fLen;
					plaAdop	 = plaTmp;
					vecCrossAdop = vecCross;
				}
			}
		}
	}

	/* �E�H�[���^�C�v�̃I�u�W�F�N�g�𒲂ׂ� */
	for(i=0; i<pStage->GetWallNum(); i++)
	{
		if( SearchPlane(pStage->GetWallObj(i)->GetMesh(), &pStage->GetWallObj(i)->GetMatBase(),
					&GetPosBase(),&D3DXVECTOR3(0,-1,0), &vecCross, &plaTmp, &fLen))
		{
			if(fLenAdop > fLen)
			{
				/* ���ׂ����ׂẴI�u�W�F�N�g�̒��ň�ԋ������Z���ʂ��̗p */
				fLenAdop = fLen;
				plaAdop	 = plaTmp;
				vecCrossAdop = vecCross;
			}
		}
	}


	/* �n�ʂ����������ꍇ�A���̋����Ɩʂ̎���Ԃ� */
	if(fLenAdop < 99999)
	{
		if(plaOut)	*plaOut = plaAdop;
		if(vecOut)	*vecOut = vecCrossAdop;
		return	fLenAdop;
	}

	return 99999;
}

//--------------------------------------------------------------------------
//	Name:	SearchAllWall
//	Func:	�S�ẴI�u�W�F�N�g�̕ǂ𒲂ׂāA��ԋ����̒Z���ʂ��̗p�A
//			���̖ʂƃL�����̈ړ��x�N�g���Ƃ̌�_�A�ʂ̋t�@���x�N�g���Ƃ̌�_�A
//			�t�@���x�N�g����_�ƃL�����Ƃ̋��������߂�
//	in:		CStage*			pStage	= �X�e�[�W�N���X�ւ̃|�C���^
//			D3DXVECTOR3*	vecOut1	= �ʂ̋t�@���x�N�g���Ƃ̌�_
//			D3DXVECTOR3*	vecOut2	= �L�����̈ړ��x�N�g���Ƃ̌�_
//	Out:	float					= �ʂƂ̋���
//--------------------------------------------------------------------------
float CChara::SearchAllWall(CStage* pStage, D3DXVECTOR3* vecOut1, D3DXVECTOR3* vecOut2)
{
	float		fLenAdop,fLen;
	D3DXVECTOR3	vecCrossAdop1,vecCross1;
	D3DXVECTOR3	vecCrossAdop2,vecCross2;
	float		fTmp1, fTmp2;
	int			i;

	fLenAdop = 99999;

	/* �u���b�N�^�C�v�̃I�u�W�F�N�g�𒲂ׂ� */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		/* �L�����N�^�ƃI�u�W�F�N�g������Ă����璲�ׂȂ� */
		fTmp1 = D3DXVec3LengthSq(&( pStage->GetBlockObj(i)->GetPosBase() - GetPosBase()) );
		fTmp2 = (pStage->GetBlockObj(i)->GetLength()) * (pStage->GetBlockObj(i)->GetLength());

		if(fTmp1 < fTmp2)
		{
			if( SearchPlane2(pStage->GetBlockObj(i)->GetMesh(), &pStage->GetBlockObj(i)->GetMatBase(),
					&GetPosBase(), &m_vecMove, &vecCross1, &vecCross2, NULL, &fLen))
			{
				if(fLenAdop > fLen)
				{
					/* ���ׂ����ׂẴI�u�W�F�N�g�̒��ň�ԋ������Z���ʂ��̗p */
					fLenAdop = fLen;
					vecCrossAdop1 = vecCross1;
					vecCrossAdop2 = vecCross2;
				}
			}
		}
	}

	/* �E�H�[���^�C�v�̃I�u�W�F�N�g�𒲂ׂ� */
	for(i=0; i<pStage->GetWallNum(); i++)
	{
		if( SearchPlane2(pStage->GetWallObj(i)->GetMesh(), &pStage->GetWallObj(i)->GetMatBase(),
				&GetPosBase(), &m_vecMove, &vecCross1, &vecCross2, NULL, &fLen))
		{
			if(fLenAdop > fLen)
			{
				/* ���ׂ����ׂẴI�u�W�F�N�g�̒��ň�ԋ������Z���ʂ��̗p */
				fLenAdop = fLen;
				vecCrossAdop1 = vecCross1;
				vecCrossAdop2 = vecCross2;
			}
		}
	}

	/* �n�ʂ����������ꍇ�A���̋����Ɩʂ̎���Ԃ� */
	if(fLenAdop < 99999)
	{
		if(vecOut1)	*vecOut1 = vecCrossAdop1;
		if(vecOut2)	*vecOut2 = vecCrossAdop2;
		return	fLenAdop;
	}
	/* ������Ȃ��������́A99999��Ԃ� */
	return 99999;
}

//----------------------------------------------------------
//	Name:	SearchAllCeiling
//	Func:	�S�I�u�W�F�N�g�̓V��𒲂ׁA
//			��ԋ����̒Z���ʂ̎��A��_�A���������߂�
//	in:		CStage*			pStage = �X�e�[�W�N���X�ւ̃|�C���^
//			D3DXPLANE*		plaOut = �o�͗p�ʂ̎�
//			D3DXVECTOR3*	vecOut = �o�͗p�ʂƂ̌�_
//	Out:	float				   = �ʂƂ̋���
//----------------------------------------------------------
float CChara::SearchAllCeiling(CStage* pStage, D3DXPLANE* plaOut, D3DXVECTOR3* vecOut)
{
	float		fLenAdop,fLen;
	D3DXPLANE	plaTmp,plaAdop;
	D3DXVECTOR3	vecCrossAdop,vecCross;
	D3DXVECTOR3	vecMove;
	float		fTmp1, fTmp2;
	int			i;

	fLenAdop = 99999;

	/* �L�����N�^�̈ړ��x�N�g���ɃW�����v�l�����ꂽ�ړ��x�N�g�����Z�o */
	vecMove = m_vecMove;
	vecMove *= m_fSpeed;
	vecMove.y = m_fJump;
	D3DXVec3Normalize(&vecMove, &vecMove);

	/* �u���b�N�^�C�v�̃I�u�W�F�N�g�𒲂ׂ� */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		/* �L�����N�^�ƃI�u�W�F�N�g������Ă����璲�ׂȂ� */
		fTmp1 = D3DXVec3LengthSq(&( pStage->GetBlockObj(i)->GetPosBase() - GetPosBase()) );
		fTmp2 = (pStage->GetBlockObj(i)->GetLength()) * (pStage->GetBlockObj(i)->GetLength());

		if(fTmp1 < fTmp2)
		{
			if( SearchPlane(pStage->GetBlockObj(i)->GetMesh(), &pStage->GetBlockObj(i)->GetMatBase(),
						&GetPosBase(),&vecMove, &vecCross, &plaTmp, &fLen))
			{
				if(fLenAdop > fLen)
				{
					/* ���ׂ����ׂẴI�u�W�F�N�g�̒��ň�ԋ������Z���ʂ��̗p */
					fLenAdop = fLen;
					plaAdop	 = plaTmp;
					vecCrossAdop = vecCross;
				}
			}
		}
	}

	/* �E�H�[���^�C�v�̃I�u�W�F�N�g�𒲂ׂ� */
	for(i=0; i<pStage->GetWallNum(); i++)
	{
		if( SearchPlane(pStage->GetWallObj(i)->GetMesh(), &pStage->GetWallObj(i)->GetMatBase(),
					&GetPosBase(),&vecMove, &vecCross, &plaTmp, &fLen))
		{
			if(fLenAdop > fLen)
			{
				/* ���ׂ����ׂẴI�u�W�F�N�g�̒��ň�ԋ������Z���ʂ��̗p */
				fLenAdop = fLen;
				plaAdop	 = plaTmp;
				vecCrossAdop = vecCross;
			}
		}
	}


	/* �n�ʂ����������ꍇ�A���̋����Ɩʂ̎���Ԃ� */
	if(fLenAdop < 99999)
	{
		if(plaOut)	*plaOut = plaAdop;
		if(vecOut)	*vecOut = vecCrossAdop;
		return	fLenAdop;
	}
	return 99999;
}

//--------------------------------------------------------------
//	Name:	SearchAllPlane
//	Func:	��̍��W�l����Ō��񂾏ꍇ�A���̊Ԃɖʂ����邩
//			�������𔻒肷��
//	in:		CStage*		pStage = �X�e�[�W�N���X�ւ̃|�C���^
//			D3DXVECTOR3	vecPos1 = ���W�l�P
//			D3DXVECTOR3	vecPos2 = ���W�l�Q	
//	Out:	bool
//--------------------------------------------------------------
bool CChara::SearchAllPlane(CStage* pStage, D3DXVECTOR3 vecPos1, D3DXVECTOR3 vecPos2)
{
	float		fLen;
	D3DXVECTOR3	vecCross;
	int			i;

	/* �u���b�N�^�C�v�̃I�u�W�F�N�g�𒲂ׂ� */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		if( SearchPlane(pStage->GetBlockObj(i)->GetMesh(), 
					&pStage->GetBlockObj(i)->GetMatBase(),
					&vecPos1, &(vecPos2-vecPos1), &vecCross, NULL, &fLen))
		{
			/* �ʂ�����������A���̌�_���� */
			/* �w��x�N�g���̊ԂɌ����������ǂ����𔻒肷�� */
			if( D3DXVec3LengthSq(&(vecPos2-vecPos1)) > D3DXVec3LengthSq(&(vecCross-vecPos1)) )
			{
				/* �ʂ����������Ƃ݂Ȃ� */
				return true;
			}
		}
	}

	return false;
}