//==========================================================
// ExplosionA.h
// Auther : 桜井 博之
// Data   : 2002/03/09
//==========================================================

#if !defined(AFX_EXPLOSIONA_H__FAB780A5_11A4_48AF_9B0A_72DAC45FB3F2__INCLUDED_)
#define AFX_EXPLOSIONA_H__FAB780A5_11A4_48AF_9B0A_72DAC45FB3F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	CExplositonA
//	Func:	爆発エフェクトA 
//			片面に爆発する
//----------------------------------------------
class CExplosionA : public CEffect  
{
private:
	tagParticle m_Particle[20];
	void InitParticle();		// パーティクルの初期座標、初期移動値などの設定

public:
	void FrameMove();			// 毎フレームの処理

	CExplosionA(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CExplosionA();
};

#endif // !defined(AFX_EXPLOSIONA_H__FAB780A5_11A4_48AF_9B0A_72DAC45FB3F2__INCLUDED_)
