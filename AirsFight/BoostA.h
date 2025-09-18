//==========================================================
// BoostA.h
// Auther : 桜井 博之
// Data   : 2002/03/09
//==========================================================

#if !defined(AFX_BOOSTA_H__CF380D3C_1AEB_439B_A24E_405494248D63__INCLUDED_)
#define AFX_BOOSTA_H__CF380D3C_1AEB_439B_A24E_405494248D63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	CBoostA
//	Func:	ブースターエフェクトA
//			ダッシュ中に足元から砂煙っぽいものが出る
//----------------------------------------------
class CBoostA : public CEffect  
{
private:
	tagParticle m_Particle[10];
	void InitParticle();		// パーティクルの初期座標、初期移動値などの設定

public:
	void FrameMove();			// 毎フレームの処理

	CBoostA(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CBoostA();
};

#endif // !defined(AFX_BOOSTA_H__CF380D3C_1AEB_439B_A24E_405494248D63__INCLUDED_)
