//==========================================================
// EnemyCPU.cpp
// Auther : 桜井 博之
// Data   : 2002/05/05
//==========================================================
#include "EnemyCPU.h"

//------------------------------------------------------
//	Name:	EnemyCPU
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3Dデバイス
//	Out:	なし
//------------------------------------------------------
CEnemyCPU::CEnemyCPU(LPDIRECT3DDEVICE8 d3dDevice):CChara(d3dDevice)
{
	/* 変数の初期化 */
	m_nCnt = 0;

	/* 行動の初期化 */
	m_nNowAction = WALK;
}

//------------------------------------------------------
//	Name:	~EnemyCPU
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//------------------------------------------------------
CEnemyCPU::~CEnemyCPU()
{

}

//----------------------------------------------------------------------
//	Name:	FrameMoveGame
//	Func:	ゲーム時の毎フレームの処理
//	in:		CStage*			pStage			= ステージクラスポインタ
//			CBulManage*		pBulManage		= 弾管理クラスポインタ
//			CSpriteManage*	pSpriteManage	= スプライト管理クラスポインタ
//			CEffectManage*	pEffectManage	= エフェクト管理クラスポインタ
//	Out:	なし
//----------------------------------------------------------------------
void CEnemyCPU::FrameMoveGame(CStage* pStage, CBulManage* pBulManage, 
			CSpriteManage* pSpriteManage,CEffectManage* pEffectManage)
{
	/* 行動カウンターが尽きたか、キャラクターの行動が変化した場合 */
	/* 次の行動を決定する */
	if(m_nActionCount <= 0 || m_nNowAction != m_nNextStatus)
	{
		ComputNextAction(pEffectManage);			// 次の行動を決定
		m_nNowAction = m_nNextStatus;				// 次の行動へ移行
	}

	/* 行動時間を減らしていく */
	m_nActionCount--;

	/* 弾との当たり判定 */
	IsHitBullet(pBulManage, pEffectManage);

	/* キャラクターの行動により処理を分ける */
	switch(m_nNowAction)
	{
	case START:			Start();								break;
	case WALK:			Walk(pStage);							break;
	case DASH:			Dash(pStage, pEffectManage);			break;

	case JUMP_MAIN:		JumpMain(pStage);						break;
	case JUMP_START:	JumpStart(pStage, pEffectManage);		break;
	case JUMP_END:		JumpEnd();								break;
	case FLYGHT:		Flyght(pStage, pEffectManage);			break;

	case ATTACK_S:		Attack_S();								break;
	case ATTACK:		Attack(pBulManage);						break;

	case DAMAGE_LAND:	DamageLand(pStage, pEffectManage);		break;
	case DAMAGE_AIR:	DamageAir(pStage, pEffectManage);		break;

	case DEAD_LAND:		DeadLand(pStage, pEffectManage);		break;
	case DEAD_AIR:		DeadAir(pStage, pEffectManage);			break;

	}

	/* 回転角度値の整頓 */
	if(m_fCharaYaw < 0)			m_fCharaYaw += 360.0f;
	else if(m_fCharaYaw > 360)	m_fCharaYaw -= 360.0f;

	/* Yawの値から回転マトリクスを算出 */
	D3DXMATRIX	matTmp;
	D3DXMatrixRotationY(&matTmp, D3DXToRadian(m_fCharaYaw) );

	/* 単位移動方向ベクトル、スピード値から移動ベクトルの取得 */
	D3DXVECTOR3	vecMove;
	vecMove = m_vecMove * m_fSpeed;

	/* キャラクタのマトリクス値の更新 */
	m_matBase = MatUpdate(&m_matBase, &matTmp);
	m_matBase._41 += vecMove.x;
	m_matBase._42 += vecMove.y + m_fJump;
	m_matBase._43 += vecMove.z;

	/* モーションのさまざまな更新 */
	m_pActiveMotion->Play();

	/* ダメージカウントのデクリメント */
	m_nDamageCnt--;
	if(m_nDamageCnt < 0)	m_nDamageCnt = 0;

	//----------------------------------
	//	キャラクタに関するデータの送信
	//----------------------------------
	/* カウンターのインクリメント */
	static int nSendCnt=0;
	nSendCnt++;

	/* ウラワザ 強制召還 */
	if(m_matBase._42 < -120.0f)
	{
		m_matBase._41 = 0;
		m_matBase._42 = 0;
		m_matBase._43 = 0;
	}

}

