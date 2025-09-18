//==========================================================
// Game.cpp
// Auther : ���� ���V
// Data   : 2002/01/10
//==========================================================

#include "Game.h"

//------------------------------------------------------
//	Name:	CGame
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3D�f�o�C�X
//	Out:	�Ȃ�
//------------------------------------------------------
CGame::CGame(LPDIRECT3DDEVICE8 d3dDevice)
	 :GameStatus(d3dDevice)
{
	/* �q�s�|�n�m�d�p�����[�^�̐ݒ� */
	m_CharaParam[0].pMeshData = new CMeshData(m_pd3dDevice);// ���b�V���ǂݍ���
	m_CharaParam[0].pMeshData->Create(const_cast<TCHAR*>("data\\Chara\\RT-One\\RT-One.X"));

	m_CharaParam[0].nMaxLife     = 2800;		// �ő�g�o
	m_CharaParam[0].nMaxEnergy   = 1000;		// �ő�G�l���M�[

	m_CharaParam[0].fWalkSpeed   = 0.6f;		// ���s���x
	m_CharaParam[0].fBackSpeed   = 0.3f;		// ��ޑ��x
	m_CharaParam[0].fDashSpeed   = 1.5f;		// �_�b�V�����x

	m_CharaParam[0].fTurn        = 2.0f;		// ���񑬓x

	m_CharaParam[0].fJumpUp		 = 1.0f;		// �W�����v�J�n���̂x���ړ���
	m_CharaParam[0].fJumpDown	 = 0.02f;		// �W�����v���̍~�����x
	m_CharaParam[0].fJumpForward = 0.8f;		// �W�����v���̑O�i���x
	m_CharaParam[0].fJumpBack    = 0.5f;		// �W�����v���̌�ޑ��x

	m_CharaParam[0].fFlyForward	 = 1.5f;		// ��s���̑O�i���x
	m_CharaParam[0].fFlyBack	 = 1.0f;		// ��s���̌�ޑ��x
	m_CharaParam[0].fFlyPlumb    = 0.05f;		// ��s���̏㏸���x

	m_CharaParam[0].fLockLength  = 220.0f;		// ���b�N�I���̂ł��钷��

	m_CharaParam[0].fBrakes		 = 0.04f;		// �_���[�W���̃u���[�L

	/* �q�s�|�s�v�n�p�����[�^�̐ݒ� */
	m_CharaParam[1].pMeshData = new CMeshData(m_pd3dDevice);// ���b�V���ǂݍ���
	m_CharaParam[1].pMeshData->Create(const_cast<TCHAR*>("data\\Chara\\RT-Two\\RT-Two.X"));

	m_CharaParam[1].nMaxLife     = 3500;		// �ő�g�o
	m_CharaParam[1].nMaxEnergy   = 1500;		// �ő�G�l���M�[

	m_CharaParam[1].fWalkSpeed   = 0.4f;		// ���s���x
	m_CharaParam[1].fBackSpeed   = 0.2f;		// ��ޑ��x
	m_CharaParam[1].fDashSpeed   = 2.0f;		// �_�b�V�����x

	m_CharaParam[1].fTurn        = 1.5f;		// ���񑬓x

	m_CharaParam[1].fJumpUp		 = 0.8f;		// �W�����v�J�n���̂x���ړ���
	m_CharaParam[1].fJumpDown	 = 0.03f;		// �W�����v���̍~�����x
	m_CharaParam[1].fJumpForward = 0.5f;		// �W�����v���̑O�i���x
	m_CharaParam[1].fJumpBack    = 0.3f;		// �W�����v���̌�ޑ��x

	m_CharaParam[1].fFlyForward	 = 2.0f;		// ��s���̑O�i���x
	m_CharaParam[1].fFlyBack	 = 1.5f;		// ��s���̌�ޑ��x
	m_CharaParam[1].fFlyPlumb    = 0.08f;		// ��s���̏㏸���x

	m_CharaParam[1].fLockLength  = 300.0f;		// ���b�N�I���̂ł��钷��

	m_CharaParam[1].fBrakes		 = 0.05f;		// �_���[�W���̃u���[�L

	/* �q�s�|�s�g�q�d�d�p�����[�^�̐ݒ� */
	m_CharaParam[2].pMeshData = new CMeshData(m_pd3dDevice);// ���b�V���ǂݍ���
	m_CharaParam[2].pMeshData->Create(const_cast<TCHAR*>("data\\Chara\\RT-Three\\RT-Three.X"));

	m_CharaParam[2].nMaxLife     = 2500;		// �ő�g�o
	m_CharaParam[2].nMaxEnergy   = 800;			// �ő�G�l���M�[

	m_CharaParam[2].fWalkSpeed   = 1.0f;		// ���s���x
	m_CharaParam[2].fBackSpeed   = 0.8f;		// ��ޑ��x
	m_CharaParam[2].fDashSpeed   = 1.5f;		// �_�b�V�����x

	m_CharaParam[2].fTurn        = 2.5f;		// ���񑬓x

	m_CharaParam[2].fJumpUp		 = 1.2f;		// �W�����v�J�n���̂x���ړ���
	m_CharaParam[2].fJumpDown	 = 0.02f;		// �W�����v���̍~�����x
	m_CharaParam[2].fJumpForward = 1.0f;		// �W�����v���̑O�i���x
	m_CharaParam[2].fJumpBack    = 0.8f;		// �W�����v���̌�ޑ��x

	m_CharaParam[2].fFlyForward	 = 1.5f;		// ��s���̑O�i���x
	m_CharaParam[2].fFlyBack	 = 1.2f;		// ��s���̌�ޑ��x
	m_CharaParam[2].fFlyPlumb    = 0.04f;		// ��s���̏㏸���x

	m_CharaParam[2].fLockLength  = 200.0f;		// ���b�N�I���̂ł��钷��

	m_CharaParam[2].fBrakes		 = 0.03f;		// �_���[�W���̃u���[�L

	/* �q�s�|�e�n�t�q�p�����[�^�̐ݒ� */
	m_CharaParam[3].pMeshData = new CMeshData(m_pd3dDevice);// ���b�V���ǂݍ���
	m_CharaParam[3].pMeshData->Create(const_cast<TCHAR*>("data\\Chara\\RT-Four\\RT-Four.X"));

	m_CharaParam[3].nMaxLife     = 4000;		// �ő�g�o
	m_CharaParam[3].nMaxEnergy   = 2000;		// �ő�G�l���M�[

	m_CharaParam[3].fWalkSpeed   = 1.0f;		// ���s���x
	m_CharaParam[3].fBackSpeed   = 0.8f;		// ��ޑ��x
	m_CharaParam[3].fDashSpeed   = 2.0f;		// �_�b�V�����x

	m_CharaParam[3].fTurn        = 2.5f;		// ���񑬓x

	m_CharaParam[3].fJumpUp		 = 1.2f;		// �W�����v�J�n���̂x���ړ���
	m_CharaParam[3].fJumpDown	 = 0.02f;		// �W�����v���̍~�����x
	m_CharaParam[3].fJumpForward = 1.0f;		// �W�����v���̑O�i���x
	m_CharaParam[3].fJumpBack    = 0.8f;		// �W�����v���̌�ޑ��x

	m_CharaParam[3].fFlyForward	 = 2.0f;		// ��s���̑O�i���x
	m_CharaParam[3].fFlyBack	 = 1.5f;		// ��s���̌�ޑ��x
	m_CharaParam[3].fFlyPlumb    = 0.08f;		// ��s���̏㏸���x

	m_CharaParam[3].fLockLength  = 300.0f;		// ���b�N�I���̂ł��钷��

	m_CharaParam[3].fBrakes		 = 0.05f;		// �_���[�W���̃u���[�L


	/* ���[�V�����f�[�^�̓ǂݍ��� */
	m_pMotionData[ANI_STOP] = new CMotionData(m_pd3dDevice);			// ����
	m_pMotionData[ANI_STOP]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\Stop.X"));

	m_pMotionData[ANI_FORWARD] = new CMotionData(m_pd3dDevice);			// �O�i
	m_pMotionData[ANI_FORWARD]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\Forward.X"));

	m_pMotionData[ANI_BACK] = new CMotionData(m_pd3dDevice);			// ���
	m_pMotionData[ANI_BACK]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\Back.X"));

	m_pMotionData[ANI_DASH_F] = new CMotionData(m_pd3dDevice);			// �O�փ_�b�V��
	m_pMotionData[ANI_DASH_F]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DashForward.X"));

	m_pMotionData[ANI_DASH_B] = new CMotionData(m_pd3dDevice);			// ���փ_�b�V��
	m_pMotionData[ANI_DASH_B]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DashBack.X"));

	m_pMotionData[ANI_DASH_R] = new CMotionData(m_pd3dDevice);			// �E�փ_�b�V��
	m_pMotionData[ANI_DASH_R]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DashRight.X"));

	m_pMotionData[ANI_DASH_L] = new CMotionData(m_pd3dDevice);			// ���փ_�b�V��
	m_pMotionData[ANI_DASH_L]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DashLeft.X"));

	m_pMotionData[ANI_ATAS] = new CMotionData(m_pd3dDevice);			// �U���\��
	m_pMotionData[ANI_ATAS]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\GunSta.X"));

	m_pMotionData[ANI_ATA] = new CMotionData(m_pd3dDevice);				// �U��
	m_pMotionData[ANI_ATA]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\GunMot.X"));

	m_pMotionData[ANI_JUMP_N] = new CMotionData(m_pd3dDevice);			// �����W�����v
	m_pMotionData[ANI_JUMP_N]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpNormal.X"));

	m_pMotionData[ANI_JUMP_F] = new CMotionData(m_pd3dDevice);			// �O���W�����v
	m_pMotionData[ANI_JUMP_F]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpForward.X"));

	m_pMotionData[ANI_JUMP_B] = new CMotionData(m_pd3dDevice);			// ����W�����v
	m_pMotionData[ANI_JUMP_B]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpBack.X"));

	m_pMotionData[ANI_JUMP_S] = new CMotionData(m_pd3dDevice);			// �W�����v�J�n
	m_pMotionData[ANI_JUMP_S]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpStart.X"));

	m_pMotionData[ANI_JUMP_E] = new CMotionData(m_pd3dDevice);			// �W�����v�I��
	m_pMotionData[ANI_JUMP_E]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpStart.X"));

	m_pMotionData[ANI_DAM_L] = new CMotionData(m_pd3dDevice);			// �n�ʃ_���[�W
	m_pMotionData[ANI_DAM_L]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DamageLand.X"));

	m_pMotionData[ANI_DAM_A] = new CMotionData(m_pd3dDevice);			// �󒆃_���[�W
	m_pMotionData[ANI_DAM_A]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DamageAir.X"));

	m_pMotionData[ANI_DEAD_L] = new CMotionData(m_pd3dDevice);			// �n�ʎ��S
	m_pMotionData[ANI_DEAD_L]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DeadLand.X"));

	m_pMotionData[ANI_DEAD_A] = new CMotionData(m_pd3dDevice);			// �󒆎��S
	m_pMotionData[ANI_DEAD_A]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DeadAir.X"));


	/* �ϐ��̏����� */
	for(int i=0; i<4; i++)
	{
		m_pChara[i] = NULL;
		m_bReady[i] = false;
	}
	m_nMyChara = 0;

	/* �X�e�[�W�N���X�̍쐬 */
	m_pStage = new CStage(m_pd3dDevice);

	/* �J�����N���X�̍쐬 */
	m_pCamera = new CCamera(m_pd3dDevice);

	/* �e�Ǘ��N���X�̍쐬 */
	m_pBulManage = new CBulManage(m_pd3dDevice);

	/* �X�v���C�g�Ǘ��N���X�̍쐬 */
	m_pSpriteManage = new CSpriteManage(m_pd3dDevice);

	/* �G�t�F�N�g�Ǘ��N���X�̍쐬 */
	m_pEffectManage = new CEffectManage(m_pd3dDevice);

	/* �G�l���M�[�Q�[�W�̍쐬 */
	m_pEnergyGauge = new CEnergyGauge(m_pd3dDevice, const_cast<TCHAR*>("data\\game\\EnergyGauge.png"));

	/* ���C�t�O���t�B�b�N�̍쐬 */
	m_pLifeGraphic = new CLifeGraphic(m_pd3dDevice, const_cast<TCHAR*>("data\\game\\LifeGraphic.png"));

	/* ���ԊǗ��N���X�̍쐬 */
	m_pTimeGraphic = new CTimeGraphic(m_pd3dDevice);
	m_pTimeGraphic->SetMaxTime(180);

	/* �͂��߂͑҂���Ԃ��� */
	m_dwNowStatus  = GAME_START;

}

