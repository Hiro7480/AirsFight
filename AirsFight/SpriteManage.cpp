//==========================================================
// SpriteManage.cpp
// Auther : ���� ���V
// Data   : 2002/04/29
//==========================================================

#include "SpriteManage.h"

//----------------------------------------------
//	Name:	CSpriteManage
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 = D3D�f�o�C�X
//	Out:	�Ȃ�
//----------------------------------------------
CSpriteManage::CSpriteManage(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* �f�o�C�X�̃Z�b�g */
	m_pd3dDevice = d3dDevice;

	/* �ŏ��̃|�C���^��NULL�� */
	m_pListTop = NULL;

	/* �X�v���C�g�쐬 */
	D3DXCreateSprite(m_pd3dDevice,&m_pSprite);

	/* �e�N�X�`���f�[�^�̓ǂݍ��� */
	D3DXCreateTextureFromFileA(m_pd3dDevice,"data\\Game\\StartLogo.png",&m_pTexture[0]);
	D3DXCreateTextureFromFileA(m_pd3dDevice,"data\\Game\\TimeOver.png",&m_pTexture[1]);
	for(int i=2; i<10; i++)	m_pTexture[i] = NULL;

	/* �N���e�B�J���Z�N�V���������� */
	InitializeCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	~CSpriteManage
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CSpriteManage::~CSpriteManage()
{
	/* ���X�g�̃f�[�^��S�č폜 */
	CListSprite *pCurrent = m_pListTop;
	CListSprite *pNext = NULL;

	while(pCurrent) {
		pNext = pCurrent->GetNext();
		delete pCurrent;
		pCurrent = pNext;
	}

	/* �g�p�����������̊J�� */
	for(int i=0; i<10; i++)	SAFE_RELEASE(m_pTexture[i]);
	SAFE_RELEASE(m_pSprite);

	/* �N���e�B�J���Z�N�V�������I�������� */
	DeleteCriticalSection(&m_cs);
}

//--------------------------------------------------------------
//	Name:	AddSprite
//	Func:	�X�v���C�g�̒ǉ�
//	in:		int			nType	= �X�v���C�g�̃^�C�v
//	Out:	CListSprite*	�쐬�����|�C���^��Ԃ� ���s����NULL��Ԃ�
//--------------------------------------------------------------
CListSprite* CSpriteManage::AddSprite(int nType)
{
	CListSprite*	pCurrent = m_pListTop;
	CListSprite*	pBack	 = NULL;

	/* �ǉ�����ʒu��T�� */
	while(pCurrent != NULL)
	{
		pBack = pCurrent;
		pCurrent = pCurrent->GetNext();
	}
	/* �ǉ��ʒu�����������炻���ɍ쐬���� */
	switch(nType)
	{
		/* �J�E���^�[���S�̍쐬 */
		case COUNT_LOGO:	pCurrent = new CCountLogo(m_pd3dDevice, m_pTexture[0]);	break;

		/* �X�^�[�g���S�̍쐬 */
		case START_LOGO:	pCurrent = new CStartLogo(m_pd3dDevice, m_pTexture[0]); break;

		/* �^�C���I�[�o�[�̍쐬 */
		case TIME_OVER:		pCurrent = new CTimeOverLogo(m_pd3dDevice, m_pTexture[1]); break;

		/* �쐬���s */
		default:	return NULL;
	}


	/* �f�[�^���Ȃ��� */
	if(pBack)	pBack->SetNext(pCurrent);
	else		m_pListTop = pCurrent;

	/* �|�C���^��Ԃ��ďI�� */
	return pCurrent;
}

//--------------------------------------------------
//	Name:	SubSprite
//	Func:	�w��X�v���C�g���폜����
//	in:		CListSprite* pSprite = �폜����w��|�C���^
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CSpriteManage::SubSprite(CListSprite* pSprite)
{
	CListSprite* pCurrent = m_pListTop;	// ���ݒ��ׂĂ���ʒu
	CListSprite* pBack = NULL;			// ���ݒ��ׂĂ���f�[�^�̂P�O�̃f�[�^


	/* ���X�g�\���̍Ō�܂ō폜����ꏊ������ */
	while(pCurrent != NULL)
	{
		if(pCurrent  == pSprite) break;

		pBack = pCurrent;
		pCurrent = pCurrent->GetNext();
	}

	/* �w��|�C���^��������Ȃ������玸�s�Ƃ݂Ȃ� */
	if(pCurrent == NULL)	return E_FAIL;

	/* �I�u�W�F�N�g�����X�g�\������폜 */
	CListSprite* pNext;
	pNext = pCurrent->GetNext();
	delete pCurrent;

	/* �f�[�^���Ȃ��� */

	/* �������f�[�^�����X�g�̏��߂̃f�[�^�������� */
	if (pBack == NULL)
	{
		m_pListTop = pNext;
		pCurrent = pNext;
	}
	/* �������f�[�^�����X�g�̓r���A���邢�͍Ō�̃f�[�^�̎� */
	else {

		pCurrent = pNext;			// ���ׂ�ʒu�����̃f�[�^�ɂ���
		pBack->SetNext(pCurrent);	// �������f�[�^���A���X�g���l�߂�
	}

	return S_OK;
}

//--------------------------------------------------
//	Name:	SubSprite
//	Func:	�X�v���C�g�̎�������
//	in:		�Ȃ�
//	Out:	�Ȃ�
//--------------------------------------------------
void CSpriteManage::SubSprite()
{
	CListSprite* pCurrent = m_pListTop;	// ���ݒ��ׂĂ���ʒu
	CListSprite* pBack = NULL;			// ���ݒ��ׂĂ���f�[�^�̂P�O�̃f�[�^
	CListSprite* pNext;

	/* ���X�g�\���̍Ō�܂Ō��� */
	while(pCurrent != NULL){

		/* �I�u�W�F�N�g�����������ׂ� */
		if(pCurrent->IsDelete()){

			/* �I�u�W�F�N�g�����X�g�\������폜 */
			pNext = pCurrent->GetNext();
			delete pCurrent;

			/* �f�[�^���q���� */
			if (pBack == NULL) {
				m_pListTop = pNext;
				pCurrent = pNext;
			}
			else {
				pCurrent = pNext;
				pBack->SetNext(pCurrent);
			}
		}
		/* ���݂̃f�[�^���A�����K�v�������� */
		else {
	
			pBack = pCurrent;
			pCurrent = pCurrent->GetNext();
		}
	}

}

//------------------------------------------------------
//	Name:	FrameMove
//	Func:	�S�ẴX�v���C�g�̖��t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------
void CSpriteManage::FrameMove()
{
	CListSprite*	pNext = m_pListTop;

	/* �N���e�B�J���Z�N�V�����ɓ��� */
	EnterCriticalSection(&m_cs);

	/* �S�ẴX�v���C�g�̖��t���[���������Ă� */
	while(pNext != NULL){
		pNext->FrameMove();
		pNext = pNext->GetNext();
	}

	/* �N���e�B�J���Z�N�V��������o�� */
	LeaveCriticalSection(&m_cs);
	
	/* �����ɑS�ẴX�v���C�g�ɑ΂��A����������s�� */
	SubSprite();


}

//----------------------------------------------
//	Name:	Render
//	Func:	�S�ẴX�v���C�g�̕`��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CSpriteManage::Render()
{
	CListSprite*	pNext = m_pListTop;

	/* �X�v���C�g�`��J�n */
	m_pSprite->Begin();

	/* �N���e�B�J���Z�N�V�����ɓ��� */
	EnterCriticalSection(&m_cs);

	/* ���X�g�\���̍Ō�܂ŌJ��Ԃ� */
	while(pNext != NULL){
		pNext->Render(m_pSprite);
		pNext = pNext->GetNext();
	}

	/* �N���e�B�J���Z�N�V��������o�� */
	LeaveCriticalSection(&m_cs);

	/* �X�v���C�g�`��I�� */
	m_pSprite->End();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�S�ẴX�v���C�g�̃f�[�^�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CSpriteManage::UpDate()
{
	CListSprite*	pNext = m_pListTop;

	/* ���X�g�\���̍Ō�܂ŌJ��Ԃ� */
	while(pNext != NULL){
		pNext->UpDate();
		pNext = pNext->GetNext();
	}
}