//------------------------------------------------------------------
//	Name:	ComputNextAction
//	Func:	コンピュータの次の行動をランダムで決める
//	in:		CEffectManage* pEffectManage	= エフェクト管理クラス
//	Out:	なし
//------------------------------------------------------------------
void CEnemyCPU::ComputNextAction(CEffectManage* pEffectManage)
{
	int nTmp;

	/* 行動を続ける時間を10フレーム～30フレームからランダムで決める */

	srand((unsigned int)time(NULL));		// ランダムの初期化
	m_nActionCount = rand()%20 + 10;


	/* 現在の行動により次の行動をランダムにて決める */
	static time_t t;
	srand((unsigned int)(t * time(&t)));		// ランダムの初期化
	switch(m_nNowAction)
	{
	/* スタート時 何もしない */
	case START:
		m_nNextStatus = START;
		break;

	/* 歩いている時 */
	case WALK:
		/* ４割で歩く。２割でダッシュ。２割でジャンプ。２割で攻撃構え  */
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 4)	m_nNextStatus = WALK;
		else if	(4 <= nTmp && nTmp < 6)	m_nNextStatus = DASH;
		else if	(6 <= nTmp && nTmp < 8)	m_nNextStatus = JUMP_START;
		else							m_nNextStatus = ATTACK_S;

		/* ダッシュに移行する際の初期化 */
		if(m_nNextStatus == DASH)
		{
			/* エネルギーが1/3以上残っていればダッシュの初期化 */
			if( (float)m_nNowEnergy / (float)m_pParam->nMaxEnergy > 0.35f ){
				m_fSpeed = 0;
			}
			/* そうでなければダッシュ取り消し やっぱ歩く */
			else	m_nNextStatus = WALK;
		}

		/* ジャンプ開始に移行する際の初期化 */
		if(m_nNextStatus == JUMP_START)
		{
			/* ジャンプに移行するまでのカウンターをセット */
			m_nCnt = 15;
		}

		/* 攻撃構えに移行する際の初期化 */
		if(m_nNextStatus == ATTACK_S)
		{
			/* スピードを０にする */
			m_fSpeed = 0;
		}
		break;

	/* ダッシュしている時 */
	case DASH:
		/* ６割で歩く。 ４割でダッシュ。*/
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 6)		m_nNextStatus = WALK;
		else								m_nNextStatus = DASH;

		/* ダッシュを続けるための条件 */
		if(m_nNextStatus = DASH)
			/* エネルギーがないとダメ */
			if(m_nNowEnergy <= 0)	m_nNextStatus = WALK;

		break;

	/* ジャンプ開始時  何もしない */
	case JUMP_START:
		m_nNextStatus = JUMP_START;
		break;
	
	/* ジャンプ中 ６割で飛行。４割でジャンプ */
	case JUMP_MAIN:
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 6)		m_nNextStatus = FLYGHT;
		else								m_nNextStatus = JUMP_MAIN;

		/* 飛行に移行する際の条件*/
		if(m_nNextStatus == FLYGHT)
		{
			/* エネルギーが1/3以上残っていなければダメ */
			if( (float)m_nNowEnergy / (float)m_pParam->nMaxEnergy < 0.35f )
				m_nNextStatus = JUMP_MAIN;
		}

		break;

	/* ジャンプ終了時 何もしない */
	case JUMP_END:
		m_nNextStatus = JUMP_START;
		break;

	/* 飛行時 ６割でジャンプ。４割で飛行。 */
	case FLYGHT:
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 6)	m_nNextStatus = FLYGHT;
		else							m_nNextStatus = JUMP_MAIN;

		/* 飛行を続けるための条件 */
		if(m_nNextStatus = FLYGHT)
			/* エネルギーがないとダメ */
			if(m_nNowEnergy <= 0)	m_nNextStatus = JUMP_MAIN;

		break;

	/* 攻撃構え中 １割で攻撃構え ７割で攻撃 ２割で歩き */
	case ATTACK_S:
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 1)	m_nNextStatus = ATTACK_S;
		else if	(1 <= nTmp && nTmp < 8)	m_nNextStatus = ATTACK;
		else							m_nNextStatus = WALK;

		/* 攻撃に移行する際の初期化 */
		if(m_nNextStatus == ATTACK)
		{
			m_pActiveMotion->SetBlend(ANI_ATA,  1.0f);			/* ブレンド係数を格納 */
			m_pActiveMotion->SetBlend(ANI_ATAS, 0.0f);
			m_nCnt = m_pActiveMotion->GetMaxTime(ANI_ATA);		/* モーション最大フレーム数の取得 */
			m_pActiveMotion->SetActiveTime(ANI_ATA, 0);			/* アニメーション現在時間を0に */
		}
		break;

	/* 攻撃中 何もしない */
	case ATTACK:
		m_nNextStatus = ATTACK;
		break;

	/* 地上ダメージ中 何もしない */
	case DAMAGE_LAND:
		m_nNextStatus = DAMAGE_LAND;
		break;

	/* 空中ダメージ中 何もしない */
	case DAMAGE_AIR:
		m_nNextStatus = DAMAGE_AIR;
		break;

	/* 地上死亡中 ９割で何もしない。１割で生き返る */
	case DEAD_LAND:
		nTmp = rand()%10;
		if		(0 <= nTmp && nTmp < 9)	m_nNextStatus = DEAD_LAND;
		else							m_nNextStatus = JUMP_MAIN;

		/* 復活する時の処理 */
		if(m_nNextStatus == JUMP_MAIN)
		{
			m_nNowLife = m_pParam->nMaxLife;				// ＨＰを最大に回復
			m_fJump = 0.5f;									// ジャンプ値を格納
			m_nNowAction = JUMP_MAIN;						// ジャンプに移行
			pEffectManage->AddEffect(REVIVAL, m_matBase);	// 復活エフェクト
		}
		break;

	/* 空中死亡中 何もしない */
	case DEAD_AIR:
		m_nNextStatus = DEAD_AIR;
		break;
	}

	/* 特別処理 次の行動がジャンプの場合に限り、行動カウンターを半分にする */
	if(m_nNextStatus == JUMP_MAIN)
		m_nActionCount /= 2;

	/* 仮想キーをランダムで決める */

	/* 仮想キーを初期化 */
	m_tagVirtualKey.Up = false;
	m_tagVirtualKey.Down = false;
	m_tagVirtualKey.Left = false;
	m_tagVirtualKey.Right = false;

	/* 上下を決める ６割で上 １割で下 ３割で無し*/
	srand((unsigned int)time(NULL));		// ランダムの初期化
	nTmp = rand()%10;
	if		(0 <= nTmp && nTmp < 6)		m_tagVirtualKey.Up = true;
	else if	(nTmp == 6)					m_tagVirtualKey.Down = true;

	/* 左右を決める ６割で無し ２割で右 ２割で左 */
	srand((unsigned int)time(NULL));		// ランダムの初期化
	nTmp = rand()%10;
	if		(0 <= nTmp && nTmp < 2)	m_tagVirtualKey.Right = true;
	else if	(2 <= nTmp && nTmp < 4)	m_tagVirtualKey.Left = true;

}

