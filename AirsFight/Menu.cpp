//==========================================================
// Menu.cpp
// Auther : ���� ���V
// Data   : 2002/05/01
//==========================================================

#include "Menu.h"

//------------------------------------------------------
//	Name:	CMenu
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3D�f�o�C�X
//	Out:	�Ȃ�
//------------------------------------------------------
CMenu::CMenu(LPDIRECT3DDEVICE8 d3dDevice)
	  :GameStatus(d3dDevice)
{	
	long	lTmp;
	int		i;

	/* �R���s���[�^�t���O�̏����� */
	for(i=0; i<4; i++)	m_bCPUFlg[i] = false;

	/* ID�z��̓Y������0 */
	m_nMyChara = 0;	

	/* �v���C���[�̏����� */
	m_nSelectChara[0] = 0;		// �L�����N�^�̏�����
	m_bOK[0] = false;			// �����܂�

	/* �R���s���[�^�������_���Ō��߂� */
	srand(time(&lTmp));		// �����_���̏�����
	for(i=1; i<4; i++)
	{
		srand(lTmp * rand()%500);
		m_nSelectChara[i] = rand()%4;	// �L�����N�^�����߂�
		m_bOK[i] = true;				// �����n�j
	}

	/* ���j���[�w�i�̍쐬 */
	m_pBackGround = new CScrollBG(m_pd3dDevice, "data\\Menu\\MenuBG.png", 256, 256);
	m_pBackGround->SetVecDir(D3DXVECTOR2(1.0, 1.0));

	/* ���j���[���S�̍쐬 */
	m_pLogo = new CSprite(m_pd3dDevice, "Data\\Menu\\MenuLogo.png");
	m_pLogo->SetVec(D3DXVECTOR2(64, 8));
	m_pLogo->SetRec(0,0,512,64);

	/* �摜�̍쐬 */
	for(i=0; i<4; i++)
	{
		/* �L�����N�^�C���[�W�̍쐬 */
		m_pCharaImage[i] = new CSprite(m_pd3dDevice, "Data\\Menu\\CharaImage.png");

		/* �q�d�`�c�x�X�v���C�g�̍쐬 */
		m_pReady[i]		 = new CSprite(m_pd3dDevice, "Data\\Menu\\Ready.png");
		m_pReady[i]->SetRec(0,0,200,128);

		/* �v���C���[�̖��O�̍쐬 */
		m_pPlayerName[i] = new CFont(m_pd3dDevice, "HGP�޼��E", 30);
		m_pPlayerName[i]->SetFormat(DT_CENTER);
		m_pPlayerName[i]->SetColor(255, 0, 0);
	}

	/* �v���C���[���̊i�[ */
	m_pPlayerName[0]->SetString( "PLAYER" );
	m_pPlayerName[1]->SetString( "COMPUTER1" );
	m_pPlayerName[2]->SetString( "COMPUTER2" );
	m_pPlayerName[3]->SetString( "COMPUTER3" );

	/* �L�����N�^�X�v���C�g�̕`��ʒu�̏����� */
	m_pCharaImage[0]->SetVec(D3DXVECTOR2(0, 80));
	m_pCharaImage[1]->SetVec(D3DXVECTOR2(320, 80));
	m_pCharaImage[2]->SetVec(D3DXVECTOR2(0, 280));
	m_pCharaImage[3]->SetVec(D3DXVECTOR2(320, 280));

	/* �q�d�`�c�x�X�v���C�g�̕`��ʒu�̏����� */
	m_pReady[0]->SetVec(D3DXVECTOR2( 40, 120));
	m_pReady[1]->SetVec(D3DXVECTOR2(360, 120));
	m_pReady[2]->SetVec(D3DXVECTOR2( 40, 320));
	m_pReady[3]->SetVec(D3DXVECTOR2(360, 320));

	/* �v���C���[�̖��O�̕`��ʒu������ */
	m_pPlayerName[0]->SetRec(  0, 240, 200, 280);
	m_pPlayerName[1]->SetRec(320, 240, 520, 280);
	m_pPlayerName[2]->SetRec(  0, 440, 200, 480);
	m_pPlayerName[3]->SetRec(320, 440, 520, 480);

}
//----------------------------------------------
//	Name:	~CMenu
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CMenu::~CMenu()
{
	/* �g�p�����������̊J�� */
	SAFE_DELETE(m_pBackGround);
	SAFE_DELETE(m_pLogo);
	for(int i=0; i<4; i++)
	{
		SAFE_DELETE(m_pCharaImage[i]);
		SAFE_DELETE(m_pReady[i]);
		SAFE_DELETE(m_pPlayerName[i]);
	}
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	Out:	�Ȃ�
//	In:		int = ��ԕύX���ʎq
//----------------------------------------------
int CMenu::FrameMove()
{
	/* �������܂��I�𒆂Ȃ�I�����鏈�� */
	if(!m_bOK[m_nMyChara])
	{
		/* ������� */
		if(GetAsyncKeyState(VK_UP) & 0x0001)
		{
			m_nSelectChara[m_nMyChara]++;
			if(m_nSelectChara[m_nMyChara] >= MAX_CHARA)
				m_nSelectChara[m_nMyChara] = 0;
		}

		/* �������� */
		else if(GetAsyncKeyState(VK_DOWN) & 0x0001)
		{
			m_nSelectChara[m_nMyChara]--;
			if(m_nSelectChara[m_nMyChara] < 0)
				m_nSelectChara[m_nMyChara] = MAX_CHARA-1;
		}

		/* �G���^�[�������Ə����n�j */
		else if(GetAsyncKeyState(VK_RETURN) & 0x0001)
		{
			m_bOK[m_nMyChara] = true;
		}
	}

	/* ��������������ς݂Ȃ�҂� */
	else
	{
		/* �G�X�P�[�v�������Ƃ���������蒼�� */
		if(GetAsyncKeyState(VK_ESCAPE) & 0x0001)
		{
			m_bOK[m_nMyChara] = false;
		}
	}

	/* �I�����Ă���L�����N�^�ɂ��A�\���ʒu�����߂� */
	for(int i=0; i<4; i++)
	{
		switch(m_nSelectChara[i])
		{
		/* RT-ONE��\������ */
		case 0:
			m_pCharaImage[i]->SetRec(0,0,256,150);
			break;
		/* RT-TWO��\������ */
		case 1:
			m_pCharaImage[i]->SetRec(0,150,256,300);
			break;
		/* RT-THREE��\������ */
		case 2:
			m_pCharaImage[i]->SetRec(0,300,256,450);
			break;
		/* RT_FOUR��\������ */
		case 3:
			m_pCharaImage[i]->SetRec(256,0,512,150);
			break;

		/* �v���C���[�����Ȃ��Ƃ݂Ȃ��A�u�N�����Ȃ��v��\������ */
		case -1:
			m_pCharaImage[i]->SetRec(256,300,512,450);
			break;
		}
	}

	/* ���j���[�w�i�𓮂��� */
	m_pBackGround->FrameMove();

	/* �S���n�j�Ȃ�Q�[���ֈڍs���� */
	if(m_bOK[0] && m_bOK[1] && m_bOK[2] && m_bOK[3])
		return CHANGE_GAME;

	return NO_CHANGE;
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void CMenu::Render()
{
	int i;

	/* ���j���[�w�i */
	m_pBackGround->Render();

	/* ���j���[���S */
	m_pLogo->Render();

	/* �L�����N�^�C���[�W */
	for(i=0; i<4; i++)
		m_pCharaImage[i]->Render();

	/* �v���C���[�� */
	for(i=0; i<4; i++)
		m_pPlayerName[i]->Render();

	/* �q�d�`�c�x�X�v���C�g */
	for(i=0; i<4; i++)
		if(m_nSelectChara[i] != -1 && m_bOK[i])
			m_pReady[i]->Render();

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�X�V
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void CMenu::UpDate()
{
	int i;

	/* ���j���[�w�i */
	m_pBackGround->UpDate();

	/* ���j���[���S */
	m_pLogo->UpDate();

	/* �L�����N�^�C���[�W */
	for(i=0; i<4; i++)
		m_pCharaImage[i]->UpDate();

	/* �v���C���[�� */
	for(i=0; i<4; i++)
		m_pPlayerName[i]->UpDate();

	/* �q�d�`�c�x�X�v���C�g */
	for(i=0; i<4; i++)
		m_pReady[i]->UpDate();
}
