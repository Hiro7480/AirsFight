//==========================================================
// Title.cpp
// Auther : ���� ���V
// Data   : 2002/01/11
//==========================================================

#include "Title.h"

//------------------------------------------------------
//	Name:	CTitle
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3D�f�o�C�X
//	Out:	�Ȃ�
//------------------------------------------------------
CTitle::CTitle(LPDIRECT3DDEVICE8 d3dDevice)
	  :GameStatus(d3dDevice)
{
	/* �^�C�g�����S�̍쐬 */
	m_pTitleLogo = new CSprite(m_pd3dDevice, const_cast<TCHAR*>("Data\\Title\\TitleLogo.png"));
	m_pTitleLogo->SetVec(D3DXVECTOR2(64, 50));
	m_pTitleLogo->SetRec(0, 0, 480, 200);

	/* �G���^�[�����̍쐬 */
	m_pPressEnter = new CSprite(m_pd3dDevice, const_cast<TCHAR*>("Data\\Title\\PressEnter.png"));
	m_pPressEnter->SetVec(D3DXVECTOR2(192, 350));
	m_pPressEnter->SetRec(0, 0, 256, 64);

	/* �^�C�g���L�����N�^�̍쐬 */
	m_pTitleChara = new CSprite(m_pd3dDevice, const_cast<TCHAR*>("Data\\Title\\TitleChara.png"));
	m_pTitleChara->SetVec(D3DXVECTOR2(380, 0));
	m_pTitleChara->SetRec(0, 0, 256, 512);

	/* �^�C�g���w�i�̍쐬 */
	m_pBackGround = new CScrollBG(m_pd3dDevice, const_cast<TCHAR*>("data\\Title\\TitleBG.png"), 512, 512);
	m_pBackGround->SetVecDir(D3DXVECTOR2(1.0, 1.0));

}
//----------------------------------------------
//	Name:	~CTitle
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CTitle::~CTitle()
{
	/* �g�p�����������̊J�� */
	SAFE_DELETE(m_pTitleLogo);
	SAFE_DELETE(m_pPressEnter);
	SAFE_DELETE(m_pTitleChara);
	SAFE_DELETE(m_pBackGround);
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	Out:	�Ȃ�
//	In:		int = ��ԕύX���ʎq
//----------------------------------------------
int CTitle::FrameMove()
{
	/* �^�C�g�����S */
	m_pTitleLogo->FrameMove();

	/* �G���^�[���� */
	m_pPressEnter->FrameMove();

	/* �^�C�g���L���� */
	m_pTitleChara->FrameMove();

	/* �^�C�g���w�i */
	m_pBackGround->FrameMove();

	/* ���^�[�����������烁�j���[�ֈڍs���� */
	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
		return CHANGE_MENU;

	return NO_CHANGE;
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void CTitle::Render()
{
	/* �^�C�g���w�i */
	m_pBackGround->Render();

	/* �^�C�g���L���� */
	m_pTitleChara->Render();

	/* �G���^�[���� */
	m_pPressEnter->Render();

	/* �^�C�g�����S */
	m_pTitleLogo->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�X�V
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void CTitle::UpDate()
{
	/* �^�C�g���w�i */
	m_pBackGround->UpDate();

	/* �^�C�g���L���� */
	m_pTitleChara->UpDate();

	/* �G���^�[���� */
	m_pPressEnter->UpDate();

	/* �^�C�g�����S */
	m_pTitleLogo->UpDate();
}
