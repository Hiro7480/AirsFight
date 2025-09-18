//==========================================================
// CountLogo.cpp
// Auther : 桜井 博之
// Data   : 2002/04/29
//==========================================================

#include "CountLogo.h"

//------------------------------------------------------
//	Name:	CCountLogo
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8	 d3dDevice = D3Dデバイス
//			, LPDIRECT3DTEXTURE8 pTexture  = テクスチャ
//	Out:	なし
//------------------------------------------------------
CCountLogo::CCountLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture)
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

}

//----------------------------------------------
//	Name:	~CCountLogo
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CCountLogo::~CCountLogo()
{

}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CCountLogo::FrameMove()
{
	/* アニメカウンターにより、テクスチャの使う部分を決める */
	switch(m_nAnimeCnt / 60)
	{
		/* 「カウント３」を表示する */
		case 0:
			C2DGraphicObj::SetRec(256, 0, 383, 127);
			break;
		/* 「カウント２」を表示する */
		case 1:
			C2DGraphicObj::SetRec(128, 0, 255, 127);
			break;
		/* 「カウント１」を表示する */
		case 2:
			C2DGraphicObj::SetRec( 0, 0, 127, 127);
			break;
	}

	/* アニメカウンターによりアルファ値とスケール値を操作 */
	int	nCnt = m_nAnimeCnt % 60;

	/* アニメーションが0～29なら、だんだん不透明にしていきながら縮小していく */
	if(nCnt < 30)
	{
		m_nAlphaBase = (255 / 30) * nCnt;
		m_fScaleBase = (2.0f-(2.0f/30.0f)*nCnt)+1.0f;
	}

	/* アニメーションが30～59なら固定 */
	else
	{
		m_nAlphaBase = 255;
		m_fScaleBase = 1.0f;
	}

	/* 表示位置の設定 */
	C2DGraphicObj::SetVec(D3DXVECTOR2(320-(64*m_fScaleBase), 240-(64*m_fScaleBase)));

	/* アニメカウンターのインクリメント */
	m_nAnimeCnt++;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		LPD3DXSPRITE pSprite
//	Out:	なし
//----------------------------------------------
void CCountLogo::Render(LPD3DXSPRITE pSprite)
{
	D3DXVECTOR2 vec2(m_fScaleStock, m_fScaleStock);

	/* 透明値を入れたスプライト描画 */
	pSprite->Draw(	m_pTexture,
					&m_rectStock,
					&vec2,
					NULL,
					0.0f,
					&m_vecStock,
					D3DCOLOR_ARGB(m_nAlphaStock, 255, 255, 255) );

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CCountLogo::UpDate()
{
	C2DGraphicObj::UpDate();

	/* 透明値の更新 */
	m_nAlphaStock = m_nAlphaBase;

	/* スケール値の更新 */
	m_fScaleStock = m_fScaleBase;

}