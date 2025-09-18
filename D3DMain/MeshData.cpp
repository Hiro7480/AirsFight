//==========================================================
// MeshData.cpp
// Auther : 桜井 博之
// Data   : 2002/03/21
//==========================================================

#include "MeshData.h"

//**********************************************
//	CMeshObjectクラス
//**********************************************

//----------------------------------------------
//	Name:	CMeshObject
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	なし
//----------------------------------------------
CMeshObject::CMeshObject(LPDIRECT3DDEVICE8 pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;

	//strcpy(m_strName, "CMeshObject");
	_tcscpy_s(m_strName, _T("CMeshObject"));
	m_pSysMemMesh		= NULL;
	m_pLocalMesh		= NULL;
	m_dwNumMaterials	= 0L;
	m_pMaterials		= NULL;
	m_pTextures			= NULL;
}

//----------------------------------------------
//	Name:	~CMeshObject
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CMeshObject::~CMeshObject()
{
	Destroy();
}

//----------------------------------------------
//	Name:	Create
//	Func:	ファイルからの作成
//	in:		TCHAR* strFilename = ファイルパス
//	Out:	HRESULT
//----------------------------------------------
HRESULT	CMeshObject::Create(TCHAR* strFilename)
{
	LPD3DXBUFFER pMtrlBuffer = NULL;	// マテリアルバッファ

	/* カレントディレクトリを保存 */
	TCHAR strCurrentDirectory[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, strCurrentDirectory);

	/* Xファイルのパス部分を取得する */
	TCHAR strDir[_MAX_DIR];
	//_tsplitpath(strFilename, NULL, strDir, NULL, NULL);

	_tsplitpath_s(
		strFilename, 
		NULL, 0,
		strDir, _MAX_DIR,
		NULL, 0,
		NULL, 0);



	/* メッシュのロード */
	if( FAILED(	D3DXLoadMeshFromX(	strFilename, D3DXMESH_SYSTEMMEM,	
									m_pd3dDevice, NULL, &pMtrlBuffer, 
									&m_dwNumMaterials, &m_pSysMemMesh ) ) )
		return E_FAIL;

	SetCurrentDirectory(strDir);		// カレントディレクトリを変更

	/* メッシュからマテリアルの取得 */
	if( pMtrlBuffer && m_dwNumMaterials > 0 )
	{
		/* マテリアルの先頭アドレスにセット */
		D3DXMATERIAL* d3dxMtrls = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();
		/* マテリアルの数分だけマテリアルとテクスチャをメモリに確保 */
		m_pMaterials = new D3DMATERIAL8[m_dwNumMaterials];
		m_pTextures  = new LPDIRECT3DTEXTURE8[m_dwNumMaterials];

		/* マテリアルをコピーして、テクスチャを作っていく */
		for( DWORD i=0; i<m_dwNumMaterials; i++ )
		{
			/* マテリアルをコピー */
			m_pMaterials[i] 		= d3dxMtrls[i].MatD3D;
			m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;
			m_pTextures[i]			= NULL;

			/* テクスチャの作成 */
			if( d3dxMtrls[i].pTextureFilename )
			{
				if( FAILED( D3DXCreateTextureFromFile( m_pd3dDevice, d3dxMtrls[i].pTextureFilename,	
													   &m_pTextures[i] ) ) )
					m_pTextures[i] = NULL;
			}
		}
	}
	SetCurrentDirectory(strCurrentDirectory);	// カレントディレクトリを元に戻す

	SAFE_RELEASE( pMtrlBuffer );

	/* バウンディングスフィアの長さの算出 */
	ComputLength();

	return S_OK;

}

