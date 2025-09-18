//==========================================================
// 3DGraphicObj.cpp
// Auther : 桜井 博之
// Data   : 2002/02/26
//==========================================================

#include "3DGraphicObj.h"

//----------------------------------------------
//	Name:	C3DGraphicObj
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3Dデバイス
//	Out:	なし
//----------------------------------------------
C3DGraphicObj::C3DGraphicObj(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* D3Dデバイスのセット */
	m_pd3dDevice = d3dDevice;

	/* マトリクス値の初期化 */
	D3DXMatrixIdentity(&m_matBase);
	D3DXMatrixIdentity(&m_matStock);
}

//----------------------------------------------
//	Name:	~C3DGraphicObj
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
C3DGraphicObj::~C3DGraphicObj()
{

}
//----------------------------------------------
//	Name:	GetPosBase
//	Func:	処理用マトリクスの値をベクトルで返す
//	in:		なし
//	Out:	D3DXVECTOR3
//----------------------------------------------
D3DXVECTOR3 C3DGraphicObj::GetPosBase()
{
	D3DXVECTOR3	vecTmp;

	vecTmp.x = m_matBase._41;
	vecTmp.y = m_matBase._42;
	vecTmp.z = m_matBase._43;

	return vecTmp;
}

//----------------------------------------------
//	Name:	GetPosStock
//	Func:	描画用マトリクスの値をベクトルで返す
//	in:		なし
//	Out:	D3DXVECTOR3
//----------------------------------------------
D3DXVECTOR3 C3DGraphicObj::GetPosStock()
{
	D3DXVECTOR3	vecTmp;

	vecTmp.x = m_matStock._41;
	vecTmp.y = m_matStock._42;
	vecTmp.z = m_matStock._43;

	return vecTmp;
}
