//==========================================================
// EffectManage.cpp
// Auther : 桜井 博之
// Data   : 2002/03/09
//==========================================================
#include "EffectManage.h"

//----------------------------------------------
//	Name:	CEffectManage
//	Func:	コンストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CEffectManage::CEffectManage(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* デバイスのセット */
	m_pd3dDevice = d3dDevice;

	/* 初めのポインタをNULLに */
	m_pListTop = NULL;

	/* テクスチャデータの読み込み */
	D3DXCreateTextureFromFileA(m_pd3dDevice,"data\\Effect\\ExplosionA.png",&m_pTexture[0]);
	for(int i=1; i<TEXTURE_NUM; i++)	m_pTexture[i] = NULL;

	/* クリティカルセクション初期化 */
	InitializeCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	~CEffectManage
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CEffectManage::~CEffectManage()
{
	/* リストのデータを全て削除 */
	CEffect *pCurrent = m_pListTop;
	CEffect *pNext = NULL;

	while(pCurrent) {
		pNext = pCurrent->GetNext();
		delete pCurrent;
		pCurrent = pNext;
	}

	/* 使用したメモリの開放 */
	for(int i=0; i<TEXTURE_NUM; i++)	SAFE_RELEASE(m_pTexture[i]);

	/* クリティカルセクションを終了させる */
	DeleteCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	AddEffect
//	Func:	エフェクトの新規作成
//	in:		DWORD		dwType	= エフェクトタイプ
//			D3DXMATIRX* pMatIn	= マトリクス
//	Out:	なし
//----------------------------------------------
void CEffectManage::AddEffect(DWORD dwType, D3DXMATRIX matIn)
{
	CEffect*	pCurrent = m_pListTop;
	CEffect*	pBack	 = NULL;

	/* クリティカルセクションに入る */
	EnterCriticalSection(&m_cs);

	/* 追加する位置を探す */
	while(pCurrent != NULL)
	{
		pBack = pCurrent;
		pCurrent = pCurrent->GetNext();
	}
	/* 追加位置が見つかったらそこに作成する */
	switch(dwType)
	{
	case BOOST_A:		pCurrent = new CBoostA(m_pd3dDevice, m_pTexture[0], matIn);		break;
	case BOOST_B:		pCurrent = new CBoostB(m_pd3dDevice, m_pTexture[0], matIn);		break;
	case EXPLOSION_A:	pCurrent = new CExplosionA(m_pd3dDevice, m_pTexture[0], matIn);	break;
	case EXPLOSION_B:	pCurrent = new CExplosionB(m_pd3dDevice, m_pTexture[0], matIn);	break;
	case ORBIT_BUL:		pCurrent = new COrbitBul(m_pd3dDevice, m_pTexture[0], matIn);	break;
	case REVIVAL:		pCurrent = new CRevival(m_pd3dDevice, m_pTexture[0], matIn);	break;

	}

	/* データをつなげる */
	if(pBack)	pBack->SetNext(pCurrent);
	else		m_pListTop = pCurrent;

	/* クリティカルセクションから出る */
	LeaveCriticalSection(&m_cs);

}

//----------------------------------------------
//	Name:	SubEffect
//	Func:	エフェクトの削除
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CEffectManage::SubEffect()
{
	CEffect* pCurrent = m_pListTop;	// 現在調べている位置
	CEffect* pBack = NULL;			// 現在調べているデータの１つ前のデータ
	CEffect* pNext;

	// クリティカルセクションに入る
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
	// クリティカルセクションから出る
	LeaveCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	全てのエフェクトの毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CEffectManage::FrameMove()
{
	/* クリティカルセクションに入る */
	EnterCriticalSection(&m_cs);

	CEffect*	pNext = m_pListTop;
	/* リストの全てを動かす */
	while(pNext != NULL){
		pNext->FrameMove();
		pNext = pNext->GetNext();
	}

	/* 削除処理 */
	SubEffect();

	/* クリティカルセクションから出る */
	LeaveCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	Render
//	Func:	全てのエフェクトの描画
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CEffectManage::Render()
{
	// 半透明などの設定
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_pd3dDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.0f));
	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.0f));
	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.0f));
	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.0f));

	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);

	// クリティカルセクションに入る
	EnterCriticalSection(&m_cs);

	CEffect*	pNext = m_pListTop;
	// リスト構造の最後まで検索
	while(pNext != NULL){
		pNext->Render();
		pNext = pNext->GetNext();
	}
	// クリティカルセクションから出る
	LeaveCriticalSection(&m_cs);

	m_pd3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	// 半透明などの設定を戻す
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	// Ｚバッファを念のために戻す
	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	全てのエフェクトの描画用座標値更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CEffectManage::UpDate()
{
	CEffect*	pNext = m_pListTop;
	// リスト構造の最後まで検索
	while(pNext != NULL){
		pNext->UpDate();
		pNext = pNext->GetNext();
	}
}