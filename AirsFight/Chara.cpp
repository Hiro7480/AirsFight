//==========================================================
// Chara.cpp
// Auther : 桜井 博之
// Data   : 2002/01/10
//==========================================================
#include "Chara.h"

//------------------------------------------------------
//	Name:	CChara
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3Dデバイス
//	Out:	なし
//------------------------------------------------------
CChara::CChara(LPDIRECT3DDEVICE8 d3dDevice) :C3DGraphicObj(d3dDevice)
{
	/* 各変数の初期化 */
	m_pActiveMotion = NULL;
	m_pParam = NULL;

	m_vecMove *= 0;
	m_fSpeed = 0;
	m_fCharaYaw = 0;
	m_fCharaPitch = 0;
	m_fJump = 0;

	m_nDamageCnt = 0;

	m_nNowLife = 0;
	m_nNowEnergy = 0;
	m_nDeadNum = 0;

	/* 敵キャラデータの初期化 */
	for(int i=0; i<4; i++)
	{
		m_tagEnemyData[i].pMatrix = NULL;
		strcpy(m_tagEnemyData[i].Name, "Default");
	}
}

//----------------------------------------------
//	Name:	~CChara
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CChara::~CChara()
{

}
//--------------------------------------------------
//	Name:	FrameMoveStart
//	Func:	ゲーム開始時の毎フレームの処理
//	in:		なし
//	Out:	なし
//--------------------------------------------------
void CChara::FrameMoveStart()
{
	/* モーションのさまざまな更新 */
	m_pActiveMotion->Play();
}

//--------------------------------------------------
//	Name:	FrameMoveEnd
//	Func:	ゲーム終了時の毎フレームの処理
//	in:		なし
//	Out:	なし
//--------------------------------------------------
void CChara::FrameMoveEnd()
{
	/* 何もしない */
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CChara::Render()
{
	D3DXMATRIX	matView;
	D3DXVECTOR3	vecTmp;

	/* ビューマトリクスの取得 */
	m_pd3dDevice->GetTransform( D3DTS_VIEW, &matView );

	/* 現在の座標値をビュー座標系に変換する */
	D3DXVec3TransformCoord(&vecTmp, &CChara::GetPosBase(), &matView);

	/* キャラクタがカメラの後ろにいたら描画しない！ */
	if(vecTmp.z < 0)	return;

	/* キャラクタの描画 */
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matStock );
	m_pActiveMotion->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	描画用マトリクス更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CChara::UpDate()
{
	C3DGraphicObj::UpDate();

	/* アクティブモーションの更新 */
	m_pActiveMotion->UpDate();
}

//----------------------------------------------------------
//	Name:	CreateActive
//	Func:	アクティブモーションの作成
//	in:		CMotionData* pMotionData[] = モーションデータ配列
//	Out:	HRESULT
//----------------------------------------------------------
HRESULT CChara::CreateActive(CMotionData* pMotionData[])
{
	/* アクティブモーションをメモリに確保 */
	m_pActiveMotion = new CActiveMotion;

	/* メッシュデータの読み込み */
	m_pActiveMotion->LoadMesh(m_pParam->pMeshData);

	/* モーションデータの読み込み */
	m_pActiveMotion->LoadMotion(pMotionData[ANI_STOP]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_FORWARD]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_BACK]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DASH_F]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DASH_B]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DASH_R]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DASH_L]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_ATAS]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_ATA]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_N]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_F]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_B]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_S]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_JUMP_E]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DAM_L]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DAM_A]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DEAD_L]);
	m_pActiveMotion->LoadMotion(pMotionData[ANI_DEAD_A]);

	return S_OK;
}

//--------------------------------------------------------------
//	Name:	AllInit
//	Func:	キャラクタの初期化全般
//	in:		D3DXVECTOR3	vecIn		= オブジェクトの位置
//			float		fCharaYaw	= キャラクタのYaw回転角度
//	Out:	なし
//--------------------------------------------------------------
void CChara::AllInit(D3DXVECTOR3 vecPos, float fCharaYaw)
{
	D3DXMATRIX matTmp;
	D3DXMatrixIdentity(&matTmp);

	/* 指定した座標値に平行移動させる */
	matTmp._41 = vecPos.x;
	matTmp._42 = vecPos.y;
	matTmp._43 = vecPos.z;

	/* マトリクスのセット */
	m_matBase = matTmp;

	/* キャラYaw角度値のセット */
	m_fCharaYaw = fCharaYaw;

	/* LIFE値とエネルギーの初期化 */
	m_nNowLife   = m_pParam->nMaxLife;
	m_nNowEnergy = m_pParam->nMaxEnergy;
}

