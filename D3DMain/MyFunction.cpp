//==========================================================
// MyFunction.h
// Func   : 自作汎用関数
// Auther : 桜井 博之
// Data   : 2002/01/15
//==========================================================
#include	"MyFunction.h"
//------------------------------------------
//	Name:	GetAngle
//	Func:	二つの長さの値から、その角度を求める
//	In:		double			*dwY
//			double			*dwX
//	Out:	double
//------------------------------------------
double GetAngle(CONST double dwY, CONST double dwX)
{
	double dwTmp;
	dwTmp = atan2(dwY,dwX);

	// ラジアン値を角度に変換
	dwTmp = (float)D3DXUntiRagian((float)dwTmp);

	return dwTmp;
}


//------------------------------------------
//	Name:	SetVec3Length
//	Func:	ベクトルを任意の長さに返す
//	In:		D3DXVECTOR3*		pOut
//			CONST D3DXVECTOR3*	pIn
//			float				fLength
//	Out:	D3DXVECTOR3
//------------------------------------------
D3DXVECTOR3	SetVec3Length(D3DXVECTOR3* pOut, CONST D3DXVECTOR3*	pIn, float fLength)
{
	D3DXVECTOR3	vecTmp;

	D3DXVec3Normalize(&vecTmp,pIn);
	vecTmp *= fLength;

	if(pOut)*pOut = vecTmp;
	return vecTmp;
}

//------------------------------------------
//	Name:	GetVec3Inverce
//	Func:	ベクトルを逆にして返す(笑)
//	In:		D3DXVECTOR3*		pOut
//			CONST D3DXVECTOR3*	pIn
//	Out:	D3DXVECTOR3
//------------------------------------------
D3DXVECTOR3 GetVec3Inverce(D3DXVECTOR3* pOut, CONST D3DXVECTOR3* pIn)
{
	D3DXVECTOR3	vecTmp = *pIn;

	vecTmp.x *= -1;
	vecTmp.y *= -1;
	vecTmp.z *= -1;

	if(pOut)	*pOut = vecTmp;
	return vecTmp;
}

//------------------------------------------
//	Name:	GetNormalVec3ToMat
//	Func:	マトリックスから
//			単位方向ベクトルを求める
//	In:		D3DXVECTOR3*		pVecOut
//			CONST D3DXMATRIX*	pMatIn
//	Out:	D3DXVECTOR3
//------------------------------------------
D3DXVECTOR3 GetNormalVec3ToMat(D3DXVECTOR3* pVecOut, CONST D3DXMATRIX* pMatIn)
{
	D3DXVECTOR3 vec3l(0, 0, 1);			// ローカル座標進行方向ベクトル
	D3DXVECTOR3	vec3w;					// ワールド座標進行方向ベクトル
	D3DXMATRIX	matTmp;

	matTmp = *pMatIn;

	// 対象の座標値をカット
	matTmp._41 = 0;
	matTmp._42 = 0;
	matTmp._43 = 0;

	// マトリクスから単位方向ベクトルに変換
	D3DXVec3TransformCoord(&vec3w, &vec3l, &matTmp);
	D3DXVec3Normalize(&vec3w,&vec3w);

	// 値を返す
	if(pVecOut)	*pVecOut = vec3w;
	return vec3w;
}

//----------------------------------------------------------
//	Name:	GetMatrixToVec
//	Func:	位置ベクトル、方向ベクトルから
//			マトリクスを求める (失敗したため未使用)
//	In:		D3DXMATRIX*			pMatOut	= 出力用マトリクス
//			CONST D3DXVECTOR3*	pVecPos	= 位置ベクトル
//			CONST D3DXVECTOR3*	pVecDir = 方向ベクトル
//	Out:	D3DXMATRIX
//----------------------------------------------------------
D3DXMATRIX	GetMatrixToVec(D3DXMATRIX* pMatOut,
						   CONST D3DXVECTOR3* pVecPos,
						   CONST D3DXVECTOR3* pVecDir)

