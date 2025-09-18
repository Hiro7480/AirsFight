//==========================================================
// MeshData.h
// Auther : ���� ���V
// Data   : 2002/04/17
//==========================================================

#if !defined(AFX_MESHMANAGE_H__CB3368AD_E699_4815_BB1F_E754620B133B__INCLUDED_)
#define AFX_MESHMANAGE_H__CB3368AD_E699_4815_BB1F_E754620B133B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include "CompatiDX8.h"
#include <d3d8.h>
#include <d3dx8.h>
#include <tchar.h>
#include <rmxfguid.h>

//------------------------------
//		�萔��`
//------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)=NULL; } }
#endif
//----------------------------------------------------------
//	Name	: CMeshObject
//	Func	: �ЂƂ̂w���b�V�����Ǘ�����N���X
//----------------------------------------------------------
class CMeshObject  
{
public:
	LPDIRECT3DDEVICE8	m_pd3dDevice;		// D3D�f�o�C�X

	TCHAR				m_strName[512];		// ���b�V���̖��O
	LPD3DXMESH          m_pSysMemMesh;		// �V�X�e���������Ɏ擾���郁�b�V��
	LPD3DXMESH          m_pLocalMesh;		// ���ێg�p���郁�b�V��
	float				m_fLength;			// �o�E���f�B���O�X�t�B�A�̔��a
    
	DWORD				m_dwNumMaterials;	// ���b�V���̒��̃}�e���A���̐�
	D3DMATERIAL8*		m_pMaterials;		// �}�e���A���̐擪�A�h���X
	LPDIRECT3DTEXTURE8*	m_pTextures;		// �e�N�X�`���̐擪�A�h���X

public:

	HRESULT Render(BOOL bNoAlpha=TRUE, BOOL bAlpha=TRUE);	// �`��֐�

	HRESULT Create( TCHAR* strFilename );					// �t�@�C������̍쐬
	HRESULT Create( LPDIRECTXFILEDATA pFileData );			// �K�w�\�����̍쐬
	HRESULT	ComputLength();									// �o�E���f�B���O�X�t�B�A�̔��a�̎Z�o
	HRESULT Destroy();										// �I�u�W�F�N�g�̍폜
	HRESULT	RestoreDeviceObjects();							// �I�u�W�F�N�g�̏C��
	HRESULT InvalidateDeviceObjects();						// �u�q�`�l��j������

	/* �A�N�Z�X�֐� */
	LPD3DXMESH	GetSysMemMesh();				// �V�X�e�����b�V���̎擾
	LPD3DXMESH	GetLocalMesh();					// ���[�J�����b�V���̎擾
	float		GetLength();					// �o�E���f�B���O�X�t�B�A�̔��a�̎擾

	/* �I�v�V�����֐� */
	HRESULT	SetFVF(DWORD dwFVF);				// ���_�t�H�[�}�b�g�̐ݒ�

	CMeshObject(LPDIRECT3DDEVICE8 pd3dDevice);
	virtual ~CMeshObject();

};

//----------------------------------------------
//	Name:	GetSysMemMesh
//	Func:	�V�X�e�����b�V���̎擾
//	in:		�Ȃ�
//	Out:	LPD3DXMESH = ���b�V���f�[�^
//----------------------------------------------
inline LPD3DXMESH CMeshObject::GetSysMemMesh()
{
	return m_pSysMemMesh;
}

//----------------------------------------------
//	Name:	GetSysMemMesh
//	Func:	���[�J�����b�V���̎擾
//	in:		�Ȃ�
//	Out:	LPD3DXMESH = ���b�V���f�[�^
//----------------------------------------------
inline LPD3DXMESH CMeshObject::GetLocalMesh()
{
	return m_pLocalMesh;
}

//----------------------------------------------
//	Name:	GetLength
//	Func:	�o�E���f�B���O�X�t�B�A�̔��a�̎擾
//	in:		�Ȃ�
//	Out:	float = ���a�̒���
//----------------------------------------------
inline float CMeshObject::GetLength()
{
	return m_fLength;
}

//----------------------------------------------------------
//	Name	: CMeshFrame
//	Func	: ���b�V���̊K�w�\���������N���X
//----------------------------------------------------------
class CMeshFrame
{
friend class CMeshData;

private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;		// D3D�f�o�C�X

	TCHAR				m_strName[512];		// �t���[���̖��O
	int					m_nNumber;			// �K�w�\���ł̏��Ԕԍ�
	D3DXMATRIX			m_matBase;			// �}�g���N�X
	CMeshObject*		m_pMesh;			// ���b�V���I�u�W�F�N�g

	CMeshFrame*			m_pNext;			// ���K�w���b�V��
	CMeshFrame*			m_pChild;			// �q�����b�V��

public:
	/* �ʏ�`�� */
	HRESULT Render( BOOL bNoAlpha=TRUE,BOOL bAlpha=TRUE );
	/* ���[�V�����␳�l���܂߂��`�� */
	HRESULT Render( D3DXMATRIX matMotion[], BOOL bNoAlpha=TRUE,BOOL bAlpha=TRUE );

	HRESULT Destroy();							// �I�u�W�F�N�g�̍폜
	HRESULT	RestoreDeviceObjects();				// �I�u�W�F�N�g�̏C��
	HRESULT InvalidateDeviceObjects();			// �I�u�W�F�N�g�̏�����

	/* �A�N�Z�X�֐� */
	void		SetMatrix(D3DXMATRIX matTmp);	// �}�g���N�X�̃Z�b�g
	void		SetName(TCHAR* strName);		// ���O�̃Z�b�g
	void		SetNumber(int nNum);			// �ԍ��̃Z�b�g