//------------------------------------------------------------------
//	Name:	Start
//	Func:	ゲームスタート時
//	in:		なし
//	Out:	なし
//------------------------------------------------------------------
void CEnemyCPU::Start()
{
//	static nCnt = 0;

	/* ３秒間待つ */
//	m_nCnt++;
	/* ３秒たったらWALKに移行する */
//	if(m_nCnt>180)	m_nNowAction = WALK;
}

//------------------------------------------------------
//	Name:	Walk
//	Func:	歩いている行動
//	in:		CStage* pStage = ステージクラスへのポインタ
//	Out:	なし
//------------------------------------------------------
void CEnemyCPU::Walk(CStage* pStage)
{
	//--------------------------
	//	入力関係の処理
	//--------------------------
	/* 左に旋回する */
	if(m_tagVirtualKey.Left)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* 右に旋回する */
	else if(m_tagVirtualKey.Right)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* 前に進む */
	if(m_tagVirtualKey.Up)	
	{
		m_fSpeed = m_pParam->fWalkSpeed;
		m_fMoveYaw = m_fCharaYaw;
		m_pActiveMotion->ChangeMotion(ANI_FORWARD);
	}

	/* 後ろへ後退する */
	else if(m_tagVirtualKey.Down)
	{
		m_fSpeed = m_pParam->fBackSpeed;
		m_fMoveYaw = m_fCharaYaw-180.0f;
		m_pActiveMotion->ChangeMotion(ANI_BACK);
	}

	/* 前にも後ろにも進まない */
	else
	{
		m_fSpeed = 0;
		m_fMoveYaw = m_fCharaYaw;
		m_pActiveMotion->ChangeMotion(ANI_STOP);
	}

	/* エネルギーの回復 */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

	//--------------------------
	//	壁関係の処理
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* 足元の地面を調べ、見つけた面が一定距離(少し多め)以上、*/
	/* あるいは見つからなかったらジャンプへ移行 */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) > HIT_GROUND+1.5f)
	{
		m_nNowAction = JUMP_MAIN;
	}
	// 面が一定距離以内に見つかった場合（立っていると見なされた場合）
	else
	{
		m_matBase._42 = vecTmp.y + 5.0f;				// キャラの足が地面についているように修正
		m_vecMove = GetVecToPlane(&plaTmp, m_fMoveYaw);	// 移動角度と地面から単位方向ベクトルの取得
	}

	/* 壁を調べ、見つけた面が一定距離内なら壁に沿って進む */
	D3DXVECTOR3 vecCross1,vecCross2;
	if(SearchAllWall(pStage, &vecCross1, &vecCross2) < HIT_WALL)
	{
		m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
		if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);

		m_nActionCount = 0;		// 同時に、次の行動に移る
	}
}

