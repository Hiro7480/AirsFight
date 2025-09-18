//==========================================================
// ScrollBG.cpp
// Auther : 桜井 博之
// Data   : 2002/05/01
//==========================================================

#include "ScrollBG.h"


//------------------------------------------------------------------
//	Name:	CScrollBG
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice   = D3Dデバイス
//			TCHAR*			  strFileName = テクスチャファイル名
//			float			  fHeight	  = テクスチャの高さサイズ
//			float			  fWidth	  = テクスチャの幅サイズ
//	Out:	なし
//------------------------------------------------------------------
CScrollBG::CScrollBG(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFileName, float fHeight, float fWidth)
		:C2DGraphicObj(d3dDevice)
{
	/* テクスチャデータの読み込み */
	D3DXCreateTextureFromFile(m_pd3dDevice,strFileName,&m_pTexture);

	/* テクスチャサイズのセット */
	m_fHeight = fHeight;
	m_fWidth  = fWidth;

	/* スプライト作成 */
	D3DXCreateSprite(m_pd3dDevice,&m_pSprite);

	/* 表示位置の初期化 */
	m_vecBase.x = 0;
	m_vecBase.y = 0;
}

//------------------------------------------------------
//	Name:	~CScrollBG
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//------------------------------------------------------
CScrollBG::~CScrollBG()
{
	/* 使用したメモリの開放 */
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);

}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CScrollBG::FrameMove()
{
	/* 画像を移動ベクトル分だけ動かす */
	m_vecBase.x -= m_vecDir.x;
	m_vecBase.y -= m_vecDir.y;

	/* テクスチャサイズ以上は減らさない */
	if(m_vecBase.x < -m_fWidth)		m_vecBase.x = 0;
	if(m_vecBase.y < -m_fHeight)	m_vecBase.y = 0;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CScrollBG::Render()
{
	float	fXPos, fYPos;

	D3DXVECTOR2 pos;

	/* 描画開始 */
	m_pSprite->Begin();

	/* 画面一杯埋まるまでスプライトを描画する */
	for(fXPos=m_vecStock.x; fXPos<640; fXPos+=m_fWidth)
	{
		for(fYPos=m_vecStock.y; fYPos<480; fYPos+=m_fHeight)
		{
			pos.x = fXPos;
			pos.y = fYPos;
			m_pSprite->Draw(m_pTexture, NULL, NULL, NULL, 0.0f, &pos,
							D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	/* 描画終了 */
	m_pSprite->End();

}

