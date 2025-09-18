//==========================================================
// D3DMain.cpp
// Auther : 桜井 博之
// Data   : 2002/01/03
//==========================================================

#include "D3DMain.h"

// グローバル変数
static CD3DMain* g_pCAppli = NULL;


//----------------------------------------------
//	Name:	WndProc
//	Func:	ウィンドウプロシージャ
//	In	:	HWND hWnd		ウィンドウハンドル
//			UINT msg		メッセージ識別子
//			UINT wParam		第１メッセージパラメータ
//			LONG lParam		第２メッセージパラメータ
//	Out:	LRESULT
//----------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
{
	return g_pCAppli->MsgProc(hWnd, msg, wParam, lParam);
}

//----------------------------------------------
//	Name:	FrameThread
//	Func:	処理用スレッド
//	In:		VOID*	親と共有するデータのアドレス
//	Out:	DWORD
//----------------------------------------------
DWORD WINAPI FrameThread(VOID *pVOID)
{
	g_pCAppli->FrameProc();
	return TRUE;
}

//----------------------------------------------
//	Name:	D3DMain
//	Func:	コンストラクタ
//	In	:	なし
//	Out:	なし
//----------------------------------------------
CD3DMain::CD3DMain()
{
	g_pCAppli = this;

	/* タイトル名の初期化 */
	//strcpy(szTitle, "AIRS FIGHT");
	_tcscpy_s(szTitle, _T("AIRS FIGHT"));

	/* Windowクラス名の初期化 */
	//strcpy(szWindowClass, "AIRS FIGHT");
	_tcscpy_s(szWindowClass, _T("AIRS FIGHT"));



	/* ウィンドウモードの初期化(TRUE ウィンドウモード FALSE フルスクリーンモード) */
	m_bWindowMode = true;

	/* ウィンドウサイズの初期化 */
	m_nWndHeight = SCREEN_HEIGHT;
	m_nWndWidth  = SCREEN_WIDTH;

	/* 各フラグの初期化 */
	m_bAppActive = false;
	m_bEndFlg = false;
	m_bFpsFlg = false;
	m_bThread = false;
	m_bRenderFlg = false;
}

//----------------------------------------------
//	Name:	Run
//	Func:	メインループ
//	In	:	なし
//	Out:	int
//----------------------------------------------
int CD3DMain::Run()
{

	MSG msg;
	while(!m_bEndFlg)
	{
		/* メッセージ処理 */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		/* アイドル時間（メッセージがなかった時）に描画処理を行う */
		else{
			RenderProc();
		}
	}
	return (int)(msg.wParam);
}

//----------------------------------------------
//	Name:	MsgProc
//	Func:	メインウインドウにくるメッセージの処理
//	In	:	HWND hWnd		ウィンドウハンドル
//			UINT msg		メッセージ識別子
//			UINT wParam		第１メッセージパラメータ
//			LONG lParam		第２メッセージパラメータ
//	Out:	LRESULT
//----------------------------------------------
LRESULT CD3DMain::MsgProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
{
	switch(msg){
		break;
	case WM_ACTIVATE:
		m_bAppActive = !((BOOL)HIWORD(wParam));
		break;

	case WM_KEYDOWN:				// 何かキーを押されている?
		switch(wParam){
		case VK_F5:
			m_bFpsFlg = !m_bFpsFlg;	// FPS表示フラグ反転
			break;
		}
		break;
	case WM_CLOSE:
			m_bEndFlg = true;		// 終了処理
			CleanAppli();
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);	// 他に処理をまわす
	}
	return 0;
}

