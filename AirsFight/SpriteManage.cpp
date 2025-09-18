//==========================================================
// SpriteManage.cpp
// Auther : 桜井 博之
// Data   : 2002/04/29
//==========================================================

#include "SpriteManage.h"

//----------------------------------------------
//	Name:	CSpriteManage
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 = D3Dデバイス
//	Out:	なし
//----------------------------------------------
CSpriteManage::CSpriteManage(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* デバイスのセット */
	m_pd3dDevice = d3dDevice;

	/* 最初のポインタをNULLに */
	m_pListTop = NULL;

	/* スプライト作成 */
	D3DXCreateSprite(m_pd3dDevice,&m_pSprite);

	/* テクスチャデータの読み込み */
	D3DXCreateTextureFromFileA(m_pd3dDevice,"data\\Game\\StartLogo.png",&m_pTexture[0]);
	D3DXCreateTextureFromFileA(m_pd3dDevice,"data\\Game\\TimeOver.png",&m_pTexture[1]);
	for(int i=2; i<10; i++)	m_pTexture[i] = NULL;

	/* クリティカルセクション初期化 */
	InitializeCriticalSection(&m_cs);
}

//----------------------------------------------
//	Name:	~CSpriteManage
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CSpriteManage::~CSpriteManage()
{
	/* リストのデータを全て削除 */
	CListSprite *pCurrent = m_pListTop;
	CListSprite *pNext = NULL;

	while(pCurrent) {
		pNext = pCurrent->GetNext();
		delete pCurrent;
		pCurrent = pNext;
	}

	/* 使用したメモリの開放 */
	for(int i=0; i<10; i++)	SAFE_RELEASE(m_pTexture[i]);
	SAFE_RELEASE(m_pSprite);

	/* クリティカルセクションを終了させる */
	DeleteCriticalSection(&m_cs);
}

//--------------------------------------------------------------
//	Name:	AddSprite
//	Func:	スプライトの追加
//	in:		int			nType	= スプライトのタイプ
//	Out:	CListSprite*	作成したポインタを返す 失敗時はNULLを返す
//--------------------------------------------------------------
CListSprite* CSpriteManage::AddSprite(int nType)
{
	CListSprite*	pCurrent = m_pListTop;
	CListSprite*	pBack	 = NULL;

	/* 追加する位置を探す */
	while(pCurrent != NULL)
	{
		pBack = pCurrent;
		pCurrent = pCurrent->GetNext();
	}
	/* 追加位置が見つかったらそこに作成する */
	switch(nType)
	{
		/* カウンターロゴの作成 */
		case COUNT_LOGO:	pCurrent = new CCountLogo(m_pd3dDevice, m_pTexture[0]);	break;

		/* スタートロゴの作成 */
		case START_LOGO:	pCurrent = new CStartLogo(m_pd3dDevice, m_pTexture[0]); break;

		/* タイムオーバーの作成 */
		case TIME_OVER:		pCurrent = new CTimeOverLogo(m_pd3dDevice, m_pTexture[1]); break;

		/* 作成失敗 */
		default:	return NULL;
	}


	/* データをつなげる */
	if(pBack)	pBack->SetNext(pCurrent);
	else		m_pListTop = pCurrent;

	/* ポインタを返して終了 */
	return pCurrent;
}

//--------------------------------------------------
//	Name:	SubSprite
//	Func:	指定スプライトを削除する
//	in:		CListSprite* pSprite = 削除する指定ポインタ
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CSpriteManage::SubSprite(CListSprite* pSprite)
{
	CListSprite* pCurrent = m_pListTop;	// 現在調べている位置
	CListSprite* pBack = NULL;			// 現在調べているデータの１つ前のデータ


	/* リスト構造の最後まで削除する場所を検索 */
	while(pCurrent != NULL)
	{
		if(pCurrent  == pSprite) break;

		pBack = pCurrent;
		pCurrent = pCurrent->GetNext();
	}

	/* 指定ポインタが見つからなかったら失敗とみなす */
	if(pCurrent == NULL)	return E_FAIL;

	/* オブジェクトをリスト構造から削除 */
	CListSprite* pNext;
	pNext = pCurrent->GetNext();
	delete pCurrent;

	/* データをつなげる */

	/* 消したデータがリストの初めのデータだった時 */
	if (pBack == NULL)
	{
		m_pListTop = pNext;
		pCurrent = pNext;
	}
	/* 消したデータがリストの途中、あるいは最後のデータの時 */
	else {

		pCurrent = pNext;			// 調べる位置を次のデータにする
		pBack->SetNext(pCurrent);	// 消したデータ分、リストを詰める
	}

	return S_OK;
}

//--------------------------------------------------
//	Name:	SubSprite
//	Func:	スプライトの自動消去
//	in:		なし
//	Out:	なし
//--------------------------------------------------
void CSpriteManage::SubSprite()
{
	CListSprite* pCurrent = m_pListTop;	// 現在調べている位置
	CListSprite* pBack = NULL;			// 現在調べているデータの１つ前のデータ
	CListSprite* pNext;

	/* リスト構造の最後まで検索 */
	while(pCurrent != NULL){

		/* オブジェクトを消すか調べる */
		if(pCurrent->IsDelete()){

			/* オブジェクトをリスト構造から削除 */
			pNext = pCurrent->GetNext();
			delete pCurrent;

			/* データを繋げる */
			if (pBack == NULL) {
				m_pListTop = pNext;
				pCurrent = pNext;
			}
			else {
				pCurrent = pNext;
				pBack->SetNext(pCurrent);
			}
		}
		/* 現在のデータが、消す必要が無い時 */
		else {
	
			pBack = pCurrent;
			pCurrent = pCurrent->GetNext();
		}
	}

}

//------------------------------------------------------
//	Name:	FrameMove
//	Func:	全てのスプライトの毎フレームの処理
//	in:		なし
//	Out:	なし
//------------------------------------------------------
void CSpriteManage::FrameMove()
{
	CListSprite*	pNext = m_pListTop;

	/* クリティカルセクションに入る */
	EnterCriticalSection(&m_cs);

	/* 全てのスプライトの毎フレーム処理を呼ぶ */
	while(pNext != NULL){
		pNext->FrameMove();
		pNext = pNext->GetNext();
	}

	/* クリティカルセクションから出る */
	LeaveCriticalSection(&m_cs);
	
	/* 同時に全てのスプライトに対し、消去判定を行う */
	SubSprite();


}

//----------------------------------------------
//	Name:	Render
//	Func:	全てのスプライトの描画
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CSpriteManage::Render()
{
	CListSprite*	pNext = m_pListTop;

	/* スプライト描画開始 */
	m_pSprite->Begin();

	/* クリティカルセクションに入る */
	EnterCriticalSection(&m_cs);

	/* リスト構造の最後まで繰り返す */
	while(pNext != NULL){
		pNext->Render(m_pSprite);
		pNext = pNext->GetNext();
	}

	/* クリティカルセクションから出る */
	LeaveCriticalSection(&m_cs);

	/* スプライト描画終了 */
	m_pSprite->End();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	全てのスプライトのデータ更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CSpriteManage::UpDate()
{
	CListSprite*	pNext = m_pListTop;

	/* リスト構造の最後まで繰り返す */
	while(pNext != NULL){
		pNext->UpDate();
		pNext = pNext->GetNext();
	}
}