//----------------------------------------------
//	Name:	~CGame
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CGame::~CGame()
{
	int i;

	/* �g�p�����������̊J�� */
	for(i=0; i<4; i++)			// ���b�V���f�[�^�̉��
		SAFE_DELETE(m_CharaParam[i].pMeshData);	

	for(i=0; i<MAX_MOTION; i++)	// ���[�V�����f�[�^�̉��
		SAFE_DELETE(m_pMotionData[i]);

	for(i=0; i<4; i++)				// �L�����N�^�N���X�̉��
		SAFE_DELETE(m_pChara[i]);	

	SAFE_DELETE(m_pStage);			// �X�e�[�W�N���X�̉��
	SAFE_DELETE(m_pCamera);			// �J�����N���X�̉��
	SAFE_DELETE(m_pBulManage);		// �e�Ǘ��N���X�̉��
	SAFE_DELETE(m_pSpriteManage);	// �X�v���C�g�Ǘ��N���X�̉��
	SAFE_DELETE(m_pEffectManage);	// �G�t�F�N�g�Ǘ��N���X�̉��

	SAFE_DELETE(m_pEnergyGauge);	// �G�l���M�[�Q�[�W�X�v���C�g�̉��
	SAFE_DELETE(m_pLifeGraphic);	// ���C�t�X�v���C�g�̉��
	SAFE_DELETE(m_pTimeGraphic);	// �c�莞�ԃX�v���C�g�̊J��
}

