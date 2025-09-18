// =================================
//	File:	MyFunction.h
//	Func:	自作汎用関数
//  Date:	2002/01/04
//	Author:	桜井 博之
// =================================

#ifndef MYFUNCTION_H
#define MYFUNCTION_H

//------------------------------
//	インクルード
//------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "MeshData.h"

//------------------------------
//	プロトタイプ宣言
//------------------------------

//------------------------------------------
//	Name:	GetAngle
//	Func:	二つの長さの値から、その角度を求める
//------------------------------------------
double		GetAngle(CONST double dwY, CONST double dwX);

//------------------------------------------
//	Name:	SetVec3Length
//	Func:	ベクトルを任意の長さに返す
//------------------------------------------
D3DXVECTOR3	SetVec3Length(D3DXVECTOR3* pOut, CONST D3DXVECTOR3*	pIn, float fLength);

//------------------------------------------
//	Name:	GetVec3Inverce
//	Func:	ベクトルを逆にして返す(笑)
//------------------------------------------
D3DXVECTOR3 GetVec3Inverce(D3DXVECTOR3* pOut, CONST D3DXVECTOR3* pIn);

//------------------------------------------
//	Name:	GetNormalVec3ToMat
//	Func:	マトリックスから
//			単位方向ベクトルを求める
//------------------------------------------
D3DXVECTOR3 GetNormalVec3ToMat(D3DXVECTOR3* pVecOut, CONST D3DXMATRIX* pMatIn);

//------------------------------------------
//	Name:	GetMatrixToVec
//	Func:	位置ベクトル、方向ベクトルから
//			マトリクスを求める
//------------------------------------------
D3DXMATRIX	GetMatrixToVec(D3DXMATRIX* pMatOut, CONST D3DXVECTOR3* pVecPos, CONST D3DXVECTOR3* pVecDir);

//------------------------------------------
//	Name:	MatUpdate
//	Func:	マトリクスを回転値のみ更新
//------------------------------------------
D3DXMATRIX	MatUpdate(const D3DXMATRIX* pMatBase, const D3DXMATRIX* pMatRot);

//------------------------------------------------------------------
//	Name:	GetLengthEX
//	Func:	ベクトルの指定した軸だけの長さを返す
//			(たとえばＹ軸を無くしてＸ，Ｚ軸だけの長さを得る時に使用)
//------------------------------------------------------------------
float		GetLengthEX(const D3DXVECTOR3* pVecIn, bool XEnable, bool YEnable, bool ZEnable);

//------------------------------------------
//	Name:	D3DXUntiRagian
//	Func:	ラジアンを角度に変換して返す
//------------------------------------------
float		D3DXUntiRagian(float ragian);

//------------------------------------------------------------------------------
//	Name:	SearchPlane
//	Func:	指定位置、指定ベクトルにより
//			メッシュデータの中の一番近い面と、その距離を求める
//------------------------------------------------------------------------------
bool SearchPlane(CMeshObject* pMeshIn, CONST D3DXMATRIX* pMatIn,
				 CONST D3DXVECTOR3* pPosIn, CONST D3DXVECTOR3* pVecIn,
				 D3DXVECTOR3* pCrossOut, D3DXPLANE*	pPlaneOut, float* pfLengthOut);

//------------------------------------------------------------------------------
//	Name:	SearchPlane2
//	Func:	指定位置、指定ベクトルによりメッシュデータの中の面を見つけ、
//			指定位置との最短距離(法線ベクトル)を求める。
//			同時に、指定ベクトルと面との交点も返す。
//			その最短距離が一番短い面を採用し、交点座標値、面の式、面との最短距離を返す。
//------------------------------------------------------------------------------
bool SearchPlane2(CMeshObject* pMeshIn, CONST D3DXMATRIX* pMatIn,
				 CONST D3DXVECTOR3* pPosIn, CONST D3DXVECTOR3* pVecIn,
				 D3DXVECTOR3* pCrossOut1, D3DXVECTOR3* pCrossOut2, 
				 D3DXPLANE*	pPlaneOut, float* pfLenOut);

//------------------------------------------------------------------------------
//	Name:	PointInPoly
//	Func:	指定した３点で作られる三角形の中に、３角形で作られる面上の
//			指定した座標があるかどうかを判別する
//------------------------------------------------------------------------------
bool PointInPoly(CONST D3DXVECTOR3* pV1, CONST D3DXVECTOR3* pV2,
				 CONST D3DXVECTOR3* pV3, CONST D3DXVECTOR3* pVP);

//------------------------------------------------------------------------------
//	Name:	PlaneReflect
//	Func:	面との反射ベクトルを求める
//------------------------------------------------------------------------------
D3DXVECTOR3 PlaneReflect(D3DXVECTOR3* pOut, CONST D3DXPLANE* pPlaneIn, 
						 CONST D3DXVECTOR3* pVecIn);
//------------------------------------------------------------------------------
//	Name:	TransProject
//	Func:	３次元座標からプロジェクションに投影した３次元座標を得る
//------------------------------------------------------------------------------
D3DXVECTOR3 TransProject(LPDIRECT3DDEVICE8 d3dDevice,
						 D3DXVECTOR3* pVec3Out, D3DXVECTOR3* pVec3In);


#endif