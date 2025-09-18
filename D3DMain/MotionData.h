//==========================================================
// MotionData.h
// Auther : ���� ���V
// Data   : 2002/04/16
//==========================================================

#if !defined(AFX_MOTIONDATA_H__8E2130F7_0AFD_4E37_A6C7_7EBB78D78964__INCLUDED_)
#define AFX_MOTIONDATA_H__8E2130F7_0AFD_4E37_A6C7_7EBB78D78964__INCLUDED_

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

#ifndef SAFE_DELETES
#define SAFE_DELETES(p)			{ if(p) { delete[] (p);   (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)=NULL; } }
#endif

//----------------------------------------------
//	Name:	tagRotateKey
//	Func:	��]�L�[�\����
//----------------------------------------------
typedef	struct{
	int				nTime;
	int				nFloats;
	D3DXQUATERNION	quatRot;	
} tagRotateKey;

//----------------------------------------------
//	Name:	tagPositionKey
//	Func:	�ʒu�L�[�\����
//----------------------------------------------
typedef	struct{
	int			nTime;
	int			nFloats;
	D3DXVECTOR3	vecPos;
} tagPositionKey;

//--------------------------------------------------------------
//	Name	: CMotionFrame
//	Func	: �ЂƂ̃t���[���ɑ΂���A�j���[�V����
//--------------------------------------------------------------
class CMotionFrame  
{
friend class CMotionData;
friend class CActiveFrame;
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3D�f�o�C�X

	CMotionFrame*		m_pNext;		// ���̃f�[�^�ւ̃|�C���^
	TCHAR				m_strName[512];	// �t���[����

	int					m_nRotKeyNum;	// ��]�L�[�z��̍ő吔
	tagRotateKey*		m_pRotKey;		// ��]�L�[�z��̐擪�A�h���X
	int					m_nPosKeyNum;	// �ʒu�L�[�z��̍ő吔
	tagPositionKey*		m_pPosKey;		// �ʒu�L�[�z��̐擪�A�h���X

public:
	HRESULT	CreateKey(LPDIRECTXFILEDATA pFileData);	// �A�j���[�V�����L�[�̍쐬
	HRESULT	Destroy();								// �S�Ẵf�[�^�̍폜

	/* �A�N�Z�X�֐� */
	CMotionFrame*	GetNext();					// ���̃f�[�^�ւ̃|�C���^���擾
	TCHAR*			GetName();					// ���O�̎擾
	void			SetName(TCHAR* strName);	// ���O�̃Z�b�g

	CMotionFrame(LPDIRECT3DDEVICE8 pd3dDevice);
	virtual ~CMotionFrame();

};

//----------------------------------------------
//	Name:	GetNext
//	Func:	���̃f�[�^�ւ̃|�C���^���擾
//	in:		�Ȃ�
//	Out:	CMotionFrame* = ���̃f�[�^�ւ̃|�C���^
//----------------------------------------------
inline CMotionFrame* CMotionFrame::GetNext()
{
	return m_pNext;
}

//----------------------------------------------
//	Name:	GetName
//	Func:	���O�̎擾
//	in:		�Ȃ�
//	Out:	TCHAR* = ���O
//----------------------------------------------
inline TCHAR* CMotionFrame::GetName()
{
	return m_strName;
}

//----------------------------------------------
//	Name:	GetName
//	Func:	���O�̎擾
//	in:		TCHAR* strName = �w�薼
//	Out:	�Ȃ�
//----------------------------------------------
inline void CMotionFrame::SetName(TCHAR* strName)
{
	//strcpy(m_strName,strName);
	_tcscpy_s(m_strName, _countof(m_strName), strName);
}

//--------------------------------------------------------------
//	Name	: CMotionData
//	Func	: �A�j���[�V�����f�[�^�����X�g�\���ŊǗ�����N���X
//--------------------------------------------------------------
class CMotionData  
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3D�f�o�C�X

	CMotionFrame*		m_pListTop;		// ���X�g�\���̍ŏ��ɂ���f�[�^
	TCHAR				m_strName[512];	// �A�j���[�V�����̖��O
	int					m_nMaxFrame;	// �A�j���[�V�����̍ő�t���[������
	int					m_nFrameNum;	// ���X�g�\���̃t���[����

public:
	HRESULT	Create(TCHAR* strFilename);						// �t�@�C�����烊�X�g�\�����쐬
	CMotionFrame* CreateFrame(LPDIRECTXFILEDATA pFileData,	// Create����Ă΂��
						CMotionFrame* pCurrentFrame);

	HRESULT			ComputMaxFrame();			// �ő�t���[�����Ԃ����߂�
	HRESULT			Destroy();					// �S�I�u�W�F�N�g�̍폜

	/* �A�N�Z�X�֐� */
	int				GetFrameNum();				// �t���[������Ԃ�
	CMotionFrame*	GetListTop();				// ���X�g�̍ŏ��ɂ���f�[�^��Ԃ�
	int				GetMaxFrame();				// �ő�t���[�����Ԃ�Ԃ�

	CMotionData(LPDIRECT3DDEVICE8 pd3dDevice);
	virtual ~CMotionData();

};

//----------------------------------------------
//	Name:	GetFrameNum
//	Func:	�t���[������Ԃ�
//	in:		�Ȃ�
//	Out:	int = �t���[����
//----------------------------------------------
inline int CMotionData::GetFrameNum()
{
	return m_nFrameNum;
}

//----------------------------------------------
//	Name:	GetListTop
//	Func:	���X�g�\���̍ŏ��̃f�[�^��Ԃ�
//	in:		�Ȃ�
//	Out:	CMotionFrame* = ���X�g�̏��߂̃f�[�^
//----------------------------------------------
inline CMotionFrame* CMotionData::GetListTop()
{
	return m_pListTop;
}

//----------------------------------------------
//	Name:	GetListTop
//	Func:	�ő�t���[�����Ԃ�Ԃ�
//	in:		�Ȃ�
//	Out:	int = �ő�t���[������
//----------------------------------------------
inline int CMotionData::GetMaxFrame()
{
	return m_nMaxFrame;
}

#endif // !defined(AFX_MOTIONDATA_H__8E2130F7_0AFD_4E37_A6C7_7EBB78D78964__INCLUDED_)