//--------------------------------------------------
//	Name:	CreateChara
//	Func:	�L�����N�^�̍쐬
//	In:		int SelectChara[] = �I���L�����N�^�z��
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CGame::CreateChara(int SelectChara[])
{
	/* �R���s���[�^�̐l�� */
	int nCPUNum = 0;

	m_pChara[0] = new CMyPlayer(m_pd3dDevice);
	m_pChara[1] = new CEnemyCPU(m_pd3dDevice);
	m_pChara[2] = new CEnemyCPU(m_pd3dDevice);
	m_pChara[3] = new CEnemyCPU(m_pd3dDevice);

	/* ���O���Z�b�g����*/
	m_pChara[0]->SetName(const_cast<TCHAR*>("PLAYER"));
	m_pChara[1]->SetName(const_cast<TCHAR*>("COMPUTER1"));
	m_pChara[2]->SetName(const_cast<TCHAR*>("COMPUTER2"));
	m_pChara[3]->SetName(const_cast<TCHAR*>("COMPUTER3"));

	/* �ԍ����Z�b�g���� */
	m_pChara[0]->SetNum(0);
	m_pChara[1]->SetNum(1);
	m_pChara[2]->SetNum(2);
	m_pChara[3]->SetNum(3);

	/* �L�����N�^�̏������W�l�Ȃǂ̐ݒ� */
	/* �L�����N�^�[�P�̐ݒ� */
	if(m_pChara[0])
	{
		m_pChara[0]->SetType(&m_CharaParam[SelectChara[0]]);
		m_pChara[0]->CreateActive(m_pMotionData);
		m_pChara[0]->AllInit(D3DXVECTOR3( 0.0f, -95.0f, -100.0f), 0);

		/* �����̑��삷��L�����N�^�Ȃ�A�ʃL�����ւ̃}�g���N�X�|�C���^�̃Z�b�g */
		if(m_nMyChara == 0)
		{
			if(m_pChara[1])	m_pChara[0]->SetEnemyData(0, m_pChara[1]->GetMatPointer(), m_pChara[1]->GetLifePointer(), m_pChara[1]->GetName());
			if(m_pChara[2])	m_pChara[0]->SetEnemyData(1, m_pChara[2]->GetMatPointer(), m_pChara[2]->GetLifePointer(), m_pChara[2]->GetName());
			if(m_pChara[3])	m_pChara[0]->SetEnemyData(2, m_pChara[3]->GetMatPointer(), m_pChara[3]->GetLifePointer(), m_pChara[3]->GetName());

			/* �L�����N�^�[���t�H���g�̍쐬 */
			m_pChara[0]->CreateCharaName();

			/* �L�����N�^�[���C�t�t�H���g�̍쐬 */
			m_pChara[0]->CreateCharaLife();

		}
	}

	/* �L�����N�^�[�Q�̐ݒ� */
	if(m_pChara[1])
	{
		m_pChara[1]->SetType(&m_CharaParam[SelectChara[1]]);
		m_pChara[1]->CreateActive(m_pMotionData);
		m_pChara[1]->AllInit(D3DXVECTOR3( 100.0f, -95.0f, 0.0f), 270);

		/* �����̑��삷��L�����N�^�Ȃ�A�ʃL�����ւ̃}�g���N�X�|�C���^�̃Z�b�g */
		if(m_nMyChara == 1)
		{
			if(m_pChara[0])	m_pChara[1]->SetEnemyData(0, m_pChara[0]->GetMatPointer(), m_pChara[0]->GetLifePointer(), m_pChara[0]->GetName());
			if(m_pChara[2])	m_pChara[1]->SetEnemyData(1, m_pChara[2]->GetMatPointer(), m_pChara[2]->GetLifePointer(), m_pChara[2]->GetName());
			if(m_pChara[3])	m_pChara[1]->SetEnemyData(2, m_pChara[3]->GetMatPointer(), m_pChara[3]->GetLifePointer(), m_pChara[3]->GetName());

			/* �L�����N�^�[���t�H���g�̍쐬 */
			m_pChara[1]->CreateCharaName();

			/* �L�����N�^�[���C�t�t�H���g�̍쐬 */
			m_pChara[1]->CreateCharaLife();
		}
	}

	/* �L�����N�^�[�R�̐ݒ� */
	if(m_pChara[2])
	{
		m_pChara[2]->SetType(&m_CharaParam[SelectChara[2]]);
		m_pChara[2]->CreateActive(m_pMotionData);
		m_pChara[2]->AllInit(D3DXVECTOR3( 0.0f, -95.0f, 100.0f), 180);

		/* �����̑��삷��L�����N�^�Ȃ�A�ʃL�����ւ̃}�g���N�X�|�C���^�̃Z�b�g */
		if(m_nMyChara == 2)
		{
			if(m_pChara[0])	m_pChara[2]->SetEnemyData(0, m_pChara[0]->GetMatPointer(), m_pChara[0]->GetLifePointer(), m_pChara[0]->GetName());
			if(m_pChara[1])	m_pChara[2]->SetEnemyData(1, m_pChara[1]->GetMatPointer(), m_pChara[1]->GetLifePointer(), m_pChara[1]->GetName());
			if(m_pChara[3])	m_pChara[2]->SetEnemyData(2, m_pChara[3]->GetMatPointer(), m_pChara[3]->GetLifePointer(), m_pChara[3]->GetName());

			/* �L�����N�^�[���t�H���g�̍쐬 */
			m_pChara[2]->CreateCharaName();

			/* �L�����N�^�[���C�t�t�H���g�̍쐬 */
			m_pChara[2]->CreateCharaLife();
		}
	}

	/* �L�����N�^�[�S�̐ݒ� */
	if(m_pChara[3])
	{
		m_pChara[3]->SetType(&m_CharaParam[SelectChara[3]]);
		m_pChara[3]->CreateActive(m_pMotionData);
		m_pChara[3]->AllInit(D3DXVECTOR3( -100.0f, -95.0f, 0.0f), 90);

		/* �����̑��삷��L�����N�^�Ȃ�A�ʃL�����ւ̃}�g���N�X�|�C���^�̃Z�b�g */
		if(m_nMyChara == 3)
		{
			if(m_pChara[0])	m_pChara[3]->SetEnemyData(0, m_pChara[0]->GetMatPointer(), m_pChara[0]->GetLifePointer(), m_pChara[0]->GetName());
			if(m_pChara[1])	m_pChara[3]->SetEnemyData(1, m_pChara[1]->GetMatPointer(), m_pChara[1]->GetLifePointer(),m_pChara[1]->GetName());
			if(m_pChara[2])	m_pChara[3]->SetEnemyData(2, m_pChara[2]->GetMatPointer(), m_pChara[2]->GetLifePointer(),m_pChara[2]->GetName());

			/* �L�����N�^�[���t�H���g�̍쐬 */
			m_pChara[3]->CreateCharaName();

			/* �L�����N�^�[���C�t�t�H���g�̍쐬 */
			m_pChara[3]->CreateCharaLife();
		}
	}

	/* �G�l���M�[�Q�[�W�N���X�ɁA�ő�G�l���M�[�l�̊i�[������ */
	m_pEnergyGauge->SetMaxEnergy(m_pChara[m_nMyChara]->GetMaxEnergy());

	/* ���C�t�O���t�B�b�N�N���X�ɁA�ő�g�o�̒l���i�[���� */
	m_pLifeGraphic->InitLife(m_pChara[m_nMyChara]->GetMaxLife());

	/* �ő吧�����Ԃ̃Z�b�g */
	m_pTimeGraphic->SetMaxTime(180);

	return S_OK;
}