{
	D3DXMATRIX matTmp;
	float fYaw, fPitch, fRoll;

	/* 方向ベクトルの値から、角度成分を求める */
	fYaw	= (float)atan2(pVecDir->x, pVecDir->z);
//	fPitch	= (float)atan2(pVecDir->z, pVecDir->y);
//	fRoll	= (float)atan2(pVecDir->y, pVecDir->x);

	fPitch = 0;
	fRoll = 0;

	/* それぞれの角度成分からマトリクスを求める */
	D3DXMatrixRotationYawPitchRoll(&matTmp, -fYaw/2, fPitch, fRoll);

	/* 指定位置に平行移動させる */
	matTmp._41 = pVecPos->x;
	matTmp._42 = pVecPos->y;
	matTmp._43 = pVecPos->z;

	/* 値を格納して返す */
	if(pMatOut)	*pMatOut = matTmp;
	return matTmp;
}

//------------------------------------------
//	Name:	MatUpdate
//	Func:	マトリクスを回転値のみ更新
//	In:		D3DXMATRIX*	pMatBase
//			D3DXMATRIX*	pMatRot
//	Out:	D3DXMATRIX
//------------------------------------------
D3DXMATRIX MatUpdate(const D3DXMATRIX* pMatBase, const D3DXMATRIX* pMatRot)
{
	D3DXMATRIX matTmp;

	D3DXMatrixIdentity(&matTmp);
	matTmp = *pMatRot * matTmp;

	// 元の座標値を足す
	matTmp._41 = pMatBase->_41;
	matTmp._42 = pMatBase->_42;
	matTmp._43 = pMatBase->_43;

	return matTmp;
}

//------------------------------------------
//	Name:	GetLengthEX
//	Func:	ベクトルの指定した軸だけの長さを返す
//			(たとえばＹ軸を無くしてＸ，Ｚ軸だけの長さを得る時に使用)
//	In:		const D3DXVECTOR3*	pVecIn
//			bool				XEnable
//			bool				YEnable
//			bool				ZEnable
//	Out:	float
//------------------------------------------
float GetLengthEX(const D3DXVECTOR3* pVecIn, bool XEnable, bool YEnable, bool ZEnable)
{
	D3DXVECTOR3	vecTmp;

	if(XEnable) vecTmp.x = pVecIn->x;	else vecTmp.x = 0;
	if(YEnable) vecTmp.y = pVecIn->y;	else vecTmp.y = 0;
	if(ZEnable) vecTmp.z = pVecIn->z;	else vecTmp.z = 0;

	return D3DXVec3Length(&vecTmp);

}
//------------------------------------------
//	Name:	D3DXUntiRagian
//	Func:	ラジアンを角度に変換して返す
//	In:		float	ragian = ラジアン値
//	Out:	int			   = 通常角度(0～360)
//------------------------------------------
float	D3DXUntiRagian(float ragian)
{
	return (ragian / 3.141592654f * 180.0f);
}

