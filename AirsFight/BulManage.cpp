//==========================================================
// CBullet.cpp
// Auther : ���� ���V
// Data   : 2002/01/11
//==========================================================

#include "BulManage.h"

//----------------------------------------------
//	Name:	CBulManage
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 = D3D�f�o�C�X
//	Out:	�Ȃ�
//----------------------------------------------
CBulManage::CBulManage(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* �f�o�C�X�̃Z�b�g */
	m_pd3dDevice = d3dDevice;

	/* �ŏ��̃|�C���^��NULL�� */
	m_pListTop = NULL;

	/* �e�p�����[�^�̍쐬 */
	m_tagParam[0].pBulMesh = new CMeshObject(m_pd3dDevice);
	m_tagParam[0].pBulMesh->Create(const_cast<TCHAR*>("data\\Bullet\\Bullet.X"));
	m_tagParam[0].pBulMesh->RestoreDeviceObjects();

	m_tagParam[0].fSpeed = 3.0f;
	m_tagParam[0].nMaxLife = 120;
	m_tagParam[0].nShotFrame = 5;

	/* �g��Ȃ��Ƃ���ɂ�NULL�� */
	m_tagParam[1].pBulMesh = NULL;
	m_tagParam[2].pBulMesh = NULL;

	/* �N���e�B�J���Z�N�V���������� */
	InitializeCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	~CBullet
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CBulManage::~CBulManage()
{
	/* ���X�g�̃f�[�^��S�č폜 */
	CBullet *pCurrent = m_pListTop;
	CBullet *pNext = NULL;

	while(pCurrent) {
		pNext = pCurrent->GetNext();
		delete pCurrent;
		pCurrent = pNext;
	}

	/* ���b�V���f�[�^�̉�� */
	for(int i=0; i<3; i++)
		SAFE_DELETE(m_tagParam[i].pBulMesh);

	/* �N���e�B�J���Z�N�V�������I�������� */
	DeleteCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	AddBullet
//	Func:	�e�̒ǉ�
//	in:		int			nType		= �e�̃^�C�v
//			D3DXMATRIX	matBase		= �����}�g���N�X
//			int			nCharaNum	= �L�����N�^�ԍ�
//	Out:	�Ȃ�
//----------------------------------------------
void CBulManage::AddBullet(int nType, D3DXMATRIX matBase, int nCharaNum)
{
	/* ID�ԍ� */
	static long	lID = 0;

	CBullet*	pCurrent = m_pListTop;
	CBullet*	pBack	 = NULL;

	/* �N���e�B�J���Z�N�V�����ɓ��� */
	EnterCriticalSection(&m_cs);

	/* �ǉ�����ʒu��T�� */
	while(pCurrent != NULL)
	{
		pBack = pCurrent;
		pCurrent = pCurrent->GetNext();
	}
	/* �ǉ��ʒu�����������炻���ɍ쐬���� */
	pCurrent = new CBullet(m_pd3dDevice, &m_tagParam[nType], matBase, lID);

	/* �f�[�^���Ȃ��� */
	if(pBack)	pBack->SetNext(pCurrent);
	else		m_pListTop = pCurrent;

	/* �N���e�B�J���Z�N�V��������o�� */
	LeaveCriticalSection(&m_cs);

	lID ++;
}

//----------------------------------------------
//	Name:	SubBullet
//	Func:	�e�̍폜
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CBulManage::SubBullet()
{
	CBullet* pCurrent = m_pListTop;	// ���ݒ��ׂĂ���ʒu
	CBullet* pBack = NULL;			// ���ݒ��ׂĂ���f�[�^�̂P�O�̃f�[�^
	CBullet* pNext;

	/* �N���e�B�J���Z�N�V�����ɓ��� */
	EnterCriticalSection(&m_cs);

	// ���X�g�\���̍Ō�܂Ō���
	while(pCurrent != NULL){
		if(pCurrent->IsDelete()){
			// �I�u�W�F�N�g�����X�g�\������폜
			pNext = pCurrent->GetNext();
			delete pCurrent;

			if (pBack == NULL) {
				// �O�̃f�[�^�������i���ݒ��ׂĂ���f�[�^���A���X�g�̐擪�̃f�[�^�̎�
				m_pListTop = pNext;
				pCurrent = pNext;
			}
			else {
				// ���X�g�̓r���̃f�[�^�̎�
				pCurrent = pNext;			// ���ׂ�ʒu�����̃f�[�^�ɂ���
				pBack->SetNext(pCurrent);	// �������f�[�^���A���X�g���l�߂�
			}
		}
		else {
			// ���݂̃f�[�^���A�����K�v��������
			pBack = pCurrent;
			pCurrent = pCurrent->GetNext();
		}
	}

	/* �N���e�B�J���Z�N�V��������o�� */
	LeaveCriticalSection(&m_cs);

}

//------------------------------------------------------
//	Name:	FrameMove
//	Func:	�S�Ă̒e�̖��t���[���̏���
//	in:		CStage* pStage = �X�e�[�W�N���X�ւ̃|�C���^
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X�|�C���^
//	Out:	�Ȃ�
//------------------------------------------------------
void CBulManage::FrameMove(CStage* pStage, CEffectManage* pEffectManage)
{
	CBullet*	pNext = m_pListTop;

	/* ���X�g�\���̍Ō�܂ŌJ��Ԃ� */
	while(pNext != NULL){
		pNext->FrameMove(pEffectManage);
		pNext = pNext->GetNext();
	}

	/* �e�̕ǂƂ̂����蔻�� */
	HitPlane(pStage, pEffectManage);

	/* �e�̍폜 */
	SubBullet();
}

//------------------------------------------------------
//	Name:	SearchBullet
//	Func:	���ʔԍ�����e��{��
//	in:		long lID = �w�莯�ʔԍ�
//	Out:	�Ȃ�
//------------------------------------------------------
CBullet* CBulManage::SearchBullet(long lID)
{
	CBullet*	pNext = m_pListTop;
	long		IDTmp;

	/* ���X�g�\���̍Ō�܂ŌJ��Ԃ� */
	while(pNext != NULL){
		IDTmp = pNext->GetID();

		/* �w��ID�Ƃ����Ă����琬�� */
		if(IDTmp == lID)
			return pNext;

		/* �����Ă��Ȃ������玟�̒e�𒲂ׂ� */
		else
			pNext = pNext->GetNext();
	}

	/* �S�Ă̒e�ɂȂ����NULL��Ԃ� */
	return NULL;
}

//------------------------------------------------------
//	Name:	HitPlane
//	Func:	���ׂĂ̒e�̕ǂƂ̓����蔻��
//	in:		CStage* pStage = �X�e�[�W�N���X�ւ̃|�C���^
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X�|�C���^
//	Out:	�Ȃ�
//------------------------------------------------------
void CBulManage::HitPlane(CStage* pStage, CEffectManage* pEffectManage)
{
	CBullet*	pNext = m_pListTop;

	/* ���X�g�\���̍Ō�܂ŌJ��Ԃ� */
	while(pNext != NULL)
	{
		// �e�̈ʒu�ƕǂƂ��������A��苗���ȓ��Ȃ�e������
		if(SearchAllPlane(pStage, pNext->GetPosBase(), pNext->GetMoveVec()) < HIT_WALL_LENGTH)
		{
			pNext->Delete();
			pEffectManage->AddEffect(EXPLOSION_B, pNext->GetMatBase());
		}
		pNext = pNext->GetNext();
	}
}

//----------------------------------------------
//	Name:	Render
//	Func:	�S�Ă̒e�̕`��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CBulManage::Render()
{
	CBullet*	pNext = m_pListTop;

	/* �N���e�B�J���Z�N�V�����ɓ��� */
	EnterCriticalSection(&m_cs);

	/* ���X�g�\���̍Ō�܂ŌJ��Ԃ� */
	while(pNext != NULL){
		pNext->Render();
		pNext = pNext->GetNext();
	}

	/* �N���e�B�J���Z�N�V��������o�� */
	LeaveCriticalSection(&m_cs);

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�S�Ă̒e�̕`��p���W�l�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CBulManage::UpDate()
{
	CBullet*	pNext = m_pListTop;

	/* ���X�g�\���̍Ō�܂ŌJ��Ԃ� */
	while(pNext != NULL){
		pNext->UpDate();
		pNext = pNext->GetNext();
	}
}

//--------------------------------------------------------------
//	Name:	SearchAllPlane
//	Func:	�S�ẴI�u�W�F�N�g�̕ǂ𒲂ׂāA��ԋ����̒Z���ʂ��̗p�A
//			���������ꍇ���̖ʂƂ̋����݂̂�Ԃ�
//	in:		CStage*			pStage	= �X�e�[�W�N���X�ւ̃|�C���^
//			D3DXVECTOR3		vecPos	= �I�u�W�F�N�g�̍��W�l
//			D3DXVECTOR3		vecMove	= �I�u�W�F�N�g�̈ړ�����
//	Out:	float					= �ʂƂ̋���
//--------------------------------------------------------------
float CBulManage::SearchAllPlane(CStage* pStage, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecMove)
{
	float		fLenAdop,fLen;
	D3DXVECTOR3	vecCrossAdop1,vecCross1;
	D3DXVECTOR3	vecCrossAdop2,vecCross2;
	float		fTmp1, fTmp2;
	int			i;

	D3DXVECTOR3 diff;
	D3DXMATRIX matBase;

	fLenAdop = 99999;

	/* �u���b�N�^�C�v�̃I�u�W�F�N�g�𒲂ׂ� */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		/* �L�����N�^�ƃI�u�W�F�N�g������Ă����璲�ׂȂ� */
		diff = pStage->GetBlockObj(i)->GetPosBase() - vecPos;
		fTmp1 = D3DXVec3LengthSq(&diff );
		fTmp2 = (pStage->GetBlockObj(i)->GetLength()) * (pStage->GetBlockObj(i)->GetLength());

		if(fTmp1 < fTmp2)
		{
			matBase = pStage->GetBlockObj(i)->GetMatBase();
			if( SearchPlane(pStage->GetBlockObj(i)->GetMesh(), &matBase,
				&vecPos, &vecMove, NULL, NULL, &fLen))
			{
				if(fLenAdop > fLen)
				{
					// ���ׂ����ׂẴI�u�W�F�N�g�̒��ň�ԋ������Z���ʂ��̗p
					fLenAdop = fLen;
				}
			}
		}
	}

	/* �E�H�[���^�C�v�̃I�u�W�F�N�g�𒲂ׂ� */
	for(i=0; i<pStage->GetWallNum(); i++)
	{
		matBase = pStage->GetWallObj(i)->GetMatBase();
		if( SearchPlane(pStage->GetWallObj(i)->GetMesh(), &matBase,
			&vecPos, &vecMove, NULL, NULL, &fLen))
		{
			if(fLenAdop > fLen)
			{
				// ���ׂ����ׂẴI�u�W�F�N�g�̒��ň�ԋ������Z���ʂ��̗p
				fLenAdop = fLen;
			}
		}
	}

	// �ʂ����������ꍇ���̋�����Ԃ�
	return fLenAdop;
}