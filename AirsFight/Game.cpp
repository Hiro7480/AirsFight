//==========================================================
// Game.cpp
// Auther : 桜井 博之
// Data   : 2002/01/10
//==========================================================

#include "Game.h"

//------------------------------------------------------
//	Name:	CGame
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3Dデバイス
//	Out:	なし
//------------------------------------------------------
CGame::CGame(LPDIRECT3DDEVICE8 d3dDevice)
	 :GameStatus(d3dDevice)
{
	/* ＲＴ－ＯＮＥパラメータの設定 */
	m_CharaParam[0].pMeshData = new CMeshData(m_pd3dDevice);// メッシュ読み込み
	m_CharaParam[0].pMeshData->Create(const_cast<TCHAR*>("data\\Chara\\RT-One\\RT-One.X"));

	m_CharaParam[0].nMaxLife     = 2800;		// 最大ＨＰ
	m_CharaParam[0].nMaxEnergy   = 1000;		// 最大エネルギー

	m_CharaParam[0].fWalkSpeed   = 0.6f;		// 歩行速度
	m_CharaParam[0].fBackSpeed   = 0.3f;		// 後退速度
	m_CharaParam[0].fDashSpeed   = 1.5f;		// ダッシュ速度

	m_CharaParam[0].fTurn        = 2.0f;		// 旋回速度

	m_CharaParam[0].fJumpUp		 = 1.0f;		// ジャンプ開始時のＹ軸移動量
	m_CharaParam[0].fJumpDown	 = 0.02f;		// ジャンプ中の降下速度
	m_CharaParam[0].fJumpForward = 0.8f;		// ジャンプ中の前進速度
	m_CharaParam[0].fJumpBack    = 0.5f;		// ジャンプ中の後退速度

	m_CharaParam[0].fFlyForward	 = 1.5f;		// 飛行中の前進速度
	m_CharaParam[0].fFlyBack	 = 1.0f;		// 飛行中の後退速度
	m_CharaParam[0].fFlyPlumb    = 0.05f;		// 飛行中の上昇速度

	m_CharaParam[0].fLockLength  = 220.0f;		// ロックオンのできる長さ

	m_CharaParam[0].fBrakes		 = 0.04f;		// ダメージ中のブレーキ

	/* ＲＴ－ＴＷＯパラメータの設定 */
	m_CharaParam[1].pMeshData = new CMeshData(m_pd3dDevice);// メッシュ読み込み
	m_CharaParam[1].pMeshData->Create(const_cast<TCHAR*>("data\\Chara\\RT-Two\\RT-Two.X"));

	m_CharaParam[1].nMaxLife     = 3500;		// 最大ＨＰ
	m_CharaParam[1].nMaxEnergy   = 1500;		// 最大エネルギー

	m_CharaParam[1].fWalkSpeed   = 0.4f;		// 歩行速度
	m_CharaParam[1].fBackSpeed   = 0.2f;		// 後退速度
	m_CharaParam[1].fDashSpeed   = 2.0f;		// ダッシュ速度

	m_CharaParam[1].fTurn        = 1.5f;		// 旋回速度

	m_CharaParam[1].fJumpUp		 = 0.8f;		// ジャンプ開始時のＹ軸移動量
	m_CharaParam[1].fJumpDown	 = 0.03f;		// ジャンプ中の降下速度
	m_CharaParam[1].fJumpForward = 0.5f;		// ジャンプ中の前進速度
	m_CharaParam[1].fJumpBack    = 0.3f;		// ジャンプ中の後退速度

	m_CharaParam[1].fFlyForward	 = 2.0f;		// 飛行中の前進速度
	m_CharaParam[1].fFlyBack	 = 1.5f;		// 飛行中の後退速度
	m_CharaParam[1].fFlyPlumb    = 0.08f;		// 飛行中の上昇速度

	m_CharaParam[1].fLockLength  = 300.0f;		// ロックオンのできる長さ

	m_CharaParam[1].fBrakes		 = 0.05f;		// ダメージ中のブレーキ

	/* ＲＴ－ＴＨＲＥＥパラメータの設定 */
	m_CharaParam[2].pMeshData = new CMeshData(m_pd3dDevice);// メッシュ読み込み
	m_CharaParam[2].pMeshData->Create(const_cast<TCHAR*>("data\\Chara\\RT-Three\\RT-Three.X"));

	m_CharaParam[2].nMaxLife     = 2500;		// 最大ＨＰ
	m_CharaParam[2].nMaxEnergy   = 800;			// 最大エネルギー

	m_CharaParam[2].fWalkSpeed   = 1.0f;		// 歩行速度
	m_CharaParam[2].fBackSpeed   = 0.8f;		// 後退速度
	m_CharaParam[2].fDashSpeed   = 1.5f;		// ダッシュ速度

	m_CharaParam[2].fTurn        = 2.5f;		// 旋回速度

	m_CharaParam[2].fJumpUp		 = 1.2f;		// ジャンプ開始時のＹ軸移動量
	m_CharaParam[2].fJumpDown	 = 0.02f;		// ジャンプ中の降下速度
	m_CharaParam[2].fJumpForward = 1.0f;		// ジャンプ中の前進速度
	m_CharaParam[2].fJumpBack    = 0.8f;		// ジャンプ中の後退速度

	m_CharaParam[2].fFlyForward	 = 1.5f;		// 飛行中の前進速度
	m_CharaParam[2].fFlyBack	 = 1.2f;		// 飛行中の後退速度
	m_CharaParam[2].fFlyPlumb    = 0.04f;		// 飛行中の上昇速度

	m_CharaParam[2].fLockLength  = 200.0f;		// ロックオンのできる長さ

	m_CharaParam[2].fBrakes		 = 0.03f;		// ダメージ中のブレーキ

	/* ＲＴ－ＦＯＵＲパラメータの設定 */
	m_CharaParam[3].pMeshData = new CMeshData(m_pd3dDevice);// メッシュ読み込み
	m_CharaParam[3].pMeshData->Create(const_cast<TCHAR*>("data\\Chara\\RT-Four\\RT-Four.X"));

	m_CharaParam[3].nMaxLife     = 4000;		// 最大ＨＰ
	m_CharaParam[3].nMaxEnergy   = 2000;		// 最大エネルギー

	m_CharaParam[3].fWalkSpeed   = 1.0f;		// 歩行速度
	m_CharaParam[3].fBackSpeed   = 0.8f;		// 後退速度
	m_CharaParam[3].fDashSpeed   = 2.0f;		// ダッシュ速度

	m_CharaParam[3].fTurn        = 2.5f;		// 旋回速度

	m_CharaParam[3].fJumpUp		 = 1.2f;		// ジャンプ開始時のＹ軸移動量
	m_CharaParam[3].fJumpDown	 = 0.02f;		// ジャンプ中の降下速度
	m_CharaParam[3].fJumpForward = 1.0f;		// ジャンプ中の前進速度
	m_CharaParam[3].fJumpBack    = 0.8f;		// ジャンプ中の後退速度

	m_CharaParam[3].fFlyForward	 = 2.0f;		// 飛行中の前進速度
	m_CharaParam[3].fFlyBack	 = 1.5f;		// 飛行中の後退速度
	m_CharaParam[3].fFlyPlumb    = 0.08f;		// 飛行中の上昇速度

	m_CharaParam[3].fLockLength  = 300.0f;		// ロックオンのできる長さ

	m_CharaParam[3].fBrakes		 = 0.05f;		// ダメージ中のブレーキ


	/* モーションデータの読み込み */
	m_pMotionData[ANI_STOP] = new CMotionData(m_pd3dDevice);			// 立ち
	m_pMotionData[ANI_STOP]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\Stop.X"));

	m_pMotionData[ANI_FORWARD] = new CMotionData(m_pd3dDevice);			// 前進
	m_pMotionData[ANI_FORWARD]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\Forward.X"));

	m_pMotionData[ANI_BACK] = new CMotionData(m_pd3dDevice);			// 後退
	m_pMotionData[ANI_BACK]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\Back.X"));

	m_pMotionData[ANI_DASH_F] = new CMotionData(m_pd3dDevice);			// 前へダッシュ
	m_pMotionData[ANI_DASH_F]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DashForward.X"));

	m_pMotionData[ANI_DASH_B] = new CMotionData(m_pd3dDevice);			// 後ろへダッシュ
	m_pMotionData[ANI_DASH_B]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DashBack.X"));

	m_pMotionData[ANI_DASH_R] = new CMotionData(m_pd3dDevice);			// 右へダッシュ
	m_pMotionData[ANI_DASH_R]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DashRight.X"));

	m_pMotionData[ANI_DASH_L] = new CMotionData(m_pd3dDevice);			// 左へダッシュ
	m_pMotionData[ANI_DASH_L]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DashLeft.X"));

	m_pMotionData[ANI_ATAS] = new CMotionData(m_pd3dDevice);			// 攻撃構え
	m_pMotionData[ANI_ATAS]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\GunSta.X"));

	m_pMotionData[ANI_ATA] = new CMotionData(m_pd3dDevice);				// 攻撃
	m_pMotionData[ANI_ATA]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\GunMot.X"));

	m_pMotionData[ANI_JUMP_N] = new CMotionData(m_pd3dDevice);			// 垂直ジャンプ
	m_pMotionData[ANI_JUMP_N]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpNormal.X"));

	m_pMotionData[ANI_JUMP_F] = new CMotionData(m_pd3dDevice);			// 前方ジャンプ
	m_pMotionData[ANI_JUMP_F]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpForward.X"));

	m_pMotionData[ANI_JUMP_B] = new CMotionData(m_pd3dDevice);			// 後方ジャンプ
	m_pMotionData[ANI_JUMP_B]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpBack.X"));

	m_pMotionData[ANI_JUMP_S] = new CMotionData(m_pd3dDevice);			// ジャンプ開始
	m_pMotionData[ANI_JUMP_S]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpStart.X"));

	m_pMotionData[ANI_JUMP_E] = new CMotionData(m_pd3dDevice);			// ジャンプ終了
	m_pMotionData[ANI_JUMP_E]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\JumpStart.X"));

	m_pMotionData[ANI_DAM_L] = new CMotionData(m_pd3dDevice);			// 地面ダメージ
	m_pMotionData[ANI_DAM_L]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DamageLand.X"));

	m_pMotionData[ANI_DAM_A] = new CMotionData(m_pd3dDevice);			// 空中ダメージ
	m_pMotionData[ANI_DAM_A]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DamageAir.X"));

	m_pMotionData[ANI_DEAD_L] = new CMotionData(m_pd3dDevice);			// 地面死亡
	m_pMotionData[ANI_DEAD_L]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DeadLand.X"));

	m_pMotionData[ANI_DEAD_A] = new CMotionData(m_pd3dDevice);			// 空中死亡
	m_pMotionData[ANI_DEAD_A]->Create(const_cast<TCHAR*>("data\\Chara\\Motion\\DeadAir.X"));


	/* 変数の初期化 */
	for(int i=0; i<4; i++)
	{
		m_pChara[i] = NULL;
		m_bReady[i] = false;
	}
	m_nMyChara = 0;

	/* ステージクラスの作成 */
	m_pStage = new CStage(m_pd3dDevice);

	/* カメラクラスの作成 */
	m_pCamera = new CCamera(m_pd3dDevice);

	/* 弾管理クラスの作成 */
	m_pBulManage = new CBulManage(m_pd3dDevice);

	/* スプライト管理クラスの作成 */
	m_pSpriteManage = new CSpriteManage(m_pd3dDevice);

	/* エフェクト管理クラスの作成 */
	m_pEffectManage = new CEffectManage(m_pd3dDevice);

	/* エネルギーゲージの作成 */
	m_pEnergyGauge = new CEnergyGauge(m_pd3dDevice, const_cast<TCHAR*>("data\\game\\EnergyGauge.png"));

	/* ライフグラフィックの作成 */
	m_pLifeGraphic = new CLifeGraphic(m_pd3dDevice, const_cast<TCHAR*>("data\\game\\LifeGraphic.png"));

	/* 時間管理クラスの作成 */
	m_pTimeGraphic = new CTimeGraphic(m_pd3dDevice);
	m_pTimeGraphic->SetMaxTime(180);

	/* はじめは待ち状態から */
	m_dwNowStatus  = GAME_START;

}