//--------------------------------------------------
//	Name:	IsHitBullet
//	Func:	弾との当たり判定
//	in:		CBulManage*		pBulManage		= 弾管理クラス
//			CEffectManage*	pEffectManage	= エフェクト管理クラス
//	Out:	なし
//--------------------------------------------------
void CChara::IsHitBullet(CBulManage* pBulManage,
						 CEffectManage* pEffectManage)
{
	/* 自分がダメージ中であれば、あたり判定を行わない */
	if(m_nNowAction == DAMAGE_LAND || m_nNowAction == DAMAGE_AIR)
		return;

	/* 無敵時間であっても当たり判定を行わない */
	else if(m_nDamageCnt > 0)
		return;

	D3DXVECTOR3	vecBulPos;	// 弾の位置を示す

	/* リストの最初の弾を取得 */
	CBullet* pBullet = pBulManage->GetListTop();;

	/* リストの最後まであたり判定を繰り返す */
	while(pBullet)
	{
		vecBulPos = pBullet->GetPosBase();	// 弾の位置の取得

		/* 弾が発生してから１フレーム以上たっている事、 */
		/* キャラクタとの距離が一定以内である事の場合、当たったとみなす */
		if(	pBullet->GetTimeCount() > 1 &&
			D3DXVec3LengthSq( &(C3DGraphicObj::GetPosBase() - vecBulPos) ) < (HIT_CHARA_LENGTH * HIT_CHARA_LENGTH) ) 
			break;

		/* 次の弾を調べる */
		pBullet = pBullet->GetNext();
	}

	/* どの弾とも当たらなかった場合は終了する */
	if(pBullet == NULL)	return;

	/* 弾が当たった時の処理 */
	// この辺は武器によって変える（予定）

	int nDamage;						// ダメージ値の格納
	srand((unsigned int)time(NULL));
	nDamage = rand()%500 + 500;
	m_nNowLife  -= nDamage;

	pBullet->Delete();					// 弾を消す

	m_vecMove = pBullet->GetMoveVec();	// 移動方向ベクトルの格納

	/* 弾の方向ベクトルから移動方向角度を求める */
	m_fMoveYaw = (float)GetAngle((double)pBullet->GetMoveVec().x, (double)pBullet->GetMoveVec().z);

	m_fSpeed = 1.5f;					// スピード値の格納	
	m_fJump += 0.2f;					// ジャンプ値の格納

	D3DXMATRIX matTmp;
	/* 死亡判定 */
	if(IsDead())
	{
		/* ライフを0にしとく */
		m_nNowLife = 0;

		/* 死んだ回数を一つ増やす */
		m_nDeadNum++;

		/* 死ぬと空中死亡状態に移行し、エフェクトを三つ発生 */
		for(int i=0; i<3; i++)
		{
			matTmp = m_matBase;
			matTmp._41 += (float)(rand()%10-5) / 1.0f;
			matTmp._42 += (float)(rand()%10-5) / 1.0f;
			matTmp._43 += (float)(rand()%10-5) / 1.0f;

			pEffectManage->AddEffect(EXPLOSION_B, matTmp);
		}
		m_nNowAction = DEAD_AIR;
	}
	else
	{
		/* 死ななければ空中ダメージ状態に移行し、エフェクトをひとつ発生 */
		pEffectManage->AddEffect(EXPLOSION_B, m_matBase);
		m_nNowAction = DAMAGE_AIR;
	}
}

//--------------------------------------------------
//	Name:	IsDead
//	Func:	死亡判定
//	in:		なし
//	Out:	bool = 死んでいるならTrue
//--------------------------------------------------
bool CChara::IsDead()
{
	/* こんな関数作って意味があるのかどうかは疑問 */
	if(m_nNowLife <= 0)	return true;
	return false;
}

