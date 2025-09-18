//==========================================================
// Camera.h
// Auther : 桜井 博之
// Data   : 2002/02/20
//==========================================================

#if !defined(AFX_CAMERA_H__E859F97C_FFC1_471D_9A68_CDF90E8FBD4A__INCLUDED_)
#define AFX_CAMERA_H__E859F97C_FFC1_471D_9A68_CDF90E8FBD4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include <d3dx8.h>
#include "MyFunction.h"
#include "3DGraphicObj.h"
#include "MyPlayer.h"

//----------------------------------------------
//	Name:	CCamera
//	Func:	カメラクラス
//----------------------------------------------
class CCamera:public C3DGraphicObj
{
private:
	D3DXVECTOR3	m_vecPos;				// カメラの位置
	D3DXVECTOR3	m_vecStock;				// ストック用カメラ位置
	float		m_fNowYaw;				// 現在Yaw角度
	float		m_fNowPitch;			// 現在Pitch角度
	float		m_fNextYaw;				// 目標Yaw角度
	float		m_fNextPitch;			// 目標Pitch角度

	float		m_fFrameSpeed;			// カメラの１フレーム移動量
	float		m_fLength;				// カメラと目標との距離

	/* カメラの位置を動かす関数 */
	void	SetPosition(CChara* pChara);		// カメラ位置の算出
	void	SetNowYaw(CChara* pChara);			// 現在Yaw角度の算出
	void	SetNowPitch(CChara* pChara);		// 現在Pitch角度の算出
	void	SetNextYaw(D3DXVECTOR3* vecIn);		// 目標Yaw角度の算出
	void	SetNextPitch(D3DXVECTOR3* vecIn);	// 目標Pitch角度の算出
	void	SetNextPitch(float fPitch);			// 目標Pitch角度の直接格納
	void	MoveYaw();							// 現在Yaw角度を目標Yaw角度に近づける
	void	MovePitch();						// 現在Pitch角度を目標Pitch角度に近づける

public:
	void	FrameMove(CMyPlayer* pMyPlayer);	// 毎フレームの処理
	void	Render(CChara* pChara);				// 描画時の処理
	void	UpDate();							// 描画用変数の更新

	D3DXVECTOR3	GetPosition(){return m_vecPos;};	// カメラ位置を返す

	CCamera(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CCamera();

};

#endif // !defined(AFX_CAMERA_H__E859F97C_FFC1_471D_9A68_CDF90E8FBD4A__INCLUDED_)
