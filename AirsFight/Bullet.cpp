//==========================================================
// Bullet.cpp
// Auther : 桜井 博之
// Data   : 2002/01/11
//==========================================================

#include "Bullet.h"


//----------------------------------------------
//	Name:	CBullet
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3Dデバイス
//			tagBulParam*	  pType		= 弾のタイプ
//			D3DXMATRIX		  matBase	= 初期マトリクス
//			long			  lID		= 識別番号
//	Out:	なし
//----------------------------------------------
CBullet::CBullet(LPDIRECT3DDEVICE8 d3dDevice, tagBulParam* pType, D3DXMATRIX matBase, long lID)
		:C3DGraphicObj(d3dDevice)
{
	/* パラメータのポインタを格納 */
	m_pBulStatus = pType;	

	/* 弾の初期行列を指定行列に */
	m_matBase = matBase;

	/* 次へのポインタの初期化 */
	m_pNext = NULL;

	/* 経過時間の初期化 */
	m_nTimeCount = 0;

	/* 移動ベクトルの算出 */
	m_vecMove = GetNormalVec3ToMat(NULL, &m_matBase);

	/* 識別番号の格納 */
	m_lID = lID;
}

//----------------------------------------------
//	Name:	~CBullet
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CBullet::~CBullet()
{

}

//------------------------------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		CEffectManage* pEffectManage = エフェクト管理クラス
//	Out:	なし
//------------------------------------------------------------------
void CBullet::FrameMove(CEffectManage* pEffectManage)
{
	/* 座標値の更新 */
	m_matBase._41 += m_vecMove.x * m_pBulStatus->fSpeed;
	m_matBase._42 += m_vecMove.y * m_pBulStatus->fSpeed;
	m_matBase._43 += m_vecMove.z * m_pBulStatus->fSpeed;

	/* エフェクトを３回に１回発生 */
	static int nCnt=0;
	nCnt++;
	if(nCnt % 3 == 0)
		pEffectManage->AddEffect(ORBIT_BUL, m_matBase);

	/* 経過時間のインクリメント */
	m_nTimeCount++;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CBullet::Render()
{
	/* ワールド変換 */
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &m_matStock);
	
	/* 描画 */
	m_pBulStatus->pBulMesh->Render();
}

//----------------------------------------------
//	Name:	IsDelete
//	Func:	弾を消すかどうかを判定
//	in:		なし
//	Out:	bool
//----------------------------------------------
bool CBullet::IsDelete()
{
	/* 弾の経過時間が生存時間をオーバーしていたら消すとみなす */
	if(m_nTimeCount >= m_pBulStatus->nMaxLife)	return	true;

	else	return false;
}