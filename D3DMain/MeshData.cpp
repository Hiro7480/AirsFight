//==========================================================
// MeshData.cpp
// Auther : ���� ���V
// Data   : 2002/03/21
//==========================================================

#include "MeshData.h"

//**********************************************
//	CMeshObject�N���X
//**********************************************

//----------------------------------------------
//	Name:	CMeshObject
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	�Ȃ�
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
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CMeshObject::~CMeshObject()
{
	Destroy();
}

//----------------------------------------------
//	Name:	Create
//	Func:	�t�@�C������̍쐬
//	in:		TCHAR* strFilename = �t�@�C���p�X
//	Out:	HRESULT
//----------------------------------------------
HRESULT	CMeshObject::Create(TCHAR* strFilename)
{
	LPD3DXBUFFER pMtrlBuffer = NULL;	// �}�e���A���o�b�t�@

	/* �J�����g�f�B���N�g����ۑ� */
	TCHAR strCurrentDirectory[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, strCurrentDirectory);

	/* X�t�@�C���̃p�X�������擾���� */
	TCHAR strDir[_MAX_DIR];
	//_tsplitpath(strFilename, NULL, strDir, NULL, NULL);

	_tsplitpath_s(
		strFilename, 
		NULL, 0,
		strDir, _MAX_DIR,
		NULL, 0,
		NULL, 0);



	/* ���b�V���̃��[�h */
	if( FAILED(	D3DXLoadMeshFromX(	strFilename, D3DXMESH_SYSTEMMEM,	
									m_pd3dDevice, NULL, &pMtrlBuffer, 
									&m_dwNumMaterials, &m_pSysMemMesh ) ) )
		return E_FAIL;

	SetCurrentDirectory(strDir);		// �J�����g�f�B���N�g����ύX

	/* ���b�V������}�e���A���̎擾 */
	if( pMtrlBuffer && m_dwNumMaterials > 0 )
	{
		/* �}�e���A���̐擪�A�h���X�ɃZ�b�g */
		D3DXMATERIAL* d3dxMtrls = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();
		/* �}�e���A���̐��������}�e���A���ƃe�N�X�`�����������Ɋm�� */
		m_pMaterials = new D3DMATERIAL8[m_dwNumMaterials];
		m_pTextures  = new LPDIRECT3DTEXTURE8[m_dwNumMaterials];

		/* �}�e���A�����R�s�[���āA�e�N�X�`��������Ă��� */
		for( DWORD i=0; i<m_dwNumMaterials; i++ )
		{
			/* �}�e���A�����R�s�[ */
			m_pMaterials[i] 		= d3dxMtrls[i].MatD3D;
			m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;
			m_pTextures[i]			= NULL;

			/* �e�N�X�`���̍쐬 */
			if( d3dxMtrls[i].pTextureFilename )
			{
				if( FAILED( D3DXCreateTextureFromFile( m_pd3dDevice, d3dxMtrls[i].pTextureFilename,	
													   &m_pTextures[i] ) ) )
					m_pTextures[i] = NULL;
			}
		}
	}
	SetCurrentDirectory(strCurrentDirectory);	// �J�����g�f�B���N�g�������ɖ߂�

	SAFE_RELEASE( pMtrlBuffer );

	/* �o�E���f�B���O�X�t�B�A�̒����̎Z�o */
	ComputLength();

	return S_OK;

}

