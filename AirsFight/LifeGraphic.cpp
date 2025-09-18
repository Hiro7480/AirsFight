//==========================================================
// LifeGraphic.cpp
// Auther : 桜井 博之
// Data   : 2002/05/04
//==========================================================
#include "LifeGraphic.h"

//----------------------------------------------------------
//	Name:	CLifeGraphic
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice	  = D3Dデバイス
//			TCHAR*			  srcFileName = テクスチャファイル名
//	Out:	なし
//----------------------------------------------------------
CLifeGraphic::CLifeGraphic(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName)
			 :CSprite(d3dDevice, srcFileName)
{
	/* 変数の初期化 */
	m_nNextLife = 0;
	m_nNowLife  = 0;

	/* 基本描画位置のセット */
	m_vecPos = D3DXVECTOR2(50, 20);

	/* レクトの初期化 */
	for(int i=0; i<4; i++)
	{
		SetRect(&m_rcBase[i], 0,0,0,0);
	}
}

//----------------------------------------------------------
//	Name:	~CLifeGraphic
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
CLifeGraphic::~CLifeGraphic()
{

}

//----------------------------------------------------------
//	Name:	InitLife
//	Func:	ライフ値の初期化
//	in:		int nLife	= ライフの初期値
//	Out:	なし
//----------------------------------------------------------
void CLifeGraphic::InitLife(int nLife)
{
	/* 最大ライフ値を格納 */
	m_nMaxLife = nLife;

	/* 目標ライフ値、現在ライフ値ともに格納 */
	m_nNextLife = nLife;
	m_nNowLife  = nLife;
}

//----------------------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CLifeGraphic::FrameMove()
{
	float fTmp;

	/* 現在LIFE、目標LIFEともに０未満の数値には行かないようにする */
	if(m_nNextLife < 0)	m_nNextLife = 0;
	if(m_nNowLife  < 0) m_nNowLife  = 0;

	/* 現在LIFEを目標LIFEに近づける */
	if		(m_nNextLife > m_nNowLife)
	{
		fTmp = ( (float)m_nNextLife-(float)m_nNowLife ) / 10.0f+0.5f;
		if(fTmp <= 1.0f)	fTmp = 1.0f;
		m_nNowLife += (int)fTmp;
	}

	else if	(m_nNextLife < m_nNowLife)
	{
		fTmp = ( (float)m_nNowLife-(float)m_nNextLife ) /10.0f+0.5f;
		if(fTmp <= 1.0f)	fTmp = 1.0f;
		m_nNowLife -= (int)fTmp;
	}

	/* 最大LIFEと、現在LIFEから、文字の色を決める */
	int		nRectTop;
	fTmp = (float)m_nNowLife / (float)m_nMaxLife;

	if		(fTmp > 0.66f)	nRectTop = 0;	// 2/3以上あれば緑
	else if	(fTmp > 0.33f)	nRectTop = 80;	// 1/3以上あれば黄色
	else					nRectTop = 160;	// それ以下ならば赤

	/* 現在LIFEから、RECT値を求める */
	int nTmp;
	int	nLife;
	/* 1000の位のRECTを求める */
	nTmp = m_nNowLife / 1000;
	SetRect(&m_rcBase[0], 50*nTmp, nRectTop, 50*(nTmp+1), nRectTop+80);

	/* 100の位のRECTを求める */
	nLife = m_nNowLife % 1000;
	nTmp = nLife / 100;
	SetRect(&m_rcBase[1], 50*nTmp, nRectTop, 50*(nTmp+1), nRectTop+80);

	/* 10の位のRECTを求める */
	nLife = m_nNowLife % 100;
	nTmp = nLife / 10;
	SetRect(&m_rcBase[2], 50*nTmp, nRectTop, 50*(nTmp+1), nRectTop+80);

	/* 1の位のRECTを求める */
	nLife = m_nNowLife % 10;
	nTmp = nLife;
	SetRect(&m_rcBase[3], 50*nTmp, nRectTop, 50*(nTmp+1), nRectTop+80);
}

//----------------------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CLifeGraphic::Render()
{
	RECT rcTmp;
	D3DXVECTOR2 vec2;

	/* 描画開始 */
	m_pSprite->Begin();

	/* 背景を半透明で描画する */
	SetRect(&rcTmp, 0, 330, 210, 420);
	vec2 = D3DXVECTOR2(m_vecPos.x - 5.0f, m_vecPos.y - 5.0f);
	m_pSprite->Draw(m_pTexture, &rcTmp, NULL, NULL, 0.0f,
		&vec2, D3DCOLOR_ARGB(128, 255, 255, 255));

	/* 外枠を描画する */
	SetRect(&rcTmp, 0, 240, 210, 330);
	vec2 = D3DXVECTOR2(m_vecPos.x - 5.0f, m_vecPos.y - 5.0f);
	m_pSprite->Draw(m_pTexture, &rcTmp, NULL, NULL, 0.0f,
		&vec2, D3DCOLOR_ARGB(255, 255, 255, 255));


	/* ライフを描画する */
	for (int i = 0; i < 4; i++)
	{
		vec2 = D3DXVECTOR2(m_vecPos.x + (50 * i), m_vecPos.y);
		m_pSprite->Draw(m_pTexture, &m_rcStock[i], NULL, NULL, 0.0f,
			&vec2, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	/* 描画終了 */
	m_pSprite->End();
}

//----------------------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CLifeGraphic::UpDate()
{
	for(int i=0; i<4; i++)
	{
		m_rcStock[i] = m_rcBase[i];
	}
}