//----------------------------------------------
//	Name:	~CGame
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CGame::~CGame()
{
	int i;

	/* 使用したメモリの開放 */
	for(i=0; i<4; i++)			// メッシュデータの解放
		SAFE_DELETE(m_CharaParam[i].pMeshData);	

	for(i=0; i<MAX_MOTION; i++)	// モーションデータの解放
		SAFE_DELETE(m_pMotionData[i]);

	for(i=0; i<4; i++)				// キャラクタクラスの解放
		SAFE_DELETE(m_pChara[i]);	

	SAFE_DELETE(m_pStage);			// ステージクラスの解放
	SAFE_DELETE(m_pCamera);			// カメラクラスの解放
	SAFE_DELETE(m_pBulManage);		// 弾管理クラスの解放
	SAFE_DELETE(m_pSpriteManage);	// スプライト管理クラスの解放
	SAFE_DELETE(m_pEffectManage);	// エフェクト管理クラスの解放

	SAFE_DELETE(m_pEnergyGauge);	// エネルギーゲージスプライトの解放
	SAFE_DELETE(m_pLifeGraphic);	// ライフスプライトの解放
	SAFE_DELETE(m_pTimeGraphic);	// 残り時間スプライトの開放
}

//--------------------------------------------------
//	Name:	CreateChara
//	Func:	キャラクタの作成
//	In:		int SelectChara[] = 選択キャラクタ配列
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CGame::CreateChara(int SelectChara[])
{
	/* コンピュータの人数 */
	int nCPUNum = 0;

	m_pChara[0] = new CMyPlayer(m_pd3dDevice);
	m_pChara[1] = new CEnemyCPU(m_pd3dDevice);
	m_pChara[2] = new CEnemyCPU(m_pd3dDevice);
	m_pChara[3] = new CEnemyCPU(m_pd3dDevice);

	/* 名前をセットする*/
	m_pChara[0]->SetName(const_cast<TCHAR*>("PLAYER"));
	m_pChara[1]->SetName(const_cast<TCHAR*>("COMPUTER1"));
	m_pChara[2]->SetName(const_cast<TCHAR*>("COMPUTER2"));
	m_pChara[3]->SetName(const_cast<TCHAR*>("COMPUTER3"));

	/* 番号をセットする */
	m_pChara[0]->SetNum(0);
	m_pChara[1]->SetNum(1);
	m_pChara[2]->SetNum(2);
	m_pChara[3]->SetNum(3);

	/* キャラクタの初期座標値などの設定 */
	/* キャラクター１の設定 */
	if(m_pChara[0])
	{
		m_pChara[0]->SetType(&m_CharaParam[SelectChara[0]]);
		m_pChara[0]->CreateActive(m_pMotionData);
		m_pChara[0]->AllInit(D3DXVECTOR3( 0.0f, -95.0f, -100.0f), 0);

		/* 自分の操作するキャラクタなら、別キャラへのマトリクスポインタのセット */
		if(m_nMyChara == 0)
		{
			if(m_pChara[1])	m_pChara[0]->SetEnemyData(0, m_pChara[1]->GetMatPointer(), m_pChara[1]->GetLifePointer(), m_pChara[1]->GetName());
			if(m_pChara[2])	m_pChara[0]->SetEnemyData(1, m_pChara[2]->GetMatPointer(), m_pChara[2]->GetLifePointer(), m_pChara[2]->GetName());
			if(m_pChara[3])	m_pChara[0]->SetEnemyData(2, m_pChara[3]->GetMatPointer(), m_pChara[3]->GetLifePointer(), m_pChara[3]->GetName());

			/* キャラクター名フォントの作成 */
			m_pChara[0]->CreateCharaName();

			/* キャラクターライフフォントの作成 */
			m_pChara[0]->CreateCharaLife();

		}
	}

	/* キャラクター２の設定 */
	if(m_pChara[1])
	{
		m_pChara[1]->SetType(&m_CharaParam[SelectChara[1]]);
		m_pChara[1]->CreateActive(m_pMotionData);
		m_pChara[1]->AllInit(D3DXVECTOR3( 100.0f, -95.0f, 0.0f), 270);

		/* 自分の操作するキャラクタなら、別キャラへのマトリクスポインタのセット */
		if(m_nMyChara == 1)
		{
			if(m_pChara[0])	m_pChara[1]->SetEnemyData(0, m_pChara[0]->GetMatPointer(), m_pChara[0]->GetLifePointer(), m_pChara[0]->GetName());
			if(m_pChara[2])	m_pChara[1]->SetEnemyData(1, m_pChara[2]->GetMatPointer(), m_pChara[2]->GetLifePointer(), m_pChara[2]->GetName());
			if(m_pChara[3])	m_pChara[1]->SetEnemyData(2, m_pChara[3]->GetMatPointer(), m_pChara[3]->GetLifePointer(), m_pChara[3]->GetName());

			/* キャラクター名フォントの作成 */
			m_pChara[1]->CreateCharaName();

			/* キャラクターライフフォントの作成 */
			m_pChara[1]->CreateCharaLife();
		}
	}

	/* キャラクター３の設定 */
	if(m_pChara[2])
	{
		m_pChara[2]->SetType(&m_CharaParam[SelectChara[2]]);
		m_pChara[2]->CreateActive(m_pMotionData);
		m_pChara[2]->AllInit(D3DXVECTOR3( 0.0f, -95.0f, 100.0f), 180);

		/* 自分の操作するキャラクタなら、別キャラへのマトリクスポインタのセット */
		if(m_nMyChara == 2)
		{
			if(m_pChara[0])	m_pChara[2]->SetEnemyData(0, m_pChara[0]->GetMatPointer(), m_pChara[0]->GetLifePointer(), m_pChara[0]->GetName());
			if(m_pChara[1])	m_pChara[2]->SetEnemyData(1, m_pChara[1]->GetMatPointer(), m_pChara[1]->GetLifePointer(), m_pChara[1]->GetName());
			if(m_pChara[3])	m_pChara[2]->SetEnemyData(2, m_pChara[3]->GetMatPointer(), m_pChara[3]->GetLifePointer(), m_pChara[3]->GetName());

			/* キャラクター名フォントの作成 */
			m_pChara[2]->CreateCharaName();

			/* キャラクターライフフォントの作成 */
			m_pChara[2]->CreateCharaLife();
		}
	}

	/* キャラクター４の設定 */
	if(m_pChara[3])
	{
		m_pChara[3]->SetType(&m_CharaParam[SelectChara[3]]);
		m_pChara[3]->CreateActive(m_pMotionData);
		m_pChara[3]->AllInit(D3DXVECTOR3( -100.0f, -95.0f, 0.0f), 90);

		/* 自分の操作するキャラクタなら、別キャラへのマトリクスポインタのセット */
		if(m_nMyChara == 3)
		{
			if(m_pChara[0])	m_pChara[3]->SetEnemyData(0, m_pChara[0]->GetMatPointer(), m_pChara[0]->GetLifePointer(), m_pChara[0]->GetName());
			if(m_pChara[1])	m_pChara[3]->SetEnemyData(1, m_pChara[1]->GetMatPointer(), m_pChara[1]->GetLifePointer(),m_pChara[1]->GetName());
			if(m_pChara[2])	m_pChara[3]->SetEnemyData(2, m_pChara[2]->GetMatPointer(), m_pChara[2]->GetLifePointer(),m_pChara[2]->GetName());

			/* キャラクター名フォントの作成 */
			m_pChara[3]->CreateCharaName();

			/* キャラクターライフフォントの作成 */
			m_pChara[3]->CreateCharaLife();
		}
	}

	/* エネルギーゲージクラスに、最大エネルギー値の格納をする */
	m_pEnergyGauge->SetMaxEnergy(m_pChara[m_nMyChara]->GetMaxEnergy());

	/* ライフグラフィッククラスに、最大ＨＰの値を格納する */
	m_pLifeGraphic->InitLife(m_pChara[m_nMyChara]->GetMaxLife());

	/* 最大制限時間のセット */
	m_pTimeGraphic->SetMaxTime(180);

	return S_OK;
}


