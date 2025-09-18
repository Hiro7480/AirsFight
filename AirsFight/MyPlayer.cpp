//==========================================================
// MyPlayer.cpp
// Auther : 桜井 博之
// Data   : 2002/05/05
//==========================================================
#include "MyPlayer.h"

//------------------------------------------------------
//	Name:	MyPlayer
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3Dデバイス
//	Out:	なし
//------------------------------------------------------
CMyPlayer::CMyPlayer(LPDIRECT3DDEVICE8 d3dDevice):CChara(d3dDevice)
{
	/* ロックオン関係の変数の初期化 */
	for(int i=0; i<3; i++)
	{
		m_bCanLock[i]	= false;
		m_vecProject[i] *= 0;
		m_vecView[i]	*= 0;

		/* ロックオンマーカーの作成 */
		m_pLockMarker[i] = new CLockOnMarker(m_pd3dDevice, const_cast<TCHAR*>("data\\Game\\LockOn.png"));
		m_pLockMarker[i]->SetRec(0,0, 64, 64);

		/* キャラクタライフフォントの初期化 */
		m_pCharaLife[i] = NULL;

		/* キャラクタ名前フォントの初期化 */
		m_pCharaName[i] = NULL;
	}

	m_bNowLock = false;
 	m_nLockTarget = -1;

	/* 汎用カウンタの初期化 */
	m_nCnt = 0;

	/* 行動の初期化 */
	m_nNowAction = WALK;
}

