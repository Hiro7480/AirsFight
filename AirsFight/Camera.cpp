//==========================================================
// CCamera.cpp
// Auther : 桜井 博之
// Data   : 2002/02/25
//==========================================================

#include "Camera.h"

//----------------------------------------------
//	Name:	CCamera
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3Dデバイスz
//	Out:	なし
//----------------------------------------------
CCamera::CCamera(LPDIRECT3DDEVICE8 d3dDevice)
		:C3DGraphicObj(d3dDevice)
{
	m_fLength = 30.0f;			// 対象との距離の設定
	m_fFrameSpeed = 2.0f;		// カメラ1フレーム移動量の設定

	m_fNowYaw = 180.0f;
	m_fNextYaw = 180.0f;
	m_fNowPitch = 0.0f;
	m_fNextPitch = 0.0f;
}

//----------------------------------------------
//	Name:	~CCamera
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CCamera::~CCamera()
{

}

//------------------------------------------------------
//	Name:	FrameMove
//	Func:	毎フレームの処理
//	in:		CChara* pChara = プレイヤークラスへのポインタ
//	Out:	なし
//------------------------------------------------------
void CCamera::FrameMove(CMyPlayer* pMyPlayer)
{
	D3DXVECTOR3 vec;
	D3DXMATRIX mat;

	/* ロックオンしていないとき */
	if(!pMyPlayer->GetLockFlg())
	{
		/* 目標となる角度の格納 */
		mat = pMyPlayer->GetMatBase();
		vec = GetNormalVec3ToMat(NULL, &mat);
		SetNextYaw(&vec);
		SetNextPitch(pMyPlayer->GetPitch()-10.0f);

		// 現在角度を目標角度に近づける
		MoveYaw();
		MovePitch();

		// 現在角度からカメラ位置の設定
		SetPosition(pMyPlayer);
	}

	/* ロックオンしているとき */
	else
	{
		/* キャラ→目標への単位方向ベクトルの算出 */
		D3DXVECTOR3	vecTmp;
		vecTmp = pMyPlayer->GetLockVec() - pMyPlayer->GetPosBase();
		D3DXVec3Normalize(&vecTmp, &vecTmp);
		vecTmp.y -= 0.2f;

		/* 単位方向ベクトル値により目標となる角度を算出 */
		SetNextYaw(&vecTmp);
		SetNextPitch(&vecTmp);

		/* 現在角度を目標角度に近づける */
		MoveYaw();
		MovePitch();

		/* 現在角度からカメラ位置の設定 */
		SetPosition(pMyPlayer);
	}
}
//----------------------------------------------
//	Name:	Render
//	Func:	描画時用の処理
//	in:		CChara* pChara = キャラクタクラス
//	Out:	なし
//----------------------------------------------
void CCamera::Render(CChara* pChara)
{
	D3DXVECTOR3 vec1 = pChara->GetPosStock();
	D3DXVECTOR3 vec2(0.0f, 1.0f, 0.0f);

	/* 対象位置とカメラ位置からビュー変換マトリクスを算出する */
	D3DXMatrixLookAtLH(&m_matStock, &m_vecStock, &vec1, &vec2);

	/* カメラ位置設定 */
	m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_matStock );
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	描画時用変数の更新
//	in:		なし
//	Out:	なし
//----------------------------------------------
void CCamera::UpDate()
{
	C3DGraphicObj::UpDate();
	m_vecStock = m_vecPos;
}

//----------------------------------------------
//	Name:	SetPosition
//	Func:	カメラ位置を現在角度により算出
//	in:		CChara* pChara	= キャラクタクラス
//	Out:	なし
//----------------------------------------------
void CCamera::SetPosition(CChara* pChara)
{
	D3DXVECTOR3	vecTmp;
	D3DXMATRIX	matTmp1;
	D3DXMATRIX	matTmp2;

	// 現在角度よりＹ軸回転行列を作る
	D3DXMatrixRotationY(&matTmp1, D3DXToRadian(m_fNowYaw));

	// 現在角度よりＸ軸回転行列を作る
	D3DXMatrixRotationX(&matTmp2, D3DXToRadian(m_fNowPitch));

	// 総合の回転行列を求める
	matTmp1 = matTmp2 * matTmp1;

	// カメラのローカル座標を作成する
	D3DXVECTOR3 v = D3DXVECTOR3(0, 0, m_fLength);
	D3DXVec3TransformCoord(&vecTmp, &v, &matTmp1);

	// ローカル座標をワールド座標に変換する
	vecTmp.x += pChara->GetPosBase().x;
	vecTmp.y += pChara->GetPosBase().y;
	vecTmp.z += pChara->GetPosBase().z;

	// カメラ座標に格納
	m_vecPos = vecTmp;
}

//----------------------------------------------
//	Name:	SetNowYaw
//	Func:	現在Yaw角度をカメラ位置と対象位置から算出
//	in:		CChara* pChara = キャラクタクラス
//	Out:	なし
//----------------------------------------------
void CCamera::SetNowYaw(CChara* pChara)
{
	D3DXVECTOR3	vecTmp;
	vecTmp = pChara->GetPosBase() - m_vecPos;
	GetVec3Inverce(&vecTmp, &vecTmp);

	m_fNowYaw  = D3DXUntiRagian((float)atan2(vecTmp.x, vecTmp.z));
}

