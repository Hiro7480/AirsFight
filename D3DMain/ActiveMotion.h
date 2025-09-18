//==========================================================
// ActiveMotion.h
// Auther : 桜井 博之
// Data   : 2002/04/16
//==========================================================

#if !defined(AFX_Active_H__2AA65FEF_1CB0_4E22_8246_689FB7A01849__INCLUDED_)
#define AFX_Active_H__2AA65FEF_1CB0_4E22_8246_689FB7A01849__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------
#include "CompatiDX8.h"
#include <d3d8.h>
#include <d3dx8.h>
#include "MeshData.h"
#include "MotionData.h"

//----------------------------------------------------------
//	Name	: CActiveFrame
//	Func	: 対応するCMeshFrameとCMotionFrameをもつ
//----------------------------------------------------------
class CActiveFrame  
{
private:
	CMeshFrame*		m_pMeshFrame;		// 対応するメッシュフレーム
	CMotionFrame*	m_pMotionFrame;		// 対応するアニメーション

	D3DXQUATERNION	m_qtMotion;			// モーション用クオータニオン（回転補正値）
	D3DXVECTOR3		m_vecMotion;		// モーション用ベクトル（位置補正値）

public:
	
	HRESULT	Create(CMeshFrame* pMeshFrame, CMotionFrame* pMotionFrame);	// 初期化
	HRESULT	ComputQuat(int nActiveTime);			// 現在時間から回転補正値を算出
	HRESULT	ComputVec(int nActiveTime);				// 現在時間から位置補正値を算出

	D3DXQUATERNION	GetQuat();						// 回転補正値を返す
	D3DXVECTOR3		GetVec();						// 位置補正値を返す

	HRESULT	Destroy();								// 全オブジェクトの削除

	float SuppleNum(int nMiddle, int nMax, int nMin);
	CActiveFrame();
	virtual ~CActiveFrame();

};

//----------------------------------------------
//	Name:	GetQuat
//	Func:	回転補正値（クオータニオン）を返す
//	in:		なし
//	Out:	D3DXQUATERNION = 回転補正値
//----------------------------------------------
inline D3DXQUATERNION CActiveFrame::GetQuat()
{
	return m_qtMotion;
}

//----------------------------------------------
//	Name:	GetVec
//	Func:	位置補正値（ベクトル）を返す
//	in:		なし
//	Out:	D3DXVECTOR3 = 位置補正値
//----------------------------------------------
inline D3DXVECTOR3 CActiveFrame::GetVec()
{
	return m_vecMotion;
}

//----------------------------------------------------------
//	Name	: CActiveData
//	Func	: ひとつのアニメーションをリアルタイムに更新する
//----------------------------------------------------------
class CActiveData  
{
private:
	friend class CActiveMotion;

	CMeshData*			m_pMeshData;			// 対応するメッシュデータ
	CMotionData*		m_pMotionData;			// 対応するモーションデータ

	CActiveFrame*		m_pActiveFrame[32];		// フレームデータ
	int					m_nActiveFrameNum;		// フレームデータ数

	int					m_nMaxTime;				// 最大フレーム時間
	int					m_nActiveTime;			// 現在フレーム時間

public:

	HRESULT	CreateFrame(CMeshData* pMeshData,	// フレームデータの作成
			CMotionData* pMotionData);
	HRESULT	ComputMotion();						// 現在時間からクオータニオンを算出
	HRESULT	Run();								// アニメーションの再生

	HRESULT Destroy();							// 全オブジェクトの削除

	/* アクセス関数 */
	int		GetMaxTime();						// 最大フレーム時間を返す
	void	SetActiveTime(int nTime);			// 現在フレーム時間のセット

	CActiveData();
	virtual ~CActiveData();

};

//----------------------------------------------
//	Name:	GetMaxTime
//	Func:	最大フレーム時間を返す
//	in:		なし
//	Out:	int = 最大フレーム時間
//----------------------------------------------
inline int CActiveData::GetMaxTime()
{
	return m_nMaxTime;
};

//----------------------------------------------
//	Name:	SetActiveTime
//	Func:	現在フレーム時間のセット
//	in:		int nTime = 指定フレーム時間
//	Out:	なし
//----------------------------------------------
inline void CActiveData::SetActiveTime(int nTime)
{
	m_nActiveTime = nTime;
};

//----------------------------------------------------------
//	Name	: CActiveMotion
//	Func	: 複数のモーションを総管理するクラス
//----------------------------------------------------------
class CActiveMotion
{
private:
	CMeshData*			m_pMeshData;				// 対応するメッシュデータ
	D3DXMATRIX			m_matMotion[32];			// モーションマトリクス配列
	D3DXMATRIX			m_matStock[32];				// 描画時用マトリクス配列
	int					m_nMeshFrameNum;			// メッシュフレーム数

	CActiveData*		m_pActiveData[32];			// モーションデータ配列ポインタ
	float				m_fBlendNum[32];			// ブレンド係数
	int					m_nActiveDataNum;			// モーションデータ数

public:
	HRESULT	LoadMesh(CMeshData* pMeshData);			// メッシュデータのセット
	HRESULT	LoadMotion(CMotionData* pMotionData);	// モーションデータ作成

