//==========================================================
// Chara.h
// Auther : 桜井 博之
// Data   : 2002/02/26
//==========================================================

#if !defined(AFX_Chara_H__0BF69BE4_6286_400C_B667_F7658AF7BE57__INCLUDED_)
#define AFX_Chara_H__0BF69BE4_6286_400C_B667_F7658AF7BE57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "MyFunction.h"
#include "3DGraphicObj.h"
#include "ActiveMotion.h"

#include "Stage.h"
#include "BulManage.h"
#include "SpriteManage.h"
#include "EffectManage.h"

#include "time.h"

//------------------------------
//	定数定義
//------------------------------

/* キャラクターの状態識別子 */
enum{
	START,		// ゲーム開始前
	WALK,		// 歩いている
	DASH,		// 走っている
	ATTACK_S,	// 攻撃構え
	ATTACK,		// 攻撃

	JUMP_START,	// ジャンプ開始
	JUMP_MAIN,	// ジャンプ中
	JUMP_END,	// ジャンプ終了

	FLYGHT,		// 飛行中

	DAMAGE_LAND,// 地面にいてダメージ
	DAMAGE_AIR,	// 空中にいてダメージ

	DEAD_LAND,	// 地面にいて死亡
	DEAD_AIR	// 空中にいて死亡
};

/* アニメーションの識別子(連番必須) */
#define ANI_STOP		0	// 止まっている
#define ANI_FORWARD		1	// 走っている
#define ANI_BACK		2	// 後退している
#define ANI_DASH_F		3	// 前方にダッシュ
#define ANI_DASH_B		4	// 後方にダッシュ
#define ANI_DASH_R		5	// 右にダッシュ
#define ANI_DASH_L		6	// 左にダッシュ
#define ANI_ATAS		7	// 攻撃構え
#define ANI_ATA 		8	// 攻撃アニメーション

#define ANI_JUMP_N		9	// 垂直にジャンプ
#define ANI_JUMP_F		10	// 前方にジャンプ
#define ANI_JUMP_B		11	// 後方にジャンプ
#define ANI_JUMP_S		12	// ジャンプ開始時
#define ANI_JUMP_E		13	// ジャンプ終了時
#define ANI_DAM_L		14	// 地面でダメージ
#define ANI_DAM_A		15	// 空中でダメージ
#define ANI_DEAD_L		16	// 地上で死亡
#define ANI_DEAD_A		17	// 空中で死亡

#define MAX_MOTION		18	// モーション最大数

/* 面との当たり判定距離 */
#define HIT_GROUND		5.0f// 地面との当たり判定距離
#define HIT_WALL		3.0f// 壁との当たり判定距離
#define HIT_CEILING		5.0f// 天井との当たり判定距離

/* エネルギーの使用量、回復量 */
#define USE_ENERGY_DASH 3	// ダッシュ中に使うエネルギー値
#define USE_ENERGY_FLY	3	// 飛行中に使うエネルギー値
#define REST_ENERGY		2	// 毎フレーム回復するエネルギー値

/* ダメージの後の無敵時間 */
#define DAMAGE_CNT		20

/* エフェクトの発生する間隔 */
#define EFFECT_DASH		4	// ダッシュ時に出るブーストエフェクト
#define EFFECT_FLY		4	// 飛行時にでるブーストエフェクト
#define EFFECT_BUL		3	// 弾を飛ばしている時にでる軌道エフェクト

/* データを送信する間隔 */
#define SEND_CHARA		4	// キャラクタの座標値などの更新間隔

/* キー操作方法の定義 */
#define KEY_FORWARD			VK_UP		// 前進キー
#define KEY_BACK			VK_DOWN		// 後退キー
#define KEY_RIGHT			VK_RIGHT	// 右旋回
#define KEY_LEFT			VK_LEFT		// 左旋回

#define KEY_LOCK			VK_SPACE	// ロックオン
#define KEY_ATAS			'A'			// 攻撃構え
#define KEY_ATTACK			'S'			// 攻撃
#define KEY_DASH			'Z'			// ダッシュ
#define KEY_JUMP			'X'			// ジャンプ

#define KEY_ANGLE_CONTROL	VK_SHIFT	// アングル操作
#define KEY_ANGLE_FORMAT	VK_CONTROL	// アングル初期化
#define KEY_ANGLE_UP		VK_NUMPAD0	// 上を向く
#define KEY_ANGLE_DOWN		VK_NUMPAD1	// 下を向く


