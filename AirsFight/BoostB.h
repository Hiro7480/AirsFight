//==========================================================
// BoostB.h
// Auther : 桜井 博之
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_BOOSTB_H__DA1C08DC_1EB1_42B6_8C5B_09255BD6EADA__INCLUDED_)
#define AFX_BOOSTB_H__DA1C08DC_1EB1_42B6_8C5B_09255BD6EADA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include "Effect.h"

//----------------------------------------------
//	Name:	CBoostA
//	Func:	ブースターエフェクトＢ
//			ジャンプ時または飛行中に煙っぽいもの
//----------------------------------------------
class CBoostB : public CEffect
{
private:
	tagParticle m_Particle[10];
	void InitParticle();		// パーティクルの初期座標、初期移動値などの設定

public:
	void FrameMove();			// 毎フレームの処理

	CBoostB(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CBoostB();

};

#endif // !defined(AFX_BOOSTB_H__DA1C08DC_1EB1_42B6_8C5B_09255BD6EADA__INCLUDED_)
