//==========================================================
// Active.cpp
// Auther : 桜井 博之
// Data   : 2002/04/16
//==========================================================

#include "ActiveMotion.h"

//**********************************************
//	CActiveFrameクラス
//**********************************************

//----------------------------------------------
//	Name:	CActiveFrame
//	Func:	コンストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CActiveFrame::CActiveFrame()
{
	m_pMeshFrame = NULL;
	m_pMotionFrame = NULL;

	D3DXQuaternionIdentity(&m_qtMotion);
	m_vecMotion *= 0;
}

//----------------------------------------------
//	Name:	~CActiveFrame
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CActiveFrame::~CActiveFrame()
{
	Destroy();
}

//------------------------------------------------------------------
//	Name:	Create
//	Func:	初期化
//	in:		CMeshFrame* pMeshFrame		= 対応するメッシュフレーム
//			CMotionFrame* pMotionFrame	= 対応するモーションフレーム
//	Out:	HRESULT
//------------------------------------------------------------------
HRESULT CActiveFrame::Create(CMeshFrame* pMeshFrame, CMotionFrame* pMotionFrame)
{
	m_pMeshFrame = pMeshFrame;
	m_pMotionFrame = pMotionFrame;

	return S_OK;
}

//----------------------------------------------
//	Name:	ComputQuat
//	Func:	現在時間から回転補正値を求める
//	in:		int nActiveTime = 現在時間
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveFrame::ComputQuat(int nActiveTime)
{
	int i;

	/* 回転キーがなかったら失敗とみなす */
	if(m_pMotionFrame->m_nRotKeyNum == 0)
		return E_FAIL;

	/* 現在時間とまったく同じキーがあるかを判定 */
	i=0;
	while(i<m_pMotionFrame->m_nRotKeyNum)
	{
		if(m_pMotionFrame->m_pRotKey[i].nTime == nActiveTime)	break;
		i++;
	}

	/* まったく同じキーがあった場合は、そのままの値を格納して終了 */
	if(i < m_pMotionFrame->m_nRotKeyNum)
	{
		m_qtMotion = m_pMotionFrame->m_pRotKey[i].quatRot;
		return S_OK;
	}

	/* 同じキーがなかった場合は */
	/* 前後の一番近くにあるキー値から補完値を求める */

	// 前後のキーを検索する
	int	nNextTime = -1;		// 次のキー
	int	nBackTime = -1;		// 前のキー

	i=0;					// 回転キー配列への添え字としても使用

	while(i < m_pMotionFrame->m_nRotKeyNum)
	{
		if(m_pMotionFrame->m_pRotKey[i].nTime > nActiveTime)
		{
			nNextTime = m_pMotionFrame->m_pRotKey[i].nTime;
			break;
		}
		else
			nBackTime = m_pMotionFrame->m_pRotKey[i].nTime;
		i++;
	}

	/* 前後のキーどちらかしか見つからなかった場合は */
	/* 見つかったキーの情報をそのまま使用して終了 */
	if(nNextTime == -1)
	{
		m_qtMotion = m_pMotionFrame->m_pRotKey[i-1].quatRot;
		return S_OK;
	}
	else if(nBackTime == -1)
	{
		m_qtMotion = m_pMotionFrame->m_pRotKey[i].quatRot;
		return S_OK;
	}

	/* キーが二つとも見つかった場合はその補完値を取る */
	D3DXQUATERNION	qtTmp;
	float			fBlend;

	/* ブレンド係数を求める */
	fBlend = SuppleNum(nActiveTime, nNextTime, nBackTime);

	/* クオータニオンの補完値を求める */
	D3DXQuaternionSlerp(&qtTmp,
		&m_pMotionFrame->m_pRotKey[i-1].quatRot,
		&m_pMotionFrame->m_pRotKey[i].quatRot, fBlend);

	/* 求めた値を格納して終了 */
	m_qtMotion = qtTmp;
	return S_OK;
}

