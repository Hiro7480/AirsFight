//==========================================================
// Effect.cpp
// Auther : 桜井 博之
// Data   : 2002/03/09
//==========================================================

#include "Effect.h"

//----------------------------------------------
//	Name:	CEffect
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3Dデバイス
//	Out:	なし
//----------------------------------------------
CEffect::CEffect(LPDIRECT3DDEVICE8 d3dDevice)
		:C3DGraphicObj(d3dDevice)
{
	m_pNext = NULL;					// 次へのポインタをNULLに
}
//----------------------------------------------
//	Name:	~CEffect
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CEffect::~CEffect()
{
	SAFE_RELEASE(m_pPointVB);
	SAFE_RELEASE(m_pPointVBRender);
}

//----------------------------------------------
//	Name:	CreateBuffer
//	Func:	頂点バッファの作成
//	in:		なし
//	Out:	bool	= 成功したらTRUEを返す
//----------------------------------------------
bool CEffect::CreateBuffer()
{
	/* 処理用頂点バッファ作成 */
	if(m_pd3dDevice->CreateVertexBuffer(m_nParticleNum * sizeof(tagPointVertex),
				D3DUSAGE_POINTS, D3DFVF_POINTVERTEX, D3DPOOL_MANAGED , &m_pPointVB) != S_OK)
			return false;
	return true;
}

//----------------------------------------------
//	Name:	CreateBufferRender
//	Func:	描画用頂点バッファの作成
//	in:		なし
//	Out:	bool	= 成功したらTRUEを返す
//----------------------------------------------
bool CEffect::CreateBufferRender()
{
	/* 描画用頂点バッファの作成 */
	if(m_pd3dDevice->CreateVertexBuffer(m_nParticleNum * sizeof(tagPointVertex),
				D3DUSAGE_POINTS, D3DFVF_POINTVERTEX, D3DPOOL_MANAGED , &m_pPointVBRender) != S_OK)
		return false;

	return true;
}

//----------------------------------------------
//	Name:	IsDelete
//	Func:	消えるかどうかの判定
//	in:		なし
//	Out:	bool
//----------------------------------------------
bool CEffect::IsDelete()
{
	if(m_nLife <= 0)	return true;
	return				false;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CEffect::Render()
{
	/* ワールドマトリックスの設定 */
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matBase );
	/* テクスチャーの設定 */
	m_pd3dDevice->SetTexture(0, m_pTexture);

	/* Ｚバッファーフラグの判定 */	
	if(m_bZBufferFlg)
		m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	else
		m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	/* 描画 */
	m_pd3dDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(m_fSize));

	m_pd3dDevice->SetStreamSource(0, m_pPointVB, sizeof(tagPointVertex));
	m_pd3dDevice->SetVertexShader(D3DFVF_POINTVERTEX);
	m_pd3dDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_nParticleNum);

	/* Ｚバッファを戻す */
	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );	
}

//---------------------------------------------
//	Name:	UpDate
//	Func:	描画情報の更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CEffect::UpDate()
{
	C3DGraphicObj::UpDate();

	tagPointVertex *pPointVertices1, *pPointVertices2;
	m_pPointVB->Lock(0, 0, (BYTE**)&pPointVertices1, 0);		// 頂点バッファのロック
	m_pPointVBRender->Lock(0, 0,(BYTE**)&pPointVertices2, 0);	// 描画用頂点バッファのロック

	/* 全てコピーする */
	for (int i=0; i < m_nParticleNum; i++){
		pPointVertices2->v    =	pPointVertices1->v;
		pPointVertices2->color=	pPointVertices1->color;

		pPointVertices1++;
		pPointVertices2++;
	}

	m_pPointVB->Unlock();		// 頂点バッファのアンロック
	m_pPointVBRender->Unlock();	// 描画用頂点バッファのアンロック
}