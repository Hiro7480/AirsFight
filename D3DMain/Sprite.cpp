//==========================================================
// Sprite.cpp
// Auther : 桜井 博之
// Data   : 2002/05/01
//==========================================================

#include "Sprite.h"

//------------------------------------------------------
//	Name:	CSprite
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice   = D3Dデバイス
//			TCHAR*			  strFileName = テクスチャファイル名
//	Out:	なし
//------------------------------------------------------
CSprite::CSprite(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFileName)
		:C2DGraphicObj(d3dDevice)
{
	/* スプライト作成 */
	D3DXCreateSprite(m_pd3dDevice,&m_pSprite);

	/* テクスチャデータの読み込み */
	D3DXCreateTextureFromFile(m_pd3dDevice,strFileName,&m_pTexture);
}

//------------------------------------------------------
//	Name:	~CSprite
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//------------------------------------------------------
CSprite::~CSprite()
{
	/* 使用したメモリの開放 */
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);

}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CSprite::Render()
{
	m_pSprite->Begin();

	/* スプライトを描画 */
	m_pSprite->Draw(m_pTexture, &m_rectStock, NULL, NULL, 0.0f, &m_vecStock,
					D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}