//----------------------------------------------
//	Name:	ComputVec
//	Func:	現在時間から位置補正値を求める
//	in:		int nActiveTime = 現在時間
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveFrame::ComputVec(int nActiveTime)
{
	int i;

	/* 位置キーがなかったら失敗とみなす */
	if(m_pMotionFrame->m_nPosKeyNum == 0)
		return E_FAIL;

	/* 現在時間とまったく同じキーがあるかを判定 */
	i=0;
	while(i<m_pMotionFrame->m_nPosKeyNum)
	{
		if(m_pMotionFrame->m_pPosKey[i].nTime == nActiveTime)	break;
		i++;
	}

	/* まったく同じキーがあった場合は、そのままの値を格納して終了 */
	if(i < m_pMotionFrame->m_nPosKeyNum)
	{
		m_vecMotion = m_pMotionFrame->m_pPosKey[i].vecPos;
		return S_OK;
	}

	/* 同じキーがなかった場合は */
	/* 前後の一番近くにあるキー値から補完値を求める */

	// 前後のキーを検索する
	int	nNextTime = -1;	// 次のキー
	int	nBackTime = -1;	// 前のキー

	i=0;				// 位置キー配列の添え字としても使用

	while(i < m_pMotionFrame->m_nPosKeyNum)
	{
		if(m_pMotionFrame->m_pPosKey[i].nTime > nActiveTime)
		{
			nNextTime = m_pMotionFrame->m_pPosKey[i].nTime;
			break;
		}
		else
			nBackTime = m_pMotionFrame->m_pPosKey[i].nTime;
		i++;
	}

	/* 前後のキーどちらかしか見つからなかった場合は */
	/* 見つかったキーの情報をそのまま使用して終了 */
	if(nNextTime == -1)
	{
		m_vecMotion = m_pMotionFrame->m_pPosKey[i-1].vecPos;
		return S_OK;
	}
	else if(nBackTime == -1)
	{
		m_vecMotion = m_pMotionFrame->m_pPosKey[i].vecPos;
		return S_OK;
	}

	/* キーが二つとも見つかった場合はその補完値を取る */
	D3DXVECTOR3		vecTmp;
	float			fBlend;

	/* ブレンド係数を求める */
	fBlend = SuppleNum(nActiveTime, nNextTime, nBackTime);

	/* ベクトルの補完値を求める */
	vecTmp=	m_pMotionFrame->m_pPosKey[i].vecPos - 
			m_pMotionFrame->m_pPosKey[i-1].vecPos;
	vecTmp *= fBlend;
	vecTmp += m_pMotionFrame->m_pPosKey[i-1].vecPos;

	/* 求めた値を格納して終了 */
	m_vecMotion = vecTmp;
	return S_OK;
}

