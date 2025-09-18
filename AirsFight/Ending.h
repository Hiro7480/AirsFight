//==========================================================
// Ending.h
// Auther : 桜井 博之
// Data   : 2002/05/20
//==========================================================

#if !defined(AFX_ENDING_H__0D5B5B1B_942D_4965_BF52_5D937583A52A__INCLUDED_)
#define AFX_ENDING_H__0D5B5B1B_942D_4965_BF52_5D937583A52A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "GameStatus.h"
#include "OrderSprite.h"
#include "ScrollBG.h"

//----------------------------------------------
//	Name:	CEnding
//	Func:	エンディング時の管理
//----------------------------------------------
class CEnding : public GameStatus  
{
	/* キャラクタのデータをあらわす構造体 */
	struct TChara{
		TCHAR	strName[256];		// 名前
		int		nDeadNum;			// 死んだ数
		int		nOrder;				// 順位
	};

	TChara			m_tagChara[4];	// キャラクタデータ
	COrderSprite*	m_pOrder[4];	// 順位スプライト

	CSprite*		m_pLogo;		// エンディング時のロゴ
	CScrollBG*		m_pBackGround;	// 背景のタイル

public:
	int		FrameMove();			// 毎フレームの処理
	void	Render();				// 画面描画
	void	UpDate();				// データ更新

	HRESULT	InitOrder(int nDeadNum1, int nDeadNum2, int nDeadNum3, int nDeadNum4);	// 順位に関する初期化


	CEnding(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEnding();
};

#endif // !defined(AFX_ENDING_H__0D5B5B1B_942D_4965_BF52_5D937583A52A__INCLUDED_)
