//==========================================================
// StartLogo.cpp
// Auther : 桜井 博之
// Data   : 2002/04/29
//==========================================================

#include "StartLogo.h"

//------------------------------------------------------
//	Name:	CStartLogo
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8	 d3dDevice = D3Dデバイス
//			, LPDIRECT3DTEXTURE8 pTexture  = テクスチャ
//	Out:	なし
//------------------------------------------------------
CStartLogo::CStartLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture)
		   :CListSprite(d3dDevice, pTexture)
{
	/* アニメカウンターの初期化 */
	m_nAnimeCnt = 0;

	/* 透明値の初期化 */
	m_nAlphaBase  = 0;
	m_nAlphaStock = 0;

	/* スケール値の初期化 */
	m_fScaleBase  = 0;
	m_fScaleStock = 0;

	/* テクスチャ表示位置の設定 */
	C2DGraphicObj::SetRec( 0, 128, 511, 255);

}

//----------------------------------------------
//	Name:	~CStartLogo
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CStartLogo::~CStartLogo()
{

}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CStartLogo::FrameMove()
{
	/* アニメーションが0～59なら、固定で表示させる */
	if(m_nAnimeCnt < 60)
	{
		m_nAlphaBase = 255;
		m_fScaleBase = 1.0f;
	}

	/* アニメーションが60～89ならフェードアウト */
	else
	{
		m_nAlphaBase = (255 / 30) * (30-(m_nAnimeCnt-30));
		m_fScaleBase = (5.0f-(5.0f/30.0f) * (30-(m_nAnimeCnt-60))) +1.0f;
	}

	/* 表示位置の設定 */
	C2DGraphicObj::SetVec(D3DXVECTOR2(320-(256*m_fScaleBase), 240-(64*m_fScaleBase)));

	/* アニメカウンターのインクリメント */
	m_nAnimeCnt++;

	/* アニメカウンターが90を超えたら終了する */
	if(m_nAnimeCnt > 90)	m_bFlg = false;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		LPD3DXSPRITE pSprite
//	Out:	なし
//----------------------------------------------
void CStartLogo::Render(LPD3DXSPRITE pSprite)
{
	D3DXVECTOR2 vec2(m_fScaleStock, m_fScaleStock);

	/* 透明値を入れたスプライト描画 */
	pSprite->Draw(m_pTexture,
		&m_rectStock,
		&vec2,
		NULL,
		0.0f,
		&m_vecStock,
		D3DCOLOR_ARGB(m_nAlphaStock, 255, 255, 255));
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CStartLogo::UpDate()
{
	C2DGraphicObj::UpDate();

	/* 透明値の更新 */
	m_nAlphaStock = m_nAlphaBase;

	/* スケール値の更新 */
	m_fScaleStock = m_fScaleBase;

}