//----------------------------------------------
//	Name:	tagCharaParam
//	Func:	キャラクタパラメータ構造体
//----------------------------------------------
typedef	struct {
	CMeshData*		pMeshData;		// 階層構造をもつメッシュデータ

//	BulStatus*		pBulStatus;		// 搭載されている弾ステータスデータ

	int				nMaxLife;		// 最大ＨＰ
	int				nMaxEnergy;		// 最大エネルギー値

	float			fWalkSpeed;		// 歩行速度
	float			fBackSpeed;		// 後退速度
	float			fDashSpeed;		// ダッシュ速度

	float			fJumpUp;		// ジャンプした瞬間のＹ軸移動量
	float			fJumpDown;		// ジャンプ中の降下量
	float			fJumpForward;	// ジャンプ中の前進移動速度
	float			fJumpBack;		// ジャンプ中の後退移動速度

	float			fFlyForward;	// 飛行中の前進移動速度
	float			fFlyBack;		// 飛行中の後退移動速度
	float			fFlyPlumb;		// 飛行中の上昇速度

	float			fTurn;			// 旋回速度

	float			fLockLength;	// ロックオンできる長さ

	float			fBrakes;		// ダメージ中に毎回スピードを減らしていく値

} tagCharaParam;

//----------------------------------------------
//	Name:	TEnemyData
//	Func:	敵キャラクターの情報
//----------------------------------------------
struct TEnemyData
{
	D3DXMATRIX*	pMatrix;		// マトリクスへのポインタ
	int*		pNowLife;		// ライフへのポインタ
	TCHAR		Name[256];		// 名前へのポインタ
};

//--------------------------------------------------
//		データ送信用構造体
//--------------------------------------------------
/* 準備OKメッセージ */
struct TReady{
	DWORD		dwDpnType;		// メッセージタイプ
	int			nCharaNum;		// キャラクタ番号
};

/* キャラに関するデータ 毎フレーム定期的に転送する */
struct TChara{
	DWORD		dwDpnType;		// メッセージタイプ
	int			nCharaNum;		// キャラクタ番号
	int			nNowLife;		// 残りライフ
	int			nDeadNum;		// 死んだ回数
	int			nAction;		// 行動
	D3DXMATRIX	matBase;		// ワールド変換マトリクス
	D3DXMATRIX	matMotion[16];	// モーションマトリクス
};

/* 被弾メッセージ */
struct THitBullet{
	DWORD		dwDpnType;		// メッセージタイプ
	long		lID;			// 弾識別番号
};

/* エフェクト発生メッセージ */
struct TEffect{
	DWORD		dwDpnType;		// メッセージタイプ
	DWORD		dwEffectType;	// エフェクトタイプ
	D3DXMATRIX	matBase;		// エフェクト発生位置
};

//----------------------------------------------
//	Name:	CChara
//	Func:	キャラクラス
//----------------------------------------------
class CChara:public C3DGraphicObj
{
protected:
	CActiveMotion*	m_pActiveMotion;	// アクティブモーションデータ
	tagCharaParam*	m_pParam;			// パラメータ構造体へのポインタ

	TEnemyData		m_tagEnemyData[3];	// 他のキャラクタのマトリクスへのポインタ

	TCHAR			m_cName[256];		// プレイヤーの名前
	int				m_nNum;				// プレイヤー番号

	int				m_nNowLife;			// 現在のＨＰ
	int				m_nNowEnergy;		// 現在のエネルギー
	int				m_nDeadNum;			// 死んだ回数
	int				m_nNowAction;		// 現在の状態

	/* キャラクタの移動等に関するメンバ */
	D3DXVECTOR3		m_vecMove;			// 動いている方向への単位方向ベクトル
	float			m_fCharaYaw;		// キャラの向いている角度
	float			m_fMoveYaw;			// キャラの向いている角度
	float			m_fCharaPitch;		// 縦方向の視線角度
	float			m_fSpeed;			// 現在の移動速度
	float			m_fJump;			// ジャンプ値
	int				m_nDamageCnt;		// ダメージを受けた後の無敵時間

	/* 面を調べるメソッド */
	float		SearchAllGround(CStage* pStage, D3DXPLANE* plaOut, D3DXVECTOR3*	vecOut);	// 地面を調べる
	float		SearchAllWall(CStage* pStage, D3DXVECTOR3* vecOut1, D3DXVECTOR3* vecOut2);	// 壁を調べる
	float		SearchAllCeiling(CStage* pStage, D3DXPLANE* plaOut, D3DXVECTOR3* vecOut);	// 天井を調べる
	bool		SearchAllPlane(CStage* pStage, D3DXVECTOR3 vecPos1, D3DXVECTOR3 vecPos2);	// 二つの座標間での、面の有無を判定
	D3DXVECTOR3	GetVecToPlane(D3DXPLANE* plaGround, float fYaw);	// 地面の式と角度から方向ベクトルを求める

public:
	/* ゲーム時の毎フレームの処理 */
	virtual void FrameMoveGame(CStage* pStage, CBulManage* pBulManage, CSpriteManage* pSpriteManage,
		CEffectManage*	pEffectManage){};