//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	In:		なし
//	Out:	int = 状態変更識別子
//----------------------------------------------
int CGame::FrameMove()
{
	/* 終了フラグ */
	bool bEndFlg = false;

	/* 状態によって処理を分ける */
	switch(m_dwNowStatus)
	{
		case GAME_START:	Start();			break;
		case GAME_MAIN:		Game();				break;
		case GAME_END:		bEndFlg = End();	break;
	}

	/* 終了フラグがたっていたらエンディングへ移行する */
	if(bEndFlg) 
	{
		/* ゲームの状態を戻す */
		m_dwNowStatus  = GAME_START;

		return CHANGE_ENDING;
	}

	return NO_CHANGE;
}

//----------------------------------------------
//	Name:	Start
//	Func:	ゲーム開始時の処理
//	Out:	なし
//	In:		なし
//----------------------------------------------
void CGame::Start()
{
	static CListSprite*	pCountLogo;
	static int nCnt = 0;

	/* ２秒たったらスタートロゴを作成する */
	if(nCnt == 120)	pCountLogo = m_pSpriteManage->AddSprite(COUNT_LOGO);

	/* カウンターのインクリメント */
	nCnt++;

	/* ５秒たったらカウントロゴを消して、スタートロゴを作る。*/
	/* ゲームを開始する */
	if(nCnt>300)
	{
		m_pSpriteManage->SubSprite(pCountLogo);
		m_pSpriteManage->AddSprite(START_LOGO);

		m_dwNowStatus = GAME_MAIN;

		/* 時間計測開始 */
		m_pTimeGraphic->Start();

		nCnt = 0;
	}

	/* ステージクラス */
	m_pStage->FrameMove();

	/* キャラクタクラス */
	for(int i=0; i<4; i++)
	{
		if(m_pChara[i])	m_pChara[i]->FrameMoveStart();
	}
	/* カメラクラス */
	m_pCamera->FrameMove((CMyPlayer*)m_pChara[0]);

	/* スプライト管理クラス */
	m_pSpriteManage->FrameMove();

	/* エネルギーゲージクラス */
	m_pEnergyGauge->SetNowEnergy(m_pChara[m_nMyChara]->GetNowEnergy());
	m_pEnergyGauge->FrameMove();

	/* ライフグラフィッククラス */
	m_pLifeGraphic->SetLife(m_pChara[m_nMyChara]->GetNowLife());
	m_pLifeGraphic->FrameMove();

	/* 時間管理クラス */
	m_pTimeGraphic->FrameMove();
}

