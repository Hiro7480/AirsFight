//==========================================================
// Main.cpp
// Auther : 桜井 博之
// Data   : 2002/01/03
//==========================================================
#include "main.h"

//----------------------------------------------
//	Name:	AIRS_FIGHT
//	Func:	コンストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
AIRS_FIGHT::AIRS_FIGHT()
{
	/* 現在の状態管理クラスの初期化 */
	m_pNowClass = NULL;

	/* クリティカルセクション初期化 */
	InitializeCriticalSection(&m_cs);

	/* 描画中フラグ初期化 */
	m_bRenderFlg = false;
}

//----------------------------------------------
//	Name:	OneTimeInit
//	Func:	一度だけの初期化
//	in:		なし
//	Out:	なし
//----------------------------------------------
HRESULT AIRS_FIGHT::OneTimeInit()
{
	/* レンダーステートを設定 */
	m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,	  TRUE );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR );
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	
	/* ライトの情報を設定 */
	D3DLIGHT8 light;
	ZeroMemory(&light, sizeof(D3DLIGHT8));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 0.5f; light.Ambient.r = 0.5f;
	light.Diffuse.g = 0.5f; light.Ambient.g = 0.5f;
	light.Diffuse.b = 0.5f; light.Ambient.b = 0.5f;
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &D3DXVECTOR3(-2.0f, 4.0f, -2.0f) );
	light.Range = 100.0f;
	m_pd3dDevice->LightEnable(0, TRUE);
	m_pd3dDevice->SetLight(0, &light);			// ライトを設定

	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xff202020 );
	
	/* 投影マトリックスを設定する */
	D3DXMATRIX matProj;
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 640.0f/480.0f, 1.0f, 1000.0f );
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	/* まずはタイトルクラスを作成 */
	m_pNowClass = new CTitle(m_pd3dDevice);

	return S_OK;
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
HRESULT AIRS_FIGHT::FrameMove()
{
	int			nNextStatus;		// 次のクラスを示す
	GameStatus*	pNewClass = NULL;	// 新規クラス

	/* キャスト用ポインタ */
	CMenu*		pMenu;
	CGame*		pGame;
	CEnding*	pEnding;

	nNextStatus = m_pNowClass->FrameMove();

	/* 戻り値の値によりクラスを変える */
	switch(nNextStatus)
	{
		/* 変更しない */
		case NO_CHANGE:	break;

		/* タイトルに変更 */
		case CHANGE_TITLE:
			/* 描画終了するのを待ってから現在のクラスを削除 */
			while(m_bRenderFlg);
			SAFE_DELETE(m_pNowClass);

			/* タイトルクラスを作成する */
			m_pNowClass = new CTitle(m_pd3dDevice);
			break;

		/* メニューに変更 */
		case CHANGE_MENU:
			/* 描画終了するのを待ってから現在のクラスを削除 */
			while(m_bRenderFlg);
			SAFE_DELETE(m_pNowClass);

			/* メニュークラスを作成する */
			m_pNowClass = new CMenu(m_pd3dDevice);
			break;

		/* ゲームに変更 */
		case CHANGE_GAME:
			/* 現在のクラスをメニュークラスにキャスト */
			pMenu = (CMenu*)m_pNowClass;

			/* ゲームクラスを作成する */
			pNewClass = new CGame(m_pd3dDevice);
			pGame = (CGame*)pNewClass;
			pGame->CreateChara(pMenu->GetSelectChara());

			/* 描画終了するまで待ってから現在のクラスを削除 */
			while(m_bRenderFlg);
			SAFE_DELETE(m_pNowClass);

			/* ゲームクラスを現在のクラスとして登録*/
			m_pNowClass = pNewClass;
			break;

		/* エンディングに変更 */
		case CHANGE_ENDING:
			/* 現在のクラスをゲームクラスにキャスト */
			pGame = (CGame*)m_pNowClass;

			/* エンディングクラスを作成する */
			pNewClass = new CEnding(m_pd3dDevice);
			pEnding = (CEnding*)pNewClass;
			pEnding->InitOrder(pGame->GetDeadNum(0), pGame->GetDeadNum(1), pGame->GetDeadNum(2), pGame->GetDeadNum(3));

			/* 描画終了するまで待ってから現在のクラスを削除 */
			while(m_bRenderFlg);
			SAFE_DELETE(m_pNowClass);

			/* エンディングクラスを現在のクラスとして登録 */
			m_pNowClass = pNewClass;
			break;
	}

	return S_OK;
}

//----------------------------------------------
//	Name:	Render
//	Func:	画面描画
//	in:		なし
//	Out:	なし
//----------------------------------------------
HRESULT AIRS_FIGHT::Render()
{
	/* 状態管理クラスがなければ終了 */
	if(!m_pNowClass)	return E_FAIL;

	/* 黒にバックバッファをクリア */
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	/* 描画中フラグをたてる */
	m_bRenderFlg = true;

	/* 画面に描画 */
	m_pNowClass->Render();

	/* 描画中フラグを戻す */
	m_bRenderFlg = false;

	return S_OK;
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	描画用マトリクス更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
HRESULT AIRS_FIGHT::UpDate()
{
	/* 状態管理クラスがなければ終了 */
	if(!m_pNowClass)	return E_FAIL;

	/* マトリクスの更新 */
	m_pNowClass->UpDate();
	return S_OK;
}

//----------------------------------------------
//	Name:	CleanUp
//	Func:	後処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
HRESULT AIRS_FIGHT::CleanUp()
{
	/* 使用したメモリの開放 */
	SAFE_DELETE(m_pNowClass);

	/* クリティカルセクションを終了させる */
	DeleteCriticalSection(&m_cs);

	return S_OK;
}

//----------------------------------------------------------------------
//	Name:	WinMain
//	Func:	Win32 アプリケーションの初期エントリポイント
//	In:		HINSTANCE	hInstance		インスタンスハンドル
//			HINSTANCE	hPrevInstance	未使用
//			LPSTR		lpCmdLine  		コマンドライン文字列ポインタ
//			int			nCmdShow		ウィンドウの状態
//  Out:	int			アプリケーションの終了コード
//----------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	/* ベースクラスの作成 */
	CD3DMain* pCMain = new AIRS_FIGHT;

	/* 通信プログラムの初期化 */
	//if(FAILED( pCMain->InitDPlay(hInstance)))
	//{
	//	SAFE_DELETE(pCMain);
	//	return FALSE;
	//}

	/* ゲームとしてのアプリケーションの全ての初期化 */
	if(FAILED( pCMain->AllCreate(hInstance) ))
	{
		SAFE_DELETE(pCMain);
		return FALSE;
	}

	/* ゲーム開始 */
	return pCMain->Run();

}
