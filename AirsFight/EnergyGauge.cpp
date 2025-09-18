//==========================================================
// EnergyGauge.cpp
// Auther : ÷ˆä ””V
// Data   : 2002/05/04
//==========================================================
#include "EnergyGauge.h"

//----------------------------------------------------------
//	Name:	CEnergyGauge
//	Func:	ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	  = D3DƒfƒoƒCƒX
//			TCHAR*			  srcFileName = ƒeƒNƒXƒ`ƒƒƒtƒ@ƒCƒ‹–¼
//	Out:	‚È‚µ
//----------------------------------------------------------
CEnergyGauge::CEnergyGauge(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName)
			 :CSprite(d3dDevice, srcFileName)
{
	/* •Ï”‚Ì‰Šú‰» */
	m_nMaxEnergy = 0;
	m_nNowEnergy = 0;

	/* Šî–{•`‰æˆÊ’u‚ÌƒZƒbƒg */
	m_vecPos = D3DXVECTOR2(40, 120);
}

//----------------------------------------------------------
//	Name:	~CEnergyGauge
//	Func:	ƒfƒXƒgƒ‰ƒNƒ^
//	in:		‚È‚µ
//	Out:	‚È‚µ
//----------------------------------------------------------
CEnergyGauge::~CEnergyGauge()
{

}

//----------------------------------------------------------
//	Name:	FrameMove
//	Func:	–ˆƒtƒŒ[ƒ€‚Ìˆ—
//	in:		‚È‚µ
//	Out:	‚È‚µ
//----------------------------------------------------------
void CEnergyGauge::FrameMove()
{
	int	nGaugeNum;	// •`‰æ‚·‚éƒQ[ƒW‚Ì”

	/* Å‘åƒGƒlƒ‹ƒM[’l‚ÆŒ»İƒGƒlƒ‹ƒM[’l‚©‚çA */
	/* •`‰æ‚·‚éƒQ[ƒW‚Ì”‚ğ‚à‚Æ‚ß‚é */
	nGaugeNum = (int) (30.0f * ((float)m_nNowEnergy / (float)m_nMaxEnergy));

	/* ƒQ[ƒW‚Ì”‚©‚çƒŒƒNƒg‚ğ‹‚ß‚é */
	int	nTop;
	nTop = 300 - (10 * nGaugeNum);
	C2DGraphicObj::SetRec(100, nTop, 149, 299);

	/* ‰æ–Ê‚É•`‰æ‚·‚éÀ•W’l‚à‹‚ß‚é */
	C2DGraphicObj::SetVec(D3DXVECTOR2(m_vecPos.x, m_vecPos.y+nTop+10.0f));

}

//----------------------------------------------------------
//	Name:	Render
//	Func:	•`‰æˆ—
//	in:		‚È‚µ
//	Out:	‚È‚µ
//----------------------------------------------------------
void CEnergyGauge::Render()
{
	RECT rc;

	/* •`‰æŠJn */
	m_pSprite->Begin();

	/* ƒQ[ƒW‚Ì”wŒi‚ğ”¼“§–¾‚É•`‰æ‚·‚é */
	SetRect(&rc, 50, 0, 99, 319);
	m_pSprite->Draw(m_pTexture, &rc, NULL, NULL, 0.0f, &m_vecPos,
					D3DCOLOR_ARGB(128, 255, 255, 255));

	/* ƒQ[ƒW‚ÌŠO˜g‚ğ•`‰æ‚·‚é */
	SetRect(&rc, 0, 0, 49, 319);
	m_pSprite->Draw(m_pTexture, &rc, NULL, NULL, 0.0f, &m_vecPos,
					D3DCOLOR_ARGB(255, 255, 255, 255));

	/* ƒQ[ƒW‚ğ•`‰æ‚·‚é */
	m_pSprite->Draw(m_pTexture, &m_rectStock, NULL, NULL, 0.0f, &m_vecStock,
					D3DCOLOR_ARGB(255, 255, 255, 255));

	/* •`‰æI—¹ */
	m_pSprite->End();	

}