//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	In:		�Ȃ�
//	Out:	int = ��ԕύX���ʎq
//----------------------------------------------
int CGame::FrameMove()
{
	/* �I���t���O */
	bool bEndFlg = false;

	/* ��Ԃɂ���ď����𕪂��� */
	switch(m_dwNowStatus)
	{
		case GAME_START:	Start();			break;
		case GAME_MAIN:		Game();				break;
		case GAME_END:		bEndFlg = End();	break;
	}

	/* �I���t���O�������Ă�����G���f�B���O�ֈڍs���� */
	if(bEndFlg) 
	{
		/* �Q�[���̏�Ԃ�߂� */
		m_dwNowStatus  = GAME_START;

		return CHANGE_ENDING;
	}

	return NO_CHANGE;
}

//----------------------------------------------
//	Name:	Start
//	Func:	�Q�[���J�n���̏���
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void CGame::Start()
{
	static CListSprite*	pCountLogo;
	static int nCnt = 0;

	/* �Q�b��������X�^�[�g���S���쐬���� */
	if(nCnt == 120)	pCountLogo = m_pSpriteManage->AddSprite(COUNT_LOGO);

	/* �J�E���^�[�̃C���N�������g */
	nCnt++;

	/* �T�b��������J�E���g���S�������āA�X�^�[�g���S�����B*/
	/* �Q�[�����J�n���� */
	if(nCnt>300)
	{
		m_pSpriteManage->SubSprite(pCountLogo);
		m_pSpriteManage->AddSprite(START_LOGO);

		m_dwNowStatus = GAME_MAIN;

		/* ���Ԍv���J�n */
		m_pTimeGraphic->Start();

		nCnt = 0;
	}

	/* �X�e�[�W�N���X */
	m_pStage->FrameMove();

	/* �L�����N�^�N���X */
	for(int i=0; i<4; i++)
	{
		if(m_pChara[i])	m_pChara[i]->FrameMoveStart();
	}
	/* �J�����N���X */
	m_pCamera->FrameMove((CMyPlayer*)m_pChara[0]);

	/* �X�v���C�g�Ǘ��N���X */
	m_pSpriteManage->FrameMove();

	/* �G�l���M�[�Q�[�W�N���X */
	m_pEnergyGauge->SetNowEnergy(m_pChara[m_nMyChara]->GetNowEnergy());
	m_pEnergyGauge->FrameMove();

	/* ���C�t�O���t�B�b�N�N���X */
	m_pLifeGraphic->SetLife(m_pChara[m_nMyChara]->GetNowLife());
	m_pLifeGraphic->FrameMove();

	/* ���ԊǗ��N���X */
	m_pTimeGraphic->FrameMove();
}

