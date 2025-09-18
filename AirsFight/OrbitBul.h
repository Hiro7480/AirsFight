//==========================================================
// OrbitBul.h
// Auther : 桜井 博之
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_ORBITBUL_H__3438B47D_2AF4_4A15_802C_D37C9BD5F4B9__INCLUDED_)
#define AFX_ORBITBUL_H__3438B47D_2AF4_4A15_802C_D37C9BD5F4B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	COrbitBul
//	Func:	爆発エフェクトA 
//			弾が壁や敵に当たった時
//----------------------------------------------
class COrbitBul : public CEffect  
{
private:
	tagParticle m_Particle[3];
	void InitParticle();		// パーティクルの初期座標、初期移動値などの設定

public:
	void FrameMove();			// 毎フレームの処理

	COrbitBul(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~COrbitBul();
};
#endif // !defined(AFX_ORBITBUL_H__3438B47D_2AF4_4A15_802C_D37C9BD5F4B9__INCLUDED_)