//--------------------------------------------------------------------------
//	Name:	Dash
//	Func:	ダッシュ行動
//	in:		CStage*			pStage			= ステージクラスポインタ
//			CEffectManage*	pEffectManage	= エフェクト管理クラスポインタ
//	Out:	なし
//--------------------------------------------------------------------------
void CEnemyCPU::Dash(CStage* pStage, CEffectManage* pEffectManage)
{
	//--------------------------
	//	入力関係の処理
	//--------------------------
	D3DXVECTOR3	vecNew;		// 今回での方向ベクトル
	vecNew *= 0;
	int		nFB=0, nLR=0;	// 入力方向をモーション処理の為格納する

	/* とりあえず今回のスピードを初期化する */
	m_fSpeed = 0.0f;

	/* 左にダッシュする */
	if(m_tagVirtualKey.Left)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.x = -1.0f;
		nLR = ANI_DASH_L;
	}
	/* 右にダッシュする */
	else if(m_tagVirtualKey.Right)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.x = 1.0f;
		nLR = ANI_DASH_R;
	}

	/* 前方にダッシュする */
	if(m_tagVirtualKey.Up)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.z = 1.0f;
		nFB = ANI_DASH_F;
	}
	/* 後方にダッシュする */
	else if(m_tagVirtualKey.Down)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.z = -1.0f;
		nFB = ANI_DASH_B;
	}

	/* キャラクターの向いている方向に修正 */
	D3DXMATRIX	matTmp;
	D3DXMatrixRotationY(&matTmp, D3DXToRadian(m_fCharaYaw) );
	D3DXVec3TransformCoord(&vecNew, &vecNew, &matTmp);
	/* 今回の方向ベクトルから移動方向角度を求める */
	m_fMoveYaw = (float)GetAngle((double)vecNew.x, (double)vecNew.z);

	/* エネルギーの減少 */
	m_nNowEnergy -= USE_ENERGY_DASH;

	/* エフェクトを何フレームかに１回発生 */
	if(m_nCnt%EFFECT_DASH == 0)
	{
		pEffectManage->AddEffect(BOOST_A, m_matBase);
	}
	m_nCnt++;

	//--------------------------
	//	モーションの変更
	//--------------------------
	/* 縦横両方押されているとき */
	if(nFB && nLR)	m_pActiveMotion->ChangeMotion(nFB, nLR, 0.1f);

	/* 縦だけ押されているとき */
	else if(nFB)	m_pActiveMotion->ChangeMotion(nFB, 0.05f);
	/* 横だけ押されているとき */
	else if(nLR)	m_pActiveMotion->ChangeMotion(nLR, 0.05f);
	/* 何も押されていないとき */
	else			m_pActiveMotion->ChangeMotion(ANI_DASH_F, 0.05f);

	//--------------------------
	//	壁関係の処理
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* 足元の地面を調べ、見つけた面が一定距離(少し多め)以上、*/
	/* あるいは見つからなかったらジャンプへ移行 */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) > HIT_GROUND+1.5f)
		m_nNowAction = JUMP_MAIN;

	/* 面が一定距離以内に見つかった場合（立っていると見なされた場合）*/
	else
	{
		m_matBase._42 = vecTmp.y + 5.0f;				// キャラの足が地面についているように修正
		m_vecMove = GetVecToPlane(&plaTmp, m_fMoveYaw);	// 移動角度と地面から単位方向ベクトルの取得
	}

	/* 壁を調べ、見つけた面が一定距離内なら壁に沿って進む */

	D3DXVECTOR3 vecCross1,vecCross2;
	if(SearchAllWall(pStage, &vecCross1, &vecCross2) < HIT_WALL)
	{
		m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
		if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);


		m_nActionCount = 0;		// 同時に、次の行動に移る
	}
}