//------------------------------------------------------
//	Name:	Create
//	Func:	階層構造時の作成
//	in:		LPDIRECTXFILEDATA pFileData = ファイルデータ
//	Out:	HRESULT
//------------------------------------------------------
HRESULT	CMeshObject::Create(LPDIRECTXFILEDATA pFileData)
{
	LPD3DXBUFFER pMtrlBuffer = NULL;

	/* ファイルデータからメッシュを作成する */
	if(FAILED(D3DXLoadMeshFromXof(	pFileData, D3DXMESH_SYSTEMMEM, m_pd3dDevice,
									NULL, &pMtrlBuffer, &m_dwNumMaterials,&m_pSysMemMesh)))
		return E_FAIL;

	/* 階層構造での作成の場合のみ、ファイルデータから名前を読み込む */
	DWORD dwNameLength;
	pFileData->GetName( NULL, &dwNameLength );
	if( dwNameLength > 0 )
		pFileData->GetName( m_strName, &dwNameLength );

	/* メッシュからマテリアルの取得 */
	if( pMtrlBuffer && m_dwNumMaterials > 0 )
	{
		/* マテリアルの先頭アドレスにセット */
		D3DXMATERIAL* d3dxMtrls = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();
		/* マテリアルの数分だけマテリアルとテクスチャをメモリに確保 */
		m_pMaterials = new D3DMATERIAL8[m_dwNumMaterials];
		m_pTextures  = new LPDIRECT3DTEXTURE8[m_dwNumMaterials];

		/* マテリアルをコピーして、テクスチャを作っていく */
		for( DWORD i=0; i<m_dwNumMaterials; i++ )
		{
			/* マテリアルをコピー */
			m_pMaterials[i] 		= d3dxMtrls[i].MatD3D;
			m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;
			m_pTextures[i]			= NULL;

			/* テクスチャの作成 */
			if( d3dxMtrls[i].pTextureFilename )
			{
				if( FAILED( D3DXCreateTextureFromFile( m_pd3dDevice, d3dxMtrls[i].pTextureFilename,	
													   &m_pTextures[i] ) ) )
					m_pTextures[i] = NULL;
			}
		}
	}
	SAFE_RELEASE( pMtrlBuffer );

	/* バウンディングスフィアの長さの算出 */
	ComputLength();

	return S_OK;
}
//----------------------------------------------
//	Name:	ComputLength
//	Func:	バウンディングスフィアの半径の算出
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::ComputLength()
{
	struct VERTEX{
		D3DXVECTOR3 v;
	};

	LPDIRECT3DVERTEXBUFFER8	pVB;	// 頂点バッファ
	VERTEX	*pVertices;				// 頂点バッファへのアクセス用
	DWORD	dwVertexNum;			// 頂点の数

	D3DXVECTOR3	vecTmp;
	float		fLength = 0;
	float		fMaxLength = 0;


	/* 頂点バッファの取得 */
	m_pSysMemMesh->GetVertexBuffer(&pVB);

	/* 頂点数の取得 */
	dwVertexNum = m_pSysMemMesh->GetNumVertices();

	/* 頂点バッファをロック */
	pVB->Lock(0,0,(BYTE**)&pVertices,0);

	/* 頂点の数だけ繰り返す */
	for(DWORD i=0; i<dwVertexNum; i++)
	{
		/* 頂点を取り出す */
		vecTmp = pVertices[i].v;

		/* 中心点からの距離を求める(中心点は0,0,0とする) */
		fLength = D3DXVec3Length(&vecTmp);

		/* 最大値と比較し、それより大きかったら最大値として登録 */
		if(fLength > fMaxLength)	fMaxLength = fLength;
	}

	/* 頂点バッファをアンロック */
	pVB->Unlock();

	/* 頂点バッファをリリース */
	SAFE_RELEASE(pVB);

	/* 見つかった最大値を格納 */
	m_fLength = fMaxLength;

	return S_OK;
}

//----------------------------------------------
//	Name:	SetFVF
//	Func:	頂点フォーマットのセット
//	in:		DWORD	dwFVF = 頂点フォーマット
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::SetFVF(DWORD dwFVF)
{
	LPD3DXMESH pTempSysMemMesh = NULL;
	LPD3DXMESH pTempLocalMesh  = NULL;

	/* システムメモリを変更させたメッシュを作成 */
	if( m_pSysMemMesh )
	{
		if( FAILED( m_pSysMemMesh->CloneMeshFVF( D3DXMESH_SYSTEMMEM, dwFVF,
												 m_pd3dDevice, &pTempSysMemMesh ) ) )
			return E_FAIL;
	}

	/* ローカルメッシュを変更させたメッシュを作成 */
	if( m_pLocalMesh )
	{
		if( FAILED( m_pLocalMesh->CloneMeshFVF( 0L, dwFVF, m_pd3dDevice,
												&pTempLocalMesh ) ) )
		{
			/* ここで失敗したらシステムメモリに作ったものを削除 */
			SAFE_RELEASE( pTempSysMemMesh );
			return E_FAIL;
		}
	}
	/* 元のメッシュを削除して、新しく作ったものを採用する */
	SAFE_RELEASE( m_pSysMemMesh );
	SAFE_RELEASE( m_pLocalMesh );

	if( pTempSysMemMesh ) m_pSysMemMesh = pTempSysMemMesh;
	if( pTempLocalMesh )  m_pLocalMesh	= pTempLocalMesh;

	/* メッシュに含まれる各頂点の法線を算出 */
	if( m_pSysMemMesh )	D3DXComputeNormals( m_pSysMemMesh);
	if( m_pLocalMesh )	D3DXComputeNormals( m_pLocalMesh);

	return S_OK;
}