//------------------------------------------------------
//	Name:	Create
//	Func:	�K�w�\�����̍쐬
//	in:		LPDIRECTXFILEDATA pFileData = �t�@�C���f�[�^
//	Out:	HRESULT
//------------------------------------------------------
HRESULT	CMeshObject::Create(LPDIRECTXFILEDATA pFileData)
{
	LPD3DXBUFFER pMtrlBuffer = NULL;

	/* �t�@�C���f�[�^���烁�b�V�����쐬���� */
	if(FAILED(D3DXLoadMeshFromXof(	pFileData, D3DXMESH_SYSTEMMEM, m_pd3dDevice,
									NULL, &pMtrlBuffer, &m_dwNumMaterials,&m_pSysMemMesh)))
		return E_FAIL;

	/* �K�w�\���ł̍쐬�̏ꍇ�̂݁A�t�@�C���f�[�^���疼�O��ǂݍ��� */
	DWORD dwNameLength;
	pFileData->GetName( NULL, &dwNameLength );
	if( dwNameLength > 0 )
		pFileData->GetName( m_strName, &dwNameLength );

	/* ���b�V������}�e���A���̎擾 */
	if( pMtrlBuffer && m_dwNumMaterials > 0 )
	{
		/* �}�e���A���̐擪�A�h���X�ɃZ�b�g */
		D3DXMATERIAL* d3dxMtrls = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();
		/* �}�e���A���̐��������}�e���A���ƃe�N�X�`�����������Ɋm�� */
		m_pMaterials = new D3DMATERIAL8[m_dwNumMaterials];
		m_pTextures  = new LPDIRECT3DTEXTURE8[m_dwNumMaterials];

		/* �}�e���A�����R�s�[���āA�e�N�X�`��������Ă��� */
		for( DWORD i=0; i<m_dwNumMaterials; i++ )
		{
			/* �}�e���A�����R�s�[ */
			m_pMaterials[i] 		= d3dxMtrls[i].MatD3D;
			m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;
			m_pTextures[i]			= NULL;

			/* �e�N�X�`���̍쐬 */
			if( d3dxMtrls[i].pTextureFilename )
			{
				if( FAILED( D3DXCreateTextureFromFile( m_pd3dDevice, d3dxMtrls[i].pTextureFilename,	
													   &m_pTextures[i] ) ) )
					m_pTextures[i] = NULL;
			}
		}
	}
	SAFE_RELEASE( pMtrlBuffer );

	/* �o�E���f�B���O�X�t�B�A�̒����̎Z�o */
	ComputLength();

	return S_OK;
}
//----------------------------------------------
//	Name:	ComputLength
//	Func:	�o�E���f�B���O�X�t�B�A�̔��a�̎Z�o
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::ComputLength()
{
	struct VERTEX{
		D3DXVECTOR3 v;
	};

	LPDIRECT3DVERTEXBUFFER8	pVB;	// ���_�o�b�t�@
	VERTEX	*pVertices;				// ���_�o�b�t�@�ւ̃A�N�Z�X�p
	DWORD	dwVertexNum;			// ���_�̐�

	D3DXVECTOR3	vecTmp;
	float		fLength = 0;
	float		fMaxLength = 0;


	/* ���_�o�b�t�@�̎擾 */
	m_pSysMemMesh->GetVertexBuffer(&pVB);

	/* ���_���̎擾 */
	dwVertexNum = m_pSysMemMesh->GetNumVertices();

	/* ���_�o�b�t�@�����b�N */
	pVB->Lock(0,0,(BYTE**)&pVertices,0);

	/* ���_�̐������J��Ԃ� */
	for(DWORD i=0; i<dwVertexNum; i++)
	{
		/* ���_�����o�� */
		vecTmp = pVertices[i].v;

		/* ���S�_����̋��������߂�(���S�_��0,0,0�Ƃ���) */
		fLength = D3DXVec3Length(&vecTmp);

		/* �ő�l�Ɣ�r���A������傫��������ő�l�Ƃ��ēo�^ */
		if(fLength > fMaxLength)	fMaxLength = fLength;
	}

	/* ���_�o�b�t�@���A�����b�N */
	pVB->Unlock();

	/* ���_�o�b�t�@�������[�X */
	SAFE_RELEASE(pVB);

	/* ���������ő�l���i�[ */
	m_fLength = fMaxLength;

	return S_OK;
}

//----------------------------------------------
//	Name:	SetFVF
//	Func:	���_�t�H�[�}�b�g�̃Z�b�g
//	in:		DWORD	dwFVF = ���_�t�H�[�}�b�g
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::SetFVF(DWORD dwFVF)
{
	LPD3DXMESH pTempSysMemMesh = NULL;
	LPD3DXMESH pTempLocalMesh  = NULL;

	/* �V�X�e����������ύX���������b�V�����쐬 */
	if( m_pSysMemMesh )
	{
		if( FAILED( m_pSysMemMesh->CloneMeshFVF( D3DXMESH_SYSTEMMEM, dwFVF,
												 m_pd3dDevice, &pTempSysMemMesh ) ) )
			return E_FAIL;
	}

	/* ���[�J�����b�V����ύX���������b�V�����쐬 */
	if( m_pLocalMesh )
	{
		if( FAILED( m_pLocalMesh->CloneMeshFVF( 0L, dwFVF, m_pd3dDevice,
												&pTempLocalMesh ) ) )
		{
			/* �����Ŏ��s������V�X�e���������ɍ�������̂��폜 */
			SAFE_RELEASE( pTempSysMemMesh );
			return E_FAIL;
		}
	}
	/* ���̃��b�V�����폜���āA�V������������̂��̗p���� */
	SAFE_RELEASE( m_pSysMemMesh );
	SAFE_RELEASE( m_pLocalMesh );

	if( pTempSysMemMesh ) m_pSysMemMesh = pTempSysMemMesh;
	if( pTempLocalMesh )  m_pLocalMesh	= pTempLocalMesh;

	/* ���b�V���Ɋ܂܂��e���_�̖@�����Z�o */
	if( m_pSysMemMesh )	D3DXComputeNormals( m_pSysMemMesh);
	if( m_pLocalMesh )	D3DXComputeNormals( m_pLocalMesh);

	return S_OK;
}


