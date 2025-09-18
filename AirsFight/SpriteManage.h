//==========================================================
// SpriteManage.h
// Auther : 桜井 博之
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_SPRITEMANAGE_H__2434EF4A_DC7E_4712_A11F_3D93B926ED56__INCLUDED_)
#define AFX_SPRITEMANAGE_H__2434EF4A_DC7E_4712_A11F_3D93B926ED56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>

#include "ListSprite.h"
#include "StartLogo.h"
#include "CountLogo.h"
#include "TimeOverLogo.h"

//------------------------------
//	定数定義
//------------------------------
/* スプライトタイプ識別子 */
#define COUNT_LOGO	0
#define START_LOGO	1
#define TIME_OVER	2

//----------------------------------------------
//	Name:	CSpriteManage
//	Func:	スプライト管理クラス
//----------------------------------------------
class CSpriteManage
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;			// D3Dデバイス
	CListSprite*		m_pListTop;				// はじめのスプライトへのポインタ

	LPD3DXSPRITE		m_pSprite;				// スプライト
	LPDIRECT3DTEXTURE8	m_pTexture[10];			// テクスチャデータ

	CRITICAL_SECTION	m_cs;					// クリティカルセクションオブジェクト

public:
	void FrameMove(); 							// 毎フレームの処理
	void Render();								// 画面描画
	void UpDate();								// データ更新

	CListSprite*	AddSprite(int nType);			// スプライトの追加
	HRESULT			SubSprite(CListSprite* pSprite);// スプライトの消去
	void			SubSprite();					// スプライトの自動消去

	/* アクセス関数 */
	CListSprite* GetListTop(){return m_pListTop;};	// はじめの弾へのポインタを返す

	CSpriteManage(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CSpriteManage();
};

#endif // !defined(AFX_SPRITEMANAGE_H__2434EF4A_DC7E_4712_A11F_3D93B926ED56__INCLUDED_)