//----------------------------------------------
//	Name:	RestoreDeviceObject
//	Func:	オブジェクトの修理
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::RestoreDeviceObjects()
{
	if( NULL == m_pSysMemMesh )
		return E_FAIL;

	/* ＶＲＡＭが破棄されちゃったんでシステムメモリに退避してある */
	/* メッシュデータをＶＲＡＭにコピーする */
	if( FAILED( m_pSysMemMesh->CloneMeshFVF( 0L, m_pSysMemMesh->GetFVF(),
											 m_pd3dDevice, &m_pLocalMesh ) ) )
		return E_FAIL;

	return S_OK;

}


//----------------------------------------------
//	Name:	InvalidateDeviceObject
//	Func:	ＶＲＡＭの破棄
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::InvalidateDeviceObjects()
{
	SAFE_RELEASE( m_pLocalMesh );

	return S_OK;
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	オブジェクトの破棄
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::Destroy()
{
	InvalidateDeviceObjects();
	for( UINT i=0; i<m_dwNumMaterials; i++ )
		SAFE_RELEASE( m_pTextures[i] );
	SAFE_DELETE_ARRAY( m_pTextures );
	SAFE_DELETE_ARRAY( m_pMaterials );

	SAFE_RELEASE( m_pSysMemMesh );

	m_dwNumMaterials = 0L;

	return S_OK;
}

//----------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		BOOL bNoAlpha = アルファ値がない部分を描くか？
//			BOOL bAlpha	  = アルファ値がある部分を書くか？
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::Render(BOOL bNoAlpha, BOOL bAlpha)
{
	if( NULL == m_pLocalMesh )
		return E_FAIL;

	/* まずアルファ値のかかってない部分を描画する */
	if( bNoAlpha )
	{
		for( DWORD i=0; i<m_dwNumMaterials; i++ )
		{
			/* アルファ値がかかっているなら描かずに次にいく */
			if( m_pMaterials[i].Diffuse.a < 1.0f )
				continue;
			/* マテリアルとテクスチャのセット */
			m_pd3dDevice->SetMaterial( &m_pMaterials[i] );
			m_pd3dDevice->SetTexture( 0, m_pTextures[i] );
			/* ポリゴンの描画 */
			m_pLocalMesh->DrawSubset( i );
		}
	}

	/* 次にアルファ値のかかっている部分を描画する */
	if( bAlpha )
	{
		for( DWORD i=0; i<m_dwNumMaterials; i++ )
		{
			/* アルファ値がかかっていないなら描かずに次にいく */
			if( m_pMaterials[i].Diffuse.a == 1.0f )
				continue;

			/* マテリアルとテクスチャのセット */
			m_pd3dDevice->SetMaterial( &m_pMaterials[i] );
			m_pd3dDevice->SetTexture( 0, m_pTextures[i] );
			/* ポリゴンの描画 */
			m_pLocalMesh->DrawSubset( i );
		}
	}

	return S_OK;
}

//**********************************************
//	CMeshFrameクラス
//**********************************************

//----------------------------------------------
//	Name:	CMeshFrame
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	なし
//----------------------------------------------
CMeshFrame::CMeshFrame(LPDIRECT3DDEVICE8 pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;
	//strcpy(m_strName, "CMeshFrame");
	_tcscpy_s(m_strName, _countof(m_strName), _T("CMeshFrame"));
	
	D3DXMatrixIdentity(&m_matBase);
	m_nNumber	= 0;
	m_pMesh		= NULL;
	m_pChild	= NULL;
	m_pNext		= NULL;
}

//----------------------------------------------
//	Name:	~CMeshFrame
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CMeshFrame::~CMeshFrame()
{
	Destroy();
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	オブジェクトの削除
//	in:		なし
//	Out:	なし
//----------------------------------------------
HRESULT CMeshFrame::Destroy()
{
	/* 自分のデータの開放 */
	if( m_pMesh )  m_pMesh->Destroy();

	/* 次のデータのものを呼ぶ */
	if( m_pChild ) m_pChild->Destroy();
	if( m_pNext )  m_pNext->Destroy();

	/* 使用したメモリの開放 */
	SAFE_DELETE( m_pMesh );
	SAFE_DELETE( m_pNext );
	SAFE_DELETE( m_pChild );

	return S_OK;
}

//----------------------------------------------
//	Name:	RestoreDeviceObject
//	Func:	オブジェクトの修理
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshFrame::RestoreDeviceObjects()
{
	/* 自分のデータの修理 */
	if( m_pMesh )  m_pMesh->RestoreDeviceObjects();

	/* 次のデータのものを呼ぶ */
	if( m_pChild ) m_pChild->RestoreDeviceObjects();
	if( m_pNext )  m_pNext->RestoreDeviceObjects();
	return S_OK;
}

//----------------------------------------------
//	Name:	InvalidateDeviceObject
//	Func:	ＶＲＡＭの破棄
//	in:		なし
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshFrame::InvalidateDeviceObjects()
{
	/* 自分のデータのＶＲＡＭ破棄 */
	if( m_pMesh )  m_pMesh->InvalidateDeviceObjects();

	/* 次のデータのものを呼ぶ */
	if( m_pChild ) m_pChild->InvalidateDeviceObjects();
	if( m_pNext )  m_pNext->InvalidateDeviceObjects();
	return S_OK;
}

//----------------------------------------------------------
//	Name:	Render
//	Func:	階層構造での描画処理
//	in:		BOOL bNoAlpha = アルファ値がない部分を描くか？
//			BOOL bAlpha	  = アルファ値がある部分を書くか？
//	Out:	HRESULT
//----------------------------------------------------------
HRESULT CMeshFrame::Render(BOOL bNoAlpha,BOOL bAlpha)
{
	D3DXMATRIX matSavedWorld, matWorld;

	/* 現在のマトリクスを退避 */
	m_pd3dDevice->GetTransform( D3DTS_WORLD, &matSavedWorld );

	/* マトリクスの掛け算を行いワールド変換する */
	D3DXMatrixMultiply( &matWorld, &m_matBase, &matSavedWorld );
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	/* 自分のメッシュの描画 */
	if( m_pMesh )	m_pMesh->Render(bNoAlpha, bAlpha);

	/* 子供のメッシュの描画 */
	if( m_pChild )	m_pChild->Render(bNoAlpha, bAlpha);

	/* ワールド変換を元に戻す */
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matSavedWorld );
	/* 次のメッシュの描画 */
	if( m_pNext )	m_pNext->Render(bNoAlpha, bAlpha);

	return S_OK;
}

//----------------------------------------------------------------------
//	Name:	Render
//	Func:	モーション補正値を含めた
//			階層構造での描画処理
//	in:		D3DXMATRIX	matMotion[] = 補正値マトリクス配列
//			BOOL bNoAlpha = アルファ値がない部分を描くか？
//			BOOL bAlpha	  = アルファ値がある部分を書くか？
//	Out:	HRESULT
//----------------------------------------------------------------------
HRESULT CMeshFrame::Render(D3DXMATRIX matMotion[], BOOL bNoAlpha,BOOL bAlpha)
{
	D3DXMATRIX matSavedWorld, matWorld;

	/* 現在のマトリクスを退避 */
	m_pd3dDevice->GetTransform( D3DTS_WORLD, &matSavedWorld );

	/* マトリクスの掛け算を行いワールド変換する */
	D3DXMatrixMultiply( &matWorld, &matMotion[m_nNumber], &matSavedWorld );
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	/* 自分のメッシュの描画 */
	if( m_pMesh )	m_pMesh->Render(bNoAlpha, bAlpha);

	/* 子供のメッシュの描画 */
	if( m_pChild )	m_pChild->Render(matMotion, bNoAlpha, bAlpha);

	/* ワールド変換を元に戻す */
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matSavedWorld );
	/* 次のメッシュの描画 */
	if( m_pNext )	m_pNext->Render(matMotion, bNoAlpha, bAlpha);

	return S_OK;
}

