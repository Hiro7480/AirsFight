//==========================================================
// MotionData.cpp
// Auther : 桜井 博之
// Data   : 2002/03/26
//==========================================================

#include "MotionData.h"

//**********************************************
//	CMotionFrameクラス
//**********************************************

//----------------------------------------------
//	Name:	CMotionFrame
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	なし
//----------------------------------------------
CMotionFrame::CMotionFrame(LPDIRECT3DDEVICE8 pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;
	m_pNext = NULL;
	m_pPosKey = NULL;
	m_pRotKey = NULL;
	m_nPosKeyNum = 0;
	m_nRotKeyNum = 0;
	//strcpy(m_strName, "CMotionFrame");
	_tcscpy_s(m_strName, _countof(m_strName), _T("CMotionFrame"));
}

//----------------------------------------------
//	Name:	~CMotionData
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CMotionFrame::~CMotionFrame()
{
	Destroy();
}

//----------------------------------------------------------
//	Name:	CreateKey
//	Func:	ファイルからアニメーションキーの作成
//	in:		LPDIRECTXFILEDATA pFileData = ファイルデータ
//	Out:	なし
//----------------------------------------------------------
HRESULT CMotionFrame::CreateKey(LPDIRECTXFILEDATA pFileData)
{
	/* 読み込み用構造体の定義 */
	typedef struct
	{
		int				nTime;
		int				nFloats;	
		float			w;
		float			x;
		float			y;
		float			z;
	}tagRot;

	/* まず最初にファイルのデータからタイプを取得する */
	const GUID* pGUID;
	if( FAILED(pFileData->GetType(&pGUID)))
		return E_FAIL;

	/* データタイプがアニメーションではないなら終了 */
	if( *pGUID != TID_D3DRMAnimationKey )
		return E_FAIL;

	/* ファイルからデータを取得 */
	PBYTE	pData;
	DWORD	dwSize;
	pFileData->GetData(NULL, &dwSize, (PVOID*)&pData);

	/* データからキータイプ、キー数を取得 */
	int		nKeyType = ((int*)pData)[0];
	int		nKeyNum  = ((int*)pData)[1];

	/* キータイプが回転キーだった場合 */
	if(nKeyType == 0)
	{
		m_nRotKeyNum = nKeyNum;					// キー最大数の格納
		m_pRotKey = new tagRotateKey[nKeyNum];	// キーの数だけメモリに配列をとる

		/* データの読み込み位置をふたつずらす */
		tagRot* pCurrent = (tagRot*)(pData + (sizeof(DWORD) * 2));

		for (int i=0; i<nKeyNum; i++)
		{
			m_pRotKey[i].nTime = pCurrent->nTime;
			m_pRotKey[i].quatRot.x = -pCurrent->x;
			m_pRotKey[i].quatRot.y = -pCurrent->y;
			m_pRotKey[i].quatRot.z = -pCurrent->z;
			m_pRotKey[i].quatRot.w = pCurrent->w;
			pCurrent++;
		}
	}
	/* キータイプが拡大キーだった場合 */
	else if(nKeyType == 1)
	{
		// 現在対応していません
	}

	/* キータイプが位置キーだった場合 */
	else if(nKeyType == 2)
	{
		m_nPosKeyNum = nKeyNum;						// キー最大数の格納
		m_pPosKey = new tagPositionKey[nKeyNum];	// キーの数だけメモリに配列をとる

		/* データの読み込み位置をふたつずらす */
		tagPositionKey* pCurrent = (tagPositionKey*)(pData + (sizeof(DWORD) * 2));

		for (int i=0; i<nKeyNum; i++)
		{
			m_pPosKey[i].nTime = pCurrent->nTime;
			m_pPosKey[i].vecPos = pCurrent->vecPos;
			pCurrent++;
		}
	}

	return S_OK;
}

//----------------------------------------------------------
//	Name:	Destroy
//	Func:	全てのデータの削除
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
HRESULT CMotionFrame::Destroy()
{
	SAFE_DELETES(m_pRotKey);
	SAFE_DELETES(m_pPosKey);

	return S_OK;
}

