//==========================================================
// Main.cpp
// Auther : ���� ���V
// Data   : 2002/01/03
//==========================================================
#include "main.h"

//----------------------------------------------
//	Name:	AIRS_FIGHT
//	Func:	�R���X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
AIRS_FIGHT::AIRS_FIGHT()
{
	/* ���݂̏�ԊǗ��N���X�̏����� */
	m_pNowClass = NULL;

	/* �N���e�B�J���Z�N�V���������� */
	InitializeCriticalSection(&m_cs);

	/* �`�撆�t���O������ */
	m_bRenderFlg = false;
}

//----------------------------------------------
//	Name:	OneTimeInit
//	Func:	��x�����̏�����
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
HRESULT AIRS_FIGHT::OneTimeInit()
{
	/* �����_�[�X�e�[�g��ݒ� */
	m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,	  TRUE );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR );
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	
	/* ���C�g�̏���ݒ� */
	D3DLIGHT8 light;
	ZeroMemory(&light, sizeof(D3DLIGHT8));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 0.5f; light.Ambient.r = 0.5f;
	light.Diffuse.g = 0.5f; light.Ambient.g = 0.5f;
	light.Diffuse.b = 0.5f; light.Ambient.b = 0.5f;
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &D3DXVECTOR3(-2.0f, 4.0f, -2.0f) );
	light.Range = 100.0f;
	m_pd3dDevice->LightEnable(0, TRUE);
	m_pd3dDevice->SetLight(0, &light);			// ���C�g��ݒ�

	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xff202020 );
	
	/* ���e�}�g���b�N�X��ݒ肷�� */
	D3DXMATRIX matProj;
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 640.0f/480.0f, 1.0f, 1000.0f );
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	/* �܂��̓^�C�g���N���X���쐬 */
	m_pNowClass = new CTitle(m_pd3dDevice);

	return S_OK;
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
HRESULT AIRS_FIGHT::FrameMove()
{
	int			nNextStatus;		// ���̃N���X������
	GameStatus*	pNewClass = NULL;	// �V�K�N���X

	/* �L���X�g�p�|�C���^ */
	CMenu*		pMenu;
	CGame*		pGame;
	CEnding*	pEnding;

	nNextStatus = m_pNowClass->FrameMove();

	/* �߂�l�̒l�ɂ��N���X��ς��� */
	switch(nNextStatus)
	{
		/* �ύX���Ȃ� */
		case NO_CHANGE:	break;

		/* �^�C�g���ɕύX */
		case CHANGE_TITLE:
			/* �`��I������̂�҂��Ă��猻�݂̃N���X���폜 */
			while(m_bRenderFlg);
			SAFE_DELETE(m_pNowClass);

			/* �^�C�g���N���X���쐬���� */
			m_pNowClass = new CTitle(m_pd3dDevice);
			break;

		/* ���j���[�ɕύX */
		case CHANGE_MENU:
			/* �`��I������̂�҂��Ă��猻�݂̃N���X���폜 */
			while(m_bRenderFlg);
			SAFE_DELETE(m_pNowClass);

			/* ���j���[�N���X���쐬���� */
			m_pNowClass = new CMenu(m_pd3dDevice);
			break;

		/* �Q�[���ɕύX */
		case CHANGE_GAME:
			/* ���݂̃N���X�����j���[�N���X�ɃL���X�g */
			pMenu = (CMenu*)m_pNowClass;

			/* �Q�[���N���X���쐬���� */
			pNewClass = new CGame(m_pd3dDevice);
			pGame = (CGame*)pNewClass;
			pGame->CreateChara(pMenu->GetSelectChara());

			/* �`��I������܂ő҂��Ă��猻�݂̃N���X���폜 */
			while(m_bRenderFlg);
			SAFE_DELETE(m_pNowClass);

			/* �Q�[���N���X�����݂̃N���X�Ƃ��ēo�^*/
			m_pNowClass = pNewClass;
			break;

		/* �G���f�B���O�ɕύX */
		case CHANGE_ENDING:
			/* ���݂̃N���X���Q�[���N���X�ɃL���X�g */
			pGame = (CGame*)m_pNowClass;

			/* �G���f�B���O�N���X���쐬���� */
			pNewClass = new CEnding(m_pd3dDevice);
			pEnding = (CEnding*)pNewClass;
			pEnding->InitOrder(pGame->GetDeadNum(0), pGame->GetDeadNum(1), pGame->GetDeadNum(2), pGame->GetDeadNum(3));

			/* �`��I������܂ő҂��Ă��猻�݂̃N���X���폜 */
			while(m_bRenderFlg);
			SAFE_DELETE(m_pNowClass);

			/* �G���f�B���O�N���X�����݂̃N���X�Ƃ��ēo�^ */
			m_pNowClass = pNewClass;
			break;
	}

	return S_OK;
}

//----------------------------------------------
//	Name:	Render
//	Func:	��ʕ`��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
HRESULT AIRS_FIGHT::Render()
{
	/* ��ԊǗ��N���X���Ȃ���ΏI�� */
	if(!m_pNowClass)	return E_FAIL;

	/* ���Ƀo�b�N�o�b�t�@���N���A */
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	/* �`�撆�t���O�����Ă� */
	m_bRenderFlg = true;

	/* ��ʂɕ`�� */
	m_pNowClass->Render();

	/* �`�撆�t���O��߂� */
	m_bRenderFlg = false;

	return S_OK;
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�`��p�}�g���N�X�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
HRESULT AIRS_FIGHT::UpDate()
{
	/* ��ԊǗ��N���X���Ȃ���ΏI�� */
	if(!m_pNowClass)	return E_FAIL;

	/* �}�g���N�X�̍X�V */
	m_pNowClass->UpDate();
	return S_OK;
}

//----------------------------------------------
//	Name:	CleanUp
//	Func:	�㏈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
HRESULT AIRS_FIGHT::CleanUp()
{
	/* �g�p�����������̊J�� */
	SAFE_DELETE(m_pNowClass);

	/* �N���e�B�J���Z�N�V�������I�������� */
	DeleteCriticalSection(&m_cs);

	return S_OK;
}

//----------------------------------------------------------------------
//	Name:	WinMain
//	Func:	Win32 �A�v���P�[�V�����̏����G���g���|�C���g
//	In:		HINSTANCE	hInstance		�C���X�^���X�n���h��
//			HINSTANCE	hPrevInstance	���g�p
//			LPSTR		lpCmdLine  		�R�}���h���C��������|�C���^
//			int			nCmdShow		�E�B���h�E�̏��
//  Out:	int			�A�v���P�[�V�����̏I���R�[�h
//----------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	/* �x�[�X�N���X�̍쐬 */
	CD3DMain* pCMain = new AIRS_FIGHT;

	/* �ʐM�v���O�����̏����� */
	//if(FAILED( pCMain->InitDPlay(hInstance)))
	//{
	//	SAFE_DELETE(pCMain);
	//	return FALSE;
	//}

	/* �Q�[���Ƃ��ẴA�v���P�[�V�����̑S�Ă̏����� */
	if(FAILED( pCMain->AllCreate(hInstance) ))
	{
		SAFE_DELETE(pCMain);
		return FALSE;
	}

	/* �Q�[���J�n */
	return pCMain->Run();

}