//------------------------------------------------------
//	Name:	~MyPlayer
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//------------------------------------------------------
CMyPlayer::~CMyPlayer()
{
	/* 使用したメモリの開放 */
	for(int i=0; i<3; i++)
	{
		SAFE_DELETE(m_pLockMarker[i]);
		SAFE_DELETE(m_pCharaName[i]);
		SAFE_DELETE(m_pCharaLife[i]);
	}
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
void CMyPlayer::FrameMoveGame(CStage* pStage, CBulManage* pBulManage, 
			CSpriteManage* pSpriteManage,CEffectManage* pEffectManage)
{
	int i;

	/* アングルＵＰとアングルＤＯＷＮを同時に押す、または	 */
	/* 角度初期化キーを押すと角度を初期化する				 */
	if( ( GetAsyncKeyState(KEY_ANGLE_UP)&0x8000 ) &&  ( GetAsyncKeyState(KEY_ANGLE_DOWN)&0x8000 ) ||
		GetAsyncKeyState(KEY_ANGLE_FORMAT) & 0x8000)
		m_fCharaPitch = 0.0f;


	/* アングルＵＰまたはアングル操作＋αをおすと上を向く */
	else if	(GetAsyncKeyState(KEY_ANGLE_UP) & 0x8000 || 
			(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) && (GetAsyncKeyState(VK_DOWN)&0x8000) )
		m_fCharaPitch += m_pParam->fTurn/2;

	/* アングルＤＯＷＮまたはアングル操作＋αをおすと下を向く */
	else if	(GetAsyncKeyState(KEY_ANGLE_DOWN) & 0x8000 || 
			(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) && (GetAsyncKeyState(VK_UP)&0x8000) )
		m_fCharaPitch -= m_pParam->fTurn/2;

	/* 角度を-60～60の間で縛る */
	if(m_fCharaPitch < -60.0f)		m_fCharaPitch = -60.0f;
	else if(m_fCharaPitch > 60.0f)	m_fCharaPitch = 60.0f;	


	/* ロックオンに関する処理 */
	LockOn(pStage);

	/* 弾との当たり判定 */
	IsHitBullet(pBulManage, pEffectManage);

	/* キャラクターの行動により処理を分ける */
	switch(m_nNowAction)
	{
	case START:			Start(pSpriteManage);						break;
	case WALK:			Walk(pStage);								break;
	case DASH:			Dash(pStage, pEffectManage);				break;

	case JUMP_MAIN:		JumpMain(pStage);							break;
	case JUMP_START:	JumpStart(pStage, pEffectManage);			break;
	case JUMP_END:		JumpEnd();									break;
	case FLYGHT:		Flyght(pStage, pEffectManage);				break;

	case ATTACK_S:		Attack_S();									break;
	case ATTACK:		Attack(pBulManage);							break;

	case DAMAGE_LAND:	DamageLand(pStage, pEffectManage);			break;
	case DAMAGE_AIR:	DamageAir(pStage, pEffectManage);			break;

	case DEAD_LAND:		DeadLand(pStage, pEffectManage);			break;
	case DEAD_AIR:		DeadAir(pStage, pEffectManage);				break;

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

	/* 敵キャラのライフフォントの更新 */
	for(i=0; i<3; i++)
	{
		m_pCharaLife[i]->SetString(*m_tagEnemyData[i].pNowLife);
	}

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
//	Name:	Start
//	Func:	ゲームを開始する
//	in:		CSpriteManage* pSpriteManage = スプライト管理クラス
//	Out:	なし
//------------------------------------------------------------------
void CMyPlayer::Start(CSpriteManage* pSpriteManage)
{
	/* 呼ばれないから意味がない */
	/* すみません消し忘れていました */
}

//------------------------------------------------------
//	Name:	Walk
//	Func:	歩いている行動
//	in:		CStage* pStage = ステージクラスへのポインタ
//	Out:	なし
//------------------------------------------------------
void CMyPlayer::Walk(CStage* pStage)
{
	//--------------------------
	//	入力関係の処理
	//--------------------------
	/* 左に旋回する */
	if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* 右に旋回する */
	else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* 前に進む */
	if(	GetAsyncKeyState(KEY_FORWARD)&0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )	
	{
		m_fSpeed = m_pParam->fWalkSpeed;
		m_fMoveYaw = m_fCharaYaw;
		m_pActiveMotion->ChangeMotion(ANI_FORWARD);
	}

	/* 後ろへ後退する */
	else if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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

	/* エネルギーが1/3以上残っている場合はダッシュする */
	if(	GetAsyncKeyState(KEY_DASH) & 0x8000 &&
		(float)m_nNowEnergy / (float)m_pParam->nMaxEnergy > 0.35f)
	{
		/* 現在速度を初期化してダッシュ行動に移行 */
		m_fSpeed = 0;
		m_nNowAction = DASH;
		m_nCnt = 0;
	}

	/* ジャンプする */
	else if(GetAsyncKeyState(KEY_JUMP) & 0x8000)
	{
		/* カウント値を格納してジャンプ開始行動に移行 */
		m_nCnt = 15;
		m_nNowAction = JUMP_START;
	}

	/* 武器を構える */
	if(GetAsyncKeyState(KEY_ATAS) & 0x8000)
	{
		// キャラクターをとめる
		m_fSpeed = 0;

		// 武器構え行動に移行
		m_nNowAction = ATTACK_S;
	}

	/* エネルギーの回復 */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

	//--------------------------
	//	壁関係の処理
	//--------------------------
	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;
	/* 足元の地面を調べ、見つけた面が一定距離（少し多め）以上、*/
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
	}
}

//--------------------------------------------------------------------------
//	Name:	Dash
//	Func:	ダッシュ行動
//	in:		CStage*			pStage			= ステージクラスポインタ
//			CEffectManage*	pEffectManage	= エフェクト管理クラスポインタ
//	Out:	なし
//--------------------------------------------------------------------------
void CMyPlayer::Dash(CStage* pStage, CEffectManage* pEffectManage )
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
	if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.x = -1.0f;
		nLR = ANI_DASH_L;
	}
	/* 右にダッシュする */
	else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.x = 1.0f;
		nLR = ANI_DASH_R;
	}

	/* 前方にダッシュする */
	if(GetAsyncKeyState(KEY_FORWARD) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
	{
		m_fSpeed = m_pParam->fDashSpeed;
		vecNew.z = 1.0f;
		nFB = ANI_DASH_F;
	}
	/* 後方にダッシュする */
	else if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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

	/* SHIFTを離す、またエネルギーが無い場合はWALKに移行する */
	if(!(GetAsyncKeyState(KEY_DASH)&0x8000) || m_nNowEnergy <= 0)
	{
		m_nNowAction = WALK;
	}

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
	/* 足元の地面を調べ、見つけた面が一定距離（少し多め）以上、*/
	/* あるいは見つからなかったらジャンプへ移行 */
	if (SearchAllGround(pStage, &plaTmp, &vecTmp) >HIT_GROUND + 1.5f)
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
	}
}