//------------------------------------------------------------------------------
//	Name:	SearchPlane
//	Func:	指定位置、指定ベクトルにより
//			メッシュデータの中の一番近い面と、その距離を求める
//
//	In:		CMeshObject*			pMeshIn		= 対象となるメッシュ
//			CONST	D3DXMATRIX*		pMatIn		= メッシュのマトリックス
//			CONST	D3DXVECTOR3*	pPosIn		= 指定ベクトル元座標
//			CONST	D3DXVECTOR3*	pVecIn		= 指定方向ベクトル
//			D3DXVECTOR3*			pCrossOut	= 交点座標値を格納して返す
//			D3DXPLANE*				pPlaneOut	= 結果の面の式を格納して返す
//			float*					pfLengthOut	= 面の交点との距離を返す	
//	Out:	bool								= 面の取得に成功したらTRUE
//------------------------------------------------------------------------------
bool SearchPlane(CMeshObject* pMeshIn, CONST D3DXMATRIX* pMatIn,
				 CONST D3DXVECTOR3* pPosIn, CONST D3DXVECTOR3* pVecIn,
				 D3DXVECTOR3* pCrossOut, D3DXPLANE*	pPlaneOut, float* pfLengthOut)
{
	typedef struct {
		D3DXVECTOR3 v;
		D3DCOLOR color;
	} VERTEX;

	LPDIRECT3DVERTEXBUFFER8	pVB;		// 頂点バッファインターフェイス
	LPDIRECT3DINDEXBUFFER8	pIB;		// インデックスバッファインターフェイス
	DWORD	dwNumFaces;					// 面の数

	// 頂点バッファ、インデックスバッファへのアクセス用
	WORD	*pIndices;
	VERTEX	*pVertices;

	// バッファのインターフェイス取得
	pMeshIn->GetSysMemMesh()->GetVertexBuffer(&pVB);
	pMeshIn->GetSysMemMesh()->GetIndexBuffer(&pIB);
	// 面の数を取得
	dwNumFaces = pMeshIn->GetLocalMesh()->GetNumFaces();

	// ポリゴンを探す
	D3DXVECTOR3	Vertex[3];
	D3DXVECTOR3	CrossPoint;
	D3DXVECTOR3	CrossPointMax;		// 採用する交点座標値
	D3DXPLANE	PlaneTmp;

	D3DXPLANE	PlaneMax;			// 採用する面の式
	float		fLengthMax=99999;	// 採用する面と指定座標との距離
	float		fLengthTmp;
	DWORD		i;

	pVB->Lock(0,0,(BYTE**)&pVertices,0);
	pIB->Lock(0,0,(BYTE**)&pIndices,0);

	// 面の数だけ繰り返す
	for(i=0; i<dwNumFaces; i++)
	{
		// インデックスバッファより、ポリゴンの３頂点を求める
		Vertex[0] = pVertices[pIndices[i*3+0]*2].v;
		Vertex[1] = pVertices[pIndices[i*3+1]*2].v;
		Vertex[2] = pVertices[pIndices[i*3+2]*2].v;

		// 頂点をワールド変換(？)
		D3DXVec3TransformCoord(&Vertex[0], &Vertex[0], pMatIn);
		D3DXVec3TransformCoord(&Vertex[1], &Vertex[1], pMatIn);
		D3DXVec3TransformCoord(&Vertex[2], &Vertex[2], pMatIn);

		// 三つの頂点から面の式を算出する
		D3DXPlaneFromPoints(&PlaneTmp, &Vertex[0], &Vertex[1], &Vertex[2]);
		// 調べたい点、ベクトル方向が面の表にあるか調べる

		D3DXVECTOR3 negVec = (*pVecIn) * -1.0f;
		D3DXVECTOR3 normal(PlaneTmp.a, PlaneTmp.b, PlaneTmp.c);

		if(	D3DXPlaneDotCoord(&PlaneTmp, pPosIn) > 0 &&
			D3DXVec3Dot(&normal, &negVec) > 0)
		{
			// 指定した直線と求めた面との交点を求める
			D3DXVECTOR3 linePoint1 = *pPosIn;
			D3DXVECTOR3 linePoint2 = *pPosIn + *pVecIn;
			D3DXVECTOR3 CrossPoint;

			if(D3DXPlaneIntersectLine(&CrossPoint, &PlaneTmp, &linePoint2, &linePoint1))
			//if(D3DXPlaneIntersectLine(&CrossPoint, &PlaneTmp, &(*pPosIn + *pVecIn), pPosIn))
			{
				// 面との交点が三つの頂点の中にあるかどうか判別する
				if(PointInPoly(&Vertex[0], &Vertex[1], &Vertex[2], &CrossPoint))
				{
					// 指定した頂点と求めた交点との距離を求め、一番距離の短い面を採用する
					D3DXVECTOR3 diff = CrossPoint - *pPosIn;
					fLengthTmp = D3DXVec3Length(&diff);
					if(fLengthTmp < fLengthMax){
						fLengthMax = fLengthTmp;
						PlaneMax = PlaneTmp;
						CrossPointMax = CrossPoint;
					}
				}
			}
		}
	}
	pVB->Unlock();
	pIB->Unlock();

	// 頂点バッファをリリース
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);

	// 面が見つかった場合値を格納してTRUEを返す
	if(fLengthMax < 99999){
		if(pCrossOut)	*pCrossOut = CrossPointMax;
		if(pPlaneOut)	*pPlaneOut = PlaneMax;
		*pfLengthOut = fLengthMax;
		return	true;
	}
	// 見つからなかった場合FALSEを返す
	return false;
}