//----------------------------------------------
//	Name:	Game
//	Func:	�Q�[���J�n���̏���
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void CGame::Game()
{
	/* �X�e�[�W�N���X */
	m_pStage->FrameMove();

	/* �L�����N�^�N���X */
	for(int i=0; i<4; i++)
	{
		if(m_pChara[i])
			m_pChara[i]->FrameMoveGame(	m_pStage, m_pBulManage, m_pSpriteManage,m_pEffectManage);
	}

	/* �J�����N���X */
	m_pCamera->FrameMove((CMyPlayer*)m_pChara[0]);

	/* �e�Ǘ��N���X */
	m_pBulManage->FrameMove(m_pStage, m_pEffectManage);

	/* �X�v���C�g�Ǘ��N���X */
	m_pSpriteManage->FrameMove();

	/* �G�t�F�N�g�Ǘ��N���X */
	m_pEffectManage->FrameMove();

	/* �G�l���M�[�Q�[�W�N���X */
	m_pEnergyGauge->SetNowEnergy(m_pChara[m_nMyChara]->GetNowEnergy());
	m_pEnergyGauge->FrameMove();

	/* ���C�t�O���t�B�b�N�N���X */
	m_pLifeGraphic->SetLife(m_pChara[m_nMyChara]->GetNowLife());
	m_pLifeGraphic->FrameMove();

	/* ���ԊǗ��N���X */
	m_pTimeGraphic->FrameMove();

	/* �������Ԃ��I��������A�Q�[�����I������ */
	if(m_pTimeGraphic->IsEnd())	m_dwNowStatus = GAME_END;
}