//----------------------------------------------
//	Name:	SetNowPitch
//	Func:	現在Pitch角度をカメラ位置と対象位置から算出
//	in:		CChara* pChara = キャラクタクラス
//	Out:	なし
//----------------------------------------------
void CCamera::SetNowPitch(CChara* pChara)
{
	D3DXVECTOR3	vecTmp;
	vecTmp =m_vecPos - pChara->GetPosBase();
	GetVec3Inverce(&vecTmp, &vecTmp);

	// X,Z軸の長さを求める
	float	fTmp;
	fTmp = GetLengthEX(&vecTmp, true, false, true);

	m_fNowPitch  = D3DXUntiRagian((float)atan2(vecTmp.y, fTmp));
}

//----------------------------------------------
//	Name:	SetNextYaw
//	Func:	指定した方向にカメラを向かせるために、
//			目標となるYaw角度を算出
//	in:		D3DXVECTOR3* vecIn
//	Out:	なし
//----------------------------------------------
void CCamera::SetNextYaw(D3DXVECTOR3* vecIn)
{
	// ベクトルを逆にする
	D3DXVECTOR3	vecTmp;
	vecTmp = GetVec3Inverce(NULL, vecIn);

	// 角度の計算
	m_fNextYaw = D3DXUntiRagian((float)atan2(vecTmp.x, vecTmp.z));

	// 360を超えたら修正
	if(m_fNextYaw >= 360.0f)		m_fNextYaw -= 360.0f;
	else if(m_fNextYaw < 0.0f)		m_fNextYaw += 360.0f;
}

//----------------------------------------------
//	Name:	SetNextPitch
//	Func:	指定した方向にカメラを向かせるために、
//			目標となるPitch角度を算出
//	in:		D3DXVECTOR3* vecIn
//	Out:	なし
//----------------------------------------------
void CCamera::SetNextPitch(D3DXVECTOR3* vecIn)
{
	// ベクトルを逆にする
	D3DXVECTOR3	vecTmp;
	vecTmp = GetVec3Inverce(NULL, vecIn);

	// X,Z軸の長さを求める
	float	fTmp;
	fTmp = GetLengthEX(&vecTmp, true, false, true);

	// 角度の計算
	m_fNextPitch = D3DXUntiRagian((float)atan2(-vecTmp.y, fTmp));

	// 360を超えたら修正
	if(m_fNextPitch >= 360.0f)		m_fNextPitch -= 360.0f;
	else if(m_fNextPitch < 0.0f)	m_fNextPitch += 360.0f;
}

//----------------------------------------------
//	Name:	SetNextPitch
//	Func:	単純に目標になるPitch角度をセット
//	in:		float fPitch = Pitch角度値
//	Out:	なし
//----------------------------------------------
void CCamera::SetNextPitch(float fPitch)
{
	m_fNextPitch = fPitch;
}

//----------------------------------------------
//	Name:	MoveYaw
//	Func:	現在Yaw角度値を目標Yaw角度値に近づける
//	in:		D3DXVECTOR3* vecIn
//	Out:	なし
//----------------------------------------------
void CCamera::MoveYaw()
{
	// カメラを回転させる際、右回りか左回りか
	// どちらが近いか判定
	// 目標角度と現在角度が同じなら処理をしない
	if(m_fNowYaw != m_fNextYaw)
	{
		float fTmp;
		fTmp = m_fNowYaw - m_fNextYaw;
		// 360を超えたら修正
		if(fTmp >= 360.0f)		fTmp -= 360.0f;
		else if(fTmp < 0.0f)	fTmp += 360.0f;

		// 左回り（マイナス）の方が近い時
		if(fTmp < 180.0f)
		{
			// 移動量の算出
			m_fFrameSpeed = fTmp / 10.0f;	
			// カメラ位置の移動
			m_fNowYaw -= m_fFrameSpeed;
		}
		// 右回り（プラス）の方が近い時
		else
		{
			// 移動量の算出
			fTmp = 360.0f - fTmp;
			m_fFrameSpeed = fTmp / 10.0f;
			// カメラ位置の移動
			m_fNowYaw += m_fFrameSpeed;
		}
	}
	// 360を超えたら修正
	if(m_fNowYaw >= 360.0f)		m_fNowYaw -= 360.0f;
	else if(m_fNowYaw < 0.0f)	m_fNowYaw += 360.0f;
}

//----------------------------------------------
//	Name:	MovePitch
//	Func:	現在Yaw角度値を目標Yaw角度値に近づける
//	in:		D3DXVECTOR3* vecIn
//	Out:	なし
//----------------------------------------------
void CCamera::MovePitch()
{
	// カメラを回転させる際、右回りか左回りか
	// どちらが近いか判定
	// 目標角度と現在角度が同じなら処理をしない
	if(m_fNowPitch != m_fNextPitch)
	{
		float fTmp;
		fTmp = m_fNowPitch - m_fNextPitch;
		// 360を超えたら修正
		if(fTmp >= 360.0f)		fTmp -= 360.0f;
		else if(fTmp < 0.0f)	fTmp += 360.0f;

		// 左回り（マイナス）の方が近い時
		if(fTmp < 180.0f)
		{
			// 移動量の算出
			m_fFrameSpeed = fTmp / 10.0f;	
			// カメラ位置の移動
			m_fNowPitch -= m_fFrameSpeed;
		}
		// 右回り（プラス）の方が近い時
		else
		{
			// 移動量の算出
			fTmp = 360.0f - fTmp;
			m_fFrameSpeed = fTmp / 10.0f;
			// カメラ位置の移動
			m_fNowPitch += m_fFrameSpeed;
		}
	}

	// 360を超えたら修正
	if(m_fNowPitch >= 360.0f)	m_fNowPitch -= 360.0f;
	else if(m_fNowPitch < 0.0f)	m_fNowPitch += 360.0f;
}