//----------------------------------------------
//	Name:	Attack_S
//	Func:	攻撃構え行動
//	in:		なし
//	Out:	無し
//----------------------------------------------
void CEnemyCPU::Attack_S()
{
	static float fNextYaw;		// 目標Yaw角度
	static float fMoveSpeed;	// カメラ移動速度

	/* 左に旋回する */
	if(m_tagVirtualKey.Left)
		m_fCharaYaw -= m_pParam->fTurn/2;

	/* 右に旋回する */
	else if(m_tagVirtualKey.Right)
		m_fCharaYaw += m_pParam->fTurn/2;

	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;

	/* モーションの更新 */
	m_pActiveMotion->ChangeMotion(ANI_ATAS);

	/* エネルギーの回復 */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

}

//------------------------------------------------------
//	Name:	Attack
//	Func:	攻撃行動
//	in:		CBulManage* pBulManage = 弾管理クラスポインタ
//	Out:	なし
//------------------------------------------------------
void CEnemyCPU::Attack(CBulManage* pBulManage)
{
	/* 特定のフレームだけ弾を出す */
	if(m_nCnt == m_pActiveMotion->GetMaxTime(ANI_ATA))
	{
		D3DXMATRIX matTmp;
		D3DXMatrixIdentity(&matTmp);

		/* 向いている方向に弾を撃つ */
		D3DXMatrixRotationX(&matTmp, D3DXToRadian(-m_fCharaPitch));

		/* 座標値をある程度手の位置に修正 */
		matTmp._41 += 0.0f;
		matTmp._42 += 3.5f;
		matTmp._43 += 0.0f;

		/* 弾を出す処理 */
		matTmp = matTmp * m_matBase;
		pBulManage->AddBullet(0, matTmp, m_nNum);

	}

	// アニメーション中の処理
	if(m_nCnt > 0)
	{
		/* アニメーションカウンターを減らす */
		m_nCnt--;
	}

	// アニメーション終了
	// ブレンド係数を元に戻し、ATTACK_Sに移行する
	else
	{
		/* ブレンド係数を元に戻す */
		m_pActiveMotion->SetBlend(ANI_ATAS, 1.0f);
		m_pActiveMotion->SetBlend(ANI_ATA,	0.0f);
		m_nNowAction = ATTACK_S;
	}

	/* エネルギーの回復 */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

}

//------------------------------------------------------------------
//	Name:	JumpStart
//	Func:	ジャンプ開始行動
//	in:		CStage*			pStage		  = ステージクラス
//			CEffectManage*	pEffectManage = エフェクト管理クラス
//	Out:	無し
//------------------------------------------------------------------
void CEnemyCPU::JumpStart(CStage* pStage, CEffectManage* pEffectManage)
{
	/* カウンターが続く間、ジャンプ開始行動が続く */
	if(m_nCnt>0)
	{
		/* モーションの変化 */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_S);

		// カウンターを減らしていく
		m_nCnt--;

		/* 地面を調べ、見つけた面が一定距離(少し少なめ)以下なら着地する */
		D3DXVECTOR3	vecTmp;
		if (SearchAllGround(pStage, NULL, &vecTmp) < 4.5f)
		{
			m_fJump = 0;
			m_matBase._42 = vecTmp.y + 5.0f;
			m_nNowAction = WALK;
		}

		/* 壁を調べ、見つけた面が一定距離内なら壁に沿って進む */
		D3DXVECTOR3 vecCross1,vecCross2;
		if(SearchAllWall(pStage, &vecCross1, &vecCross2) < 2.0f)
		{
			m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
			if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);
		}

		/* 天井を調べ、天井が見つかったらジャンプ値をなくす */
		if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < 4.0f)
		{
			m_fJump = 0;
		}

		/* エネルギーの回復 */
		if(m_nNowEnergy < m_pParam->nMaxEnergy)
			m_nNowEnergy+=REST_ENERGY;

	}

	// カウンターが終了したら次にジャンプできるまでのカウント値をセットしジャンプに移行する
	else
	{
		m_nNowAction = JUMP_MAIN;
		m_fJump = m_pParam->fJumpUp;
		m_nCnt = 30;
	}

}