//----------------------------------------------
//	Name:	End
//	Func:	�Q�[���J�n���̏���
//	Out:	�Ȃ�
//	In:		bool = �Q�[���I���t���O
//----------------------------------------------
bool CGame::End()
{
	static CListSprite*	pEndLogo;
	static int nCnt = 0;

	/* �͂��߂ɏI�����S���쐬���� */
	if(nCnt == 0)	pEndLogo = m_pSpriteManage->AddSprite(TIME_OVER);

	/* �J�E���^�[�̃C���N�������g */
	nCnt++;

	/* �R�b��������I�����S�������āA�Q�[�����I������ */
	if(nCnt>180)
	{
		m_pSpriteManage->SubSprite(pEndLogo);
		nCnt = 0;
		return true;
	}

	/* �X�e�[�W�N���X */
	m_pStage->FrameMove();

	/* �L�����N�^�N���X */
	for(int i=0; i<4; i++)
	{
		if(m_pChara[i])	m_pChara[i]->FrameMoveEnd();
	}
	/* �J�����N���X */
	m_pCamera->FrameMove((CMyPlayer*)m_pChara[0]);

	/* �X�v���C�g�Ǘ��N���X */
	m_pSpriteManage->FrameMove();

	/* �G�l���M�[�Q�[�W�N���X */
	m_pEnergyGauge->SetNowEnergy(m_pChara[m_nMyChara]->GetNowEnergy());
	m_pEnergyGauge->FrameMove();

	/* ���C�t�O���t�B�b�N�N���X */
	m_pLifeGraphic->SetLife(m_pChara[m_nMyChara]->GetNowLife());
	m_pLifeGraphic->FrameMove();

	/* ���ԊǗ��N���X */
	m_pTimeGraphic->FrameMove();

	return false;

}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void CGame::Render()
{
	int i;

	/* �J�����N���X */
	m_pCamera->Render(m_pChara[0]);

	/* �X�e�[�W�N���X */
	m_pStage->Render();

	/* �L�����N�^�N���X */
	/* �܂��͎����ȊO�̃L�����N�^��`�� */
	for(i=0; i<4; i++)
	{
		if(m_pChara[i] && m_nMyChara != i)
			m_pChara[i]->Render();
	}

	/* ���Ɏ����̃L������`�� */
	for(i=0; i<4; i++)
	{
		if(m_pChara[i] && m_nMyChara == i)
			m_pChara[i]->Render();
	}

	/* �e�Ǘ��N���X */
	m_pBulManage->Render();

	/* �G�t�F�N�g�Ǘ��N���X */
	m_pEffectManage->Render();

	/* �G�l���M�[�Q�[�W�N���X */
	m_pEnergyGauge->Render();

	/* ���C�t�O���t�B�b�N�N���X */
	m_pLifeGraphic->Render();

	/* ���ԊǗ��N���X */
	m_pTimeGraphic->Render();

	/* �X�v���C�g�Ǘ��N���X�i�K���Ō�Ɂj */
	m_pSpriteManage->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�`��p�}�g���N�X�X�V
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void CGame::UpDate()
{
	/* �J�����N���X */
	m_pCamera->UpDate();

	/* �X�e�[�W�N���X */
	m_pStage->UpDate();

	/* �L�����N�^�N���X */
	for(int i=0; i<4; i++)
	{
		if(m_pChara[i])
			m_pChara[i]->UpDate();
	}

	/* �e�Ǘ��N���X */
	m_pBulManage->UpDate();

	/* �X�v���C�g�Ǘ��N���X */
	m_pSpriteManage->UpDate();

	/* �G�t�F�N�g�Ǘ��N���X */
	m_pEffectManage->UpDate();

	/* �G�l���M�[�Q�[�W�N���X */
	m_pEnergyGauge->UpDate();

	/* ���C�t�O���t�B�b�N�N���X */
	m_pLifeGraphic->UpDate();

	/* ���ԊǗ��N���X */
	m_pTimeGraphic->UpDate();

}
