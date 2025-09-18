//==========================================================
// ExplosionB.h
// Auther : 桜井 博之
// Data   : 2002/05/09
//==========================================================

#if !defined(AFX_EXPLOTIONB_H__FB55AF9D_7CC3_431C_859F_E631F67584CE__INCLUDED_)
#define AFX_EXPLOTIONB_H__FB55AF9D_7CC3_431C_859F_E631F67584CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	CExplositonB
//	Func:	爆発エフェクトB
//			弾がキャラクタに当たった場合
//----------------------------------------------
class CExplosionB : public CEffect  
{
private:
	tagParticle m_Particle[20];
	void InitParticle();		// パーティクルの初期座標、初期移動値などの設定

public:
	void FrameMove();			// 毎フレームの処理

	CExplosionB(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CExplosionB();
};

#endif // !defined(AFX_EXPLOTIONB_H__FB55AF9D_7CC3_431C_859F_E631F67584CE__INCLUDED_)