//----------------------------------------------
//	Name:	Game
//	Func:	ゲーム開始時の処理
//	Out:	なし
//	In:		なし
//----------------------------------------------
void CGame::Game()
{
	/* ステージクラス */
	m_pStage->FrameMove();

	/* キャラクタクラス */
	for(int i=0; i<4; i++)
	{
		if(m_pChara[i])
			m_pChara[i]->FrameMoveGame(	m_pStage, m_pBulManage, m_pSpriteManage,m_pEffectManage);
	}

	/* カメラクラス */
	m_pCamera->FrameMove((CMyPlayer*)m_pChara[0]);

	/* 弾管理クラス */
	m_pBulManage->FrameMove(m_pStage, m_pEffectManage);

	/* スプライト管理クラス */
	m_pSpriteManage->FrameMove();

	/* エフェクト管理クラス */
	m_pEffectManage->FrameMove();

	/* エネルギーゲージクラス */
	m_pEnergyGauge->SetNowEnergy(m_pChara[m_nMyChara]->GetNowEnergy());
	m_pEnergyGauge->FrameMove();

	/* ライフグラフィッククラス */
	m_pLifeGraphic->SetLife(m_pChara[m_nMyChara]->GetNowLife());
	m_pLifeGraphic->FrameMove();

	/* 時間管理クラス */
	m_pTimeGraphic->FrameMove();

	/* 制限時間が終了したら、ゲームを終了する */
	if(m_pTimeGraphic->IsEnd())	m_dwNowStatus = GAME_END;
}

