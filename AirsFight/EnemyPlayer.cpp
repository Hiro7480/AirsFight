//==========================================================
// EnemyPlayer.cpp
// Auther : 桜井 博之
// Data   : 2002/05/05
//==========================================================
#include "EnemyPlayer.h"

//------------------------------------------------------
//	Name:	EnemyPlayer
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3Dデバイス
//	Out:	なし
//------------------------------------------------------
CEnemyPlayer::CEnemyPlayer(LPDIRECT3DDEVICE8 d3dDevice):CChara(d3dDevice)
{

}

//------------------------------------------------------
//	Name:	~EnemyPlayer
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//------------------------------------------------------
CEnemyPlayer::~CEnemyPlayer()
{

}

//----------------------------------------------------------------------
//	Name:	FrameMoveGame
//	Func:	ゲーム時の毎フレームの処理
//	in:		CStage*			pStage			= ステージクラスポインタ
//			CBulManage*		pBulManage		= 弾管理クラスポインタ
//			CSpriteManage*	pSpriteManage	= スプライト管理クラスポインタ
//			CEffectManage*	pEffectManage	= エフェクト管理クラスポインタ
//	Out:	なし
//----------------------------------------------------------------------
void CEnemyPlayer::FrameMoveGame(CStage* pStage, CBulManage* pBulManage, 
			CSpriteManage* pSpriteManage,CEffectManage* pEffectManage)
{
	/* 現在の状態によってエフェクトを発生させる */
	switch(m_nNowAction)
	{
	case DASH:
		pEffectManage->AddEffect(BOOST_A, m_matBase);
		break;

	case FLYGHT:
		pEffectManage->AddEffect(BOOST_B, m_matBase);
		break;
	}
}