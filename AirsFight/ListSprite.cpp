//==========================================================
// ListSprite.cpp
// Auther : 桜井 博之
// Data   : 2002/04/29
//==========================================================

#include "ListSprite.h"

//----------------------------------------------
//	Name:	CListSprite
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8	d3dDevice = D3Dデバイス
//			LPDIRECT3DTEXTURE8	pTexture  = テクスチャ
//	Out:	なし
//----------------------------------------------
CListSprite::CListSprite(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture)
		:C2DGraphicObj(d3dDevice) 
{
	/* 次のデータへのポインタ初期化 */
	m_pNext = NULL;

	/* 当然生存させます */
	m_bFlg = true;

	/* テクスチャのセット */
	m_pTexture = pTexture;
}

//----------------------------------------------
//	Name:	~CListSprite
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CListSprite::~CListSprite()
{

}

//----------------------------------------------
//	Name:	IsDelete
//	Func:	消去判定
//	in:		なし
//	Out:	bool
//----------------------------------------------
bool CListSprite::IsDelete()
{
	/* 生存フラグがたっていなければＯＫ */
	if(m_bFlg == false)		return true;

	/* 立ってれば消さない */
	return false;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		LPD3DXSPRITE pSprite = スプライト
//	Out:	なし
//----------------------------------------------
void CListSprite::Render(LPD3DXSPRITE pSprite)
{
	/* スプライトを描画 */
	pSprite->Draw(m_pTexture, &m_rectStock, NULL, NULL, 0.0f, &m_vecStock,
					D3DCOLOR_ARGB(255, 255, 255, 255));
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CListSprite::UpDate()
{
	C2DGraphicObj::UpDate();

	/* 後なんか書くかも */

}