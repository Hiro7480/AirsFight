//==========================================================
// EnergyGauge.h
// Auther : 桜井 博之
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_ENERGYGAUGE_H__BA0EE9C3_70F3_4B94_ACDE_93759D70DE69__INCLUDED_)
#define AFX_ENERGYGAUGE_H__BA0EE9C3_70F3_4B94_ACDE_93759D70DE69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------
//	インクルード
//--------------------------
#include "Sprite.h"

//------------------------------------------
//	Name:	CEnergyGauge
//	Func:	エネルギーゲージの描画
//------------------------------------------
class CEnergyGauge : public CSprite
{
private:
	int				m_nMaxEnergy;	// 最大エネルギー値
	int				m_nNowEnergy;	// 現在エネルギー値

	D3DXVECTOR2		m_vecPos;		// 基本描画位置

public:
	void	FrameMove();	// 毎フレームの処理
	void	Render();		// 描画処理	

	/* アクセス関数 */
	void SetMaxEnergy(int nMaxEnergy){m_nMaxEnergy = nMaxEnergy;};	// 最大エネルギー値のセット
	void SetNowEnergy(int nNowEnergy){m_nNowEnergy = nNowEnergy;};	// 現在エネルギー値のセット

	CEnergyGauge(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName);
	virtual ~CEnergyGauge();

};

#endif // !defined(AFX_ENERGYGAUGE_H__BA0EE9C3_70F3_4B94_ACDE_93759D70DE69__INCLUDED_)
