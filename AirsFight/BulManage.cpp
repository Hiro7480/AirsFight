//==========================================================
// CBullet.cpp
// Auther : 桜井 博之
// Data   : 2002/01/11
//==========================================================

#include "BulManage.h"

//----------------------------------------------
//	Name:	CBulManage
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 = D3Dデバイス
//	Out:	なし
//----------------------------------------------
CBulManage::CBulManage(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* デバイスのセット */
	m_pd3dDevice = d3dDevice;

	/* 最初のポインタをNULLに */
	m_pListTop = NULL;

	/* 弾パラメータの作成 */
	m_tagParam[0].pBulMesh = new CMeshObject(m_pd3dDevice);
	m_tagParam[0].pBulMesh->Create(const_cast<TCHAR*>("data\\Bullet\\Bullet.X"));
	m_tagParam[0].pBulMesh->RestoreDeviceObjects();

	m_tagParam[0].fSpeed = 3.0f;
	m_tagParam[0].nMaxLife = 120;
	m_tagParam[0].nShotFrame = 5;

	/* 使わないところにはNULLを */
	m_tagParam[1].pBulMesh = NULL;
	m_tagParam[2].pBulMesh = NULL;

	/* クリティカルセクション初期化 */
	InitializeCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	~CBullet
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CBulManage::~CBulManage()
{
	/* リストのデータを全て削除 */
	CBullet *pCurrent = m_pListTop;
	CBullet *pNext = NULL;

	while(pCurrent) {
		pNext = pCurrent->GetNext();
		delete pCurrent;
		pCurrent = pNext;
	}

	/* メッシュデータの解放 */
	for(int i=0; i<3; i++)
		SAFE_DELETE(m_tagParam[i].pBulMesh);

	/* クリティカルセクションを終了させる */
	DeleteCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	AddBullet
//	Func:	弾の追加
//	in:		int			nType		= 弾のタイプ
//			D3DXMATRIX	matBase		= 初期マトリクス
//			int			nCharaNum	= キャラクタ番号
//	Out:	なし
//----------------------------------------------
void CBulManage::AddBullet(int nType, D3DXMATRIX matBase, int nCharaNum)
{
	/* ID番号 */
	static long	lID = 0;

	CBullet*	pCurrent = m_pListTop;
	CBullet*	pBack	 = NULL;

	/* クリティカルセクションに入る */
	EnterCriticalSection(&m_cs);

	/* 追加する位置を探す */
	while(pCurrent != NULL)
	{
		pBack = pCurrent;
		pCurrent = pCurrent->GetNext();
	}
	/* 追加位置が見つかったらそこに作成する */
	pCurrent = new CBullet(m_pd3dDevice, &m_tagParam[nType], matBase, lID);

	/* データをつなげる */
	if(pBack)	pBack->SetNext(pCurrent);
	else		m_pListTop = pCurrent;

	/* クリティカルセクションから出る */
	LeaveCriticalSection(&m_cs);

	lID ++;
}

//----------------------------------------------
//	Name:	SubBullet
//	Func:	弾の削除
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CBulManage::SubBullet()
{
	CBullet* pCurrent = m_pListTop;	// 現在調べている位置
	CBullet* pBack = NULL;			// 現在調べているデータの１つ前のデータ
	CBullet* pNext;

	/* クリティカルセクションに入る */
	EnterCriticalSection(&m_cs);

	// リスト構造の最後まで検索
	while(pCurrent != NULL){
		if(pCurrent->IsDelete()){
			// オブジェクトをリスト構造から削除
			pNext = pCurrent->GetNext();
			delete pCurrent;

			if (pBack == NULL) {
				// 前のデータが無い（現在調べているデータが、リストの先頭のデータの時
				m_pListTop = pNext;
				pCurrent = pNext;
			}
			else {
				// リストの途中のデータの時
				pCurrent = pNext;			// 調べる位置を次のデータにする
				pBack->SetNext(pCurrent);	// 消したデータ分、リストを詰める
			}
		}
		else {
			// 現在のデータが、消す必要が無い時
			pBack = pCurrent;
			pCurrent = pCurrent->GetNext();
		}
	}

	/* クリティカルセクションから出る */
	LeaveCriticalSection(&m_cs);

}

//------------------------------------------------------
//	Name:	FrameMove
//	Func:	全ての弾の毎フレームの処理
//	in:		CStage* pStage = ステージクラスへのポインタ
//			CEffectManage*	pEffectManage	= エフェクト管理クラスポインタ
//	Out:	なし
//------------------------------------------------------
void CBulManage::FrameMove(CStage* pStage, CEffectManage* pEffectManage)
{
	CBullet*	pNext = m_pListTop;

	/* リスト構造の最後まで繰り返す */
	while(pNext != NULL){
		pNext->FrameMove(pEffectManage);
		pNext = pNext->GetNext();
	}

	/* 弾の壁とのあたり判定 */
	HitPlane(pStage, pEffectManage);

	/* 弾の削除 */
	SubBullet();
}

//------------------------------------------------------
//	Name:	SearchBullet
//	Func:	識別番号から弾を捜す
//	in:		long lID = 指定識別番号
//	Out:	なし
//------------------------------------------------------
CBullet* CBulManage::SearchBullet(long lID)
{
	CBullet*	pNext = m_pListTop;
	long		IDTmp;

	/* リスト構造の最後まで繰り返す */
	while(pNext != NULL){
		IDTmp = pNext->GetID();

		/* 指定IDとあっていたら成功 */
		if(IDTmp == lID)
			return pNext;

		/* あっていなかったら次の弾を調べる */
		else
			pNext = pNext->GetNext();
	}

	/* 全ての弾になければNULLを返す */
	return NULL;
}

//------------------------------------------------------
//	Name:	HitPlane
//	Func:	すべての弾の壁との当たり判定
//	in:		CStage* pStage = ステージクラスへのポインタ
//			CEffectManage*	pEffectManage	= エフェクト管理クラスポインタ
//	Out:	なし
//------------------------------------------------------
void CBulManage::HitPlane(CStage* pStage, CEffectManage* pEffectManage)
{
	CBullet*	pNext = m_pListTop;

	/* リスト構造の最後まで繰り返す */
	while(pNext != NULL)
	{
		// 弾の位置と壁とを検索し、一定距離以内なら弾を消す
		if(SearchAllPlane(pStage, pNext->GetPosBase(), pNext->GetMoveVec()) < HIT_WALL_LENGTH)
		{
			pNext->Delete();
			pEffectManage->AddEffect(EXPLOSION_B, pNext->GetMatBase());
		}
		pNext = pNext->GetNext();
	}
}

//----------------------------------------------
//	Name:	Render
//	Func:	全ての弾の描画
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CBulManage::Render()
{
	CBullet*	pNext = m_pListTop;

	/* クリティカルセクションに入る */
	EnterCriticalSection(&m_cs);

	/* リスト構造の最後まで繰り返す */
	while(pNext != NULL){
		pNext->Render();
		pNext = pNext->GetNext();
	}

	/* クリティカルセクションから出る */
	LeaveCriticalSection(&m_cs);

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	全ての弾の描画用座標値更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CBulManage::UpDate()
{
	CBullet*	pNext = m_pListTop;

	/* リスト構造の最後まで繰り返す */
	while(pNext != NULL){
		pNext->UpDate();
		pNext = pNext->GetNext();
	}
}

//--------------------------------------------------------------
//	Name:	SearchAllPlane
//	Func:	全てのオブジェクトの壁を調べて、一番距離の短い面を採用、
//			見つかった場合その面との距離のみを返す
//	in:		CStage*			pStage	= ステージクラスへのポインタ
//			D3DXVECTOR3		vecPos	= オブジェクトの座標値
//			D3DXVECTOR3		vecMove	= オブジェクトの移動方向
//	Out:	float					= 面との距離
//--------------------------------------------------------------
float CBulManage::SearchAllPlane(CStage* pStage, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecMove)
{
	float		fLenAdop,fLen;
	D3DXVECTOR3	vecCrossAdop1,vecCross1;
	D3DXVECTOR3	vecCrossAdop2,vecCross2;
	float		fTmp1, fTmp2;
	int			i;

	D3DXVECTOR3 diff;
	D3DXMATRIX matBase;

	fLenAdop = 99999;

	/* ブロックタイプのオブジェクトを調べる */
	for(i=0; i<pStage->GetBlockNum(); i++)
	{
		/* キャラクタとオブジェクトが離れていたら調べない */
		diff = pStage->GetBlockObj(i)->GetPosBase() - vecPos;
		fTmp1 = D3DXVec3LengthSq(&diff );
		fTmp2 = (pStage->GetBlockObj(i)->GetLength()) * (pStage->GetBlockObj(i)->GetLength());

		if(fTmp1 < fTmp2)
		{
			matBase = pStage->GetBlockObj(i)->GetMatBase();
			if( SearchPlane(pStage->GetBlockObj(i)->GetMesh(), &matBase,
				&vecPos, &vecMove, NULL, NULL, &fLen))
			{
				if(fLenAdop > fLen)
				{
					// 調べたすべてのオブジェクトの中で一番距離が短い面を採用
					fLenAdop = fLen;
				}
			}
		}
	}

	/* ウォールタイプのオブジェクトを調べる */
	for(i=0; i<pStage->GetWallNum(); i++)
	{
		matBase = pStage->GetWallObj(i)->GetMatBase();
		if( SearchPlane(pStage->GetWallObj(i)->GetMesh(), &matBase,
			&vecPos, &vecMove, NULL, NULL, &fLen))
		{
			if(fLenAdop > fLen)
			{
				// 調べたすべてのオブジェクトの中で一番距離が短い面を採用
				fLenAdop = fLen;
			}
		}
	}

	// 面が見つかった場合その距離を返す
	return fLenAdop;
}