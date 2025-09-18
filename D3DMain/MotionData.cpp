//==========================================================
// MotionData.cpp
// Auther : ���� ���V
// Data   : 2002/03/26
//==========================================================

#include "MotionData.h"

//**********************************************
//	CMotionFrame�N���X
//**********************************************

//----------------------------------------------
//	Name:	CMotionFrame
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	�Ȃ�
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
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CMotionFrame::~CMotionFrame()
{
	Destroy();
}

//----------------------------------------------------------
//	Name:	CreateKey
//	Func:	�t�@�C������A�j���[�V�����L�[�̍쐬
//	in:		LPDIRECTXFILEDATA pFileData = �t�@�C���f�[�^
//	Out:	�Ȃ�
//----------------------------------------------------------
HRESULT CMotionFrame::CreateKey(LPDIRECTXFILEDATA pFileData)
{
	/* �ǂݍ��ݗp�\���̂̒�` */
	typedef struct
	{
		int				nTime;
		int				nFloats;	
		float			w;
		float			x;
		float			y;
		float			z;
	}tagRot;

	/* �܂��ŏ��Ƀt�@�C���̃f�[�^����^�C�v���擾���� */
	const GUID* pGUID;
	if( FAILED(pFileData->GetType(&pGUID)))
		return E_FAIL;

	/* �f�[�^�^�C�v���A�j���[�V�����ł͂Ȃ��Ȃ�I�� */
	if( *pGUID != TID_D3DRMAnimationKey )
		return E_FAIL;

	/* �t�@�C������f�[�^���擾 */
	PBYTE	pData;
	DWORD	dwSize;
	pFileData->GetData(NULL, &dwSize, (PVOID*)&pData);

	/* �f�[�^����L�[�^�C�v�A�L�[�����擾 */
	int		nKeyType = ((int*)pData)[0];
	int		nKeyNum  = ((int*)pData)[1];

	/* �L�[�^�C�v����]�L�[�������ꍇ */
	if(nKeyType == 0)
	{
		m_nRotKeyNum = nKeyNum;					// �L�[�ő吔�̊i�[
		m_pRotKey = new tagRotateKey[nKeyNum];	// �L�[�̐������������ɔz����Ƃ�

		/* �f�[�^�̓ǂݍ��݈ʒu���ӂ����炷 */
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
	/* �L�[�^�C�v���g��L�[�������ꍇ */
	else if(nKeyType == 1)
	{
		// ���ݑΉ����Ă��܂���
	}

	/* �L�[�^�C�v���ʒu�L�[�������ꍇ */
	else if(nKeyType == 2)
	{
		m_nPosKeyNum = nKeyNum;						// �L�[�ő吔�̊i�[
		m_pPosKey = new tagPositionKey[nKeyNum];	// �L�[�̐������������ɔz����Ƃ�

		/* �f�[�^�̓ǂݍ��݈ʒu���ӂ����炷 */
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
//	Func:	�S�Ẵf�[�^�̍폜
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
HRESULT CMotionFrame::Destroy()
{
	SAFE_DELETES(m_pRotKey);
	SAFE_DELETES(m_pPosKey);

	return S_OK;
}

//**********************************************
//	CMotionData�N���X
//**********************************************

//----------------------------------------------
//	Name:	CMotionData
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 pd3dDevice
//	Out:	�Ȃ�
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
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CMotionData::~CMotionData()
{
	Destroy();
}

//------------------------------------------------------
//	Name:	Create
//	Func:	�t�@�C������A�j���[�V�������X�g�\�����쐬
//	in:		TCHAR* strFilename = �t�@�C���p�X
//	Out:	�Ȃ�
//------------------------------------------------------
HRESULT	CMotionData::Create(TCHAR* strFilename)
{
	LPDIRECTXFILE			pDXFile		= NULL;
	LPDIRECTXFILEENUMOBJECT pEnumObj	= NULL;
	LPDIRECTXFILEDATA		pFileData	= NULL;

	LPDIRECTXFILEDATA		pChildData	= NULL;
	LPDIRECTXFILEOBJECT		pChildObj	= NULL;

	/* �t�@�C�������擾���� */
	TCHAR strFname[_MAX_FNAME];
	//_tsplitpath(strFilename, NULL, NULL, strFname, NULL);

	_tsplitpath_s(	strFilename, 
					NULL, 0,
					NULL, 0,
					strFname, _MAX_FNAME,
					NULL, 0);

	/* �t�@�C�����̊i�[ */
	//strcpy(m_strName, strFname);
	_tcscpy_s(m_strName, _countof(m_strName), strFname);

	/* �w�t�@�C���I�u�W�F�N�g�̍쐬 */
	if(FAILED(DirectXFileCreate(&pDXFile)))	return E_FAIL;

	/* �f�[�^�̃��[�h */
	if( FAILED(pDXFile->CreateEnumObject( strFilename, DXFILELOAD_FROMFILE, &pEnumObj)))
	{
		pDXFile->Release();
		return E_FAIL;
	}

	/* �ǂݍ��񂾃f�[�^���烊�X�g�\�����쐬���Ă��� */
	while( SUCCEEDED( pEnumObj->GetNextDataObject( &pFileData ) ) )
	{
		/* �t�@�C���̃f�[�^�^�C�v���擾���� */
		const GUID*	pGUID;
		if(FAILED(pFileData->GetType(&pGUID)))
			return E_FAIL;

		/* �f�[�^�^�C�v���A�j���[�V�����Z�b�g�������ꍇ�̂ݏ������s�� */
		if(*pGUID == TID_D3DRMAnimationSet)
		{
			CMotionFrame*		pParentFrame = NULL;

			/* �t���[�����Ƃ̃A�j���[�V������T���Ă��� */
			while(SUCCEEDED(pFileData->GetNextObject(&pChildObj)))
			{
				/* �q���̃t�@�C���f�[�^�̎擾 */
				if( SUCCEEDED(pChildObj->QueryInterface(IID_IDirectXFileData,
														(VOID**)&pChildData)))
				{
					pParentFrame = CreateFrame(pChildData, pParentFrame);
					m_nFrameNum++;
					pChildData->Release();
					pChildObj->Release();
				}
				/* ���s�� */
				else{
					pChildObj->Release();
				}
			}
			/* �A�j���[�V�����t�@�C���̍쐬�����Ƃ݂Ȃ� */
			/* �ЂƂA�j���[�V�����Z�b�g��ǂݍ��񂾂�ӂ��ڂ͂���Ȃ� */
			pFileData->Release();
			break;

		}
		/* �f�[�^�^�C�v���A�j���[�V�����Z�b�g�ł͂Ȃ������ꍇ */
		else
		{
			pFileData->Release();
		}
	}

	/* pEnumObj���t�@�C���̍Ō�܂œǂ܂��� */
	while( SUCCEEDED( pEnumObj->GetNextDataObject( &pFileData )));

	/* �g�p�����������̊J�� */
	SAFE_RELEASE( pFileData );
	SAFE_RELEASE( pEnumObj );
	SAFE_RELEASE( pDXFile );

	/* ���X�g�̂͂��߂Ƀf�[�^�������Ă���Γǂݍ��ݐ����A*/
	/* �����łȂ��Ƃ��͎��s�Ƃ��� */
	if(m_pListTop != NULL)
	{
		ComputMaxFrame();	// �ő�t���[�������v�Z���Ă���
		return S_OK;
	}
	else					return E_FAIL;
}

//----------------------------------------------------------
//	Name:	CreateFrame
//	Func:	�t�@�C������ЂƂ̃t���[�����쐬����
//			Create�̒��ŌĂ΂��
//	in:		LPDIRECTXFILEDATA pFileData = �t�@�C���f�[�^
//			CMeshFrame*	pParentFrame	= �O�̃f�[�^�̃|�C���^
//	Out:	CMotionFrame* = �쐬���ꂽ�f�[�^�̃|�C���^
//----------------------------------------------------------
CMotionFrame* CMotionData::CreateFrame(LPDIRECTXFILEDATA pFileData, CMotionFrame* pParentFrame)
{
	/* �ŏ��Ƀt�@�C���̃f�[�^����^�C�v���擾���� */
	const GUID* pGUID;
	if( FAILED(pFileData->GetType(&pGUID)))
		return NULL;

	/* �f�[�^�^�C�v���A�j���[�V�����ł͂Ȃ��Ȃ�I�� */
	if( *pGUID != TID_D3DRMAnimation )
		return NULL;

	/* �V�K���[�V�����t���[���̍쐬 */
	CMotionFrame*	pCurrentFrame = new CMotionFrame(m_pd3dDevice);

	/* ���O�̎擾 */
	TCHAR strName[512];
	DWORD dwNameLength;
	pFileData->GetName( NULL, &dwNameLength );
	if( dwNameLength > 0 )
		pFileData->GetName( strName, &dwNameLength );
	pCurrentFrame->SetName(strName);

	/* ����Ƀt�@�C������A�j���[�V�����L�[��T���Ă��� */
	LPDIRECTXFILEDATA		pChildData	= NULL;
	LPDIRECTXFILEOBJECT		pChildObj	= NULL;

	while(SUCCEEDED(pFileData->GetNextObject(&pChildObj)))
	{
		/* �q���̃t�@�C���f�[�^�̎擾 */
		if( SUCCEEDED(pChildObj->QueryInterface(IID_IDirectXFileData,
												(VOID**)&pChildData)))
		{
			pCurrentFrame->CreateKey(pChildData);
			pChildData->Release();
			pChildObj->Release();
		}
		/* ���s�� */
		else{
			pChildObj->Release();
		}
	}

	/* �f�[�^���Ȃ��� */
	if(pParentFrame)	pParentFrame->m_pNext = pCurrentFrame;
	else				m_pListTop = pCurrentFrame;

	return pCurrentFrame;
}

//----------------------------------------------
//	Name:	ComputMaxFrame
//	Func:	�ő�t���[�����Ԃ����߂�
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CMotionData::ComputMaxFrame()
{
	CMotionFrame*	pCurrentFrame = m_pListTop;
	int				nTmp, nMaxFrame=0;

	while(pCurrentFrame)
	{
		/* ��]�L�[�̍ő�t���[�����Ԃ����߂� */
		if(pCurrentFrame->m_pRotKey)
		{
			nTmp = pCurrentFrame->m_pRotKey[pCurrentFrame->m_nRotKeyNum-1].nTime;
			if(nMaxFrame<nTmp)	nMaxFrame = nTmp;
		}
		/* �ʒu�L�[�̍ő�t���[�����Ԃ����߂� */
		if(pCurrentFrame->m_pPosKey)
		{
			nTmp = pCurrentFrame->m_pPosKey[pCurrentFrame->m_nPosKeyNum-1].nTime;
			if(nMaxFrame<nTmp)	nMaxFrame = nTmp;
		}

		/* ���̃f�[�^�� */
		pCurrentFrame = pCurrentFrame->m_pNext;
	}

	/* �ő�t���[�����Ԃ̊i�[ */
	m_nMaxFrame = nMaxFrame;

	return S_OK;
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	�S�ẴI�u�W�F�N�g�̍폜
//	in:		�Ȃ�
//	Out:	�Ȃ�
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