//----------------------------------------------
//	Name:	RestoreDeviceObject
//	Func:	�I�u�W�F�N�g�̏C��
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::RestoreDeviceObjects()
{
	if( NULL == m_pSysMemMesh )
		return E_FAIL;

	/* �u�q�`�l���j�����ꂿ�������ŃV�X�e���������ɑޔ����Ă��� */
	/* ���b�V���f�[�^���u�q�`�l�ɃR�s�[���� */
	if( FAILED( m_pSysMemMesh->CloneMeshFVF( 0L, m_pSysMemMesh->GetFVF(),
											 m_pd3dDevice, &m_pLocalMesh ) ) )
		return E_FAIL;

	return S_OK;

}


//----------------------------------------------
//	Name:	InvalidateDeviceObject
//	Func:	�u�q�`�l�̔j��
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::InvalidateDeviceObjects()
{
	SAFE_RELEASE( m_pLocalMesh );

	return S_OK;
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	�I�u�W�F�N�g�̔j��
//	in:		�Ȃ�
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
//	Func:	�`�揈��
//	in:		BOOL bNoAlpha = �A���t�@�l���Ȃ�������`�����H
//			BOOL bAlpha	  = �A���t�@�l�����镔�����������H
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshObject::Render(BOOL bNoAlpha, BOOL bAlpha)
{
	if( NULL == m_pLocalMesh )
		return E_FAIL;

	/* �܂��A���t�@�l�̂������ĂȂ�������`�悷�� */
	if( bNoAlpha )
	{
		for( DWORD i=0; i<m_dwNumMaterials; i++ )
		{
			/* �A���t�@�l���������Ă���Ȃ�`�����Ɏ��ɂ��� */
			if( m_pMaterials[i].Diffuse.a < 1.0f )
				continue;
			/* �}�e���A���ƃe�N�X�`���̃Z�b�g */
			m_pd3dDevice->SetMaterial( &m_pMaterials[i] );
			m_pd3dDevice->SetTexture( 0, m_pTextures[i] );
			/* �|���S���̕`�� */
			m_pLocalMesh->DrawSubset( i );
		}
	}

	/* ���ɃA���t�@�l�̂������Ă��镔����`�悷�� */
	if( bAlpha )
	{
		for( DWORD i=0; i<m_dwNumMaterials; i++ )
		{
			/* �A���t�@�l���������Ă��Ȃ��Ȃ�`�����Ɏ��ɂ��� */
			if( m_pMaterials[i].Diffuse.a == 1.0f )
				continue;

			/* �}�e���A���ƃe�N�X�`���̃Z�b�g */
			m_pd3dDevice->SetMaterial( &m_pMaterials[i] );
			m_pd3dDevice->SetTexture( 0, m_pTextures[i] );
			/* �|���S���̕`�� */
			m_pLocalMesh->DrawSubset( i );
		}
	}

	return S_OK;
}

//**********************************************
//	CMeshFrame�N���X
//**********************************************

//----------------------------------------------
//	Name:	CMeshFrame
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	�Ȃ�
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
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CMeshFrame::~CMeshFrame()
{
	Destroy();
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	�I�u�W�F�N�g�̍폜
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
HRESULT CMeshFrame::Destroy()
{
	/* �����̃f�[�^�̊J�� */
	if( m_pMesh )  m_pMesh->Destroy();

	/* ���̃f�[�^�̂��̂��Ă� */
	if( m_pChild ) m_pChild->Destroy();
	if( m_pNext )  m_pNext->Destroy();

	/* �g�p�����������̊J�� */
	SAFE_DELETE( m_pMesh );
	SAFE_DELETE( m_pNext );
	SAFE_DELETE( m_pChild );

	return S_OK;
}

//----------------------------------------------
//	Name:	RestoreDeviceObject
//	Func:	�I�u�W�F�N�g�̏C��
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshFrame::RestoreDeviceObjects()
{
	/* �����̃f�[�^�̏C�� */
	if( m_pMesh )  m_pMesh->RestoreDeviceObjects();

	/* ���̃f�[�^�̂��̂��Ă� */
	if( m_pChild ) m_pChild->RestoreDeviceObjects();
	if( m_pNext )  m_pNext->RestoreDeviceObjects();
	return S_OK;
}

//----------------------------------------------
//	Name:	InvalidateDeviceObject
//	Func:	�u�q�`�l�̔j��
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMeshFrame::InvalidateDeviceObjects()
{
	/* �����̃f�[�^�̂u�q�`�l�j�� */
	if( m_pMesh )  m_pMesh->InvalidateDeviceObjects();

	/* ���̃f�[�^�̂��̂��Ă� */
	if( m_pChild ) m_pChild->InvalidateDeviceObjects();
	if( m_pNext )  m_pNext->InvalidateDeviceObjects();
	return S_OK;
}

//----------------------------------------------------------
//	Name:	Render
//	Func:	�K�w�\���ł̕`�揈��
//	in:		BOOL bNoAlpha = �A���t�@�l���Ȃ�������`�����H
//			BOOL bAlpha	  = �A���t�@�l�����镔�����������H
//	Out:	HRESULT
//----------------------------------------------------------
HRESULT CMeshFrame::Render(BOOL bNoAlpha,BOOL bAlpha)
{
	D3DXMATRIX matSavedWorld, matWorld;

	/* ���݂̃}�g���N�X��ޔ� */
	m_pd3dDevice->GetTransform( D3DTS_WORLD, &matSavedWorld );

	/* �}�g���N�X�̊|���Z���s�����[���h�ϊ����� */
	D3DXMatrixMultiply( &matWorld, &m_matBase, &matSavedWorld );
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	/* �����̃��b�V���̕`�� */
	if( m_pMesh )	m_pMesh->Render(bNoAlpha, bAlpha);

	/* �q���̃��b�V���̕`�� */
	if( m_pChild )	m_pChild->Render(bNoAlpha, bAlpha);

	/* ���[���h�ϊ������ɖ߂� */
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matSavedWorld );
	/* ���̃��b�V���̕`�� */
	if( m_pNext )	m_pNext->Render(bNoAlpha, bAlpha);

	return S_OK;
}

//----------------------------------------------------------------------
//	Name:	Render
//	Func:	���[�V�����␳�l���܂߂�
//			�K�w�\���ł̕`�揈��
//	in:		D3DXMATRIX	matMotion[] = �␳�l�}�g���N�X�z��
//			BOOL bNoAlpha = �A���t�@�l���Ȃ�������`�����H
//			BOOL bAlpha	  = �A���t�@�l�����镔�����������H
//	Out:	HRESULT
//----------------------------------------------------------------------
HRESULT CMeshFrame::Render(D3DXMATRIX matMotion[], BOOL bNoAlpha,BOOL bAlpha)
{
	D3DXMATRIX matSavedWorld, matWorld;

	/* ���݂̃}�g���N�X��ޔ� */
	m_pd3dDevice->GetTransform( D3DTS_WORLD, &matSavedWorld );

	/* �}�g���N�X�̊|���Z���s�����[���h�ϊ����� */
	D3DXMatrixMultiply( &matWorld, &matMotion[m_nNumber], &matSavedWorld );
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	/* �����̃��b�V���̕`�� */
	if( m_pMesh )	m_pMesh->Render(bNoAlpha, bAlpha);

	/* �q���̃��b�V���̕`�� */
	if( m_pChild )	m_pChild->Render(matMotion, bNoAlpha, bAlpha);

	/* ���[���h�ϊ������ɖ߂� */
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matSavedWorld );
	/* ���̃��b�V���̕`�� */
	if( m_pNext )	m_pNext->Render(matMotion, bNoAlpha, bAlpha);

	return S_OK;
}