//----------------------------------------------
//	Name:	GetVecToPlane
//	Func:	地面の面の式とキャラクタの回転角度から
//			キャラクタの単位方向ベクトルを求める
//			地面が坂道になっていてそれを上るときに使用
//
//	in:		D3DXPLANE	plaGround = 指定地面
//			float		fYaw      = 指定回転角度
//	Out:	D3DXVECTOR3*
//----------------------------------------------
D3DXVECTOR3 CChara::GetVecToPlane(D3DXPLANE* plaGround, float fYaw)
{
	D3DXVECTOR3	vec3X,vec3Y,vec3Z;
	D3DXVECTOR3	vecAdop;
	D3DXMATRIX	matTmp;

	// 面に垂直なＹ軸回転をしたマトリックスを作成し
	// 移動ベクトルを作成する
	// Ｙ成分を設定
	vec3Y.x = plaGround->a;
	vec3Y.y = plaGround->b;
	vec3Y.z = plaGround->c;

	// Ｚ成分を設定
	vec3Z.x = (float)sin( D3DXToRadian(fYaw) );
	vec3Z.y = 0;
	vec3Z.z = (float)cos( D3DXToRadian(fYaw) );

	// Ｘ成分をもとめる
	D3DXVec3Cross(&vec3X, &vec3Y, &vec3Z);
	D3DXVec3Normalize(&vec3X, &vec3X);
	// Ｚ成分をもとめる
	D3DXVec3Cross(&vec3Z, &vec3X, &vec3Y);
	D3DXVec3Normalize(&vec3Z, &vec3Z);

	// マトリックスの単位行列化
	D3DXMatrixIdentity(&matTmp);

	// 各成分をマトリックスに反映する
	matTmp._11 = vec3X.x;	matTmp._12 = vec3X.y;	matTmp._13 = vec3X.z;
	matTmp._21 = vec3Y.x;	matTmp._22 = vec3Y.y;	matTmp._23 = vec3Y.z;
	matTmp._31 = vec3Z.x;	matTmp._32 = vec3Z.y;	matTmp._33 = vec3Z.z;

	// ようやく単位方向ベクトルの取得！
	D3DXVec3TransformNormal(&vecAdop, &D3DXVECTOR3(0, 0, 1), &matTmp);

	return vecAdop;

}

//----------------------------------------------------------
//	Name:	SearchAllGround
//	Func:	全てのオブジェクトの地面を調べ、
//			一番距離の短い面の式、交点、距離を求める
//	in:		CStage*			pStage = ステージクラスへのポインタ
//			D3DXPLANE*		plaOut = 出力用面の式
//			D3DXVECTOR3*	vecOut = 出力用面との交点
//	Out:	float				   = 面との距離
//----------------------------------------------------------
float CChara::SearchAllGround(CStage* pStage, D3DXPLANE* plaOut, D3DXVECTOR3* vecOut)
{
	float		fLenAdop,fLen;
	D3DXPLANE	plaTmp,plaAdop;
	D3DXVECTOR3	vecCrossAdop,vecCross;
	float		fTmp1, fTmp2;
	int			i;

	fLenAdop = 99999;


	/* ブロックタイプのオブジェクトを調べる */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		/* キャラクタとオブジェクトが離れていたら調べない */
		fTmp1 = D3DXVec3LengthSq(&( pStage->GetBlockObj(i)->GetPosBase() - GetPosBase()) );
		fTmp2 = (pStage->GetBlockObj(i)->GetLength() + 5.0f) * (pStage->GetBlockObj(i)->GetLength()+ 5.0f);

		if(fTmp1 < fTmp2)
		{
			if( SearchPlane(pStage->GetBlockObj(i)->GetMesh(), &pStage->GetBlockObj(i)->GetMatBase(),
						&GetPosBase(),&D3DXVECTOR3(0,-1,0), &vecCross, &plaTmp, &fLen))
			{
				if(fLenAdop > fLen)
				{
					/* 調べたすべてのオブジェクトの中で一番距離が短い面を採用 */
					fLenAdop = fLen;
					plaAdop	 = plaTmp;
					vecCrossAdop = vecCross;
				}
			}
		}
	}

	/* ウォールタイプのオブジェクトを調べる */
	for(i=0; i<pStage->GetWallNum(); i++)
	{
		if( SearchPlane(pStage->GetWallObj(i)->GetMesh(), &pStage->GetWallObj(i)->GetMatBase(),
					&GetPosBase(),&D3DXVECTOR3(0,-1,0), &vecCross, &plaTmp, &fLen))
		{
			if(fLenAdop > fLen)
			{
				/* 調べたすべてのオブジェクトの中で一番距離が短い面を採用 */
				fLenAdop = fLen;
				plaAdop	 = plaTmp;
				vecCrossAdop = vecCross;
			}
		}
	}


	/* 地面が見つかった場合、その距離と面の式を返す */
	if(fLenAdop < 99999)
	{
		if(plaOut)	*plaOut = plaAdop;
		if(vecOut)	*vecOut = vecCrossAdop;
		return	fLenAdop;
	}

	return 99999;
}

