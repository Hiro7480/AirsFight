//==========================================================
// D3DMain.cpp
// Auther : ���� ���V
// Data   : 2002/01/03
//==========================================================

#include "D3DMain.h"

// �O���[�o���ϐ�
static CD3DMain* g_pCAppli = NULL;


//----------------------------------------------
//	Name:	WndProc
//	Func:	�E�B���h�E�v���V�[�W��
//	In	:	HWND hWnd		�E�B���h�E�n���h��
//			UINT msg		���b�Z�[�W���ʎq
//			UINT wParam		��P���b�Z�[�W�p�����[�^
//			LONG lParam		��Q���b�Z�[�W�p�����[�^
//	Out:	LRESULT
//----------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
{
	return g_pCAppli->MsgProc(hWnd, msg, wParam, lParam);
}

//----------------------------------------------
//	Name:	FrameThread
//	Func:	�����p�X���b�h
//	In:		VOID*	�e�Ƌ��L����f�[�^�̃A�h���X
//	Out:	DWORD
//----------------------------------------------
DWORD WINAPI FrameThread(VOID *pVOID)
{
	g_pCAppli->FrameProc();
	return TRUE;
}

//----------------------------------------------
//	Name:	D3DMain
//	Func:	�R���X�g���N�^
//	In	:	�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CD3DMain::CD3DMain()
{
	g_pCAppli = this;

	/* �^�C�g�����̏����� */
	//strcpy(szTitle, "AIRS FIGHT");
	_tcscpy_s(szTitle, _T("AIRS FIGHT"));

	/* Window�N���X���̏����� */
	//strcpy(szWindowClass, "AIRS FIGHT");
	_tcscpy_s(szWindowClass, _T("AIRS FIGHT"));



	/* �E�B���h�E���[�h�̏�����(TRUE �E�B���h�E���[�h FALSE �t���X�N���[�����[�h) */
	m_bWindowMode = true;

	/* �E�B���h�E�T�C�Y�̏����� */
	m_nWndHeight = SCREEN_HEIGHT;
	m_nWndWidth  = SCREEN_WIDTH;

	/* �e�t���O�̏����� */
	m_bAppActive = false;
	m_bEndFlg = false;
	m_bFpsFlg = false;
	m_bThread = false;
	m_bRenderFlg = false;
}

//----------------------------------------------
//	Name:	Run
//	Func:	���C�����[�v
//	In	:	�Ȃ�
//	Out:	int
//----------------------------------------------
int CD3DMain::Run()
{

	MSG msg;
	while(!m_bEndFlg)
	{
		/* ���b�Z�[�W���� */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		/* �A�C�h�����ԁi���b�Z�[�W���Ȃ��������j�ɕ`�揈�����s�� */
		else{
			RenderProc();
		}
	}
	return (int)(msg.wParam);
}

//----------------------------------------------
//	Name:	MsgProc
//	Func:	���C���E�C���h�E�ɂ��郁�b�Z�[�W�̏���
//	In	:	HWND hWnd		�E�B���h�E�n���h��
//			UINT msg		���b�Z�[�W���ʎq
//			UINT wParam		��P���b�Z�[�W�p�����[�^
//			LONG lParam		��Q���b�Z�[�W�p�����[�^
//	Out:	LRESULT
//----------------------------------------------
LRESULT CD3DMain::MsgProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
{
	switch(msg){
		break;
	case WM_ACTIVATE:
		m_bAppActive = !((BOOL)HIWORD(wParam));
		break;

	case WM_KEYDOWN:				// �����L�[��������Ă���?
		switch(wParam){
		case VK_F5:
			m_bFpsFlg = !m_bFpsFlg;	// FPS�\���t���O���]
			break;
		}
		break;
	case WM_CLOSE:
			m_bEndFlg = true;		// �I������
			CleanAppli();
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);	// ���ɏ������܂킷
	}
	return 0;
}

//----------------------------------------------
//	Name:	FrameProc
//	Func:	�����p�X���b�h
//	In:		�Ȃ�
//	Out:	�Ȃ� 
//----------------------------------------------
void CD3DMain::FrameProc()
{
	static DWORD dwLastTime = 0;		// ��t���[���O�̎���
	static DWORD dwLastSecondTime = 0;	// ��b�O�̎���
	static DWORD dwLoopNum = 0;			// ��b�ɉ���t���[������������̃J�E���g

	while(m_bThread) {

		/* ���t���[���̏��� */
 		FrameMove();

		/* �`�撆�łȂ���Ώ����X�V���ĕ`��t���O��ON�ɂ��� */
		if(m_bRenderFlg == false)
		{
			UpDate();				// �`����X�V
			m_bRenderFlg = true;	// �`��t���OON
		}

		/* FPS�̌v�Z */
		dwLoopNum++;
		DWORD StartTime = timeGetTime();
		if(StartTime - dwLastSecondTime >= 1000.0)
		{
			m_fFrameFps	= (float)(dwLoopNum*1000.0/(StartTime-dwLastSecondTime));
			dwLastSecondTime = StartTime;
			dwLoopNum = 0L;
		}

		/* �]�������ԃX���b�h���x�܂��� */
		DWORD dwTimeTmp = timeGetTime() - dwLastTime;
		if (FLAME_RATE >= dwTimeTmp)
		{
			Sleep(FLAME_RATE - dwTimeTmp);
		}
		dwLastTime = timeGetTime();
	}
}

