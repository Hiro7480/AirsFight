//==========================================================
// Bullet.h
// Auther : 桜井 博之
// Data   : 2002/01/11
//==========================================================

#if !defined(AFX_BULLET_H__7E4D9C62_06AE_11D6_AE81_0000F4905862__INCLUDED_)
#define AFX_BULLET_H__7E4D9C62_06AE_11D6_AE81_0000F4905862__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include <d3dx8.h>
#include "MyFunction.h"
#include "3DGraphicObj.h"
#include "MeshData.h"

#include "EffectManage.h"

//----------------------------------------------
//	Name:	BulStatus
//	Func:	弾ステータス構造体
//----------------------------------------------
typedef	struct {
	CMeshObject*	pBulMesh;			// 弾メッシュデータ
	int				nMaxLife;			// 有効最大時間(フレーム数)
	int				nShotFrame;			// 連射性能(次の弾が出るまでのフレーム数)
	float			fSpeed;				// 移動速度

} tagBulParam;

//----------------------------------------------
//	Name:	CBullet
//	Func:	弾クラス
//----------------------------------------------
class CBullet: public C3DGraphicObj
{
private:
	long			m_lID;				// 識別番号
	CBullet*		m_pNext;			// 次の弾へのポインタ
	D3DXVECTOR3		m_vecMove;			// 移動ベクトル
	tagBulParam*	m_pBulStatus;		// 固定ステータス(ポインタ)
	int				m_nTimeCount;		// 作られてからの経過時間

public:
	void FrameMove(CEffectManage* pEffectManage);	// 毎フレームの処理
	void Render();									// 画面描画
	bool IsDelete();								// 弾を消すかどうかを判定

	void Delete(){m_nTimeCount = m_pBulStatus->nMaxLife;};	// 強制的に弾を消す

	/* アクセス関数 */
	CBullet*	GetNext(){return m_pNext;};					// 次の弾へのポインタを返す
	D3DXVECTOR3	GetMoveVec(){return m_vecMove;};			// 移動ベクトル値を返す
	int			GetTimeCount(){return m_nTimeCount;};		// 作られてからの経過時間を返す
	int			GetID(){return m_lID;};						// IDを返す

	void		SetNext(CBullet* pNext){m_pNext = pNext;};	// 次の弾へのポインタをセット

	CBullet(LPDIRECT3DDEVICE8 d3dDevice, tagBulParam* pType, D3DXMATRIX matBase, long lID);
	virtual ~CBullet();
};

#endif // !defined(AFX_Bullet_H__7E4D9C62_06AE_11D6_AE81_0000F4905862__INCLUDED_)