//**********************************************
//	CMeshDataクラス
//**********************************************

//----------------------------------------------
//	Name:	CMeshData
//	Func:	コンストラクタ
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	なし
//----------------------------------------------
CMeshData::CMeshData(LPDIRECT3DDEVICE8 pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;
	strcpy_s(m_strName, sizeof(m_strName), "CMeshFrame");
	m_pListTop = NULL;
	m_nFrameNum = 0;
}

//----------------------------------------------
//	Name:	~CMeshData
//	Func:	デストラクタ
//	in:		なし
//	Out:	なし
//----------------------------------------------
CMeshData::~CMeshData()
{
	Destroy();
}

//----------------------------------------------
//	Name:	Create
//	Func:	階層メッシュをファイルから作成
//	in:		TCHAR* strFilename
//	Out:	なし
//----------------------------------------------
HRESULT CMeshData::Create(TCHAR* strFilename)
{
	LPDIRECTXFILE			pDXFile   = NULL;
	LPDIRECTXFILEENUMOBJECT pEnumObj  = NULL;
	LPDIRECTXFILEDATA		pFileData = NULL;

	/* カレントディレクトリを保存 */
	TCHAR strCurrentDirectory[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, strCurrentDirectory);
	/* Xファイルのパス部分と、ファイル名を取得する */
	TCHAR strDir[_MAX_DIR];
	TCHAR strFname[_MAX_FNAME];
	//_tsplitpath(strFilename, NULL, strDir, strFname, NULL);

	_tsplitpath_s(strFilename, 
				NULL, 0, 
				strDir, _MAX_DIR,
				strFname, _MAX_FNAME,
				NULL, 0);

	/* ファイル名の格納 */
	//strcpy(m_strName, strFname);
	_tcscpy_s(m_strName, strFname);

	/* Ｘファイルオブジェクトの作成 */
	if(FAILED(DirectXFileCreate(&pDXFile)))	return E_FAIL;

	/* データのロード */
	if( FAILED(pDXFile->CreateEnumObject( strFilename, DXFILELOAD_FROMFILE, &pEnumObj)))
	{
		pDXFile->Release();
		return E_FAIL;
	}

	/* カレントディレクトリを変更 */
	SetCurrentDirectory(strDir);

	/* 読み込んだデータから階層構造を作成していく */
	while( SUCCEEDED( pEnumObj->GetNextDataObject( &pFileData ) ) )
	{
		CreateTree( pFileData, NULL );
		pFileData->Release();
	}

	/* カレントディレクトリを元に戻す */
	SetCurrentDirectory(strCurrentDirectory);

	/* 使用したメモリの開放 */
	SAFE_RELEASE( pFileData );
	SAFE_RELEASE( pEnumObj );
	SAFE_RELEASE( pDXFile );

	/* オブジェクトの修理？ */
	RestoreDeviceObjects();

	return S_OK;
}

