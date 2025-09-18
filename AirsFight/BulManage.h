//==========================================================
// BulManage.h
// Auther : 桜井 博之
// Data   : 2002/01/11
//==========================================================

#if !defined(AFX_BULMANAGE_H__7E4D9C63_06AE_11D6_AE81_0000F4905862__INCLUDED_)
#define AFX_BULMANAGE_H__7E4D9C63_06AE_11D6_AE81_0000F4905862__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//------------------------------
//	インクルード
//------------------------------
#include <d3dx8.h>
#include "MyFunction.h"

#include "Bullet.h"
#include "Stage.h"
#include "EffectManage.h"

//------------------------------
//		定数定義
//------------------------------
#define HIT_WALL_LENGTH		2.0f	// 壁とのあたり判定する距離
#define HIT_CHARA_LENGTH	5.0f	// キャラクターとの当たり判定距離

//--------------------------------------------------
//		データ送信用構造体
//--------------------------------------------------
/* 弾の発射を示す */
struct TBullet{
	DWORD		dwDpnType;		// メッセージタイプ
	D3DXMATRIX	matBase;		// 弾発射位置、角度
	int			nType;			// 弾のタイプ
	int			nCharaID;		// 弾を出したキャラクタ
};

//----------------------------------------------
//	Name:	BulManage
//	Func:	弾管理クラス
//----------------------------------------------
class CBulManage
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;				// D3Dデバイス

	CBullet*			m_pListTop;					// はじめの弾へのポインタ
	tagBulParam			m_tagParam[3];				// 弾パラメータ

	CRITICAL_SECTION	m_cs;						// クリティカルセクションオブジェクト

public:
	void FrameMove(CStage* pStage, 					// 毎フレームの処理
		CEffectManage* pEffectManage);			
	void Render();									// 画面描画
	void UpDate();									// 描画用座標値更新

	void AddBullet(int nType, D3DXMATRIX matBase, int nCharaNum);	// 弾の追加
	void SubBullet();												// 弾の消去処理

	CBullet* SearchBullet(long lID);				// 識別番号から弾を捜す

	void HitPlane(CStage* pStage,					// 弾の壁との当たり判定
		CEffectManage* pEffectManage);

	float SearchAllPlane(CStage* pStage,			// 面との当たり判定
		D3DXVECTOR3 vecPos, D3DXVECTOR3 vecMove); 

	/* アクセス関数 */
	tagBulParam*	GetBulStatus(int nType){return &m_tagParam[nType];};	// 弾固定ステータス値のポインタを返す
	CBullet*		GetListTop(){return m_pListTop;};						// はじめの弾へのポインタを返す

	CBulManage(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CBulManage();
};

#endif // !defined(AFX_BULMANAGE_H__7E4D9C63_06AE_11D6_AE81_0000F4905862__INCLUDED_)