	TCHAR*		GetName();						// ���O�̎擾
	D3DXMATRIX	GetMatrix();					// �}�g���N�X�̎擾
	CMeshFrame*	GetFrame(int nFrame);			// �w��ԍ��̃t���[����Ԃ�
	int			GetNumber();					// �ԍ��̎擾

	CMeshFrame(LPDIRECT3DDEVICE8 m_pd3dDevice);
	virtual ~CMeshFrame();
};

//----------------------------------------------
//	Name:	SetMatrix
//	Func:	�}�g���N�X�̃Z�b�g
//	in:		D3DXMATRIX matTmp = �w��}�g���N�X
//	Out:	�Ȃ�
//----------------------------------------------
inline void CMeshFrame::SetMatrix(D3DXMATRIX matTmp)
{
	m_matBase = matTmp;
}

//----------------------------------------------
//	Name:	SetName
//	Func:	���O�̃Z�b�g
//	in:		TCHAR* strName = �w�薼
//	Out:	�Ȃ�
//----------------------------------------------
inline void CMeshFrame::SetName(TCHAR* strName)
{
	//strcpy(m_strName,strName);
	_tcscpy_s(m_strName, _countof(m_strName), strName);
}

//----------------------------------------------
//	Name:	SetNumber
//	Func:	�ԍ��̃Z�b�g
//	in:		int nNum = �w��ԍ�
//	Out:	�Ȃ�
//----------------------------------------------
inline void CMeshFrame::SetNumber(int nNum)
{
	m_nNumber = nNum;
}

//----------------------------------------------
//	Name:	GetName
//	Func:	���O�̎擾
//	in:		�Ȃ�
//	Out:	TCHAR* = ���O
//----------------------------------------------
inline TCHAR* CMeshFrame::GetName()
{
	return m_strName;
}

//----------------------------------------------
//	Name:	GetMatrix
//	Func:	�}�g���N�X�̎擾
//	in:		�Ȃ�
//	Out:	D3DXMATRIX = �}�g���N�X
//----------------------------------------------
inline D3DXMATRIX CMeshFrame::GetMatrix()
{
	return m_matBase;
}

//----------------------------------------------
//	Name:	GetFrame
//	Func:	�}�g���N�X�̎擾
//	in:		int = nFrame	= �w��t���[���ԍ�
//	Out:	CMeshFrame		= ���b�V���t���[��
//----------------------------------------------
inline CMeshFrame* CMeshFrame::GetFrame(int nFrame)
{
	CMeshFrame* pFrame;

	/* �����̃t���[���̔ԍ��������Ȃ炻�̂܂ܕԂ� */
	if(nFrame == m_nNumber)
		return this;

	/* �q���𒲂ׂĂ��� */
	if(m_pChild)
		if(NULL != (pFrame = m_pChild->GetFrame(nFrame)))
			return pFrame;

	/* ���𒲂ׂĂ��� */
	if(m_pNext)
		if(NULL != (pFrame = m_pNext->GetFrame(nFrame)))
			return pFrame;

	/* ������Ȃ������Ƃ���NULL��Ԃ� */
	return NULL;
}
//----------------------------------------------
//	Name:	GetNumber
//	Func:	�ԍ��̎擾
//	in:		�Ȃ�
//	Out:	int = �t���[���ԍ�
//----------------------------------------------
inline int CMeshFrame::GetNumber()
{
	return m_nNumber;
}

//----------------------------------------------------------
//	Name	: CMeshData
//	Func	: �K�w�\���������b�V�����Ǘ�����N���X
//----------------------------------------------------------
class CMeshData
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3D�f�o�C�X

	CMeshFrame*			m_pListTop;		// �K�w�\���̈�ԍŏ��ɂ���f�[�^
	TCHAR				m_strName[512];	// �w�t�@�C���̖��O
	int					m_nFrameNum;	// �K�w�\���̃t���[����

public:
	HRESULT	Render();									// �ʏ�̕`��
	HRESULT	Render(D3DXMATRIX matMotion[]);				// ���[�V�����␳�l���܂߂��`��

	HRESULT	Create(TCHAR* strFilename);					// �K�w���b�V�����t�@�C������쐬
	HRESULT	CreateTree(	LPDIRECTXFILEDATA pFileData,	// �K�w���b�V�������Ƃ��ɍċA�I�Ɏg�p
						CMeshFrame* pParentFrame);
	HRESULT Destroy();									// �S�I�u�W�F�N�g�̍폜
	HRESULT	RestoreDeviceObjects();						// �S�I�u�W�F�N�g�̏C��
	HRESULT InvalidateDeviceObjects();					// �S�I�u�W�F�N�g�̂u�q�`�l�j��

	/* �A�N�Z�X�֐� */
	int			GetFrameNum();							// �f�[�^�̐��̎擾
	CMeshFrame*	GetFrame(int nFrame);					// �w��t���[���̎擾

	CMeshData(LPDIRECT3DDEVICE8 pd3dDevice);
	virtual ~CMeshData();

};

//----------------------------------------------
//	Name:	GetFrameNum
//	Func:	�f�[�^���̎擾
//	in:		�Ȃ�
//	Out:	int = �f�[�^��
//----------------------------------------------
inline int CMeshData::GetFrameNum()
{
	return m_nFrameNum;
}

//----------------------------------------------
//	Name:	GetFrame
//	Func:	�w��t���[���̎擾
//	in:		int nFrame	= �w��t���[���ԍ�
//	Out:	CMeshFrame*	= ���b�V���t���[�� 
//----------------------------------------------
inline CMeshFrame* CMeshData::GetFrame(int nFrame)
{
	return m_pListTop->GetFrame(nFrame);
}

#endif // !defined(AFX_MESHMANAGE_H__CB3368AD_E699_4815_BB1F_E754620B133B__INCLUDED_)