//----------------------------------------------
// Name:	RenderProc
// Func:	�`��p�X���b�h
// In:		�Ȃ�
// Out:		�Ȃ� 
//----------------------------------------------
void CD3DMain::RenderProc()
{
	static DWORD dwLastTime = 0;		// ��t���[���O�̎���
	static DWORD dwLastSecondTime = 0;	// ��b�O�̎���
	static DWORD dwLoopNum = 0;			// ��b�ɉ���t���[������������̃J�E���g

	/* �`��t���O�������Ă���Ε`�揈�� */
	if(!m_bRenderFlg) return;

	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
	m_pd3dDevice->BeginScene();

	/* ���t���[���̕`�揈�� */
	Render();

	/* �`��t���O��OFF�ɂ��� */
	m_bRenderFlg = false;

	/* DEBUG���̕\�� */
	if (m_bFpsFlg) {
		char szMsg1[128],szMsg2[128];
		RECT rect[2];

		//sprintf(szMsg1, "Comput FPS = %f", m_fFrameFps);
		//sprintf(szMsg2, "Render FPS = %f", m_fRenderFps);

		sprintf_s(szMsg1, sizeof(szMsg1), "Comput FPS = %f", m_fFrameFps);
		sprintf_s(szMsg2, sizeof(szMsg2), "Render FPS = %f", m_fRenderFps);


		SetRect(&rect[0],350,50, 640,480);
		SetRect(&rect[1],350,100,640,480);

		m_pd3dXFont->Begin();
		m_pd3dXFont->DrawTextA(szMsg1, -1, &rect[0], DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		m_pd3dXFont->DrawTextA(szMsg2, -1, &rect[1], DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		m_pd3dXFont->End();
	}

	m_pd3dDevice->EndScene();

	/* �o�b�N�o�b�t�@����ʂɔ��f */
	m_pd3dDevice->Present( NULL, NULL, NULL, NULL );

	/* FPS�̌v�Z */
	dwLoopNum++;
	DWORD StartTime = timeGetTime();
	if(StartTime - dwLastSecondTime >= 1000.0)
	{
		m_fRenderFps = (float)(dwLoopNum*1000.0/(StartTime-dwLastSecondTime));
		dwLastSecondTime = StartTime;
		dwLoopNum = 0L;
	}

	/* �]�������ԃX���b�h���x�܂��� */
	DWORD dwTimeTmp = timeGetTime() - dwLastTime;
	if (RENDER_FLAME_RATE >= dwTimeTmp)
	{
		Sleep(RENDER_FLAME_RATE - dwTimeTmp);
	}
	dwLastTime = timeGetTime();
}

//----------------------------------------------
//	Name:	AllCreate
//	Func:	�E�B���h�E�Ȃǂ̍쐬
//	In	:	HINSTANCE hInst	�C���X�^���X�n���h��
//	Out:	HRESULT			��������
//----------------------------------------------
HRESULT CD3DMain::AllCreate(HINSTANCE hInst)
{
	/* �C���X�^���X�n���h���̃R�s�[ */
	m_hInst = hInst;

	/* �E�B���h�E�N���X�̓o�^ */
	WNDCLASSEX wcex;
	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.hInstance     = hInst;
	wcex.lpszClassName = szWindowClass;
	wcex.lpfnWndProc   = (WNDPROC)WndProc;
	wcex.style         = CS_CLASSDC;
	wcex.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName  = NULL;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	
	RegisterClassEx(&wcex);

	/* �E�B���h�E���[�h�ƃt���X�N���[�����[�h�Ƃ̔��� */
	DWORD	dwWindowStyle;
	if(m_bWindowMode)	dwWindowStyle = STYLE_WINDOW;
	else				dwWindowStyle = STYLE_FULLSCREEN;

	/* �E�B���h�E�̍쐬 */
	RECT  rc = {0,0,m_nWndWidth,m_nWndHeight};
	AdjustWindowRect( &rc, dwWindowStyle, NULL);
	m_hWnd = CreateWindow(szWindowClass,				// �N���X��
						szTitle,						// �L���v�V������
						dwWindowStyle,					// �X�^�C��
						CW_USEDEFAULT, CW_USEDEFAULT,	// �\���ʒu
						(rc.right  - rc.left),			// �\���T�C�Y
						(rc.bottom - rc.top),
						GetDesktopWindow(), NULL, wcex.hInstance, NULL);		// ���̑�

	/* �E�B���h�E�쐬�̎��s���͏I�� */
	if (!m_hWnd)	return E_FAIL;

	/* �^�C�}�[�̐��x���グ�� */
	timeBeginPeriod( 1 );

	/* DirectX�̏����� */
	if (FAILED(InitD3D()))	return E_FAIL;

	/* ��񂾂��Ă΂�鏉���� */
	if (FAILED(OneTimeInit()))	return E_FAIL;

	/* �X���b�h�쐬 */
	m_bThread = true;
	m_hThread = CreateThread(NULL, 0, FrameThread,  NULL, 0, &m_dwThreadID);

	/* �X���b�h�̗D��x���グ�� */
	SetThreadPriority(m_hThread, THREAD_PRIORITY_HIGHEST);

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);			// �E�B���h�E��������悤�ɂ���
	UpdateWindow(m_hWnd);						// �E�B���h�E�̍ĕ`��
	SetFocus(m_hWnd);							// �t�H�[�J�X��������

	return S_OK;
}

//----------------------------------------------
//	Name:	InitD3D
//	Func:	Direct3D�̏�����
//	In	:	�Ȃ�
//	Out:	HRESULT			��������
//----------------------------------------------
HRESULT CD3DMain::InitD3D()
{
	int i;

	// �f�o�C�X���e�[�u��
	struct TCreateDevice {
		D3DDEVTYPE type;
		DWORD      behavior;
	};
	const TCreateDevice device[4] = {
		{ D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING },	// T&L HAL
		{ D3DDEVTYPE_HAL, D3DCREATE_MIXED_VERTEXPROCESSING	  },	// MIX? HAL
		{ D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// HAL
		{ D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// REF
	};

	// 3D�I�u�W�F�N�g���N���G�C�g
	if (NULL == (m_pD3D = Direct3DCreate8(D3D_SDK_VERSION)))
		return E_FAIL;

	// �����t�H�[�}�b�g�̃o�b�N�o�b�t�@��ݒ肷�邱�Ƃ��ł���悤�ɁA
	// ���݂̃f�X�N�g�b�v�f�B�X�v���C�E���[�h�𓾂�
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;
	
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	// D3DDevice���N���G�C�g���邽�߂Ɏg�p�����\���̂�ݒ�
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = m_bWindowMode;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = m_bWindowMode ? d3ddm.Format : D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth  = m_bWindowMode ? (rc.right-rc.left): SCREEN_WIDTH;
	d3dpp.BackBufferHeight = m_bWindowMode ? (rc.bottom-rc.top): SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	
	// �f�o�C�X���쐬����
	for (i=0; i<4; i++){
		if SUCCEEDED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, device[i].type, m_hWnd, 
											device[i].behavior | D3DCREATE_MULTITHREADED, &d3dpp, &m_pd3dDevice))
			break;
	}
	// �ǂ̃��[�h�ł��쐬�ł��Ȃ������ꍇ�͎��s�Ƃ݂Ȃ�
	if (i >= 3) return E_FAIL;

	// �f�o�b�O�p�t�H���g�̍쐬
	HFONT hFont = CreateFont(	0, 0, 0, 0, 			// ����, ��, �c
								FW_BOLD, FALSE,			// ����, �C�^���b�N��
								FALSE, FALSE, 			// �����t��, �ł��������t��
								SHIFTJIS_CHARSET, 		// �����Z�b�g
								OUT_DEFAULT_PRECIS,		// �o�͐��x
								CLIP_DEFAULT_PRECIS,	// �N���b�s���O���x
								DEFAULT_QUALITY,		// �o�͕i��
								DEFAULT_PITCH,			// �s�b�`�ƃt�@�~��
								"�l�r �S�V�b�N");		// �t�H���g��
   
	if (FAILED(D3DXCreateFont(m_pd3dDevice, hFont, &m_pd3dXFont))) {
		DeleteObject(hFont);
		return E_FAIL;
	}
	DeleteObject(hFont);

	return S_OK;
}

//----------------------------------------------
//	Name:	CleanAppli
//	Func:	Direct3D�̏�����
//	In	:	�Ȃ�
//	Out:	HRESULT			��������
//----------------------------------------------
HRESULT CD3DMain::CleanAppli()
{
	// �X���b�h���I��������
	m_bThread = false;

	// ���̎��Ԃ�҂��Ă���X���b�h�폜
	Sleep(300);
	CloseHandle(m_hThread);

	// �^�C�}�[�̐��x��߂�
	timeEndPeriod( 1 );

	// �g�p�����������̊J��
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pd3dXFont);

	CleanUp();

	return S_OK;
}