//**********************************************
//	CMotionDataクラス
//**********************************************

//----------------------------------------------
//	Name:	CMotionData
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	なし
//----------------------------------------------
CMotionData::CMotionData(LPDIRECT3DDEVICE8 pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;
	//strcpy(m_strName, "CMeshFrame");
	_tcscpy_s(m_strName, _countof(m_strName), _T("CMeshFrame"));
	m_pListTop = NULL;
	m_nFrameNum = 0;
}

//----------------------------------------------
//	Name:	~CMotionData
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CMotionData::~CMotionData()
{
	Destroy();
}

//------------------------------------------------------
//	Name:	Create
//	Func:	ファイルからアニメーションリスト構造を作成
//	in:		TCHAR* strFilename = ファイルパス
//	Out:	なし
//------------------------------------------------------
HRESULT	CMotionData::Create(TCHAR* strFilename)
{
	LPDIRECTXFILE			pDXFile		= NULL;
	LPDIRECTXFILEENUMOBJECT pEnumObj	= NULL;
	LPDIRECTXFILEDATA		pFileData	= NULL;

	LPDIRECTXFILEDATA		pChildData	= NULL;
	LPDIRECTXFILEOBJECT		pChildObj	= NULL;

	/* ファイル名を取得する */
	TCHAR strFname[_MAX_FNAME];
	//_tsplitpath(strFilename, NULL, NULL, strFname, NULL);

	_tsplitpath_s(	strFilename, 
					NULL, 0,
					NULL, 0,
					strFname, _MAX_FNAME,
					NULL, 0);

	/* ファイル名の格納 */
	//strcpy(m_strName, strFname);
	_tcscpy_s(m_strName, _countof(m_strName), strFname);

	/* Ｘファイルオブジェクトの作成 */
	if(FAILED(DirectXFileCreate(&pDXFile)))	return E_FAIL;

	/* データのロード */
	if( FAILED(pDXFile->CreateEnumObject( strFilename, DXFILELOAD_FROMFILE, &pEnumObj)))
	{
		pDXFile->Release();
		return E_FAIL;
	}

	/* 読み込んだデータからリスト構造を作成していく */
	while( SUCCEEDED( pEnumObj->GetNextDataObject( &pFileData ) ) )
	{
		/* ファイルのデータタイプを取得する */
		const GUID*	pGUID;
		if(FAILED(pFileData->GetType(&pGUID)))
			return E_FAIL;

		/* データタイプがアニメーションセットだった場合のみ処理を行う */
		if(*pGUID == TID_D3DRMAnimationSet)
		{
			CMotionFrame*		pParentFrame = NULL;

			/* フレームごとのアニメーションを探していく */
			while(SUCCEEDED(pFileData->GetNextObject(&pChildObj)))
			{
				/* 子供のファイルデータの取得 */
				if( SUCCEEDED(pChildObj->QueryInterface(IID_IDirectXFileData,
														(VOID**)&pChildData)))
				{
					pParentFrame = CreateFrame(pChildData, pParentFrame);
					m_nFrameNum++;
					pChildData->Release();
					pChildObj->Release();
				}
				/* 失敗時 */
				else{
					pChildObj->Release();
				}
			}
			/* アニメーションファイルの作成成功とみなす */
			/* ひとつアニメーションセットを読み込んだらふたつ目はいらない */
			pFileData->Release();
			break;

		}
		/* データタイプがアニメーションセットではなかった場合 */
		else
		{
			pFileData->Release();
		}
	}

	/* pEnumObjをファイルの最後まで読ませる */
	while( SUCCEEDED( pEnumObj->GetNextDataObject( &pFileData )));

	/* 使用したメモリの開放 */
	SAFE_RELEASE( pFileData );
	SAFE_RELEASE( pEnumObj );
	SAFE_RELEASE( pDXFile );

	/* リストのはじめにデータが入っていれば読み込み成功、*/
	/* そうでないときは失敗とする */
	if(m_pListTop != NULL)
	{
		ComputMaxFrame();	// 最大フレーム数を計算しておく
		return S_OK;
	}
	else					return E_FAIL;
}