//------------------------------------------------------------------------------
//	Name:	SearchPlane2
//	Func:	指定位置、指定ベクトルにより
//			メッシュデータの中の面を見つけ、指定位置との最短距離(法線ベクトル)を求める。
//			同時に、指定ベクトルと面との交点も返す。
//			その最短距離が一番短い面を採用し、交点座標値、面の式、面との最短距離を返す。
//
//	In:		CMeshObject*				pMeshIn		// 対象となるメッシュ
//			CONST	D3DXMATRIX*		pMatIn		// メッシュのマトリックス
//			CONST	D3DXVECTOR3*	pPosIn		// 指定ベクトル元座標
//			CONST	D3DXVECTOR3*	pVecIn		// 指定方向ベクトル
//			D3DXVECTOR3*			pCrossOut1	// 法線ベクトルとの交点座標値を格納して返す
//			D3DXVECTOR3*			pCrossOut2	// 指定ベクトルとの交点座標値を格納して返す
//			D3DXPLANE*				pPlaneOut	// 結果の面の式を格納して返す
//			float*					pfLenOut	// 面の交点との距離を返す
//	Out:	bool								// 面の取得に成功したらTRUE
//------------------------------------------------------------------------------
bool SearchPlane2(CMeshObject* pMeshIn, CONST D3DXMATRIX* pMatIn,
				 CONST D3DXVECTOR3* pPosIn, CONST D3DXVECTOR3* pVecIn,
				 D3DXVECTOR3* pCrossOut1, D3DXVECTOR3* pCrossOut2, 
				 D3DXPLANE*	pPlaneOut, float* pfLenOut)
{
	typedef struct {
		D3DXVECTOR3 v;
		D3DCOLOR color;
	} VERTEX;

	LPDIRECT3DVERTEXBUFFER8	pVB;		// 頂点バッファインターフェイス
	LPDIRECT3DINDEXBUFFER8	pIB;		// インデックスバッファインターフェイス
	DWORD	dwNumFaces;					// 面の数

	// 頂点バッファ、インデックスバッファへのアクセス用
	WORD	*pIndices;
	VERTEX	*pVertices;

	// バッファのインターフェイス取得
	pMeshIn->GetSysMemMesh()->GetVertexBuffer(&pVB);
	pMeshIn->GetSysMemMesh()->GetIndexBuffer(&pIB);
	// 面の数を取得
	dwNumFaces = pMeshIn->GetLocalMesh()->GetNumFaces();

	// ポリゴンを探す
	D3DXVECTOR3	Vertex[3];

	D3DXVECTOR3	vecCross1;			// 一時的に保存する交点座標値
	D3DXVECTOR3 vecCross2;

	D3DXVECTOR3	vecCrossAdop1;		// 採用する交点座標値
	D3DXVECTOR3	vecCrossAdop2;

	D3DXVECTOR3	vecN;				// 法線ベクトルを格納するのに使用

	D3DXPLANE	plaTmp;				// 採用する面の式
	D3DXPLANE	plaAdop;

	float		fLenAdop=99999;		// 採用する面と指定座標との距離
	float		fLen;
	DWORD		i;

	pVB->Lock(0,0,(BYTE**)&pVertices,0);
	pIB->Lock(0,0,(BYTE**)&pIndices,0);

	// 面の数だけ繰り返す
	for(i=0; i<dwNumFaces; i++)
	{
		// インデックスバッファより、ポリゴンの３頂点を求める
		Vertex[0] = pVertices[pIndices[i*3+0]*2].v;
		Vertex[1] = pVertices[pIndices[i*3+1]*2].v;
		Vertex[2] = pVertices[pIndices[i*3+2]*2].v;

		// 頂点をワールド変換(？)
		D3DXVec3TransformCoord(&Vertex[0], &Vertex[0], pMatIn);
		D3DXVec3TransformCoord(&Vertex[1], &Vertex[1], pMatIn);
		D3DXVec3TransformCoord(&Vertex[2], &Vertex[2], pMatIn);

		// 三つの頂点から面の式を算出する
		D3DXPlaneFromPoints(&plaTmp, &Vertex[0], &Vertex[1], &Vertex[2]);

		// 調べたい点、ベクトル方向が面の表にあるか調べる
		D3DXVECTOR3 normal(plaTmp.a, plaTmp.b, plaTmp.c);
		D3DXVECTOR3 negVec = (*pVecIn) * -1.0f;

		if (D3DXPlaneDotCoord(&plaTmp, pPosIn) > 0 &&
			D3DXVec3Dot(&normal, &negVec) > 0)
		{
			// 指定した移動ベクトルと面との交点を求める
			D3DXVECTOR3 linePoint1 = *pPosIn;
			D3DXVECTOR3 linePoint2 = *pPosIn + *pVecIn;
			D3DXVECTOR3 vecCross2;

			if(D3DXPlaneIntersectLine(&vecCross2, &plaTmp, &linePoint2, &linePoint1))
			{
				// 見つかった面の逆法線ベクトルを取得する
				vecN.x = -plaTmp.a;
				vecN.y = -plaTmp.b;
				vecN.z = -plaTmp.c;

				// 指定した逆法線ベクトルとその法線ベクトルを持つ面との交点を求める
				D3DXVECTOR3 linePoint1 = *pPosIn;
				D3DXVECTOR3 linePoint2 = *pPosIn + vecN;  // 一時オブジェクトではなく変数に格納
				D3DXVECTOR3 vecCross1;

				if(D3DXPlaneIntersectLine(&vecCross1, &plaTmp, &linePoint2, &linePoint1))
				{
					// 面との交点が三つの頂点の中にあるかどうか判別する
					if(PointInPoly(&Vertex[0], &Vertex[1], &Vertex[2], &vecCross1))
					{
						// 求めた法線ベクトルの、一番距離の短い面を採用する
						D3DXVECTOR3 diff = vecCross1 - *pPosIn;
						fLen = D3DXVec3Length(&diff);
						if(fLen < fLenAdop){
							fLenAdop = fLen;
							plaAdop = plaTmp;
							vecCrossAdop1 = vecCross1;
							vecCrossAdop2 = vecCross2;
						}
					}
				}
			}
		}
	}

	pVB->Unlock();
	pIB->Unlock();

	// 頂点バッファをリリース
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);

	// 面が見つかった場合値を格納してTRUEを返す
	if(fLenAdop < 99999){
		if(pCrossOut1)	*pCrossOut1 = vecCrossAdop1;
		if(pCrossOut2)	*pCrossOut2 = vecCrossAdop2;
		if(pPlaneOut)	*pPlaneOut = plaAdop;
		*pfLenOut = fLenAdop;
		return	true;
	}
	// 見つからなかった場合FALSEを返す
	return false;
}