//**********************************************
//	CMeshData�N���X
//**********************************************

//----------------------------------------------
//	Name:	CMeshData
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	�Ȃ�
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
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CMeshData::~CMeshData()
{
	Destroy();
}

//----------------------------------------------
//	Name:	Create
//	Func:	�K�w���b�V�����t�@�C������쐬
//	in:		TCHAR* strFilename
//	Out:	�Ȃ�
//----------------------------------------------
HRESULT CMeshData::Create(TCHAR* strFilename)
{
	LPDIRECTXFILE			pDXFile   = NULL;
	LPDIRECTXFILEENUMOBJECT pEnumObj  = NULL;
	LPDIRECTXFILEDATA		pFileData = NULL;

	/* �J�����g�f�B���N�g����ۑ� */
	TCHAR strCurrentDirectory[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, strCurrentDirectory);
	/* X�t�@�C���̃p�X�����ƁA�t�@�C�������擾���� */
	TCHAR strDir[_MAX_DIR];
	TCHAR strFname[_MAX_FNAME];
	//_tsplitpath(strFilename, NULL, strDir, strFname, NULL);

	_tsplitpath_s(strFilename, 
				NULL, 0, 
				strDir, _MAX_DIR,
				strFname, _MAX_FNAME,
				NULL, 0);

	/* �t�@�C�����̊i�[ */
	//strcpy(m_strName, strFname);
	_tcscpy_s(m_strName, strFname);

	/* �w�t�@�C���I�u�W�F�N�g�̍쐬 */
	if(FAILED(DirectXFileCreate(&pDXFile)))	return E_FAIL;

	/* �f�[�^�̃��[�h */
	if( FAILED(pDXFile->CreateEnumObject( strFilename, DXFILELOAD_FROMFILE, &pEnumObj)))
	{
		pDXFile->Release();
		return E_FAIL;
	}

	/* �J�����g�f�B���N�g����ύX */
	SetCurrentDirectory(strDir);

	/* �ǂݍ��񂾃f�[�^����K�w�\�����쐬���Ă��� */
	while( SUCCEEDED( pEnumObj->GetNextDataObject( &pFileData ) ) )
	{
		CreateTree( pFileData, NULL );
		pFileData->Release();
	}

	/* �J�����g�f�B���N�g�������ɖ߂� */
	SetCurrentDirectory(strCurrentDirectory);

	/* �g�p�����������̊J�� */
	SAFE_RELEASE( pFileData );
	SAFE_RELEASE( pEnumObj );
	SAFE_RELEASE( pDXFile );

	/* �I�u�W�F�N�g�̏C���H */
	RestoreDeviceObjects();

	return S_OK;
}