//----------------------------------------------
//	Name:	Attack_S
//	Func:	攻撃構え行動
//	in:		なし
//	Out:	無し
//----------------------------------------------
void CMyPlayer::Attack_S()
{
	static float fNextYaw;		// 目標Yaw角度
	static float fMoveSpeed;	// カメラ移動速度

	/* ロックオンしているとき */
	if(m_bNowLock)
	{
		/* ロックオンしている場合は構えたときに目標の方向を向く */

		/* 目標角度の計算 */
		D3DXVECTOR3	vecTmp = GetLockVec() - GetPosBase();
		GetVec3Inverce(&vecTmp, &vecTmp);
		fNextYaw = (float)GetAngle(vecTmp.x, vecTmp.z);

		/* 360を超えたら修正 */
		if(fNextYaw >= 360.0f)			fNextYaw -= 360.0f;
		else if(fNextYaw < 0.0f)		fNextYaw += 360.0f;

		/* 現在角度を目標角度に近づける */

		/* 現在Yaw、目標Yawから１フレームごとの補間移動量を求める */
		float fTmp;
		fTmp = m_fCharaYaw - fNextYaw + 180.0f;

		/* 360を超えたら修正 */
		if(fTmp >= 360.0f)		fTmp -= 360.0f;
		else if(fTmp < 0.0f)	fTmp += 360.0f;

		/* 現在角度と目標角度が一定以内なら同じにする */
		if( fTmp <= 4.0f && fTmp >= -4.0f)
			m_fCharaYaw = fNextYaw + 180.0f;	

		/* 左回り（マイナス）の方が近い時 */
		else if(fTmp < 180.0f)
		{
			// 移動量の算出
			fMoveSpeed = fTmp / 10.0f;
			if(fMoveSpeed < 2.0f)	fMoveSpeed = 2.0f;
			// キャラ位置の移動
			m_fCharaYaw -= fMoveSpeed;
		}

		/* 右回り（プラス）の方が近い時 */
		else
		{
			// 移動量の算出
			fTmp = 360.0f - fTmp;
			fMoveSpeed = fTmp / 10.0f;
			if(fMoveSpeed < 2.0f)	fMoveSpeed = 2.0f;
			// キャラ位置の移動
			m_fCharaYaw += fMoveSpeed;
		}

		/* 360を超えたら修正*/
		if(m_fCharaYaw >= 360.0f)	m_fCharaYaw -= 360.0f;
		else if(m_fCharaYaw < 0.0f)	m_fCharaYaw += 360.0f;
	}

	/* ロックオンしていないとき */
	else
	{
		/* 上キーで視線を下に下げる */
		if(GetAsyncKeyState(KEY_FORWARD) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
			if( (m_fCharaPitch-=m_pParam->fTurn/2) < -60.0f)	m_fCharaPitch = -60.0f;

		/* 下キーで視線を上にあげる */
		if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
			if( (m_fCharaPitch+=m_pParam->fTurn/2) > 60.0f)	m_fCharaPitch = 60.0f;

		/* 左に旋回する */
		if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
			m_fCharaYaw -= m_pParam->fTurn/2;

		/* 右に旋回する */
		else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
			m_fCharaYaw += m_pParam->fTurn/2;

	}

	/* 完全に構えているなら、攻撃する */
	if(GetAsyncKeyState(KEY_ATTACK) & 0x8000 && m_pActiveMotion->GetBlend(ANI_ATAS)== 1.0f)
	{
		/* ブレンド係数を格納 */
		m_pActiveMotion->SetBlend(ANI_ATA,  1.0f);
		m_pActiveMotion->SetBlend(ANI_ATAS, 0.0f);

		/* モーション最大フレーム数の取得 */
		m_nCnt = m_pActiveMotion->GetMaxTime(ANI_ATA);

		/* アニメーション現在時間を0に */
		m_pActiveMotion->SetActiveTime(ANI_ATA, 0);

		/* 攻撃行動へ移行 */
		m_nNowAction = ATTACK;
	}

	D3DXPLANE	plaTmp;
	D3DXVECTOR3	vecTmp;

	/* モーションの更新 */
	m_pActiveMotion->ChangeMotion(ANI_ATAS);

	/* TABを離すとWALKに移行する */
	if(!(GetAsyncKeyState(KEY_ATAS)&0x8000))
	{
		m_nNowAction = WALK;
	}

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
void CMyPlayer::Attack(CBulManage* pBulManage )
{
	static float fNextYaw;		// 目標Yaw角度
	static float fMoveSpeed;	// カメラ移動速度

	D3DXVECTOR3	vecTmp;

	/* 特定のフレームだけ弾を出す */
	if(m_nCnt == m_pActiveMotion->GetMaxTime(ANI_ATA))
	{
		D3DXMATRIX matTmp;
		D3DXMatrixIdentity(&matTmp);

		// ロックオンしている時はその相手の方に弾を撃つ
		if(m_bNowLock)
		{
			float		fTmp;
			float		fPitch;

			/* キャラ→目標へのベクトル値を求める */
			vecTmp = GetLockVec() - GetPosBase();
			/* X,Z軸の長さを求める */
			fTmp = GetLengthEX(&vecTmp, true, false, true);
			/* Pitch回転角度を求める */
			fPitch = (float)GetAngle(vecTmp.y, fTmp);

			D3DXMatrixRotationX(&matTmp, D3DXToRadian(-fPitch));
		}

		/* ロックオンしていない時は向いている方向に弾を撃つ */
		else {
			D3DXMatrixRotationX(&matTmp, D3DXToRadian(-m_fCharaPitch));
		}

		// 座標値をある程度手の位置に修正
		matTmp._41 += 0.0f;
		matTmp._42 += 3.5f;
		matTmp._43 += 0.0f;

		// 弾を出す処理
		matTmp = matTmp * m_matBase;
		pBulManage->AddBullet(0, matTmp, m_nNum);

		//----------------------------------
		//	弾の発射を示すデータの送信
		//----------------------------------

	}

	/* ロックオンしているときは目標の方向を向く */
	if(m_bNowLock)
	{

		/* 目標角度の計算 */
		vecTmp = GetLockVec() - GetPosBase();
		GetVec3Inverce(&vecTmp, &vecTmp);
		fNextYaw = (float)GetAngle(vecTmp.x, vecTmp.z);

		/* 360を超えたら修正 */
		if(fNextYaw >= 360.0f)			fNextYaw -= 360.0f;
		else if(fNextYaw < 0.0f)		fNextYaw += 360.0f;

		/* 現在角度を目標角度に近づける */

		/* 現在Yaw、目標Yawから１フレームごとの補間移動量を求める */
		float fTmp;
		fTmp = m_fCharaYaw - fNextYaw + 180.0f;

		/* 360を超えたら修正 */
		if(fTmp >= 360.0f)		fTmp -= 360.0f;
		else if(fTmp < 0.0f)	fTmp += 360.0f;

		/* 現在角度と目標角度が一定以内なら同じにする */
		if( fTmp <= 4.0f && fTmp >= -4.0f)
			m_fCharaYaw = fNextYaw + 180.0f;	

		/* 左回り（マイナス）の方が近い時 */
		else if(fTmp < 180.0f)
		{
			// 移動量の算出
			fMoveSpeed = fTmp / 10.0f;
			if(fMoveSpeed < 2.0f)	fMoveSpeed = 2.0f;
			// キャラ位置の移動
			m_fCharaYaw -= fMoveSpeed;
		}

		/* 右回り（プラス）の方が近い時 */
		else
		{
			// 移動量の算出
			fTmp = 360.0f - fTmp;
			fMoveSpeed = fTmp / 10.0f;
			if(fMoveSpeed < 2.0f)	fMoveSpeed = 2.0f;
			// キャラ位置の移動
			m_fCharaYaw += fMoveSpeed;
		}

		/* 360を超えたら修正*/
		if(m_fCharaYaw >= 360.0f)	m_fCharaYaw -= 360.0f;
		else if(m_fCharaYaw < 0.0f)	m_fCharaYaw += 360.0f;
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
void CMyPlayer::JumpStart(CStage* pStage, CEffectManage* pEffectManage)
{
	/* カウンターが続く間、ジャンプ開始行動が続く */
	if(m_nCnt>0)
	{
		/* モーションの変化 */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_S);

		// カウンターを減らしていく
		m_nCnt--;

		/* 地面を調べ、見つけた面が一定距離以下なら着地する */
		D3DXVECTOR3	vecTmp;
		if (SearchAllGround(pStage, NULL, &vecTmp) < HIT_GROUND)
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
		}

		/* 天井を調べ、天井が見つかったらジャンプ値をなくす */
		if (m_fJump > 0 && SearchAllCeiling(pStage, NULL, NULL) < HIT_CEILING)
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
void CMyPlayer::JumpMain(CStage* pStage)
{
	/* 左に旋回する */
	if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* 右に旋回する */
	else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* 前に移動する */
	if(GetAsyncKeyState(KEY_FORWARD) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
	{
		m_fSpeed = m_pParam->fJumpForward;

		/* 単位方向ベクトルの取得 */
		m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

		/* モーションの変化 */
		m_pActiveMotion->ChangeMotion(ANI_JUMP_F);
	}

	/* 後ろに移動する */
	else if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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

	/* エネルギーが1/3以上残っていたら */
	/* 飛び行動に移行する */
	if(GetAsyncKeyState(KEY_JUMP) & 0x8000 && m_nCnt < 0 && 
		(float)m_nNowEnergy/(float)m_pParam->nMaxEnergy > 0.35f)
	{
		m_nNowAction = 	FLYGHT;
	}

	/* 次に飛行できるまでのカウンターをデクリメント */
	m_nCnt--;

	/* だんだん地面に落ちる */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* エネルギーの回復 */
	if(m_nNowEnergy < m_pParam->nMaxEnergy)
		m_nNowEnergy+=REST_ENERGY;

	//------------------
	//	壁関係の処理
	//------------------
	/* 地面を調べ、見つけた面が一定距離（少し少なめ）以下なら着地する */
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
void CMyPlayer::JumpEnd()
{

}

//------------------------------------------------------------------
//	Name:	Flyght
//	Func:	飛んでいる行動
//	in:		CStage*			pStage		  = ステージクラス
//			CEffectManage*	pEffectManage = エフェクト管理クラス
//	Out:	無し
//------------------------------------------------------------------
void CMyPlayer::Flyght(CStage* pStage, CEffectManage* pEffectManage)
{
	/* 左に旋回する */
	if(GetAsyncKeyState(KEY_LEFT) & 0x8000)
	{
		m_fCharaYaw -= m_pParam->fTurn;
	}
	/* 右に旋回する */
	else if(GetAsyncKeyState(KEY_RIGHT) & 0x8000)
	{
		m_fCharaYaw += m_pParam->fTurn;
	}

	/* 前に移動する */
	if(GetAsyncKeyState(KEY_FORWARD) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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
	else if(GetAsyncKeyState(KEY_BACK) & 0x8000 &&
		!(GetAsyncKeyState(KEY_ANGLE_CONTROL)&0x8000) )
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

	/* ジャンプキーを離す、またエネルギーが無い場合は */
	/* カウント値を格納しジャンプに移行する */
	if(!(GetAsyncKeyState(KEY_JUMP) & 0x8000) || m_nNowEnergy <= 0)
	{
		m_nCnt = 20;
		m_nNowAction = 	JUMP_MAIN;
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
void CMyPlayer::DamageLand(CStage* pStage, CEffectManage* pEffectManage)
{
	/* 操作する事は一切出来ない */

	/* スピード値を減らしていく */
	m_fSpeed -= m_pParam->fBrakes;

	/* スピード値が０になったら元に戻る */
	if(m_fSpeed < 0)
	{
		m_nNowAction = WALK;
		/* 戻った後も少しの間無敵 */
		m_nDamageCnt = DAMAGE_CNT;
	}

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
void CMyPlayer::DamageAir(CStage* pStage, CEffectManage* pEffectManage)
{
	/* 操作する事は一切出来ない */

	/* スピード値を減らしていく */
	m_fSpeed -= m_pParam->fBrakes;

	/* だんだん地面に落ちる */
	if((m_fJump -= m_pParam->fJumpDown) < -3.0f)	m_fJump = -3.0f;

	/* スピード値が０になったら元に戻る */
	if(m_fSpeed < 0)
	{
		m_nNowAction = JUMP_MAIN;
		/* 戻った後も少しの間無敵 */
		m_nDamageCnt = DAMAGE_CNT;
	}

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
void CMyPlayer::DeadLand(CStage* pStage, CEffectManage* pEffectManage )
{
	/* 操作する事は一切出来ない */

	/* スピード値を減らしていく */
	m_fSpeed -= m_pParam->fBrakes;
	if(m_fSpeed < 0)	m_fSpeed = 0;

	/* エンターを押すと生き返る */
	if(GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		pEffectManage->AddEffect(REVIVAL, m_matBase);
		m_nNowLife = m_pParam->nMaxLife;
		m_fJump = 0.5f;
		m_nNowAction = JUMP_MAIN;
	}

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
void CMyPlayer::DeadAir(CStage* pStage, CEffectManage* pEffectManage)
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

//----------------------------------------------
//	Name:	LockOn
//	Func:	ロックオンに関する記述
//	in:		CStage* pStage = ステージクラス
//	Out:	無し
//----------------------------------------------
void CMyPlayer::LockOn(CStage* pStage)
{
	int i;

	/* ロックオン許可フラグの更新 */
	IsLockON(pStage);

	/* 全てに対して行う処理 */
	for(i=0; i<3; i++)
	{
		/* ロックオンマーカーの画面に表示する位置を設定する */
		m_pLockMarker[i]->SetVec(D3DXVECTOR2(m_vecProject[i].x, m_vecProject[i].y));

		/* キャラクター名前フォントを画面に表示する位置を設定する */
		m_pCharaName[i]->SetRec((int)m_vecProject[i].x - 64,(int)m_vecProject[i].y - 80,
								(int)m_vecProject[i].x + 64,(int)m_vecProject[i].y - 50);

		/* キャラクターライフフォントを画面に表示する位置を設定する */
		m_pCharaLife[i]->SetRec((int)m_vecProject[i].x - 64,(int)m_vecProject[i].y - 60,
								(int)m_vecProject[i].x + 64,(int)m_vecProject[i].y - 30);

		/* ロックオンの行動を更新する */
		if(!m_bCanLock[i])			m_pLockMarker[i]->SetStatus(NOT_LOCK);	// ロックオン出来ないならNOT_LOCKで
		else if(m_nLockTarget != i)	m_pLockMarker[i]->SetStatus(CAN_LOCK);	// ロックオン出来るけどターゲットじゃないならCAN_LOCKで
		else if(!m_bNowLock)		m_pLockMarker[i]->SetStatus(TAG_LOCK);	// ターゲットだけどロックオンしていない時はTAG_LOCKで
		else						m_pLockMarker[i]->SetStatus(NOW_LOCK);	// 全てクリアしたらNOW_LOCKです

		/* 毎フレームの処理 */
		m_pLockMarker[i]->FrameMove();
	}

	/* ロックオンをしている時の入力処理*/
	if(m_bNowLock){
		/* スペースを押すとロック解除 */
		if(GetAsyncKeyState(KEY_LOCK) & 0x0001)
			m_bNowLock = false;

		/* 現在の対象がロックオン不可になった時 */
		if(!m_bCanLock[m_nLockTarget])
			m_bNowLock = false;
	}

	/* ロックオンしていない時の入力処理 */
	else{
		/* ターゲットとなるキャラクタを選ぶ */
		SelectTarget();

		/* スペースを押し、可能であればロックオンする */
		if(GetAsyncKeyState(KEY_LOCK) & 0x0001 && m_nLockTarget != -1)
		{
			m_bNowLock = true;
			m_fCharaPitch = 0;
		}
	}
}


//----------------------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CMyPlayer::Render()
{

	for(int i=0; i<3; i++)
	{
		if(m_bCanLock[i]){
			/* ロックオンマーカーの描画 */
			m_pLockMarker[i]->Render();	
			/* キャラクター名の描画 */
			m_pCharaName[i]->Render();
			/* キャラクターライフの描画 */
			m_pCharaLife[i]->Render();
		}
	}

	/* キャラクタの描画 */
	CChara::Render();
}

//----------------------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CMyPlayer::UpDate()
{
	CChara::UpDate();


	for(int i=0; i<3; i++)
	{
		/* ロックオンマーカーの更新 */
		m_pLockMarker[i]->UpDate();	
		/* キャラクターネームの更新 */
		m_pCharaName[i]->UpDate();
		/* キャラクターライフの更新 */
		m_pCharaLife[i]->UpDate();

	}
}

//--------------------------------------------------
//	Name:	ComputProject
//	Func:	全ての敵キャラ座標を、プロジェクション投影する
//	in:		なし
//	Out:	なし
//--------------------------------------------------
void CMyPlayer::ComputProject()
{
	D3DXVECTOR3	vecTmp;
	vecTmp*=0;

	/* 全ての敵の座標値をプロジェクション投影する */
	for(int i=0; i<3; i++)
	{
		/* データがない時は次のデータへ */
		if(!m_tagEnemyData[i].pMatrix)	continue;

		/* 敵の座標値をベクトルに変換する */
		vecTmp.x = m_tagEnemyData[i].pMatrix->_41;
		vecTmp.y = m_tagEnemyData[i].pMatrix->_42;
		vecTmp.z = m_tagEnemyData[i].pMatrix->_43;

		/* プロジェクションに投影する */
		TransProject(m_pd3dDevice, &vecTmp, &vecTmp);
		m_vecProject[i].x = vecTmp.x;
		m_vecProject[i].y = vecTmp.y;
	}
}

//--------------------------------------------------
//	Name:	ComputView
//	Func:	全ての敵キャラ座標を、ビュー変換する
//	in:		なし
//	Out:	なし
//--------------------------------------------------
void CMyPlayer::ComputView()
{
	D3DXVECTOR3	vecTmp;	vecTmp*=0;
	D3DXMATRIX	matView;

	/* ビューマトリクスの取得 */
	m_pd3dDevice->GetTransform( D3DTS_VIEW, &matView );

	/* 全ての敵の座標値をプロジェクション投影する */
	for(int i=0; i<3; i++)
	{
		/* データがない時は次のデータへ */
		if(!m_tagEnemyData[i].pMatrix)	continue;

		/* 敵の座標値をベクトルに変換する */
		vecTmp.x = m_tagEnemyData[i].pMatrix->_41;
		vecTmp.y = m_tagEnemyData[i].pMatrix->_42;
		vecTmp.z = m_tagEnemyData[i].pMatrix->_43;

		/* ビュー座標系に変換する */
		D3DXVec3TransformCoord(&m_vecView[i], &vecTmp, &matView);
	}
}

//--------------------------------------------------
//	Name:	IsLockOn
//	Func:	ロックオンできるかどうかを調べる
//	in:		CStage* pStage = ステージクラス
//	Out:	なし
//--------------------------------------------------
void CMyPlayer::IsLockON(CStage* pStage)
{
	RECT		rcTmp;
	D3DXVECTOR3	vecTmp, vecTmp2;
	int i;

	/* キャラクタのプロジェクション座標の算出 */
	ComputProject();

	/* キャラクタのビュー座標の算出 */
	ComputView();

	/* 判定領域の設定 */
	SetRect(&rcTmp, 80, 80, 520, 400);

	/* ロックオンフラグ初期化 */
	for(i=0; i<3; i++)	m_bCanLock[i] = false;

	/* 全ての座標値に対して判定 */
	for(i=0; i<3; i++)
	{
		/* データがなければ当然ダメ */
		if(!D3DXVec2LengthSq(&m_vecProject[i]))	continue;

		/* 対象がカメラより前にいなければダメ */
		if(!(m_vecView[i].z > 0))
			continue;

		/* プロジェクション座標値が領域の中になければダメ */
		if(!(m_vecProject[i].x > rcTmp.left  && m_vecProject[i].x < rcTmp.right &&
			 m_vecProject[i].y > rcTmp.top   && m_vecProject[i].y < rcTmp.bottom  ) )
			continue;

		/* 自分との距離が一定以内でないとダメ */
		vecTmp.x = m_tagEnemyData[i].pMatrix->_41;
		vecTmp.y = m_tagEnemyData[i].pMatrix->_42;
		vecTmp.z = m_tagEnemyData[i].pMatrix->_43;
		vecTmp2 = CChara::GetPosBase() - vecTmp;
		if (D3DXVec3LengthSq(&vecTmp2) >
			(m_pParam->fLockLength * m_pParam->fLockLength))
			continue;

		/* 二つの座標間に面が見つかったらダメ */
		if(SearchAllPlane(pStage, CChara::GetPosBase(), vecTmp))
		{
			m_bCanLock[i] = false;
			continue;
		}

		/* ロックオンが可能とみなす */
		m_bCanLock[i] = true;
	}
}

//--------------------------------------------------------------
//	Name:	SelectTarget
//	Func:	ロックオンできるキャラクタの中から、
//			画面の中心に一番近いものを探して、ターゲットとする
//	in:		なし
//	Out:	なし
//--------------------------------------------------------------
void CMyPlayer::SelectTarget()
{
	float		fLen;
	float		fLenMin = 99999;
	int			nAdop = -1;

	D3DXVECTOR2	vecTmp;

	for(int i=0; i<3; i++)
	{
		/* ロックオンができないのなら除外 */
		if(!m_bCanLock[i])	continue;

		/* 画面の中心点からの距離を求める */
		vecTmp = D3DXVECTOR2(320, 240) - m_vecProject[i];
		fLen = D3DXVec2LengthSq(&vecTmp);

		/* 調べた長さが一番小さかったら採用 */
		if(fLen < fLenMin)
		{
			fLenMin = fLen;
			nAdop	= i;
		}
	}

	/* 結果をメンバに格納する */
	m_nLockTarget = nAdop;

}

//----------------------------------------------------------
//	Name:	CreateCharaName
//	Func:	キャラクタの名前フォントの作成
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CMyPlayer::CreateCharaName()
{
	for(int i=0; i<3; i++)
	{
		m_pCharaName[i] = new CFont(m_pd3dDevice, const_cast<TCHAR*>("ＭＳ ゴシック"));
		m_pCharaName[i]->SetString(m_tagEnemyData[i].Name);
		m_pCharaName[i]->SetFormat(DT_CENTER);
		m_pCharaName[i]->SetColor(0, 255, 0);
	}
}

//----------------------------------------------------------
//	Name:	CreateCharaName
//	Func:	キャラクタの名前フォントの作成
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CMyPlayer::CreateCharaLife()
{
	for(int i=0; i<3; i++)
	{
		m_pCharaLife[i] = new CFont(m_pd3dDevice, const_cast<TCHAR*>("ＭＳ ゴシック"));
		m_pCharaLife[i]->SetString(*m_tagEnemyData[i].pNowLife);
		m_pCharaLife[i]->SetFormat(DT_CENTER);
		m_pCharaLife[i]->SetColor(0, 255, 0);
	}
}