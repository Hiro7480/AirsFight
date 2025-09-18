//==========================================================
// Ending.h
// Auther : 桜井 博之
// Data   : 2002/05/20
//==========================================================
#include "Ending.h"

//------------------------------------------------------
//	Name:	CEnding
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3Dデバイス
//	Out:	なし
//------------------------------------------------------
CEnding::CEnding(LPDIRECT3DDEVICE8 d3dDevice)
	  :GameStatus(d3dDevice)
{
	/* プレイヤー名の格納 */
	strcpy(m_tagChara[0].strName, "PLAYER");
	strcpy(m_tagChara[1].strName, "COMPUTER1");
	strcpy(m_tagChara[2].strName, "COMPUTER2");
	strcpy(m_tagChara[3].strName, "COMPUTER3");

}

//----------------------------------------------
//	Name:	~CEnding
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CEnding::~CEnding()
{
	/* 使用したメモリの開放 */
	for(int i=0; i<4; i++)	SAFE_DELETE(m_pOrder[i]);

	SAFE_DELETE(m_pLogo);
	SAFE_DELETE(m_pBackGround);
}

//----------------------------------------------
//	Name:	InitOrder
//	Func:	順位に関する初期化
//	In:		int nDeadNum1 = １人目の死んだ数
//			int nDeadNum2 = ２人目の死んだ数
//			int nDeadNum3 = ３人目の死んだ数
//			int nDeadNum4 = ４人目の死んだ数
//	Out:	HRESULT
//----------------------------------------------
HRESULT CEnding::InitOrder(int nDeadNum1, int nDeadNum2, int nDeadNum3, int nDeadNum4)
{
	/* とりあえず死んだ数を格納する */
	m_tagChara[0].nDeadNum = nDeadNum1;
	m_tagChara[1].nDeadNum = nDeadNum2;
	m_tagChara[2].nDeadNum = nDeadNum3;
	m_tagChara[3].nDeadNum = nDeadNum4;

	/* 死んだ数の大きさから、順位を決める */
	bool	bOKFlg[4] = {false, false, false, false};
	int		nMaxDeadNum = 0;
	int		nMaxNumber;
	int		i;

	/* ４位から順に決めていく */
	for(i=4; i>0; i--)
	{
		for(int j=0; j<4; j++)
		{
			if(nMaxDeadNum <= m_tagChara[j].nDeadNum && !bOKFlg[j])
			{
				nMaxDeadNum = m_tagChara[j].nDeadNum;
				nMaxNumber = j;
			}
		}
		/* 最大の数値が見つかったら、順位を格納する */
		bOKFlg[nMaxNumber] = true;			// 決定フラグを立てる
		m_tagChara[nMaxNumber].nOrder = i;	// 順位を格納
		nMaxDeadNum = 0;					// 最大値の初期化
	}

	/* 格納した順位を元に、順位表を作成する */
	for(i=0; i<4; i++)
		m_pOrder[i] = new COrderSprite(	m_pd3dDevice, m_tagChara[i].nOrder,
										m_tagChara[i].strName,m_tagChara[i].nDeadNum);

	/* 背景の作成 */
	m_pBackGround = new CScrollBG(m_pd3dDevice, const_cast<TCHAR*>("data\\Ending\\EndingBG.png"), 256, 256);
	m_pBackGround->SetVecDir(D3DXVECTOR2(0.0, 1.0));

	/* ロゴの作成 */
	m_pLogo = new CSprite(m_pd3dDevice, const_cast<TCHAR*>("Data\\Ending\\EndingLogo.png"));
	m_pLogo->SetVec(D3DXVECTOR2(64, 30));
	m_pLogo->SetRec(0,0,512,64);

	return S_OK;
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	In:		なし
//	Out:	int = 状態変更識別子
//----------------------------------------------
int CEnding::FrameMove()
{
	/* リターンを押したらタイトルへ移行する */
	if(GetAsyncKeyState(VK_RETURN) & 0x0001)
		return CHANGE_TITLE;

	/* 背景を動かす */
	m_pBackGround->FrameMove();

	return NO_CHANGE;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	In:		なし
//	Out:	なし
//----------------------------------------------
void CEnding::Render()
{
	m_pBackGround->Render();
	m_pLogo->Render();

	for(int i=0; i<4; i++)
		m_pOrder[i]->Render();

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	データ更新
//	In:		なし
//	Out:	なし
//----------------------------------------------
void CEnding::UpDate()
{
	m_pBackGround->UpDate();
	m_pLogo->UpDate();

	for(int i=0; i<4; i++)
		m_pOrder[i]->UpDate();
}