//----------------------------------------------
//	Name:	JumpMain
//	Func:	ジャンプ行動
//	in:		CStage* pStage = ステージクラスへのポインタ
//	Out:	なし
//----------------------------------------------
void CEnemyCPU::JumpMain(CStage* pStage)
{
	/* 左に旋回する */
	if(m_tagVirtualKey.Left)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* 右に旋回する */
	else if(m_tagVirtualKey.Right)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* 前に移動する */
	if(m_tagVirtualKey.Up)
	{
		m_fSpeed = m_pParam->fJumpForward;

		/* 単位方向ベクトルの取得 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

		/* モーションの変化 */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_F);
	}

	/* 後ろに移動する */
	else if(m_tagVirtualKey.Down)
	{
		m_fSpeed = m_pParam->fJumpBack;

		/* 単位方向ベクトルの取得 */
		m_vecMove = -GetNormalVec3ToMat(NULL, &m_matBase);

		/* モーションの変化 */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_B);
	}
	/* 上も下も押さなかった場合 */
	else
	{
		/* 速度を落としていく */
		if((m_fSpeed-=0.05f) < 0.0f)	m_fSpeed = 0.0f;

		/* 単位方向ベクトルの取得 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

		/* モーションの変化 */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_N);
	}

	/* だんだん地面に落ちる */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* エネルギーの回復 */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

	//------------------
	//	壁関係の処理
	//------------------
	/* 地面を調べ、見つけた面が一定距離(少し少なめ)以下なら着地する */
	D3DXVECTOR3	vecTmp;
	if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND-0.5f)
	{
		m_fJump = 0;
		m_matBase._42 = vecTmp.y + 5.0f;
		m_nNowAction = WALK;
	}

	/* 壁を調べ、見つけた面が一定距離内なら壁に沿って進む */
	D3DXVECTOR3 vecCross1,vecCross2;
	if(SearchAllWall(pStage, &vecCross1, &vecCross2) < HIT_WALL)
	{
		m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
		if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);

		m_nActionCount = 0;		// 同時に、次の行動に移る
	}

	/* 天井を調べ、天井が見つかったらジャンプ値をなくす */
	if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
	{
		m_fJump = 0;
	}

}

//----------------------------------------------
//	Name:	JumpEnd
//	Func:	ジャンプ終了時
//	in:		無し
//	Out:	無し
//----------------------------------------------
void CEnemyCPU::JumpEnd()
{

}

