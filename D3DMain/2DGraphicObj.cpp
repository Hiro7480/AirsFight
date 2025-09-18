//==========================================================
// 2DGraphicObj.cpp
// Auther : 桜井 博之
// Data   : 2002/02/26
//==========================================================

#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CGraphicObjcet
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3Dデバイス
//	Out:	なし
//----------------------------------------------
C2DGraphicObj::C2DGraphicObj(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* D3Dデバイスのセット */
	m_pd3dDevice = d3dDevice;

	/* ベクトルの初期化 */
	m_vecBase *= 0;
	m_vecStock *= 0;

	/* レクトの初期化 */
	SetRect(&m_rectBase, 0,0,0,0);
	SetRect(&m_rectStock, 0,0,0,0);
}

//----------------------------------------------
//	Name:	~CGraphicObjcet
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
C2DGraphicObj::~C2DGraphicObj()
{

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	データの更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void C2DGraphicObj::UpDate()
{
	/* ベクトルの更新 */
	m_vecStock = m_vecBase;

	/* レクトの更新 */
	m_rectStock = m_rectBase;
}