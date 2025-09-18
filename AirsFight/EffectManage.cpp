//==========================================================
// EffectManage.cpp
// Auther : ���� ���V
// Data   : 2002/03/09
//==========================================================
#include "EffectManage.h"

//----------------------------------------------
//	Name:	CEffectManage
//	Func:	�R���X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CEffectManage::CEffectManage(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* �f�o�C�X�̃Z�b�g */
	m_pd3dDevice = d3dDevice;

	/* ���߂̃|�C���^��NULL�� */
	m_pListTop = NULL;

	/* �e�N�X�`���f�[�^�̓ǂݍ��� */
	D3DXCreateTextureFromFileA(m_pd3dDevice,"data\\Effect\\ExplosionA.png",&m_pTexture[0]);
	for(int i=1; i<TEXTURE_NUM; i++)	m_pTexture[i] = NULL;

	/* �N���e�B�J���Z�N�V���������� */
	InitializeCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	~CEffectManage
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CEffectManage::~CEffectManage()
{
	/* ���X�g�̃f�[�^��S�č폜 */
	CEffect *pCurrent = m_pListTop;
	CEffect *pNext = NULL;

	while(pCurrent) {
		pNext = pCurrent->GetNext();
		delete pCurrent;
		pCurrent = pNext;
	}

	/* �g�p�����������̊J�� */
	for(int i=0; i<TEXTURE_NUM; i++)	SAFE_RELEASE(m_pTexture[i]);

	/* �N���e�B�J���Z�N�V�������I�������� */
	DeleteCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	AddEffect
//	Func:	�G�t�F�N�g�̐V�K�쐬
//	in:		DWORD		dwType	= �G�t�F�N�g�^�C�v
//			D3DXMATIRX* pMatIn	= �}�g���N�X
//	Out:	�Ȃ�
//----------------------------------------------
void CEffectManage::AddEffect(DWORD dwType, D3DXMATRIX matIn)
{
	CEffect*	pCurrent = m_pListTop;
	CEffect*	pBack	 = NULL;

	/* �N���e�B�J���Z�N�V�����ɓ��� */
	EnterCriticalSection(&m_cs);

	/* �ǉ�����ʒu��T�� */
	while(pCurrent != NULL)
	{
		pBack = pCurrent;
		pCurrent = pCurrent->GetNext();
	}
	/* �ǉ��ʒu�����������炻���ɍ쐬���� */
	switch(dwType)
	{
	case BOOST_A:		pCurrent = new CBoostA(m_pd3dDevice, m_pTexture[0], matIn);		break;
	case BOOST_B:		pCurrent = new CBoostB(m_pd3dDevice, m_pTexture[0], matIn);		break;
	case EXPLOSION_A:	pCurrent = new CExplosionA(m_pd3dDevice, m_pTexture[0], matIn);	break;
	case EXPLOSION_B:	pCurrent = new CExplosionB(m_pd3dDevice, m_pTexture[0], matIn);	break;
	case ORBIT_BUL:		pCurrent = new COrbitBul(m_pd3dDevice, m_pTexture[0], matIn);	break;
	case REVIVAL:		pCurrent = new CRevival(m_pd3dDevice, m_pTexture[0], matIn);	break;

	}

	/* �f�[�^���Ȃ��� */
	if(pBack)	pBack->SetNext(pCurrent);
	else		m_pListTop = pCurrent;

	/* �N���e�B�J���Z�N�V��������o�� */
	LeaveCriticalSection(&m_cs);

}

//----------------------------------------------
//	Name:	SubEffect
//	Func:	�G�t�F�N�g�̍폜
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CEffectManage::SubEffect()
{
	CEffect* pCurrent = m_pListTop;	// ���ݒ��ׂĂ���ʒu
	CEffect* pBack = NULL;			// ���ݒ��ׂĂ���f�[�^�̂P�O�̃f�[�^
	CEffect* pNext;

	// �N���e�B�J���Z�N�V�����ɓ���
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
	// �N���e�B�J���Z�N�V��������o��
	LeaveCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	�S�ẴG�t�F�N�g�̖��t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CEffectManage::FrameMove()
{
	/* �N���e�B�J���Z�N�V�����ɓ��� */
	EnterCriticalSection(&m_cs);

	CEffect*	pNext = m_pListTop;
	/* ���X�g�̑S�Ă𓮂��� */
	while(pNext != NULL){
		pNext->FrameMove();
		pNext = pNext->GetNext();
	}

	/* �폜���� */
	SubEffect();

	/* �N���e�B�J���Z�N�V��������o�� */
	LeaveCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	Render
//	Func:	�S�ẴG�t�F�N�g�̕`��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CEffectManage::Render()
{
	// �������Ȃǂ̐ݒ�
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_pd3dDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.0f));
	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.0f));
	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.0f));
	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.0f));

	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);

	// �N���e�B�J���Z�N�V�����ɓ���
	EnterCriticalSection(&m_cs);

	CEffect*	pNext = m_pListTop;
	// ���X�g�\���̍Ō�܂Ō���
	while(pNext != NULL){
		pNext->Render();
		pNext = pNext->GetNext();
	}
	// �N���e�B�J���Z�N�V��������o��
	LeaveCriticalSection(&m_cs);

	m_pd3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	// �������Ȃǂ̐ݒ��߂�
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	// �y�o�b�t�@��O�̂��߂ɖ߂�
	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�S�ẴG�t�F�N�g�̕`��p���W�l�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CEffectManage::UpDate()
{
	CEffect*	pNext = m_pListTop;
	// ���X�g�\���̍Ō�܂Ō���
	while(pNext != NULL){
		pNext->UpDate();
		pNext = pNext->GetNext();
	}
}