//------------------------------------------------------------------
//	Name:	Flyght
//	Func:	飛んでいる行動
//	in:		CStage*			pStage		  = ステージクラス
//			CEffectManage*	pEffectManage = エフェクト管理クラス
//	Out:	無し
//------------------------------------------------------------------
void CEnemyCPU::Flyght(CStage* pStage, CEffectManage* pEffectManage)
{
	/* 左に旋回する */
	if(m_tagVirtualKey.Left)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* 右に旋回する */
	else if(m_tagVirtualKey.Right)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* 前に移動する */
	if(m_tagVirtualKey.Up)
	{
		/* 前に進む */
		m_fSpeed = m_pParam->fFlyForward;
		/* モーションの変化 */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_F);
		/* 単位方向ベクトルの取得 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

		/* ジャンプ値を０に近づける */
		if(m_fJump>0)		m_fJump -= 0.02f;
		else if(m_fJump<0)	m_fJump += 0.02f; 
	}

	/* 後ろに移動する */
	else if(m_tagVirtualKey.Down)
	{
		/* 後ろに進む */
		m_fSpeed = m_pParam->fFlyBack;
		/* モーションの変化 */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_B);
		/* 単位方向ベクトルの取得 */
		m_vecMove = -GetNormalVec3ToMat(NULL, &m_matBase);

		/* ジャンプ値を０に近づける */
		if(m_fJump>0)		m_fJump -= 0.02f;
		else if(m_fJump<0)	m_fJump += 0.02f; 
	}

	/* 上も下も押さなかった場合 */
	else
	{
		/* だんだん上昇していく */
		if( (m_fJump+=m_pParam->fFlyPlumb) > 0.8f)	m_fJump = 0.8f;

		/* 移動の速度を落としていく */
		if((m_fSpeed-=0.03f) < 0.0f)	m_fSpeed = 0.0f;
		/* モーションの変化 */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_N);
		/* 単位方向ベクトルの取得 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);
	}

	/* エネルギーの減少 飛行中は２ずつ減らす */
	m_nNowEnergy -= USE_ENERGY_FLY;

	/* エフェクトを何フレームに一回発生 */
	static int nCnt = 0;
	if(nCnt%EFFECT_FLY == 0)
	{
		pEffectManage->AddEffect(BOOST_B, m_matBase);
	}
	nCnt++;

	//------------------
	//	壁関係の処理
	//------------------
	/* 地面を調べ、見つけた面が一定距離以下なら着地する */
	D3DXVECTOR3	vecTmp;
	if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND)
	{
		m_fJump = 0;
		m_matBase._42 = vecTmp.y + 5.0f;
		m_nNowAction = WALK;
	}

	/* 壁を調べ、見つけた面が一定距離内（少し多め）なら壁に沿って進む */
	D3DXVECTOR3 vecCross1,vecCross2;
	if(SearchAllWall(pStage, &vecCross1, &vecCross2) < HIT_WALL+1.0f)
	{
		m_vecMove = (vecCross2-GetPosBase()) + (GetPosBase()-vecCross1);
		if(D3DXVec3Length(&m_vecMove) > 0.5f)	m_vecMove = SetVec3Length(NULL, &m_vecMove, 0.5f);

		m_nActionCount = 0;		// 同時に、次の行動に移る
	}

	/* 天井を調べ、天井が見つかったらジャンプ値をなくす */
	if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
	{
		m_fJump = 0;
	}
}

//------------------------------------------------------------------
//	Name:	DamageLand
//	Func:	ダメージ中･･･キャラが地面にいる
//	in:		CStage*			pStage			= ステージクラス
//			CEffectManage*	pEffectManage	= エフェクト管理クラス
//	Out:	無し
//------------------------------------------------------------------
void CEnemyCPU::DamageLand(CStage* pStage, CEffectManage* pEffectManage)
{
	/* 操作する事は一切出来ない */

	/* スピード値を減らしていく */
	m_fSpeed -= m_pParam->fBrakes;

	/* スピード値が０になったら元に戻る */
	if(m_fSpeed < 0)
		m_nNowAction = WALK;

	/* モーションの変化 */
	m_pActiveMotion->ChangeMotion(ANI_DAM_L);

	//--------------------------
	//	壁関係の処理
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* 足元の地面を調べ、見つけた面が一定距離（少し多め）以上、*/
	/* あるいは見つからなかったら空中ダメージへ移行 */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) > HIT_GROUND+1.0f)
	{
		m_nNowAction = DAMAGE_AIR;
	}

	// 面が一定距離以内に見つかった場合（立っていると見なされた場合）
	else
	{
		m_matBase._42 = vecTmp.y + 5.0f;				// キャラの足が地面についているように修正
		m_vecMove = GetVecToPlane(&plaTmp, m_fMoveYaw);	// 移動角度と地面から単位方向ベクトルの取得
	}

	/* 壁を調べ、見つけた面が一定距離内（少し多め）なら進まない（！） */
	if(SearchAllWall(pStage, NULL, NULL) < HIT_WALL+1.0f)
		m_vecMove *= 0;
}

