//==========================================================
// 3DGraphicObj.h
// Auther : 桜井 博之
// Data   : 2002/02/26
//==========================================================

#if !defined(AFX_GRAPHICOBJECT_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_)
#define AFX_3DGRAPHICOBJ_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_

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
//	Name:	C3DGraphicObj
//	Func:	３Ｄ描画オブジェクトの基底クラス
//----------------------------------------------
class C3DGraphicObj  
{
protected:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3Dデバイス
	D3DXMATRIX			m_matBase;		// 処理用マトリクス
	D3DXMATRIX			m_matStock;		// 描画用マトリクス

public:
	virtual void FrameMove(){};							// 毎フレームの処理
	virtual void Render(){};							// 描画処理
	virtual void UpDate(){m_matStock=m_matBase;};		// 描画用マトリクスを更新する

	/* アクセス関数*/
	void	SetMatrix(D3DXMATRIX mat){m_matBase=mat;};	// マトリクスのセット

	D3DXVECTOR3 GetPosBase();							// マトリクスの座標をベクトルで返す
	D3DXVECTOR3 GetPosStock();							// 描画用マトリクスの値をベクトルで返す
	D3DXMATRIX	GetMatBase(){return m_matBase;};		// マトリクスを返す
	D3DXMATRIX	GetMatStock(){return m_matStock;};		// 描画用マトリクスを返す

	D3DXMATRIX*	GetMatPointer(){return &m_matBase;};	// マトリクスのポインタを返す

	C3DGraphicObj(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~C3DGraphicObj();
};

#endif // !defined(AFX_GRAPHICOBJECT_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_)