//----------------------------------------------------------
//	Name:	CreateTree
//	Func:	階層メッシュを作るときに再帰的に使用
//	in:		LPDIRECTXFILEDATA pFileData = 子供のファイルデータ
//			CMeshFrame*	pParentFrame	= 親のフレーム
//	Out:	なし
//----------------------------------------------------------
HRESULT CMeshData::CreateTree(LPDIRECTXFILEDATA pFileData, CMeshFrame* pParentFrame)
{
	/* まず最初にファイルのデータからタイプを取得する */
	const GUID* pGUID;
	if( FAILED(pFileData->GetType(&pGUID)))
		return E_FAIL;

	/* データタイプがメッシュだったとき */
	if( *pGUID == TID_D3DRMMesh )
	{
		if( pParentFrame->m_pMesh )
			return E_FAIL;

		/* メッシュの作成 */
		pParentFrame->m_pMesh = new CMeshObject(m_pd3dDevice);
		pParentFrame->m_pMesh->Create(pFileData);

	}

	/* データタイプがマトリクスだったとき */
	else if( *pGUID == TID_D3DRMFrameTransformMatrix )
	{
		/* マトリクス値を取得 */
		D3DXMATRIX* pMat;
		DWORD		cbSize;
		if(FAILED(pFileData->GetData(NULL,&cbSize,(VOID**)&pMat)))
			return E_FAIL;

		/* フレームに格納 */
		pParentFrame->SetMatrix(*pMat);
	}

	/* データタイプがフレームだったとき */
	if( *pGUID == TID_D3DRMFrame )
	{
		/* 新規フレームの作成 */
		CMeshFrame*	pCurrentFrame = new CMeshFrame(m_pd3dDevice);
		pCurrentFrame->SetNumber(m_nFrameNum);
		m_nFrameNum++;

		/* 名前の取得 */
		TCHAR strName[512];
		DWORD dwNameLength;
		pFileData->GetName( NULL, &dwNameLength );
		if( dwNameLength > 0 )
			pFileData->GetName( strName, &dwNameLength );
		pCurrentFrame->SetName(strName);

		/* 親のデータがないときは最初のデータとみなし、ListTopに追加する */
		if(!pParentFrame)
			m_pListTop = pCurrentFrame;
		/* それ以外のときは親のデータとつなげ、階層構造を作成する */
		else{
			pCurrentFrame->m_pNext = pParentFrame->m_pChild;
			pParentFrame->m_pChild = pCurrentFrame;
		}

		//------------------------------------------------------
		// pParent･･･親	pCurrent･･･子供	とし、
		// ここでさらにpCurrentの子供(孫とする)を捜していく。
		// 孫が見つかった場合、孫のファイルデータを取得し、
		// pCurrentを親、孫のファイルデータを子供として
		// CreateTreeを再帰的に呼び出していく
		//------------------------------------------------------
		LPDIRECTXFILEDATA	pChildData = NULL;
		LPDIRECTXFILEOBJECT pChildObj = NULL;

		while( SUCCEEDED( pFileData->GetNextObject( &pChildObj ) ) )
		{
			/* 子供のファイルデータの取得 */
			if( SUCCEEDED(pChildObj->QueryInterface(IID_IDirectXFileData,
													(VOID**)&pChildData)))
			{
				/* 上記のとおり再帰的に呼び出していく */
				CreateTree( pChildData, pCurrentFrame );
				pChildData->Release();
				pChildObj->Release();
			} 
			/* 失敗時 */
			else{
				pChildObj->Release();
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

//----------------------------------------------------------
//	Name:	Destroy
//	Func:	全オブジェクトの削除
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
HRESULT CMeshData::Destroy()
{

	m_pListTop->Destroy();
	return S_OK;
}

//----------------------------------------------------------
//	Name:	RestoreDeviceObject
//	Func:	全オブジェクトの修理
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
HRESULT CMeshData::RestoreDeviceObjects()
{
	m_pListTop->RestoreDeviceObjects();
	return S_OK;
}

//----------------------------------------------------------
//	Name:	InvalidateDeviceObjects
//	Func:	全オブジェクトのＶＲＡＭ破棄
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
HRESULT CMeshData::InvalidateDeviceObjects()
{
	m_pListTop->InvalidateDeviceObjects();
	return S_OK;
}

//----------------------------------------------------------
//	Name:	Render
//	Func:	描画処理
//	in:		なし
//	Out:	なし
//----------------------------------------------------------
HRESULT CMeshData::Render()
{
	/* まずはアルファ値のかかってない部分から描画する */
	if( m_pListTop )	m_pListTop->Render( TRUE, FALSE );

	/* アルファブレンドを有効にする */
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	/* 次にアルファ値のかかっている部分を描画する */
	if( m_pListTop )	m_pListTop->Render( FALSE, TRUE );

	/* アルファブレンドを元に戻す */
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );

	return S_OK;
}

//----------------------------------------------------------------------
//	Name:	Render
//	Func:	モーション補正値を含めた描画処理
//	in:		D3DXMATRIX** ppMatMotion = 補正値マトリクス配列へのポインタのポインタ
//	Out:	HRESULT
//----------------------------------------------------------------------
HRESULT	CMeshData::Render(D3DXMATRIX matMotion[])
{
	/* まずはアルファ値のかかってない部分から描画する */
	if( m_pListTop )	m_pListTop->Render( matMotion, TRUE, FALSE );

	/* アルファブレンドを有効にする */
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	/* 次にアルファ値のかかっている部分を描画する */
	if( m_pListTop )	m_pListTop->Render( matMotion, FALSE, TRUE );

	/* アルファブレンドを元に戻す */
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );

	return S_OK;
}