	HRESULT	Render();								// 描画処理
	HRESULT	UpDate();								// 描画用マトリクス更新

	HRESULT	Destroy();								// 終了処理

	HRESULT	ChangeMotion(int nNum, float fChangeSpeed=0.1f);				// 現在のモーションの変更
	HRESULT	ChangeMotion(int nNum1, int nNum2, float fChangeSpeed=0.1f);	// 指定モーションを二つずつ半々に持つ
	HRESULT	Play();															// さまざまなデータの更新

	HRESULT	ComputMatrix();		// ブレンド係数により補完をした現在のモーションマトリクスを求める
	HRESULT	ComputAllMotion();	// 全てのモーションフレームのモーションデータの計算

	/* アクセス関数 */
	D3DXMATRIX		GetMatMotion(int nFrame);				// 指定フレームのマトリクスの取得
	int				GetMeshFrameNum();						// メッシュフレーム数の取得
	CActiveData*	GetMotion(int nMotion);					// 指定モーションデータの取得
	float			GetBlend(int nMotion);					// 指定モーションのブレンド係数の取得
	int				GetMotionNum();							// 全モーション数の取得
	int				GetMaxTime(int nMotion);				// 指定モーションの最大フレーム数の取得

	void			SetMatMotion(D3DXMATRIX matMotion,int nFrame);	// 指定フレームのマトリクスのセット
	void			SetBlend(int nMotion, float fBlend);		// 指定モーションのブレンド係数のセット
	void			SetActiveTime(int nMotion, int nTime);		// 指定モーションに現在時間のセット

	CActiveMotion();
	virtual ~CActiveMotion();

};
//------------------------------------------------------
//	Name:	GetMatMotion
//	Func:	指定フレームのマトリクスの取得
//	in:		int	nFrame	= 指定フレーム 
//	Out:	D3DXMATRIX	= マトリクス
//------------------------------------------------------
inline D3DXMATRIX CActiveMotion::GetMatMotion(int nFrame)
{
	return m_matMotion[nFrame];
};

//------------------------------------------------------
//	Name:	GetMeshFrameNum
//	Func:	メッシュフレーム数の取得
//	in:		なし
//	Out:	int = メッシュフレーム数
//------------------------------------------------------
inline int CActiveMotion::GetMeshFrameNum()
{
	return m_nMeshFrameNum;
};

//------------------------------------------------------
//	Name:	GetMotion
//	Func:	指定モーションデータの取得
//	in:		int	nMotion	= 指定モーション 
//	Out:	CActiveData = モーションデータ
//------------------------------------------------------
inline CActiveData* CActiveMotion::GetMotion(int nMotion)
{
	return m_pActiveData[nMotion];
};

//------------------------------------------------------
//	Name:	GetMotionNum
//	Func:	モーション数の取得
//	in:		なし
//	Out:	int = モーション数
//------------------------------------------------------
inline int CActiveMotion::GetMotionNum()
{
	return m_nActiveDataNum;
};

//------------------------------------------------------
//	Name:	GetBlend
//	Func:	指定モーションのブレンド係数の取得
//	in:		int nMotion	= 指定モーション
//	Out:	float		= ブレンド係数
//------------------------------------------------------
inline float CActiveMotion::GetBlend(int nMotion)
{
	return m_fBlendNum[nMotion];
}

//------------------------------------------------------
//	Name:	GetMaxTime
//	Func:	指定モーションの最大フレーム数を返す
//	in:		int nMotion	= 指定モーション
//	Out:	int			= 最大フレーム数
//------------------------------------------------------
inline int CActiveMotion::GetMaxTime(int nMotion)
{
	return m_pActiveData[nMotion]->GetMaxTime();
}

//------------------------------------------------------
//	Name:	SetMatMotion
//	Func:	指定フレームのマトリクスのセット
//	in:		D3DXMATRIX	matMotion
//			int			nFrame
//	Out:	なし
//------------------------------------------------------
inline void CActiveMotion::SetMatMotion(D3DXMATRIX matMotion, int nFrame)
{
	m_matMotion[nFrame] = matMotion;
}

//------------------------------------------------------
//	Name:	SetBlend
//	Func:	指定モーションにブレンド係数をセット
//	in:		int		nMotion	= 指定モーション
//			float	fBlend	= ブレンド係数
//	Out:	なし
//------------------------------------------------------
inline void CActiveMotion::SetBlend(int nMotion, float fBlend)
{
	m_fBlendNum[nMotion]=fBlend;
}

//------------------------------------------------------
//	Name:	SetBlend
//	Func:	現在フレーム時間の格納
//	in:		int		nMotion = 指定モーション
//			int		nTime	= 指定時間
//	Out:	なし
//------------------------------------------------------
inline void CActiveMotion::SetActiveTime(int nMotion, int nTime)
{
	m_pActiveData[nMotion]->SetActiveTime(nTime);
}

#endif // !defined(AFX_Active_H__2AA65FEF_1CB0_4E22_8246_689FB7A01849__INCLUDED_)
