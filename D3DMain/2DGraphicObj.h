//==========================================================
// 2DGraphicObj.h
// Auther : 桜井 博之
// Data   : 2002/02/26
//==========================================================

#if !defined(AFX_GRAPHICOBJECT_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_)
#define AFX_2DGRAPHICOBJ_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "define.h"

//----------------------------------------------
//	Name:	2DGraphicObj
//	Func:	２Ｄ描画オブジェクトの基底クラス
//----------------------------------------------
class C2DGraphicObj  
{
protected:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3Dデバイス

	D3DXVECTOR2			m_vecBase;		// 処理用２Ｄベクトル
	D3DXVECTOR2			m_vecStock;		// 描画用２Ｄベクトル

	RECT				m_rectBase;		// 処理用レクト
	RECT				m_rectStock;	// 描画用レクト

public:
	virtual void FrameMove(){};			// 毎フレームの処理
	virtual void Render(){};			// 描画処理
	virtual void UpDate();				// データ更新

	/* アクセス関数*/
	void	SetVec(D3DXVECTOR2 vec){m_vecBase=vec;};			// ベクトルのセット
	void	SetRec(int left, int top, int right, int bottom);	// レクトのセット

	D3DXVECTOR2 GetVecBase(){return m_vecBase;};		// 処理用ベクトルを返す
	D3DXVECTOR2 GetVecStock(){return m_vecStock;};		// 描画用ベクトルを返す

	RECT		GetRectBase(){return m_rectBase;};		// 処理用レクトを返す
	RECT		GetRectStock(){return m_rectStock;};	// 描画用レクトを返す

	C2DGraphicObj(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~C2DGraphicObj();
};

//----------------------------------------------
//	Name:	SetRec
//	Func:	レクトのセット
//	In:		int left	= 左端座標
//			int top		= 上端座標
//			int right	= 右端座標
//			int bottom	= 下端座標
//	Out:	なし
//----------------------------------------------
inline void C2DGraphicObj::SetRec(int left, int top, int right, int bottom)
{
	SetRect(&m_rectBase, left, top, right, bottom);
}

#endif // !defined(AFX_GRAPHICOBJECT_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_)