	/* ゲーム開始時の毎フレームの処理 */
	void FrameMoveStart();

	/* ゲーム終了時の毎フレームの処理 */
	void FrameMoveEnd();

	virtual void Render();					// 画面描画
	virtual void UpDate();					// データ更新

	/* アクティブモーションの作成 */
	HRESULT	CreateActive(CMotionData* pMotionData[]);

	/* キャラクタの初期化全般 */
	void	AllInit(D3DXVECTOR3 vecPos, float fCharaYaw);

	/* 弾との当たり判定 */
	void	IsHitBullet(CBulManage* pBulManage, CEffectManage* pEffectManage);

	/* 死亡判定 */
	bool	IsDead();

	/* キャラクタの名前フォントを作成 */
	virtual void CreateCharaName(){};

	/* キャラクタのライフフォントを作成 */
	virtual void CreateCharaLife(){};

	/* アクセス関数*/
	CActiveMotion*	GetActiveMotion(){return m_pActiveMotion;};	// アクティブモーションの取得
	D3DXVECTOR3		GetMoveVec(){return m_vecMove;};			// 移動ベクトルの取得
	float			GetPitch(){return m_fCharaPitch;};			// キャラクタの視線角度の取得

	TCHAR*			GetName(){return m_cName;};					// 名前の取得
	int				GetNum(){return m_nNum;};					// プレイヤー番号の取得
	int				GetNowLife(){return m_nNowLife;};			// 現在のＨＰの取得
	int				GetNowEnergy(){return m_nNowEnergy;};		// 現在のエネルギーの取得
	int				GetMaxLife();								// 最大ＨＰの取得
	int				GetMaxEnergy();								// 最大エネルギーの取得
	int 			GetNowAction(){return m_nNowAction;};		// 現在の状態の取得
	int				GetDeadNum(){return m_nDeadNum;};			// 死んだ数を取得
	int*			GetLifePointer(){return &m_nNowLife;};		// 現在のライフのポインタを取得

	void	SetAction(int nAction){m_nNowAction = nAction;};			// 行動状態の格納
	void	SetType(tagCharaParam* pType){m_pParam = pType;};			// キャラクタタイプのセット
	void	SetName(TCHAR* cName){strcpy(m_cName, cName);};				// 名前のセット
	void	SetNum(int nNum){m_nNum = nNum;};							// プレイヤー番号のセット
	void	SetNowLife(int nNowLife){m_nNowLife = nNowLife;};			// 現在ＨＰのセット
	void	SetNowEnergy(int nNowEnergy){m_nNowEnergy = nNowEnergy;};	// 現在エネルギー値のセット
	void	SetDeadNum(int nDeadNum){m_nDeadNum = nDeadNum;};			// 死んだ回数をセット

	void SetEnemyData(int n, D3DXMATRIX* pMat, int* pLife, TCHAR* pName);	// 敵キャラのデータのセット

	CChara(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CChara();
};

//----------------------------------------------
//	Name:	GetMaxLife
//	Func:	最大ＨＰの取得
//	In	:	なし
//	Out	:	int = 最大ＨＰ
//----------------------------------------------
inline int CChara::GetMaxLife()
{
	return m_pParam->nMaxLife;
}

//----------------------------------------------
//	Name:	GetMaxEnergy
//	Func:	最大エネルギーの取得
//	In	:	なし
//	Out	:	int = 最大エネルギー
//----------------------------------------------
inline int CChara::GetMaxEnergy()
{
	return m_pParam->nMaxEnergy;
}

//----------------------------------------------------------------------
//	Name:	SetEnemyData
//	Func:	敵キャラデータのセット
//	In:		int			n		= セットするキャラクタを示す
//			D3DXMATRIX* pMat	= マトリクス
//			int*		pLife	= ライフ
//			TCHAR*		pName	= 名前
//	Out:	なし
//----------------------------------------------------------------------
inline void CChara::SetEnemyData(int n, D3DXMATRIX* pMat, int* pLife, TCHAR* pName)
{
	m_tagEnemyData[n].pMatrix  = pMat;		// マトリクスのセット
	m_tagEnemyData[n].pNowLife = pLife;		// ライフのセット
	strcpy(m_tagEnemyData[n].Name, pName);	// プレイヤー名のセット
}

#endif // !defined(AFX_Chara_H__0BF69BE4_6286_400C_B667_F7658AF7BE57__INCLUDED_)