//------------------------------------------------------------------
//	Name:	DamageAir
//	Func:	ダメージ中･･･キャラが空中にいる
//	in:		CStage*			pStage			= ステージクラス
//			CEffectManage*	pEffectManage	= エフェクト管理クラス
//	Out:	無し
//------------------------------------------------------------------
void CEnemyCPU::DamageAir(CStage* pStage, CEffectManage* pEffectManage)
{
	/* 操作する事は一切出来ない */

	/* スピード値を減らしていく */
	m_fSpeed -= m_pParam->fBrakes;

	/* だんだん地面に落ちる */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* スピード値が０になったら元に戻る */
	if(m_fSpeed < 0)
		m_nNowAction = JUMP_MAIN;

	/* モーションの変化 */
	m_pActiveMotion->ChangeMotion(ANI_DAM_A);

	//------------------
	//	壁関係の処理
	//------------------
	/* 地面を調べ、見つけた面が一定距離以下なら地面ダメージへ移行する */
	D3DXVECTOR3	vecTmp;
	if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND)
	{
		m_fJump = 0;
		m_matBase._42 = vecTmp.y + 5.0f;
		m_nNowAction = DAMAGE_LAND;
	}

	/* 壁を調べ、見つけた面が一定距離内（少し多め）なら進まない（！） */
	if(SearchAllWall(pStage, NULL, NULL) < HIT_WALL+1.0f)
		m_vecMove *= 0;

	/* 天井を調べ、天井が見つかったらジャンプ値をなくす */
	if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
	{
		m_fJump = 0;
	}

}

//------------------------------------------------------------------
//	Name:	DeadLand
//	Func:	キャラが地面にいて死んでいる状態
//	in:		CStage*			pStage			= ステージクラス
//			CEffectManage*	pEffectManage	= エフェクト管理クラス
//	Out:	無し
//------------------------------------------------------------------
void CEnemyCPU::DeadLand(CStage* pStage, CEffectManage* pEffectManage)
{
	/* 操作する事は一切出来ない */

	/* スピード値を減らしていく */
	m_fSpeed -= m_pParam->fBrakes;
	if(m_fSpeed < 0)	m_fSpeed = 0;

	/* モーションの変化 */
	m_pActiveMotion->ChangeMotion(ANI_DEAD_L, 0.05f);

	//--------------------------
	//	壁関係の処理
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* 足元の地面を調べ、見つけた面が一定距離（少し多め）以上、*/
	/* あるいは見つからなかったら空中死亡へ移行 */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) > HIT_GROUND+1.0f)
	{
		m_nNowAction = DEAD_AIR;
	}

	/* 面が一定距離以内に見つかった場合（倒れているとみなされた場合） */
	else
	{
		m_matBase._42 = vecTmp.y + 5.0f;				// キャラの足が地面についているように修正
		m_vecMove = GetVecToPlane(&plaTmp, m_fMoveYaw);	// 移動角度と地面から単位方向ベクトルの取得
	}

	/* 壁を調べ、見つけた面が一定距離内（少し多め）なら進まない（！） */
	if(SearchAllWall(pStage, NULL, NULL) < HIT_WALL+1.0f)
		m_vecMove *= 0;
}

//------------------------------------------------------------------
//	Name:	DeadAir
//	Func:	キャラが空中にいて死んでいる状態
//	in:		CStage*			pStage			= ステージクラス
//			CEffectManage*	pEffectManage	= エフェクト管理クラス
//	Out:	無し
//------------------------------------------------------------------
void CEnemyCPU::DeadAir(CStage* pStage, CEffectManage* pEffectManage)
{
	/* 操作する事は一切出来ない */

	/* スピード値を減らしていく */
	m_fSpeed -= m_pParam->fBrakes;
	if(m_fSpeed < 0)	m_fSpeed = 0;

	/* だんだん地面に落ちる */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* モーションの変化 */
	m_pActiveMotion->ChangeMotion(ANI_DEAD_A, 0.05f);

	//------------------
	//	壁関係の処理
	//------------------
	/* 地面を調べ、見つけた面が一定距離以下なら地面ダメージへ移行する */
	D3DXVECTOR3	vecTmp;
	if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND)
	{
		m_fJump = 0;
		m_matBase._42 = vecTmp.y + 5.0f;
		m_nNowAction = DEAD_LAND;
	}

	/* 壁を調べ、見つけた面が一定距離内（少し多め）なら進まない（！） */
	if(SearchAllWall(pStage, NULL, NULL) < HIT_WALL+1.0f)
		m_vecMove *= 0;

	/* 天井を調べ、天井が見つかったらジャンプ値をなくす */
	if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
	{
		m_fJump = 0;
	}

}