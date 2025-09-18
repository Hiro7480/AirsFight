//==========================================================
// Menu.cpp
// Auther : 桜井 博之
// Data   : 2002/05/01
//==========================================================

#include "Menu.h"

//------------------------------------------------------
//	Name:	CMenu
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3Dデバイス
//	Out:	なし
//------------------------------------------------------
CMenu::CMenu(LPDIRECT3DDEVICE8 d3dDevice)
	  :GameStatus(d3dDevice)
{	
	long	lTmp;
	int		i;

	/* コンピュータフラグの初期化 */
	for(i=0; i<4; i++)	m_bCPUFlg[i] = false;

	/* ID配列の添え字は0 */
	m_nMyChara = 0;	

	/* プレイヤーの初期化 */
	m_nSelectChara[0] = 0;		// キャラクタの初期化
	m_bOK[0] = false;			// 準備まだ

	/* コンピュータをランダムで決める */
	srand(time(&lTmp));		// ランダムの初期化
	for(i=1; i<4; i++)
	{
		srand(lTmp * rand()%500);
		m_nSelectChara[i] = rand()%4;	// キャラクタを決める
		m_bOK[i] = true;				// 準備ＯＫ
	}

	/* メニュー背景の作成 */
	m_pBackGround = new CScrollBG(m_pd3dDevice, "data\\Menu\\MenuBG.png", 256, 256);
	m_pBackGround->SetVecDir(D3DXVECTOR2(1.0, 1.0));

	/* メニューロゴの作成 */
	m_pLogo = new CSprite(m_pd3dDevice, "Data\\Menu\\MenuLogo.png");
	m_pLogo->SetVec(D3DXVECTOR2(64, 8));
	m_pLogo->SetRec(0,0,512,64);

	/* 画像の作成 */
	for(i=0; i<4; i++)
	{
		/* キャラクタイメージの作成 */
		m_pCharaImage[i] = new CSprite(m_pd3dDevice, "Data\\Menu\\CharaImage.png");

		/* ＲＥＡＤＹスプライトの作成 */
		m_pReady[i]		 = new CSprite(m_pd3dDevice, "Data\\Menu\\Ready.png");
		m_pReady[i]->SetRec(0,0,200,128);

		/* プレイヤーの名前の作成 */
		m_pPlayerName[i] = new CFont(m_pd3dDevice, "HGPｺﾞｼｯｸE", 30);
		m_pPlayerName[i]->SetFormat(DT_CENTER);
		m_pPlayerName[i]->SetColor(255, 0, 0);
	}

	/* プレイヤー名の格納 */
	m_pPlayerName[0]->SetString( "PLAYER" );
	m_pPlayerName[1]->SetString( "COMPUTER1" );
	m_pPlayerName[2]->SetString( "COMPUTER2" );
	m_pPlayerName[3]->SetString( "COMPUTER3" );

	/* キャラクタスプライトの描画位置の初期化 */
	m_pCharaImage[0]->SetVec(D3DXVECTOR2(0, 80));
	m_pCharaImage[1]->SetVec(D3DXVECTOR2(320, 80));
	m_pCharaImage[2]->SetVec(D3DXVECTOR2(0, 280));
	m_pCharaImage[3]->SetVec(D3DXVECTOR2(320, 280));

	/* ＲＥＡＤＹスプライトの描画位置の初期化 */
	m_pReady[0]->SetVec(D3DXVECTOR2( 40, 120));
	m_pReady[1]->SetVec(D3DXVECTOR2(360, 120));
	m_pReady[2]->SetVec(D3DXVECTOR2( 40, 320));
	m_pReady[3]->SetVec(D3DXVECTOR2(360, 320));

	/* プレイヤーの名前の描画位置初期化 */
	m_pPlayerName[0]->SetRec(  0, 240, 200, 280);
	m_pPlayerName[1]->SetRec(320, 240, 520, 280);
	m_pPlayerName[2]->SetRec(  0, 440, 200, 480);
	m_pPlayerName[3]->SetRec(320, 440, 520, 480);

}
//----------------------------------------------
//	Name:	~CMenu
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CMenu::~CMenu()
{
	/* 使用したメモリの開放 */
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
//	Func:	毎フレームの処理
//	Out:	なし
//	In:		int = 状態変更識別子
//----------------------------------------------
int CMenu::FrameMove()
{
	/* 自分がまだ選択中なら選択する処理 */
	if(!m_bOK[m_nMyChara])
	{
		/* 上を押す */
		if(GetAsyncKeyState(VK_UP) & 0x0001)
		{
			m_nSelectChara[m_nMyChara]++;
			if(m_nSelectChara[m_nMyChara] >= MAX_CHARA)
				m_nSelectChara[m_nMyChara] = 0;
		}

		/* 下を押す */
		else if(GetAsyncKeyState(VK_DOWN) & 0x0001)
		{
			m_nSelectChara[m_nMyChara]--;
			if(m_nSelectChara[m_nMyChara] < 0)
				m_nSelectChara[m_nMyChara] = MAX_CHARA-1;
		}

		/* エンターを押すと準備ＯＫ */
		else if(GetAsyncKeyState(VK_RETURN) & 0x0001)
		{
			m_bOK[m_nMyChara] = true;
		}
	}

	/* 自分がもう決定済みなら待つ */
	else
	{
		/* エスケープを押すともっかいやり直し */
		if(GetAsyncKeyState(VK_ESCAPE) & 0x0001)
		{
			m_bOK[m_nMyChara] = false;
		}
	}

	/* 選択しているキャラクタにより、表示位置を決める */
	for(int i=0; i<4; i++)
	{
		switch(m_nSelectChara[i])
		{
		/* RT-ONEを表示する */
		case 0:
			m_pCharaImage[i]->SetRec(0,0,256,150);
			break;
		/* RT-TWOを表示する */
		case 1:
			m_pCharaImage[i]->SetRec(0,150,256,300);
			break;
		/* RT-THREEを表示する */
		case 2:
			m_pCharaImage[i]->SetRec(0,300,256,450);
			break;
		/* RT_FOURを表示する */
		case 3:
			m_pCharaImage[i]->SetRec(256,0,512,150);
			break;

		/* プレイヤーがいないとみなし、「誰もいない」を表示する */
		case -1:
			m_pCharaImage[i]->SetRec(256,300,512,450);
			break;
		}
	}

	/* メニュー背景を動かす */
	m_pBackGround->FrameMove();

	/* 全員ＯＫならゲームへ移行する */
	if(m_bOK[0] && m_bOK[1] && m_bOK[2] && m_bOK[3])
		return CHANGE_GAME;

	return NO_CHANGE;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	Out:	なし
//	In:		なし
//----------------------------------------------
void CMenu::Render()
{
	int i;

	/* メニュー背景 */
	m_pBackGround->Render();

	/* メニューロゴ */
	m_pLogo->Render();

	/* キャラクタイメージ */
	for(i=0; i<4; i++)
		m_pCharaImage[i]->Render();

	/* プレイヤー名 */
	for(i=0; i<4; i++)
		m_pPlayerName[i]->Render();

	/* ＲＥＡＤＹスプライト */
	for(i=0; i<4; i++)
		if(m_nSelectChara[i] != -1 && m_bOK[i])
			m_pReady[i]->Render();

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	Out:	なし
//	In:		なし
//----------------------------------------------
void CMenu::UpDate()
{
	int i;

	/* メニュー背景 */
	m_pBackGround->UpDate();

	/* メニューロゴ */
	m_pLogo->UpDate();

	/* キャラクタイメージ */
	for(i=0; i<4; i++)
		m_pCharaImage[i]->UpDate();

	/* プレイヤー名 */
	for(i=0; i<4; i++)
		m_pPlayerName[i]->UpDate();

	/* ＲＥＡＤＹスプライト */
	for(i=0; i<4; i++)
		m_pReady[i]->UpDate();
}
