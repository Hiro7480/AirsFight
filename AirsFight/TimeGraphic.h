//==========================================================
// TimeGraphic.h
// Auther : 桜井 博之
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_TIMEGRAPHIC_H__EB7CCC7F_E765_4021_9E56_1F8028076E6D__INCLUDED_)
#define AFX_TIMEGRAPHIC_H__EB7CCC7F_E765_4021_9E56_1F8028076E6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------
//	インクルード
//--------------------------
#include "CompatiDX8.h"
#include <time.h>
#include "Sprite.h"

//------------------------------------------
//	Name:	CTimeGraphic
//	Func:	残り時間を表示
//------------------------------------------
class CTimeGraphic : public CSprite
{
private:
	long	m_lStartTime;		// 開始時間
	long	m_lNowTime;			// 現在時間

	long	m_lMaxTime;			// 最大制限時間
	long	m_lLimitTime;		// 残り制限時間

	bool	m_bPlay;			// 時間計測中か？

	RECT	m_rcBase[5];		// 処理用RECT
	RECT	m_rcStock[5];		// 描画用RECT

	D3DXVECTOR2		m_vecPos;	// 基本描画位置

public:
	void	FrameMove();		// 毎フレームの処理
	void	Render();			// 描画処理
	void	UpDate();			// データ更新

	void	Start();			// 時間計測開始
	bool	IsEnd();			// 残り制限時間がなくなったか？

	/* アクセス関数 */
	long GetLimitTime(){return m_lLimitTime;};				// 残り制限時間の取得

	void SetStartTime(long lTime){m_lStartTime = lTime;};	// 開始時間のセット
	void SetNowTime(long lTime){m_lNowTime = lTime;};		// 現在時間のセット
	void SetMaxTime(long lTime){m_lMaxTime = lTime;};		// 最大制限時間のセット

	CTimeGraphic(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CTimeGraphic();
};

#endif // !defined(AFX_TIMEGRAPHIC_H__EB7CCC7F_E765_4021_9E56_1F8028076E6D__INCLUDED_)