//--------------------------------------------------------------------------
//	Name:	SearchAllWall
//	Func:	全てのオブジェクトの壁を調べて、一番距離の短い面を採用、
//			その面とキャラの移動ベクトルとの交点、面の逆法線ベクトルとの交点、
//			逆法線ベクトル交点とキャラとの距離を求める
//	in:		CStage*			pStage	= ステージクラスへのポインタ
//			D3DXVECTOR3*	vecOut1	= 面の逆法線ベクトルとの交点
//			D3DXVECTOR3*	vecOut2	= キャラの移動ベクトルとの交点
//	Out:	float					= 面との距離
//--------------------------------------------------------------------------
float CChara::SearchAllWall(CStage* pStage, D3DXVECTOR3* vecOut1, D3DXVECTOR3* vecOut2)
{
	float		fLenAdop,fLen;
	D3DXVECTOR3	vecCrossAdop1,vecCross1;
	D3DXVECTOR3	vecCrossAdop2,vecCross2;
	float		fTmp1, fTmp2;
	int			i;

	fLenAdop = 99999;

	/* ブロックタイプのオブジェクトを調べる */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		/* キャラクタとオブジェクトが離れていたら調べない */
		fTmp1 = D3DXVec3LengthSq(&( pStage->GetBlockObj(i)->GetPosBase() - GetPosBase()) );
		fTmp2 = (pStage->GetBlockObj(i)->GetLength()) * (pStage->GetBlockObj(i)->GetLength());

		if(fTmp1 < fTmp2)
		{
			if( SearchPlane2(pStage->GetBlockObj(i)->GetMesh(), &pStage->GetBlockObj(i)->GetMatBase(),
					&GetPosBase(), &m_vecMove, &vecCross1, &vecCross2, NULL, &fLen))
			{
				if(fLenAdop > fLen)
				{
					/* 調べたすべてのオブジェクトの中で一番距離が短い面を採用 */
					fLenAdop = fLen;
					vecCrossAdop1 = vecCross1;
					vecCrossAdop2 = vecCross2;
				}
			}
		}
	}

	/* ウォールタイプのオブジェクトを調べる */
	for(i=0; i<pStage->GetWallNum(); i++)
	{
		if( SearchPlane2(pStage->GetWallObj(i)->GetMesh(), &pStage->GetWallObj(i)->GetMatBase(),
				&GetPosBase(), &m_vecMove, &vecCross1, &vecCross2, NULL, &fLen))
		{
			if(fLenAdop > fLen)
			{
				/* 調べたすべてのオブジェクトの中で一番距離が短い面を採用 */
				fLenAdop = fLen;
				vecCrossAdop1 = vecCross1;
				vecCrossAdop2 = vecCross2;
			}
		}
	}

	/* 地面が見つかった場合、その距離と面の式を返す */
	if(fLenAdop < 99999)
	{
		if(vecOut1)	*vecOut1 = vecCrossAdop1;
		if(vecOut2)	*vecOut2 = vecCrossAdop2;
		return	fLenAdop;
	}
	/* 見つからなかった時は、99999を返す */
	return 99999;
}

