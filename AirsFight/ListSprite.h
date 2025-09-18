//==========================================================
// ListSprite.h
// Auther : 桜井 博之
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_SPRITE_H__E78DACD3_EDEB_47F9_B805_341AB00F7DA7__INCLUDED_)
#define AFX_SPRITE_H__E78DACD3_EDEB_47F9_B805_341AB00F7DA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CListSprite
//	Func:	リスト構造で使用するスプライト
//----------------------------------------------
class CListSprite : public C2DGraphicObj
{
private:
	CListSprite*		m_pNext;		// 次のデータへのポインタ

protected:
	LPDIRECT3DTEXTURE8	m_pTexture;		// テクスチャへのポインタ
	bool				m_bFlg;			// 生存フラグ

public:
	virtual void FrameMove(){};					// 毎フレームの処理
	virtual void Render(LPD3DXSPRITE pSprite);	// 画面描画
	virtual void UpDate();						// データ更新

	bool	IsDelete();							// 消去判定

	/* アクセス関数 */
	CListSprite*	GetNext(){return m_pNext;};			// 次のデータへのポインタを返す
	void SetNext(CListSprite* pNext){m_pNext = pNext;};	// 次のデータへのポインタをセット

	CListSprite(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture);
	virtual ~CListSprite();
};

#endif // !defined(AFX_SPRITE_H__E78DACD3_EDEB_47F9_B805_341AB00F7DA7__INCLUDED_)
