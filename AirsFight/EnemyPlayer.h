//==========================================================
// EnemyPlayer.h
// Auther : ���� ���V
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
//	Func:	�G�v���C���[�i�ΐ푊��j
//			���ɉ������Ȃ��N���X�i�I�j
//----------------------------------------------
class CEnemyPlayer : public CChara    
{

public:
	/* �Q�[�����̖��t���[���̏��� */
	void FrameMoveGame(CStage* pStage, CBulManage* pBulManage, 
			CSpriteManage* pSpriteManage,CEffectManage* pEffectManage);

	CEnemyPlayer(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEnemyPlayer();

};

#endif // !defined(AFX_ENEMYPLAYER_H__887B74A1_AEA7_4489_9EAB_1C1889DB812C__INCLUDED_)
