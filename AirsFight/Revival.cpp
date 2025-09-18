//==========================================================
// Revival.cpp
// Auther : 桜井 博之
// Data   : 2002/03/09
//==========================================================
#include "Revival.h"

//----------------------------------------------
//	Name:	CRevival
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3Dデバイス
//			LPDIRECT3DTEXTURE8	pTexture	= テクスチャ
//			D3DXMATRIX			matBase		= マトリクス
//	Out:	なし
//----------------------------------------------
CRevival::CRevival(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase)
			:CEffect(d3dDevice)
{
	CEffect::SetTexture(pTexture);				// テクスチャのセット
	C3DGraphicObj::SetMatrix(matBase);			// マトリクスのセット

	m_nParticleNum = 100;						// パーティクル数のセット
	m_fSize = 2.0f;								// サイズセット
	m_nMaxLife = 50;							// 最大生存カウンターのセット
	m_nLife = m_nMaxLife;						// 生存カウンターの初期化
	m_nInitR = 255;								// 初期色のセット
	m_nInitG = 100;
	m_nInitB = 100;

	while(!CEffect::CreateBuffer());			// 頂点バッファの作成(できるまで続ける)
	while(!CEffect::CreateBufferRender());		// 描画用頂点バッファの作成(できるまで続ける)

	InitParticle();								// 初期座標、初期移動量の設定
}

//----------------------------------------------
//	Name:	~CRevival
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CRevival::~CRevival()
{

}

//---------------------------------------------
//	Name:	InitParticle
//	Func:	パーティクルの初期座標、初期移動量の設定
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CRevival::InitParticle()
{
	// 初期値などの算出
	D3DXVECTOR3	vecTmp;
	int			nRotate;

	for(int i=0; i<m_nParticleNum; i++)
	{

		/* 初期位置の計算 */
		nRotate = (int)((360.0f / 100.0f) * i);	

		// 角度から単位方向ベクトルの算出
		vecTmp *= 0;
		vecTmp.x = float(sin(D3DXToRadian(nRotate)) * 5.0);
		vecTmp.z = float(cos(D3DXToRadian(nRotate)) * 5.0);

		/* 初期位置として格納 */
		m_Particle[i].pos = vecTmp;

		// それぞれのスプライトの移動量をランダムで決定
		vecTmp.x = 0.0f;//float(rand()%2-1)/10.0f;
		vecTmp.y = float(rand()%3+5)/30.0f;
		vecTmp.z = 0.0f;//float(rand()%2-1)/10.0f;

		// 求まった移動量をそれぞれの移動量に格納していく
		m_Particle[i].dir = vecTmp;

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
void CRevival::FrameMove()
{
	// パーティクルの移動
	for(int i=0; i<m_nParticleNum; i++)
	{
		m_Particle[i].pos += m_Particle[i].dir;			// 位置の更新

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
