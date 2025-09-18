//==========================================================
// LockOnMarker.h
// Auther : 桜井 博之
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_LOCKONMARKER_H__BDEA9907_A551_40BC_856E_92D4D9955DBE__INCLUDED_)
#define AFX_LOCKONMARKER_H__BDEA9907_A551_40BC_856E_92D4D9955DBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------
#include "Sprite.h"

//----------------------
//	状態識別子の定義
//----------------------
enum{
	NOT_LOCK,		// ロックオン出来ない
	CAN_LOCK,		// ロックオン出来る
	TAG_LOCK,		// ターゲットとしてロックオンが出来る
	NOW_LOCK		// ロックオンしている
};

//--------------------------------------------------
//	Name:	CLockOnMarker
//	Func:	ロックオンマーカーのスプライトを管理
//--------------------------------------------------
class CLockOnMarker : public CSprite  
{
private:
	DWORD	m_dwStatus;		// 現在の状態を表す

	float	m_fScale;		// スケール値
	float	m_fAlpha;		// アルファ値

public:
	void FrameMove();		// 毎フレームの処理
	void Render();			// 描画処理

	/* アクセス関数 */
	void SetStatus(DWORD dwStatus){m_dwStatus = dwStatus;};	// 状態を格納

	CLockOnMarker(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName);
	virtual ~CLockOnMarker();

};

#endif // !defined(AFX_LOCKONMARKER_H__BDEA9907_A551_40BC_856E_92D4D9955DBE__INCLUDED_)