//----------------------------------------------------------
//	Name:	CreateFrame
//	Func:	ファイルからひとつのフレームを作成する
//			Createの中で呼ばれる
//	in:		LPDIRECTXFILEDATA pFileData = ファイルデータ
//			CMeshFrame*	pParentFrame	= 前のデータのポインタ
//	Out:	CMotionFrame* = 作成されたデータのポインタ
//----------------------------------------------------------
CMotionFrame* CMotionData::CreateFrame(LPDIRECTXFILEDATA pFileData, CMotionFrame* pParentFrame)
{
	/* 最初にファイルのデータからタイプを取得する */
	const GUID* pGUID;
	if( FAILED(pFileData->GetType(&pGUID)))
		return NULL;

	/* データタイプがアニメーションではないなら終了 */
	if( *pGUID != TID_D3DRMAnimation )
		return NULL;

	/* 新規モーションフレームの作成 */
	CMotionFrame*	pCurrentFrame = new CMotionFrame(m_pd3dDevice);

	/* 名前の取得 */
	TCHAR strName[512];
	DWORD dwNameLength;
	pFileData->GetName( NULL, &dwNameLength );
	if( dwNameLength > 0 )
		pFileData->GetName( strName, &dwNameLength );
	pCurrentFrame->SetName(strName);

	/* さらにファイルからアニメーションキーを探していく */
	LPDIRECTXFILEDATA		pChildData	= NULL;
	LPDIRECTXFILEOBJECT		pChildObj	= NULL;

	while(SUCCEEDED(pFileData->GetNextObject(&pChildObj)))
	{
		/* 子供のファイルデータの取得 */
		if( SUCCEEDED(pChildObj->QueryInterface(IID_IDirectXFileData,
												(VOID**)&pChildData)))
		{
			pCurrentFrame->CreateKey(pChildData);
			pChildData->Release();
			pChildObj->Release();
		}
		/* 失敗時 */
		else{
			pChildObj->Release();
		}
	}

	/* データをつなげる */
	if(pParentFrame)	pParentFrame->m_pNext = pCurrentFrame;
	else				m_pListTop = pCurrentFrame;

	return pCurrentFrame;
}

//----------------------------------------------
//	Name:	ComputMaxFrame
//	Func:	最大フレーム時間を求める
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMotionData::ComputMaxFrame()
{
	CMotionFrame*	pCurrentFrame = m_pListTop;
	int				nTmp, nMaxFrame=0;

	while(pCurrentFrame)
	{
		/* 回転キーの最大フレーム時間を求める */
		if(pCurrentFrame->m_pRotKey)
		{
			nTmp = pCurrentFrame->m_pRotKey[pCurrentFrame->m_nRotKeyNum-1].nTime;
			if(nMaxFrame<nTmp)	nMaxFrame = nTmp;
		}
		/* 位置キーの最大フレーム時間を求める */
		if(pCurrentFrame->m_pPosKey)
		{
			nTmp = pCurrentFrame->m_pPosKey[pCurrentFrame->m_nPosKeyNum-1].nTime;
			if(nMaxFrame<nTmp)	nMaxFrame = nTmp;
		}

		/* 次のデータへ */
		pCurrentFrame = pCurrentFrame->m_pNext;
	}

	/* 最大フレーム時間の格納 */
	m_nMaxFrame = nMaxFrame;

	return S_OK;
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	全てのオブジェクトの削除
//	in:		なし
//	Out:	なし
//----------------------------------------------
HRESULT CMotionData::Destroy()
{
	CMotionFrame* pCurrent = m_pListTop;
	CMotionFrame* pNext    = NULL;

	while(pCurrent != NULL)
	{
		pNext = pCurrent->GetNext();
		SAFE_DELETE(pCurrent);
		pCurrent = pNext;
	}

	return S_OK;
}