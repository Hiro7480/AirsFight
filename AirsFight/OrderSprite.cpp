//==========================================================
// OrderSprite.cpp
// Auther : 桜井 博之
// Data   : 2002/05/20
//==========================================================

#include "OrderSprite.h"

//------------------------------------------------------
//	Name:	COrderSprite
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8	d3dDevice = D3Dデバイス
//			int					nOrder    = 順位
//			TCHAR*				strName   = 名前
//			int					nDeadNum  = 死んだ数
//	Out:	なし
//------------------------------------------------------
COrderSprite::COrderSprite(LPDIRECT3DDEVICE8 d3dDevice, int nOrder, TCHAR* strName, int nDeadNum)
{
	m_nOrder = nOrder;			/* 順位の格納 */
	strcpy(m_strName, strName);	/* 名前の格納 */
	m_nDeadNum = nDeadNum;		/* 死んだ数の格納 */

	/* 引数の順位から、基本描画座標値を算出 */
	m_vecBase.x = 100;
	m_vecBase.y = (float)(140+(90*(m_nOrder-1)));

	/* 順位フォーマットの作成 */
	m_pFormat = new CSprite(d3dDevice, "Data\\Ending\\OrderFormat.png");
	m_pFormat->SetVec(m_vecBase);
	m_pFormat->SetRec(0, 50*(m_nOrder-1), 400, 50*m_nOrder);

	/* 名前フォントの作成 */
	m_pName = new CFont(d3dDevice, "ＭＳ ゴシック");
	m_pName->SetString(strName);
	m_pName->SetRec((int)m_vecBase.x+120, (int)m_vecBase.y+20,
					(int)m_vecBase.x+300, (int)m_vecBase.y+50);

	switch(nOrder)
	{
		case 1:	m_pName->SetColor(64,  0,  0);	break;
		case 2: m_pName->SetColor(64, 64,  0);	break;
		case 3: m_pName->SetColor( 0, 64,  0);	break;
		case 4: m_pName->SetColor( 0,  0, 64);	break;
	}

	/* 死んだ数フォントの作成 */
	m_pDeadNum = new CFont(d3dDevice, "ＭＳ ゴシック");
	m_pDeadNum->SetString(nDeadNum);

	m_pDeadNum->SetRec(	(int)m_vecBase.x+350, (int)m_vecBase.y+20,
						(int)m_vecBase.x+400, (int)m_vecBase.y+50);

	switch(nOrder)
	{
		case 1:	m_pDeadNum->SetColor(64,  0,  0);	break;
		case 2: m_pDeadNum->SetColor(64, 64,  0);	break;
		case 3: m_pDeadNum->SetColor( 0, 64,  0);	break;
		case 4: m_pDeadNum->SetColor( 0,  0, 64);	break;
	}

}

//------------------------------------------------------
//	Name:	~COrderSprite
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//------------------------------------------------------
COrderSprite::~COrderSprite()
{
	/* 使用したメモリの開放 */
	SAFE_DELETE(m_pFormat);
	SAFE_DELETE(m_pName);
	SAFE_DELETE(m_pDeadNum);
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	Out:	なし
//	In:		なし
//----------------------------------------------
void COrderSprite::FrameMove()
{
	m_pFormat->FrameMove();
	m_pName->FrameMove();
	m_pDeadNum->FrameMove();
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	Out:	なし
//	In:		なし
//----------------------------------------------
void COrderSprite::Render()
{
	m_pFormat->Render();
	m_pName->Render();
	m_pDeadNum->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	Out:	なし
//	In:		なし
//----------------------------------------------
void COrderSprite::UpDate()
{
	m_pFormat->UpDate();
	m_pName->UpDate();
	m_pDeadNum->UpDate();
}