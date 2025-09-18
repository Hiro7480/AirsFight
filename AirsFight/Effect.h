//==========================================================
// Effect.h
// Auther : 桜井 博之
// Data   : 2002/03/09
//==========================================================

#if !defined(AFX_EFFECT_H__FBF1B9C6_9BEB_436F_8CCA_0EF2D335973B__INCLUDED_)
#define AFX_EFFECT_H__FBF1B9C6_9BEB_436F_8CCA_0EF2D335973B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "3DGraphicObj.h"
#include "define.h"

//----------------------------------------------
//	マクロ定義
//----------------------------------------------
#define D3DFVF_POINTVERTEX 		(D3DFVF_XYZ | D3DFVF_DIFFUSE)

//----------------------------------------------
//	Name:	tagPointVertex
//	Func:	頂点フォーマット構造体
//----------------------------------------------
typedef struct{
	D3DXVECTOR3	v;
	D3DCOLOR	color;
}tagPointVertex;

//----------------------------------------------
//	Name:	tagParticle
//	Func:	頂点情報
//----------------------------------------------
typedef struct {
	D3DXVECTOR3		pos;		// パーティクル座標
	D3DXVECTOR3		dir;		// パーティクル移動量
	unsigned char	r;			// 赤色情報
	unsigned char	g;			// 緑色情報
	unsigned char	b;			// 青色情報
}tagParticle;

//----------------------------------------------
//	Name:	CEffect
//	Func:	さまざまなエフェクトの基底クラス
//----------------------------------------------
class CEffect:public C3DGraphicObj
{
private:
	CEffect*				m_pNext;			// 次のエフェクトへのポインタ

	LPDIRECT3DVERTEXBUFFER8	m_pPointVB;			// 頂点バッファ
	LPDIRECT3DVERTEXBUFFER8	m_pPointVBRender;	// 描画用頂点バッファ
	LPDIRECT3DTEXTURE8		m_pTexture;			// テクスチャ(参照用)
	bool					m_bZBufferFlg;		// Ｚバッファフラグ

protected:
	int						m_nParticleNum;		// パーティクルの数
	int						m_nMaxLife;			// 最大生存時間
	int						m_nLife;			// 生存カウンタ
	float					m_fSize;			// サイズ
	int						m_nInitR;			// 初期赤色情報
	int						m_nInitG;			// 初期緑色情報
	int						m_nInitB;			// 初期青色情報

public:
	virtual void FrameMove(){};				// 毎フレームの処理
	virtual void Render();					// 描画処理
	void	UpDate();						// 描画情報の更新
	bool	IsDelete();						// 消えるかどうかの判定

	bool CreateBuffer();					// 頂点バッファの作成
	bool CreateBufferRender();				// 描画用頂点バッファの作成

	/* アクセス関数 */
	void SetDevice(LPDIRECT3DDEVICE8 d3dDevice){m_pd3dDevice = d3dDevice;};	// デバイスのセット
	void SetZBuffer(bool sw){m_bZBufferFlg = sw;};							// Ｚバッファー設定
	void SetTexture(LPDIRECT3DTEXTURE8 pTexture){m_pTexture = pTexture;};	// テクスチャのセット
	void SetNext(CEffect* pEffect){m_pNext = pEffect;};						// 次のポインタをセット

	LPDIRECT3DVERTEXBUFFER8 GetVB(){return m_pPointVB;};					// 頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER8 GetVBR(){return m_pPointVBRender;};				// 描画用頂点バッファの取得
	CEffect* GetNext(){return m_pNext;};									// 次のポインタを返す
	DWORD FtoDW(FLOAT f) { return *((DWORD*)&f); }							// なんかキャストする

	CEffect(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEffect();
};

#endif // !defined(AFX_EFFECT_H__FBF1B9C6_9BEB_436F_8CCA_0EF2D335973B__INCLUDED_)
