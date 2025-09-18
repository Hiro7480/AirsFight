//==========================================================
// MyPlayer.h
// Auther : 桜井 博之
// Data   : 2002/05/05
//==========================================================

#if !defined(AFX_MYPLAYER_H__19EDB939_22CA_4E75_8FDA_48CB7706909A__INCLUDED_)
#define AFX_MYPLAYER_H__19EDB939_22CA_4E75_8FDA_48CB7706909A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------
#include "Chara.h"
#include "LockOnMarker.h"
#include "Font.h"

//----------------------------------------------
//	Name:	CMyPlayer
//	Func:	自分のキャラを操作するクラス
//----------------------------------------------
class CMyPlayer : public CChara  
{
private:
	int				m_nCnt;				// 汎用カウンタ

	/* ロックオン関係の変数 */
	D3DXVECTOR3		m_vecView[3];		// ビュー変換した時の座標値
	D3DXVECTOR2		m_vecProject[3];	// 透視変換した時の座標値

	CLockOnMarker*	m_pLockMarker[3];	// ロックオンマーカー
	CFont*			m_pCharaName[3];	// キャラクター名
	CFont*			m_pCharaLife[3];	// ライフ値

	bool			m_bCanLock[3];		// ロックオンが可能か？
	bool			m_bNowLock;			// 現在ロックオンしているか？
	int				m_nLockTarget;		// ロックオンの対象
										// していない時あるいはできない時は-1

	/* キャラクターの状態により分岐する関数 */
	void	Start(CSpriteManage* pSpriteManage);
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

	/* ロックオンに関するプライベートメソッド */
	void	LockOn(CStage* pStage);		// ロックオンに関するものを記述
	void	IsLockON(CStage* pStage);	// ロックオンできるかどうか調べる
	void	SelectTarget();				// ターゲットとなるキャラクタを選ぶ
	void	ComputProject();			// プロジェクション座標値の計算
	void	ComputView();				// ビュー座標値の計算

public:
	/* ゲーム時のフレームの処理 */
	void FrameMoveGame(CStage* pStage, CBulManage* pBulManage, CSpriteManage* pSpriteManage, CEffectManage* pEffectManage);

	/* 描画処理 */
	void Render();

	/* データ更新 */
	void UpDate();

	/* キャラクタの名前フォントを作成 */
	void CreateCharaName();

	/* キャラクタのライフフォントを作成 */
	void CreateCharaLife();

	/* アクセス関数 */
	bool			GetLockFlg(){return m_bNowLock;};		// 現在ロックオンしているかを取得
	D3DXVECTOR3		GetLockVec();							// 現在のロックオン座標値の取得

	CMyPlayer(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CMyPlayer();

};

//----------------------------------------------------------------------
//	Name:	GetLockVec
//	Func:	現在ロックオンしているキャラクタの座標値を取得
//			ロックオンしていないならNULLを返す
//	In:		なし
//	Out:	D3DXVECTOR3	= ロックオンしている相手の座標値
//----------------------------------------------------------------------
inline D3DXVECTOR3 CMyPlayer::GetLockVec()
{
	/* ロックオンしていないならNULLを返す */
	if(!m_bNowLock)	return NULL;

	/* データがないときもNULLを返す（念のため） */
	if(m_tagEnemyData[m_nLockTarget].pMatrix == NULL)	return NULL;

	/* ロックオンしている場合はそのマトリクスをまず出す */
	D3DXMATRIX	matTmp = *m_tagEnemyData[m_nLockTarget].pMatrix;

	/* マトリクスをベクトルに変換して返す */
	return D3DXVECTOR3(matTmp._41, matTmp._42, matTmp._43);
}


#endif // !defined(AFX_MYPLAYER_H__19EDB939_22CA_4E75_8FDA_48CB7706909A__INCLUDED_)