//--------------------------------------------------------------
//	Name:	SupplementNum
//	Func:	二つの数値の大きいほうを1.0、小さいほうを0.0とした場合、
//			もうひとつの数値はいくつか、を求める
//	In:		int		nMiddle	= 中間の数値
//			int		nMax	= 最大値
//			int		nMin	= 最小値
//	Out:	float
//--------------------------------------------------------------
float CActiveFrame::SuppleNum(int nMiddle, int nMax, int nMin)
{
	float	fTmp1,fTmp2;

	fTmp1 = float(nMax-nMin);
	fTmp2 = float(nMiddle-nMin);

	return fTmp2/fTmp1;
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	全オブジェクトの削除
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveFrame::Destroy()
{
	return S_OK;
}

//**********************************************
//	CActiveDataクラス
//**********************************************

//----------------------------------------------
//	Name:	CActiveData
//	Func:	コンストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CActiveData::CActiveData()
{
	for(int i=0; i<32; i++)
		m_pActiveFrame[i] = NULL;
	m_pMeshData = NULL;
	m_pMotionData = NULL;

	m_nActiveFrameNum = 0;
	m_nMaxTime = 0;
	m_nActiveTime = 0;
}

//----------------------------------------------
//	Name:	~CActiveData
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CActiveData::~CActiveData()
{
	Destroy();
}

//----------------------------------------------------------
//	Name:	CreateFrame
//	Func:	フレームデータの作成
//	in:		CMeshData* pMeshData =		対応メッシュデータ
//			CMotionData* pMotionData =	対応モーションデータ
//	Out:	HRESULT
//----------------------------------------------------------
HRESULT	CActiveData::CreateFrame(CMeshData* pMeshData, CMotionData* pMotionData)
{
	int i;

	/* それぞれのメッシュデータ、モーションデータのフレーム数が同じか確認 */
	if(pMeshData->GetFrameNum() != pMotionData->GetFrameNum())
		return E_FAIL;

	/* メッシュデータ、モーションデータの格納 */
	m_pMeshData = pMeshData;
	m_pMotionData = pMotionData;
	m_nActiveFrameNum = pMeshData->GetFrameNum();

	/* アニメーション最大フレーム時間の取得 */
	m_nMaxTime = pMotionData->GetMaxFrame();

	/* フレーム配列を必要分メモリに確保 */
	for(i=0; i<m_nActiveFrameNum; i++)
		m_pActiveFrame[i] = new CActiveFrame;

	/* 対応するメッシュデータとモーションフレームをそれぞれ入れる */
	CMeshFrame*			pMeshFrame;
	CMotionFrame*		pMotionFrame = m_pMotionData->GetListTop();

	for(i=0; i<m_nActiveFrameNum; i++)
	{
		/* 順番にフレームをメッシュデータの中から見つけ、格納する */
		pMeshFrame = m_pMeshData->GetFrame(i);
		m_pActiveFrame[i]->Create(pMeshFrame, pMotionFrame);

		/* 次のデータへ */
		pMotionFrame = pMotionFrame->GetNext();
	}
	return S_OK;
}

//----------------------------------------------
//	Name:	ComputMotion
//	Func:	現在時間からモーション補正値を算出
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveData::ComputMotion()
{
	/* 全てのActiveFrameにかける */
	for(int i=0; i<m_nActiveFrameNum; i++)
	{
		m_pActiveFrame[i]->ComputQuat(m_nActiveTime);	// 回転補正値の算出
		m_pActiveFrame[i]->ComputVec(m_nActiveTime);	// 位置補正値の算出
	}
	return S_OK;
}

//----------------------------------------------
//	Name:	Run
//	Func:	アニメーションの再生
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveData::Run()
{
	m_nActiveTime++;
	if(m_nActiveTime > m_nMaxTime)
		m_nActiveTime = 0;

	return S_OK;
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	全オブジェクトの削除
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveData::Destroy()
{
	for(int i=0; i<32; i++)
		SAFE_DELETE(m_pActiveFrame[i])
	return S_OK;
}

//**********************************************
//	CActiveMotionクラス
//**********************************************

//----------------------------------------------
//	Name:	CActiveMotion
//	Func:	コンストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CActiveMotion::CActiveMotion()
{
	for(int i=0; i<32; i++)
	{
		m_pActiveData[i] = NULL;
		m_fBlendNum[i] = 0;
		D3DXMatrixIdentity(&m_matMotion[i]);
		D3DXMatrixIdentity(&m_matStock[i]);
	}
	m_fBlendNum[0] = 1.0f;
	m_nActiveDataNum = 0;
	m_nMeshFrameNum = 0;
	m_pMeshData = 0;
}

//----------------------------------------------
//	Name:	~CActiveMotion
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CActiveMotion::~CActiveMotion()
{
	Destroy();
}

//----------------------------------------------
//	Name:	LoadMesh
//	Func:	メッシュデータの読み込み
//	in:		CMeshData* pMeshData
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::LoadMesh(CMeshData* pMeshData)
{
	m_pMeshData = pMeshData;

	/* フレーム数をメッシュから取得 */
	m_nMeshFrameNum = pMeshData->GetFrameNum();

	return S_OK;
}

//----------------------------------------------
//	Name:	LoadMotion
//	Func:	モーションデータの読み込み
//	in:		CMotionData* pMotionData
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::LoadMotion(CMotionData* pMotionData)
{
	/* ポインタ配列に作成、初期化 */
	m_pActiveData[m_nActiveDataNum] = new CActiveData;
	m_pActiveData[m_nActiveDataNum]->CreateFrame(m_pMeshData, pMotionData);

	/* データ数を増やす */
	m_nActiveDataNum++;

	return S_OK;
}

//----------------------------------------------
//	Name:	ComputMatrix
//	Func:	それぞれのモーションとブレンド係数から
//			現在のモーションマトリクスを求める
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::ComputMatrix()
{
	D3DXQUATERNION	qtTmp;		// 計算用クオータニオン
	D3DXVECTOR3		vecTmp;		// 計算用ベクトル

	for(int i=0; i<m_nMeshFrameNum; i++)
	{
		qtTmp *= 0.0f;			// 計算用クオータニオンの初期化
		vecTmp *= 0.0f;			// 計算用ベクトルの初期化

		for(int j=0; j<m_nActiveDataNum; j++)
		{
			/* 回転補正値の計算 */
			qtTmp += m_pActiveData[j]->m_pActiveFrame[i]->GetQuat()*m_fBlendNum[j];
			/* 位置補正値の計算 */
			vecTmp += m_pActiveData[j]->m_pActiveFrame[i]->GetVec()*m_fBlendNum[j];
		}

		/* 計算結果をマトリクスに変換する */
		D3DXMatrixRotationQuaternion(&m_matMotion[i], &qtTmp);
		m_matMotion[i]._41 += vecTmp.x;
		m_matMotion[i]._42 += vecTmp.y;
		m_matMotion[i]._43 += vecTmp.z;
	}

	return S_OK;
}

//----------------------------------------------
//	Name:	ComputAllMotion
//	Func:	全てのモーションフレームの
//			モーションデータの計算
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::ComputAllMotion()
{
	/* 全てのモーションデータからComputMotionを呼び出す */
	for(int i=0; i<m_nActiveDataNum; i++)
		m_pActiveData[i]->ComputMotion();

	return S_OK;
}

//--------------------------------------------------
//	Name:	ChangeMotion
//	Func:	現在のモーションを指定したモーションに変更
//			ブレンド係数の操作
//	in:		int		nNum		= 指定モーション
//			float	fChangeSpeed= モーション変更速度
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CActiveMotion::ChangeMotion(int nNum, float fChangeSpeed)
{
	int i;

	/* 指定モーションがない場合は失敗とみなす */
	if(nNum >= m_nActiveDataNum)
		return E_FAIL;

	/* プラス部分のみ、退避しておく */
	float fTmp=m_fBlendNum[nNum] + fChangeSpeed;
	if(fTmp > 1.0f)	fTmp = 1.0f;

	/* 全てのブレンド係数をマイナスする（速いだろうから）*/
	for(i=0; i<m_nActiveDataNum; i++)
		if((m_fBlendNum[i]-=fChangeSpeed) < 0.0f)
			m_fBlendNum[i]=0.0f;

	/* 退避した部分を戻す */
	m_fBlendNum[nNum] = fTmp;

	/* ブレンド係数の整頓（ブレンド係数の合計が1.0になるように調整）*/
	float fTotal = 0;
	for(i=0; i<m_nActiveDataNum; i++)	fTotal += m_fBlendNum[i];

	/* 合計が1.0f以上の場合 */
	if(fTotal > 1.0f)
		for(i=0; i<m_nActiveDataNum; i++)
			m_fBlendNum[i] = m_fBlendNum[i] / fTotal;

	/* 合計が1.0f以下の場合 */
	else
		m_fBlendNum[0] += (1.0f - fTotal);


	return S_OK;
}

//--------------------------------------------------
//	Name:	ChangeMotion
//	Func:	現在のモーションを指定したモーションに変更
//			二つの指定の間を取る
//			ブレンド係数の操作
//	in:		int		nNum1		= 指定モーション１
//			int		nNum2		= 指定モーション２
//			float	fChangeSpeed= モーション変更速度
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CActiveMotion::ChangeMotion(int nNum1, int nNum2, float fChangeSpeed)
{
	int i;

	/* 指定モーションがない場合は失敗とみなす */
	if(nNum1 >= m_nActiveDataNum || nNum2 >= m_nActiveDataNum)
		return E_FAIL;

	/* プラス部分のみ、退避しておく */
	float fTmp1 = m_fBlendNum[nNum1]+=fChangeSpeed;	if(fTmp1>1.0f) fTmp1=1.0f;
	float fTmp2 = m_fBlendNum[nNum2]+=fChangeSpeed;	if(fTmp2>1.0f) fTmp2=1.0f;

	/* 全てのブレンド係数をマイナスする（速いだろうから）*/
	for(i=0; i<m_nActiveDataNum; i++)
		if((m_fBlendNum[i]-=fChangeSpeed) < 0.0f)
			m_fBlendNum[i]=0.0f;

	/* 退避した部分を戻す */
	m_fBlendNum[nNum1] = fTmp1;
	m_fBlendNum[nNum2] = fTmp2;

	/* ブレンド係数の整頓（ブレンド係数の合計が1.0になるように調整）*/
	float fTotal = 0;
	for(i=0; i<m_nActiveDataNum; i++)	fTotal += m_fBlendNum[i];

	/* 合計が1.0f以上の場合 */
	if(fTotal > 1.0f)
		for(i=0; i<m_nActiveDataNum; i++)
			m_fBlendNum[i] = m_fBlendNum[i] / fTotal;

	/* 合計が1.0f以下の場合 */
	else
		m_fBlendNum[0] += (1.0f - fTotal);

	return S_OK;
}

//------------------------------------------------------
//	Name:	Play
//	Func:	さまざまなデータ更新
//	in:		なし
//	Out:	HRESULT
//------------------------------------------------------
HRESULT CActiveMotion::Play()
{
	/* 全てのモーションの再生 */
	for(int i=0; i<m_nActiveDataNum; i++)
		m_pActiveData[i]->Run();

	/* 全てのモーションフレームの現在クオータニオンを求める */
	ComputAllMotion();

	/* ブレンド係数により複数のモーションの補完値を求める */
	ComputMatrix();

	return S_OK;
}

//------------------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	HRESULT
//------------------------------------------------------
HRESULT CActiveMotion::Render()
{
	m_pMeshData->Render(m_matStock);
	return S_OK;
}

//--------------------------------------------------
//	Name:	UpDate
//	Func:	描画用マトリクス更新
//	in:		なし
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CActiveMotion::UpDate()
{
	for(int i=0; i<m_nMeshFrameNum; i++)
		m_matStock[i] = m_matMotion[i];

	return S_OK;
}


//----------------------------------------------
//	Name:	Destroy
//	Func:	全オブジェクトの削除
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::Destroy()
{
	for(int i=0; i<32; i++)
		SAFE_DELETE(m_pActiveData[i]);
	return S_OK;
}