//----------------------------------------------
//	Name:	FrameProc
//	Func:	処理用スレッド
//	In:		なし
//	Out:	なし 
//----------------------------------------------
void CD3DMain::FrameProc()
{
	static DWORD dwLastTime = 0;		// 一フレーム前の時間
	static DWORD dwLastSecondTime = 0;	// 一秒前の時間
	static DWORD dwLoopNum = 0;			// 一秒に何回フレームが回ったかのカウント

	while(m_bThread) {

		/* 毎フレームの処理 */
 		FrameMove();

		/* 描画中でなければ情報を更新して描画フラグをONにする */
		if(m_bRenderFlg == false)
		{
			UpDate();				// 描画情報更新
			m_bRenderFlg = true;	// 描画フラグON
		}

		/* FPSの計算 */
		dwLoopNum++;
		DWORD StartTime = timeGetTime();
		if(StartTime - dwLastSecondTime >= 1000.0)
		{
			m_fFrameFps	= (float)(dwLoopNum*1000.0/(StartTime-dwLastSecondTime));
			dwLastSecondTime = StartTime;
			dwLoopNum = 0L;
		}

		/* 余った時間スレッドを休ませる */
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
// Func:	描画用スレッド
// In:		なし
// Out:		なし 
//----------------------------------------------
void CD3DMain::RenderProc()
{
	static DWORD dwLastTime = 0;		// 一フレーム前の時間
	static DWORD dwLastSecondTime = 0;	// 一秒前の時間
	static DWORD dwLoopNum = 0;			// 一秒に何回フレームが回ったかのカウント

	/* 描画フラグがたっていれば描画処理 */
	if(!m_bRenderFlg) return;

	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
	m_pd3dDevice->BeginScene();

	/* 毎フレームの描画処理 */
	Render();

	/* 描画フラグをOFFにする */
	m_bRenderFlg = false;

	/* DEBUG情報の表示 */
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

	/* バックバッファを画面に反映 */
	m_pd3dDevice->Present( NULL, NULL, NULL, NULL );

	/* FPSの計算 */
	dwLoopNum++;
	DWORD StartTime = timeGetTime();
	if(StartTime - dwLastSecondTime >= 1000.0)
	{
		m_fRenderFps = (float)(dwLoopNum*1000.0/(StartTime-dwLastSecondTime));
		dwLastSecondTime = StartTime;
		dwLoopNum = 0L;
	}

	/* 余った時間スレッドを休ませる */
	DWORD dwTimeTmp = timeGetTime() - dwLastTime;
	if (RENDER_FLAME_RATE >= dwTimeTmp)
	{
		Sleep(RENDER_FLAME_RATE - dwTimeTmp);
	}
	dwLastTime = timeGetTime();
}

//----------------------------------------------
//	Name:	AllCreate
//	Func:	ウィンドウなどの作成
//	In	:	HINSTANCE hInst	インスタンスハンドル
//	Out:	HRESULT			処理結果
//----------------------------------------------
HRESULT CD3DMain::AllCreate(HINSTANCE hInst)
{
	/* インスタンスハンドルのコピー */
	m_hInst = hInst;

	/* ウィンドウクラスの登録 */
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

	/* ウィンドウモードとフルスクリーンモードとの判定 */
	DWORD	dwWindowStyle;
	if(m_bWindowMode)	dwWindowStyle = STYLE_WINDOW;
	else				dwWindowStyle = STYLE_FULLSCREEN;

	/* ウィンドウの作成 */
	RECT  rc = {0,0,m_nWndWidth,m_nWndHeight};
	AdjustWindowRect( &rc, dwWindowStyle, NULL);
	m_hWnd = CreateWindow(szWindowClass,				// クラス名
						szTitle,						// キャプション名
						dwWindowStyle,					// スタイル
						CW_USEDEFAULT, CW_USEDEFAULT,	// 表示位置
						(rc.right  - rc.left),			// 表示サイズ
						(rc.bottom - rc.top),
						GetDesktopWindow(), NULL, wcex.hInstance, NULL);		// その他

	/* ウィンドウ作成の失敗時は終了 */
	if (!m_hWnd)	return E_FAIL;

	/* タイマーの精度を上げる */
	timeBeginPeriod( 1 );

	/* DirectXの初期化 */
	if (FAILED(InitD3D()))	return E_FAIL;

	/* 一回だけ呼ばれる初期化 */
	if (FAILED(OneTimeInit()))	return E_FAIL;

	/* スレッド作成 */
	m_bThread = true;
	m_hThread = CreateThread(NULL, 0, FrameThread,  NULL, 0, &m_dwThreadID);

	/* スレッドの優先度を上げる */
	SetThreadPriority(m_hThread, THREAD_PRIORITY_HIGHEST);

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);			// ウィンドウを見えるようにする
	UpdateWindow(m_hWnd);						// ウィンドウの再描画
	SetFocus(m_hWnd);							// フォーカスを自分に

	return S_OK;
}

//----------------------------------------------
//	Name:	InitD3D
//	Func:	Direct3Dの初期化
//	In	:	なし
//	Out:	HRESULT			処理結果
//----------------------------------------------
HRESULT CD3DMain::InitD3D()
{
	int i;

	// デバイス情報テーブル
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

	// 3Dオブジェクトをクリエイト
	if (NULL == (m_pD3D = Direct3DCreate8(D3D_SDK_VERSION)))
		return E_FAIL;

	// 同じフォーマットのバックバッファを設定することができるように、
	// 現在のデスクトップディスプレイ・モードを得る
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;
	
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	// D3DDeviceをクリエイトするために使用される構造体を設定
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = m_bWindowMode;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = m_bWindowMode ? d3ddm.Format : D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth  = m_bWindowMode ? (rc.right-rc.left): SCREEN_WIDTH;
	d3dpp.BackBufferHeight = m_bWindowMode ? (rc.bottom-rc.top): SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	
	// デバイスを作成する
	for (i=0; i<4; i++){
		if SUCCEEDED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, device[i].type, m_hWnd, 
											device[i].behavior | D3DCREATE_MULTITHREADED, &d3dpp, &m_pd3dDevice))
			break;
	}
	// どのモードでも作成できなかった場合は失敗とみなす
	if (i >= 3) return E_FAIL;

	// デバッグ用フォントの作成
	HFONT hFont = CreateFont(	0, 0, 0, 0, 			// 高さ, 幅, …
								FW_BOLD, FALSE,			// 太さ, イタリック体
								FALSE, FALSE, 			// 下線付き, 打ち消し線付き
								SHIFTJIS_CHARSET, 		// 文字セット
								OUT_DEFAULT_PRECIS,		// 出力精度
								CLIP_DEFAULT_PRECIS,	// クリッピング精度
								DEFAULT_QUALITY,		// 出力品質
								DEFAULT_PITCH,			// ピッチとファミリ
								"ＭＳ ゴシック");		// フォント名
   
	if (FAILED(D3DXCreateFont(m_pd3dDevice, hFont, &m_pd3dXFont))) {
		DeleteObject(hFont);
		return E_FAIL;
	}
	DeleteObject(hFont);

	return S_OK;
}

//----------------------------------------------
//	Name:	CleanAppli
//	Func:	Direct3Dの初期化
//	In	:	なし
//	Out:	HRESULT			処理結果
//----------------------------------------------
HRESULT CD3DMain::CleanAppli()
{
	// スレッドを終了させる
	m_bThread = false;

	// 一定の時間を待ってからスレッド削除
	Sleep(300);
	CloseHandle(m_hThread);

	// タイマーの精度を戻す
	timeEndPeriod( 1 );

	// 使用したメモリの開放
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pd3dXFont);

	CleanUp();

	return S_OK;
}