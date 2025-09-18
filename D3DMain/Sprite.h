//==========================================================
// Sprite.h
// Auther : 桜井 博之
// Data   : 2002/05/01
//==========================================================

#if !defined(AFX_SPRITE_H__5CBA9CB1_EE8B_4FE8_A59F_9A9138CE5451__INCLUDED_)
#define AFX_SPRITE_H__5CBA9CB1_EE8B_4FE8_A59F_9A9138CE5451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------
#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CSprite
//	Func:	単体スプライトの管理
//----------------------------------------------
class CSprite : public C2DGraphicObj  
{
protected:
	LPDIRECT3DTEXTURE8	m_pTexture;		// テクスチャ
	LPD3DXSPRITE		m_pSprite;		// スプライト

public:
	void Render();						// 描画処理

	CSprite(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFileName);
	virtual ~CSprite();

};

#endif // !defined(AFX_SPRITE_H__5CBA9CB1_EE8B_4FE8_A59F_9A9138CE5451__INCLUDED_)
