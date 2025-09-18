//==========================================================
// TimeGraphic.cpp
// Auther : 桜井 博之
// Data   : 2002/05/04
//==========================================================
#include "TimeGraphic.h"

//----------------------------------------------------------
//	Name:	CTimeGraphic
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice	  = D3Dデバイス
//	Out:	なし
//----------------------------------------------------------
CTimeGraphic::CTimeGraphic(LPDIRECT3DDEVICE8 d3dDevice)
			 :CSprite(d3dDevice, "data\\game\\TimeGraphic.png")
{
	/* 変数の初期化 */
	m_lStartTime = 0;
	m_lNowTime   = 0;
	m_lLimitTime = 0;

	m_bPlay		 = false;

	/* 基本描画位置のセット */
	m_vecPos = D3DXVECTOR2(400, 400);

	/* レクトの初期化 */
	for(int i=0; i<5; i++)
	{
		SetRect(&m_rcBase[i], 0,0,0,0);
	}
}

//----------------------------------------------------------
//	Name:	~CTimeGraphic
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
CTimeGraphic::~CTimeGraphic()
{

}

//----------------------------------------------------------
//	Name:	Start
//	Func:	時間計測開始
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CTimeGraphic::Start()
{
	/* 開始時間の取得 */
	time(&m_lStartTime);

	/* 開始フラグを立てる */
	m_bPlay = true;
}

//----------------------------------------------------------
//	Name:	IsEnd
//	Func:	残り制限時間がなくなったか？
//	in:		なし
//	Out:	bool = なくなっていたらTURE
//----------------------------------------------------------
bool CTimeGraphic::IsEnd()
{
	if(m_lLimitTime < 0)
	{
		/* 時間計測フラグを戻す */
		m_bPlay = false;
		return true;
	}

	return false;
}

//----------------------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CTimeGraphic::FrameMove()
{
	/* 時間計測でなければ処理を行わない */
	if(!m_bPlay) return;

	/* 現在時間を求める */
	time(&m_lNowTime);

	/* 開始時間からの経過時間を求める */
	long lTmp;
	lTmp = m_lNowTime - m_lStartTime;

	/* 最大制限時間から、残り制限時間を求める */
	m_lLimitTime = m_lMaxTime - lTmp;

	/* 残り制限時間が0以下だったら計算がおかしくなりそうなので終了する */
	if(m_lLimitTime < 0) return;

	/* 残り制限時間を分と秒に分割する */
	long lMinute = m_lLimitTime / 60;
	long lSecond = m_lLimitTime % 60;

	/* 残り制限時間から、RECT値を求める */
	int nTmp;

	/* 10分の位のRECTを求める */
	nTmp = lMinute / 10;
	SetRect(&m_rcBase[0], 30*nTmp, 0, 30*(nTmp+1), 50);

	/* 1分の位のRECTを求める */
	nTmp = lMinute % 10;
	SetRect(&m_rcBase[1], 30*nTmp, 0, 30*(nTmp+1), 50);

	/* 「：」のマークは固定 */
	SetRect(&m_rcBase[2], 300, 0, 330, 50);

	/* 10秒の位のRECTを求める */
	nTmp = lSecond / 10;
	SetRect(&m_rcBase[3], 30*nTmp, 0, 30*(nTmp+1), 50);

	/* 1秒の位のRECTを求める */
	nTmp = lSecond % 10;
	SetRect(&m_rcBase[4], 30*nTmp, 0, 30*(nTmp+1), 50);
}

//----------------------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CTimeGraphic::Render()
{
	/* 時間計測中でなかったら描画しない */
	if(!m_bPlay) return;

	/* 描画開始 */
	m_pSprite->Begin();

	/* 時間を描画する */
	for(int i=0; i<5; i++)
	{
		m_pSprite->Draw(m_pTexture, &m_rcStock[i], NULL, NULL, 0.0f, 
			&D3DXVECTOR2(m_vecPos.x+(30*i), m_vecPos.y), D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	/* 描画終了 */
	m_pSprite->End();
}

//----------------------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
void CTimeGraphic::UpDate()
{
	for(int i=0; i<5; i++)
	{
		m_rcStock[i] = m_rcBase[i];
	}
}