//------------------------------------------------------------------------------
//	Name:	PointInPoly
//	Func:	指定した３点で作られる三角形の中に、３角形で作られる面上の
//			指定した座標があるかどうかを判別する
//
//	In:		CONST	D3DXVECTOR3*	pV1 = 指定座標１
//			CONST	D3DXVECTOR3*	pV2	= 指定座標２
//			CONST	D3DXVECTOR3*	pV3	= 指定座標３
//			CONST	D3DXVECTOR3*	pVP	= 指定ポイント	
//	Out:	bool	= 三角形の中にポイントがあったらTRUE
//------------------------------------------------------------------------------
bool PointInPoly(CONST D3DXVECTOR3* pV1, CONST D3DXVECTOR3* pV2,
				 CONST D3DXVECTOR3* pV3, CONST D3DXVECTOR3* pVP)
{
	D3DXVECTOR3 vec1, vec2;
	D3DXVECTOR3	vTmp1,vTmp2,vTmp3;		// 法線ベクトル

	// 外積により法線ベクトルを求める
	vec1 = *pV2 - *pV1;
	vec2 = *pVP - *pV1;
	D3DXVec3Cross(&vTmp1, &vec1, &vec2);

	vec1 = *pV3 - *pV2;
	vec2 = *pVP - *pV2;
	D3DXVec3Cross(&vTmp2, &vec1, &vec2);

	vec1 = *pV1 - *pV3;
	vec2 = *pVP - *pV3;
	D3DXVec3Cross(&vTmp3, &vec1, &vec2);


	// 法線ベクトルを単位ベクトルにする
	D3DXVec3Normalize(&vTmp1, &vTmp1);
	D3DXVec3Normalize(&vTmp2, &vTmp2);
	D3DXVec3Normalize(&vTmp3, &vTmp3);

	// すべての法線ベクトルが並行かどうか確認
	// 微妙な誤差は無視する
	if(	fabs(vTmp1.x-vTmp2.x) < 0.005 &&
		fabs(vTmp1.y-vTmp2.y) < 0.005 &&
		fabs(vTmp1.z-vTmp2.z) < 0.005 &&

		fabs(vTmp1.x-vTmp3.x) < 0.005 &&
		fabs(vTmp1.y-vTmp3.y) < 0.005 &&
		fabs(vTmp1.z-vTmp3.z) < 0.005 )
		return true;

	// どれかひとつの法線ベクトルが0なら、線上に点があるとみなされる
	if(	vTmp1.x == 0 && vTmp1.y == 0 && vTmp1.z == 0 ||
		vTmp2.x == 0 && vTmp2.y == 0 && vTmp2.z == 0 ||
		vTmp3.x == 0 && vTmp3.y == 0 && vTmp3.z == 0)
		return true;

	return false;
}

