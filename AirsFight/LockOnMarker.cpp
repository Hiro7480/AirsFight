//==========================================================
// LockOnMarker.cpp
// Auther : 桜井 博之
// Data   : 2002/05/04
//==========================================================
#include "LockOnMarker.h"

//----------------------------------------------------------
//	Name:	CLockOnMarker
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice	  = D3Dデバイス
//			TCHAR*			  srcFileName = テクスチャファイル名
//	Out:	なし
//----------------------------------------------------------
CLockOnMarker::CLockOnMarker(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName)
			  :CSprite(d3dDevice, srcFileName)
{
	/* メンバ変数の初期化 */
	m_dwStatus = NOT_LOCK;
	m_fAlpha   = 255.0f;
	m_fScale   = 1.0f;
}

//----------------------------------------------------------
//	Name:	~CLockOnMarker
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
CLockOnMarker::~CLockOnMarker()
{

}

//----------------------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CLockOnMarker::FrameMove()
{	
	/* ロックオンできない場合 */
	if(m_dwStatus == NOT_LOCK)	return;

	/* ロックオンが可能な場合 */
	else if(m_dwStatus == CAN_LOCK)
	{
		C2DGraphicObj::SetRec(0, 0, 64, 64);
		m_fAlpha = 255.0f;
		m_fScale = 1.0f;
	}
	/* ターゲットとしてロックオンしている */
	else if(m_dwStatus == TAG_LOCK)
		C2DGraphicObj::SetRec(0, 0, 64, 64);

	/* 現在ロックオンしている */
	else if(m_dwStatus == NOW_LOCK)
		C2DGraphicObj::SetRec(64, 0, 128, 64);


	/* ターゲットとしてロックオンできる場合と、*/
	/* 現在ロックオンしている場合は */
	/* ちょっとしたアニメーションをする */
	if(m_dwStatus == TAG_LOCK || m_dwStatus == NOW_LOCK)
	{
		/* スケール値が1.0以下なら初期化 */
		if(m_fScale <= 1.0f)
		{
			m_fAlpha = 128;
			m_fScale = 1.5f;
		}
		/* だんだん小さくなりながら不透明になる */
		m_fScale -= 0.025f;
		m_fAlpha += 6.0f;
	}

	/* 画面の描画位置にスケール値を考慮に入れて修正 */
	m_vecBase.x -= 32.0f * m_fScale;
	m_vecBase.y -= 32.0f * m_fScale;

}

//----------------------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CLockOnMarker::Render()
{
	D3DXVECTOR2 vec2;

	m_pSprite->Begin();

	/* スプライトを描画 */
	vec2 = D3DXVECTOR2(m_fScale, m_fScale);
	m_pSprite->Draw(m_pTexture, &m_rectStock, &vec2,
		NULL, 0.0f, &m_vecStock, D3DCOLOR_ARGB((int)m_fAlpha, 255, 255, 255));

	m_pSprite->End();
}