//----------------------------------------------
//	Name:	End
//	Func:	ゲーム開始時の処理
//	Out:	なし
//	In:		bool = ゲーム終了フラグ
//----------------------------------------------
bool CGame::End()
{
	static CListSprite*	pEndLogo;
	static int nCnt = 0;

	/* はじめに終了ロゴを作成する */
	if(nCnt == 0)	pEndLogo = m_pSpriteManage->AddSprite(TIME_OVER);

	/* カウンターのインクリメント */
	nCnt++;

	/* ３秒たったら終了ロゴを消して、ゲームを終了する */
	if(nCnt>180)
	{
		m_pSpriteManage->SubSprite(pEndLogo);
		nCnt = 0;
		return true;
	}

	/* ステージクラス */
	m_pStage->FrameMove();

	/* キャラクタクラス */
	for(int i=0; i<4; i++)
	{
		if(m_pChara[i])	m_pChara[i]->FrameMoveEnd();
	}
	/* カメラクラス */
	m_pCamera->FrameMove((CMyPlayer*)m_pChara[0]);

	/* スプライト管理クラス */
	m_pSpriteManage->FrameMove();

	/* エネルギーゲージクラス */
	m_pEnergyGauge->SetNowEnergy(m_pChara[m_nMyChara]->GetNowEnergy());
	m_pEnergyGauge->FrameMove();

	/* ライフグラフィッククラス */
	m_pLifeGraphic->SetLife(m_pChara[m_nMyChara]->GetNowLife());
	m_pLifeGraphic->FrameMove();

	/* 時間管理クラス */
	m_pTimeGraphic->FrameMove();

	return false;

}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	Out:	なし
//	In:		なし
//----------------------------------------------
void CGame::Render()
{
	int i;

	/* カメラクラス */
	m_pCamera->Render(m_pChara[0]);

	/* ステージクラス */
	m_pStage->Render();

	/* キャラクタクラス */
	/* まずは自分以外のキャラクタを描画 */
	for(i=0; i<4; i++)
	{
		if(m_pChara[i] && m_nMyChara != i)
			m_pChara[i]->Render();
	}

	/* 次に自分のキャラを描画 */
	for(i=0; i<4; i++)
	{
		if(m_pChara[i] && m_nMyChara == i)
			m_pChara[i]->Render();
	}

	/* 弾管理クラス */
	m_pBulManage->Render();

	/* エフェクト管理クラス */
	m_pEffectManage->Render();

	/* エネルギーゲージクラス */
	m_pEnergyGauge->Render();

	/* ライフグラフィッククラス */
	m_pLifeGraphic->Render();

	/* 時間管理クラス */
	m_pTimeGraphic->Render();

	/* スプライト管理クラス（必ず最後に） */
	m_pSpriteManage->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	描画用マトリクス更新
//	Out:	なし
//	In:		なし
//----------------------------------------------
void CGame::UpDate()
{
	/* カメラクラス */
	m_pCamera->UpDate();

	/* ステージクラス */
	m_pStage->UpDate();

	/* キャラクタクラス */
	for(int i=0; i<4; i++)
	{
		if(m_pChara[i])
			m_pChara[i]->UpDate();
	}

	/* 弾管理クラス */
	m_pBulManage->UpDate();

	/* スプライト管理クラス */
	m_pSpriteManage->UpDate();

	/* エフェクト管理クラス */
	m_pEffectManage->UpDate();

	/* エネルギーゲージクラス */
	m_pEnergyGauge->UpDate();

	/* ライフグラフィッククラス */
	m_pLifeGraphic->UpDate();

	/* 時間管理クラス */
	m_pTimeGraphic->UpDate();

}
