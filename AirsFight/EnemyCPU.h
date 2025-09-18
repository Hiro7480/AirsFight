//==========================================================
// EnemyCPU.h
// Auther : 桜井 博之
// Data   : 2002/05/05
//==========================================================

#if !defined(AFX_ENEMYCPU_H__63357F8F_C02D_4E56_B282_F5DCA3A8EC96__INCLUDED_)
#define AFX_ENEMYCPU_H__63357F8F_C02D_4E56_B282_F5DCA3A8EC96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//--------------------------
//	インクルード
//--------------------------
#include "Chara.h"
#include <time.h>

//----------------------------------------------
//	Name:	CCEnemuCPU
//	Func:	敵キャラコンピュータ
//----------------------------------------------
class CEnemyCPU : public CChara  
{
private:
	/* 仮想キーが押されているかどうかを格納する構造体 */
	struct TVirtualKey
	{
		bool	Up;		// 上キー
		bool	Down;	// 下キー
		bool	Left;	// 左キー
		bool	Right;	// 右キー
	};

	int				m_nNextStatus;		// ランダムで決めた次に起こす行動
	int				m_nActionCount;		// 行動を続けるカウンター
	TVirtualKey		m_tagVirtualKey;	// 仮想キー

	int				m_nCnt;				// 汎用カウンタ

	/* コンピュータの次の行動を決める */
	void	ComputNextAction(CEffectManage* pEffectManage);

	/* キャラクターの状態により分岐する関数 */
	void	Start();
	void	Walk(CStage* pStage);
	void	Dash(CStage* pStage, CEffectManage* pEffectManage);

	void	Attack_S();
	void	Attack(CBulManage* pBulManage);
	void	JumpStart(CStage* pStage, CEffectManage* pEffectManage);

	void	JumpMain(CStage* pStage);
	void	JumpEnd();

	void	Flyght(CStage* pStage, CEffectManage* pEffectManage);

	void	DamageLand(CStage* pStage, CEffectManage* pEffectManage);
	void	DamageAir(CStage* pStage, CEffectManage* pEffectManage);

	void	DeadLand(CStage* pStage, CEffectManage* pEffectManage);
	void	DeadAir(CStage* pStage, CEffectManage* pEffectManage);

public:
	/* ゲーム時の毎フレームの処理 */
	void FrameMoveGame(CStage* pStage, CBulManage* pBulManage, CSpriteManage* pSpriteManage,
		CEffectManage* pEffectManage);

	CEnemyCPU(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEnemyCPU();

};

#endif // !defined(AFX_ENEMYCPU_H__63357F8F_C02D_4E56_B282_F5DCA3A8EC96__INCLUDED_)
