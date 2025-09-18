//==========================================================
// Revival.h
// Auther : 桜井 博之
// Data   : 2002/05/09
//==========================================================

#if !defined(AFX_REVIVAL_H__2978C598_EAEB_42A9_B308_96F0C2D99610__INCLUDED_)
#define AFX_REVIVAL_H__2978C598_EAEB_42A9_B308_96F0C2D99610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	CRevival
//	Func:	復活エフェクト
//			復活時のエフェクト
//----------------------------------------------
class CRevival : public CEffect  
{
private:
	tagParticle m_Particle[100];
	void InitParticle();		// パーティクルの初期座標、初期移動値などの設定

public:
	void FrameMove();			// 毎フレームの処理

	CRevival(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CRevival();
};

#endif // !defined(AFX_REVIVAL_H__2978C598_EAEB_42A9_B308_96F0C2D99610__INCLUDED_)