//----------------------------------------------------------
//	Name:	CreateTree
//	Func:	�K�w���b�V�������Ƃ��ɍċA�I�Ɏg�p
//	in:		LPDIRECTXFILEDATA pFileData = �q���̃t�@�C���f�[�^
//			CMeshFrame*	pParentFrame	= �e�̃t���[��
//	Out:	�Ȃ�
//----------------------------------------------------------
HRESULT CMeshData::CreateTree(LPDIRECTXFILEDATA pFileData, CMeshFrame* pParentFrame)
{
	/* �܂��ŏ��Ƀt�@�C���̃f�[�^����^�C�v���擾���� */
	const GUID* pGUID;
	if( FAILED(pFileData->GetType(&pGUID)))
		return E_FAIL;

	/* �f�[�^�^�C�v�����b�V���������Ƃ� */
	if( *pGUID == TID_D3DRMMesh )
	{
		if( pParentFrame->m_pMesh )
			return E_FAIL;

		/* ���b�V���̍쐬 */
		pParentFrame->m_pMesh = new CMeshObject(m_pd3dDevice);
		pParentFrame->m_pMesh->Create(pFileData);

	}

	/* �f�[�^�^�C�v���}�g���N�X�������Ƃ� */
	else if( *pGUID == TID_D3DRMFrameTransformMatrix )
	{
		/* �}�g���N�X�l���擾 */
		D3DXMATRIX* pMat;
		DWORD		cbSize;
		if(FAILED(pFileData->GetData(NULL,&cbSize,(VOID**)&pMat)))
			return E_FAIL;

		/* �t���[���Ɋi�[ */
		pParentFrame->SetMatrix(*pMat);
	}

	/* �f�[�^�^�C�v���t���[���������Ƃ� */
	if( *pGUID == TID_D3DRMFrame )
	{
		/* �V�K�t���[���̍쐬 */
		CMeshFrame*	pCurrentFrame = new CMeshFrame(m_pd3dDevice);
		pCurrentFrame->SetNumber(m_nFrameNum);
		m_nFrameNum++;

		/* ���O�̎擾 */
		TCHAR strName[512];
		DWORD dwNameLength;
		pFileData->GetName( NULL, &dwNameLength );
		if( dwNameLength > 0 )
			pFileData->GetName( strName, &dwNameLength );
		pCurrentFrame->SetName(strName);

		/* �e�̃f�[�^���Ȃ��Ƃ��͍ŏ��̃f�[�^�Ƃ݂Ȃ��AListTop�ɒǉ����� */
		if(!pParentFrame)
			m_pListTop = pCurrentFrame;
		/* ����ȊO�̂Ƃ��͐e�̃f�[�^�ƂȂ��A�K�w�\�����쐬���� */
		else{
			pCurrentFrame->m_pNext = pParentFrame->m_pChild;
			pParentFrame->m_pChild = pCurrentFrame;
		}

		//------------------------------------------------------
		// pParent����e	pCurrent����q��	�Ƃ��A
		// �����ł����pCurrent�̎q��(���Ƃ���)��{���Ă����B
		// �������������ꍇ�A���̃t�@�C���f�[�^���擾���A
		// pCurrent��e�A���̃t�@�C���f�[�^���q���Ƃ���
		// CreateTree���ċA�I�ɌĂяo���Ă���
		//------------------------------------------------------
		LPDIRECTXFILEDATA	pChildData = NULL;
		LPDIRECTXFILEOBJECT pChildObj = NULL;

		while( SUCCEEDED( pFileData->GetNextObject( &pChildObj ) ) )
		{
			/* �q���̃t�@�C���f�[�^�̎擾 */
			if( SUCCEEDED(pChildObj->QueryInterface(IID_IDirectXFileData,
													(VOID**)&pChildData)))
			{
				/* ��L�̂Ƃ���ċA�I�ɌĂяo���Ă��� */
				CreateTree( pChildData, pCurrentFrame );
				pChildData->Release();
				pChildObj->Release();
			} 
			/* ���s�� */
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
//	Func:	�S�I�u�W�F�N�g�̍폜
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
HRESULT CMeshData::Destroy()
{

	m_pListTop->Destroy();
	return S_OK;
}

//----------------------------------------------------------
//	Name:	RestoreDeviceObject
//	Func:	�S�I�u�W�F�N�g�̏C��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
HRESULT CMeshData::RestoreDeviceObjects()
{
	m_pListTop->RestoreDeviceObjects();
	return S_OK;
}

//----------------------------------------------------------
//	Name:	InvalidateDeviceObjects
//	Func:	�S�I�u�W�F�N�g�̂u�q�`�l�j��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
HRESULT CMeshData::InvalidateDeviceObjects()
{
	m_pListTop->InvalidateDeviceObjects();
	return S_OK;
}

//----------------------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
HRESULT CMeshData::Render()
{
	/* �܂��̓A���t�@�l�̂������ĂȂ���������`�悷�� */
	if( m_pListTop )	m_pListTop->Render( TRUE, FALSE );

	/* �A���t�@�u�����h��L���ɂ��� */
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	/* ���ɃA���t�@�l�̂������Ă��镔����`�悷�� */
	if( m_pListTop )	m_pListTop->Render( FALSE, TRUE );

	/* �A���t�@�u�����h�����ɖ߂� */
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );

	return S_OK;
}

//----------------------------------------------------------------------
//	Name:	Render
//	Func:	���[�V�����␳�l���܂߂��`�揈��
//	in:		D3DXMATRIX** ppMatMotion = �␳�l�}�g���N�X�z��ւ̃|�C���^�̃|�C���^
//	Out:	HRESULT
//----------------------------------------------------------------------
HRESULT	CMeshData::Render(D3DXMATRIX matMotion[])
{
	/* �܂��̓A���t�@�l�̂������ĂȂ���������`�悷�� */
	if( m_pListTop )	m_pListTop->Render( matMotion, TRUE, FALSE );

	/* �A���t�@�u�����h��L���ɂ��� */
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	/* ���ɃA���t�@�l�̂������Ă��镔����`�悷�� */
	if( m_pListTop )	m_pListTop->Render( matMotion, FALSE, TRUE );

	/* �A���t�@�u�����h�����ɖ߂� */
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );

	return S_OK;
}