//------------------------------------------------------------------------------
//	Name:	PlaneReflect
//	Func:	面との反射ベクトルを求める
//
//	In:		D3DXVECTOR3*			pOut		// 反射ベクトル
//			CONST	D3DXPLANE*		pPlaneIn	// 指定面
//			CONST	D3DXVECTOR3*	pVecIn		// 指定ベクトル
//	Out:	D3DXVECTOR3							// 反射ベクトル
//------------------------------------------------------------------------------
D3DXVECTOR3 PlaneReflect(D3DXVECTOR3* pOut, CONST D3DXPLANE* pPlaneIn, 
								CONST D3DXVECTOR3* pVecIn)
{

	D3DXVECTOR3 VecN, VecIn, VecOut;
	float fDot;

	// 面の法線ベクトルを求める
	VecN.x = pPlaneIn->a;
	VecN.y = pPlaneIn->b;
	VecN.z = pPlaneIn->c;

	// 指定ベクトルの逆方向ベクトル算出
	VecIn = *pVecIn * -1.0f;

	// 面の法線と指定逆ベクトルの内積を計算
	// この内積結果がマイナスの場合は
	// 面の裏側に当たっていることになる
	fDot = D3DXVec3Dot(&VecIn, &VecN);

	// 正反射ベクトルの算出
	VecOut = ( 2 * fDot * VecN ) - VecIn;

	if(pOut)	*pOut = VecOut;
	return VecOut;

}

//------------------------------------------------------------------------------
//	Name:	TransProject
//	Func:	３次元座標からプロジェクションに投影した３次元座標を得る
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3Dデバイス
//			D3DXVECTOR3*		pVec3Out	= 投影後の座標
//			D3DXVECTOR3*		pVec3In		= 投影前の座標
//	Out:	D3DXVECTOR3
//------------------------------------------------------------------------------
D3DXVECTOR3 TransProject(LPDIRECT3DDEVICE8 d3dDevice,
						 D3DXVECTOR3* pVec3Out, D3DXVECTOR3* pVec3In)
{
	D3DVIEWPORT8 Viewport;		// ビューポート
	D3DXMATRIX   matView;		// ビューマトリックス
	D3DXMATRIX   matProjct;		// プロジェクションマトリックス

	/* プロジェクションの設定 */
	d3dDevice->GetViewport ( &Viewport );
	d3dDevice->GetTransform( D3DTS_VIEW, &matView );
	d3dDevice->GetTransform( D3DTS_PROJECTION, &matProjct );

	/* ワールド座標を設定 */
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	/* プロジェクション投影する */
	D3DXVec3Project(
	  pVec3Out,
	  pVec3In,
	  &Viewport,
	  &matProjct,
	  &matView,
	  &matWorld
	);

	return *pVec3Out;
}