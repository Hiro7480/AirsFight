//==========================================================
// EffectManage.h
// Auther : 桜井 博之
// Data   : 2002/03/09
//==========================================================

#if !defined(AFX_EFFECTMANAGE_H__0BE91682_45A4_42E5_8471_10CB2C8DFEF8__INCLUDED_)
#define AFX_EFFECTMANAGE_H__0BE91682_45A4_42E5_8471_10CB2C8DFEF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include <d3dx8.h>
#include "define.h"
#include "Effect.h"

#include "BoostA.h"
#include "BoostB.h"
#include "ExplosionA.h"
#include "ExplosionB.h"
#include "OrbitBul.h"
#include "Revival.h"

//----------------------------------------------
//	定数定義
//----------------------------------------------
#define TEXTURE_NUM	10

/* エフェクトタイプ識別子 */
enum{
	BOOST_A,		// ダッシュ時のブースト
	BOOST_B,		// 飛行時のブースト

	EXPLOSION_A,	// 弾が壁に当たった時の爆発
	EXPLOSION_B,	// 弾がキャラクタに当たった時の爆発

	ORBIT_BUL,		// 弾の軌道

	REVIVAL			// 復活
};

//----------------------------------------------
//	Name:	CEffectManage
//	Func:	全てのエフェクトの管理クラス
//			リスト構造を使って管理する
//----------------------------------------------
class CEffectManage  
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;				// D3Dデバイス
	CEffect*			m_pListTop;					// はじめのエフェクトへのポインタ
	LPDIRECT3DTEXTURE8	m_pTexture[TEXTURE_NUM];	// テクスチャデータ
	CRITICAL_SECTION	m_cs;						// クリティカルセクションオブジェクト

public:
	void FrameMove();								// 毎フレームの処理
	void Render();									// 画面描画
	void UpDate();									// 描画用座標値など更新

	void AddEffect(DWORD dwType, D3DXMATRIX matIn);	// エフェクトの追加
	void SubEffect();								// エフェクト消去処理

	CEffect* GetListTop(){return m_pListTop;};		// はじめのエフェクトへのポインタを返す
	DWORD FtoDW(FLOAT f) { return *((DWORD*)&f); }	// なんかキャストする

	CEffectManage(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEffectManage();

};

#endif // !defined(AFX_EFFECTMANAGE_H__0BE91682_45A4_42E5_8471_10CB2C8DFEF8__INCLUDED_)
