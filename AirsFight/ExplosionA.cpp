//==========================================================
// ExplosionA.cpp
// Auther : 桜井 博之
// Data   : 2002/03/09
//==========================================================
#include "ExplosionA.h"

//----------------------------------------------
//	Name:	CExplosionA
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3Dデバイス
//			LPDIRECT3DTEXTURE8	pTexture	= テクスチャ
//			D3DXMATRIX			matBase		= マトリクス
//	Out:	なし
//----------------------------------------------
CExplosionA::CExplosionA(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase)
			:CEffect(d3dDevice)
{
	CEffect::SetTexture(pTexture);				// テクスチャのセット
	C3DGraphicObj::SetMatrix(matBase);			// マトリクスのセット

	m_nParticleNum = 20;						// パーティクル数のセット
	m_fSize = 3.0f;								// サイズセット
	m_nMaxLife = 30;							// 最大生存カウンターのセット
	m_nLife = m_nMaxLife;						// 生存カウンターの初期化
	m_nInitR = 255;								// 初期色のセット
	m_nInitG = 150;
	m_nInitB = 0;

	while(!CEffect::CreateBuffer());			// 頂点バッファの作成(できるまで続ける)
	while(!CEffect::CreateBufferRender());		// 描画用頂点バッファの作成(できるまで続ける)

	InitParticle();								// 初期座標、初期移動量の設定
}

//----------------------------------------------
//	Name:	~CExplosionA
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CExplosionA::~CExplosionA()
{

}

//---------------------------------------------
//	Name:	InitParticle
//	Func:	パーティクルの初期座標、初期移動量の設定
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CExplosionA::InitParticle()
{
	// 初期値などの算出
	D3DXVECTOR3	vecTmp;
	for(int i=0; i<m_nParticleNum; i++)
	{
		// それぞれのスプライトの移動量をランダムで決定
		vecTmp.x = float(rand()%10-5)/20.0f;
		vecTmp.y = float(rand()%8+3)/10.0f;
		vecTmp.z = -1.0f;

		D3DXVec3Normalize(&vecTmp, &vecTmp);		// 単位ベクトル化
		vecTmp.z += (float(rand()%3)/10.0f);		// 速度に差をつける
		vecTmp *= 0.2f;								// 全体的に速度を下げる

		// 求まった移動量をそれぞれの移動量に格納していく
		m_Particle[i].dir = vecTmp;

		// 初期座標値の格納
		m_Particle[i].pos = D3DXVECTOR3(0,0,0);

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
void CExplosionA::FrameMove()
{
	int i;

	// パーティクルの移動
	for(i=0; i<m_nParticleNum; i++)
	{
		m_Particle[i].dir.y -= 0.02f;			// 移動量の更新
		m_Particle[i].pos += m_Particle[i].dir;	// 位置の更新

		m_Particle[i].r -= (m_nInitR / m_nMaxLife);		// 色の更新
		m_Particle[i].g -= (m_nInitG / m_nMaxLife);
		m_Particle[i].b -= (m_nInitB / m_nMaxLife);
	}

	// 頂点バッファの中身を更新する
	tagPointVertex* pPointVertices;
	CEffect::GetVB()->Lock(0, 0, (BYTE**)&pPointVertices, 0);
	for (i = 0; i < m_nParticleNum; i++){
		pPointVertices->v = m_Particle[i].pos;
		pPointVertices->color = D3DCOLOR_ARGB(255, m_Particle[i].r, m_Particle[i].g, m_Particle[i].b);
		pPointVertices++;
	}
	CEffect::GetVB()->Unlock();

	// 生存カウンターのデクリメント
	m_nLife--;

}
