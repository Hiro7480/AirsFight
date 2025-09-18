//==========================================================
// EnemyPlayer.h
// Auther : 桜井 博之
// Data   : 2002/05/05
//==========================================================

#if !defined(AFX_ENEMYPLAYER_H__887B74A1_AEA7_4489_9EAB_1C1889DB812C__INCLUDED_)
#define AFX_ENEMYPLAYER_H__887B74A1_AEA7_4489_9EAB_1C1889DB812C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Chara.h"

//----------------------------------------------
//	Name:	CEnemyPlayer
//	Func:	敵プレイヤー（対戦相手）
//			特に何もしないクラス（！）
//----------------------------------------------
class CEnemyPlayer : public CChara    
{

public:
	/* ゲーム時の毎フレームの処理 */
	void FrameMoveGame(CStage* pStage, CBulManage* pBulManage, 
			CSpriteManage* pSpriteManage,CEffectManage* pEffectManage);

	CEnemyPlayer(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEnemyPlayer();

};

#endif // !defined(AFX_ENEMYPLAYER_H__887B74A1_AEA7_4489_9EAB_1C1889DB812C__INCLUDED_)
