//==========================================================
// BoostA.cpp
// Auther : 桜井 博之
// Data   : 2002/03/09
//==========================================================

#include "BoostA.h"

//----------------------------------------------
//	Name:	CBoostA
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3Dデバイス
//			LPDIRECT3DTEXTURE8	pTexture	= テクスチャ
//			D3DXMATRIX			matBase		= マトリクス
//	Out:	なし
//----------------------------------------------
CBoostA::CBoostA(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase)
		:CEffect(d3dDevice)
{
	CEffect::SetTexture(pTexture);				// テクスチャのセット

	D3DXMATRIX	matTmp = matBase;
	matTmp._42 -= 5.0f;
	C3DGraphicObj::SetMatrix(matTmp);			// マトリクスのセット

	m_nParticleNum = 10;						// パーティクル数のセット
	m_fSize = 2.0f;								// サイズセット
	m_nMaxLife = 20;							// 最大生存カウンターのセット
	m_nLife = m_nMaxLife;						// 生存カウンターの初期化
	m_nInitR = 128;								// 初期色のセット
	m_nInitG = 128;
	m_nInitB = 255;

	while(!CEffect::CreateBuffer());			// 頂点バッファの作成(できるまで続ける)
	while(!CEffect::CreateBufferRender());		// 描画用頂点バッファの作成(できるまで続ける)

	InitParticle();								// 初期座標、初期移動量の設定
}

//----------------------------------------------
//	Name:	~CBoostA
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CBoostA::~CBoostA()
{

}

//---------------------------------------------
//	Name:	InitParticle
//	Func:	パーティクルの初期座標、初期移動量の設定
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CBoostA::InitParticle()
{
	// 初期値などの算出
	D3DXVECTOR3	vecTmp;
	for(int i=0; i<m_nParticleNum; i++)
	{
		// 初期座標値の格納
		if(i < m_nParticleNum/2)	m_Particle[i].pos = D3DXVECTOR3( 1.0f, 0, 0);
		else						m_Particle[i].pos = D3DXVECTOR3(-1.0f, 0, 0);

		// 初期透明度の格納
		m_Particle[i].r = m_nInitR;
		m_Particle[i].g = m_nInitG;
		m_Particle[i].b = m_nInitB;

	}
}

//---------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CBoostA::FrameMove()
{
	int i;

	/* パーティクルの移動 */
	for(i=0; i<m_nParticleNum; i++)
	{
		/* 移動量の更新 */
		m_Particle[i].dir.x = float(rand()%20-10)/20.0f;
		m_Particle[i].dir.y = float(rand()%20)/50.0f;
		m_Particle[i].dir.z = float(rand()%20-10)/20.0f;

		/* 位置の更新 */
		m_Particle[i].pos += m_Particle[i].dir;

		/* 色の更新 */
		m_Particle[i].r -= (m_nInitR / m_nMaxLife);
		m_Particle[i].g -= (m_nInitG / m_nMaxLife);
		m_Particle[i].b -= (m_nInitB / m_nMaxLife);
	}

	/* 頂点バッファの中身を更新する */
	tagPointVertex* pPointVertices;
	CEffect::GetVB()->Lock(0, 0, (BYTE**)&pPointVertices, 0);
	for (i = 0; i < m_nParticleNum; i++){
		pPointVertices->v = m_Particle[i].pos;
		pPointVertices->color = D3DCOLOR_ARGB(255, m_Particle[i].r, m_Particle[i].g, m_Particle[i].b);
		pPointVertices++;
	}
	CEffect::GetVB()->Unlock();

	/* 生存カウンターのデクリメント */
	m_nLife--;

}