//----------------------------------------------------------
//	Name:	SearchAllCeiling
//	Func:	全オブジェクトの天井を調べ、
//			一番距離の短い面の式、交点、距離を求める
//	in:		CStage*			pStage = ステージクラスへのポインタ
//			D3DXPLANE*		plaOut = 出力用面の式
//			D3DXVECTOR3*	vecOut = 出力用面との交点
//	Out:	float				   = 面との距離
//----------------------------------------------------------
float CChara::SearchAllCeiling(CStage* pStage, D3DXPLANE* plaOut, D3DXVECTOR3* vecOut)
{
	float		fLenAdop,fLen;
	D3DXPLANE	plaTmp,plaAdop;
	D3DXVECTOR3	vecCrossAdop,vecCross;
	D3DXVECTOR3	vecMove;
	float		fTmp1, fTmp2;
	int			i;

	fLenAdop = 99999;

	/* キャラクタの移動ベクトルにジャンプ値をいれた移動ベクトルを算出 */
	vecMove = m_vecMove;
	vecMove *= m_fSpeed;
	vecMove.y = m_fJump;
	D3DXVec3Normalize(&vecMove, &vecMove);

	/* ブロックタイプのオブジェクトを調べる */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		/* キャラクタとオブジェクトが離れていたら調べない */
		fTmp1 = D3DXVec3LengthSq(&( pStage->GetBlockObj(i)->GetPosBase() - GetPosBase()) );
		fTmp2 = (pStage->GetBlockObj(i)->GetLength()) * (pStage->GetBlockObj(i)->GetLength());

		if(fTmp1 < fTmp2)
		{
			if( SearchPlane(pStage->GetBlockObj(i)->GetMesh(), &pStage->GetBlockObj(i)->GetMatBase(),
						&GetPosBase(),&vecMove, &vecCross, &plaTmp, &fLen))
			{
				if(fLenAdop > fLen)
				{
					/* 調べたすべてのオブジェクトの中で一番距離が短い面を採用 */
					fLenAdop = fLen;
					plaAdop	 = plaTmp;
					vecCrossAdop = vecCross;
				}
			}
		}
	}

	/* ウォールタイプのオブジェクトを調べる */
	for(i=0; i<pStage->GetWallNum(); i++)
	{
		if( SearchPlane(pStage->GetWallObj(i)->GetMesh(), &pStage->GetWallObj(i)->GetMatBase(),
					&GetPosBase(),&vecMove, &vecCross, &plaTmp, &fLen))
		{
			if(fLenAdop > fLen)
			{
				/* 調べたすべてのオブジェクトの中で一番距離が短い面を採用 */
				fLenAdop = fLen;
				plaAdop	 = plaTmp;
				vecCrossAdop = vecCross;
			}
		}
	}


	/* 地面が見つかった場合、その距離と面の式を返す */
	if(fLenAdop < 99999)
	{
		if(plaOut)	*plaOut = plaAdop;
		if(vecOut)	*vecOut = vecCrossAdop;
		return	fLenAdop;
	}
	return 99999;
}

//--------------------------------------------------------------
//	Name:	SearchAllPlane
//	Func:	二つの座標値を線で結んだ場合、その間に面があるか
//			無いかを判定する
//	in:		CStage*		pStage = ステージクラスへのポインタ
//			D3DXVECTOR3	vecPos1 = 座標値１
//			D3DXVECTOR3	vecPos2 = 座標値２	
//	Out:	bool
//--------------------------------------------------------------
bool CChara::SearchAllPlane(CStage* pStage, D3DXVECTOR3 vecPos1, D3DXVECTOR3 vecPos2)
{
	float		fLen;
	D3DXVECTOR3	vecCross;
	int			i;

	/* ブロックタイプのオブジェクトを調べる */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		if( SearchPlane(pStage->GetBlockObj(i)->GetMesh(), 
					&pStage->GetBlockObj(i)->GetMatBase(),
					&vecPos1, &(vecPos2-vecPos1), &vecCross, NULL, &fLen))
		{
			/* 面が見つかったら、その交点から */
			/* 指定ベクトルの間に見つかったかどうかを判定する */
			if( D3DXVec3LengthSq(&(vecPos2-vecPos1)) > D3DXVec3LengthSq(&(vecCross-vecPos1)) )
			{
				/* 面が見つかったとみなす */
				return true;
			}
		}
	}

	return false;
}