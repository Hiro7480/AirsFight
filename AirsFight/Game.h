//==========================================================
// Game.h
// Auther : 桜井 博之
// Data   : 2002/01/10
//==========================================================

#if !defined(AFX_Game_H__FD56F37B_91FF_467E_AAFB_D4571886E6D9__INCLUDED_)
#define AFX_Game_H__FD56F37B_91FF_467E_AAFB_D4571886E6D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "CompatiDX8.h"
#include "GameStatus.h"

#include "Chara.h"
#include "MyPlayer.h"
#include "EnemyPlayer.h"
#include "EnemyCPU.h"

#include "Stage.h"
#include "Camera.h"
#include "BulManage.h"
#include "SpriteManage.h"
#include "EffectManage.h"

#include "EnergyGauge.h"
#include "LifeGraphic.h"
#include "TimeGraphic.h"

//------------------------------
//	定数定義
//------------------------------
/* ゲームの状態識別子 */
enum{
	GAME_START,		// ゲーム開始
	GAME_MAIN,		// ゲームメイン
	GAME_END		// ゲーム終了
};

//----------------------------------------------
//	Name:	CGame
//	Func:	ゲーム時の管理
//----------------------------------------------
class CGame : public GameStatus
{
private:
	CChara*			m_pChara[4];				// キャラクターデータ
	tagCharaParam	m_CharaParam[4];			// キャラクタパラメータ
	CMotionData*	m_pMotionData[MAX_MOTION];	// モーションデータ配列
	int				m_nMyChara;					// キャラ配列での自分の添え字を示す

	CStage*			m_pStage;					// ステージクラス
	CCamera*		m_pCamera;					// カメラクラス
	CBulManage*		m_pBulManage;				// 弾管理クラス
	CSpriteManage*	m_pSpriteManage;			// スプライト管理クラス
	CEffectManage*	m_pEffectManage;			// エフェクト管理クラス

	CEnergyGauge*	m_pEnergyGauge;				// エネルギーゲージスプライト
	CLifeGraphic*	m_pLifeGraphic;				// ライフスプライト
	CTimeGraphic*	m_pTimeGraphic;				// 残り時間を表示

	DWORD			m_dwNowStatus;				// 現在の状態

	bool			m_bReady[4];				// 準備OKフラグ

	/* ゲームの状態によって分岐する関数 */
	void	Start();
	void	Game();
	bool	End();

public:
	int		FrameMove();			// フレーム毎の処理
	void	Render();				// 画面描画処理
	void	UpDate();				// 描画用マトリクスの更新

	HRESULT	CreateChara(int SelectChara[]);		// キャラクタの作成

	/* アクセス関数 */
	int		GetDeadNum(int n){return m_pChara[n]->GetDeadNum();};		// 死んだ数配列の取得

	CGame(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CGame();

};
#endif // !defined(AFX_Game_H__FD56F37B_91FF_467E_AAFB_D4571886E6D9__INCLUDED_)
