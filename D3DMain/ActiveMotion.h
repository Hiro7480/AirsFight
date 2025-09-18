//==========================================================
// ActiveMotion.h
// Auther : ���� ���V
// Data   : 2002/04/16
//==========================================================

#if !defined(AFX_Active_H__2AA65FEF_1CB0_4E22_8246_689FB7A01849__INCLUDED_)
#define AFX_Active_H__2AA65FEF_1CB0_4E22_8246_689FB7A01849__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include "CompatiDX8.h"
#include <d3d8.h>
#include <d3dx8.h>
#include "MeshData.h"
#include "MotionData.h"

//----------------------------------------------------------
//	Name	: CActiveFrame
//	Func	: �Ή�����CMeshFrame��CMotionFrame������
//----------------------------------------------------------
class CActiveFrame  
{
private:
	CMeshFrame*		m_pMeshFrame;		// �Ή����郁�b�V���t���[��
	CMotionFrame*	m_pMotionFrame;		// �Ή�����A�j���[�V����

	D3DXQUATERNION	m_qtMotion;			// ���[�V�����p�N�I�[�^�j�I���i��]�␳�l�j
	D3DXVECTOR3		m_vecMotion;		// ���[�V�����p�x�N�g���i�ʒu�␳�l�j

public:
	
	HRESULT	Create(CMeshFrame* pMeshFrame, CMotionFrame* pMotionFrame);	// ������
	HRESULT	ComputQuat(int nActiveTime);			// ���ݎ��Ԃ����]�␳�l���Z�o
	HRESULT	ComputVec(int nActiveTime);				// ���ݎ��Ԃ���ʒu�␳�l���Z�o

	D3DXQUATERNION	GetQuat();						// ��]�␳�l��Ԃ�
	D3DXVECTOR3		GetVec();						// �ʒu�␳�l��Ԃ�

	HRESULT	Destroy();								// �S�I�u�W�F�N�g�̍폜

	float SuppleNum(int nMiddle, int nMax, int nMin);
	CActiveFrame();
	virtual ~CActiveFrame();

};

//----------------------------------------------
//	Name:	GetQuat
//	Func:	��]�␳�l�i�N�I�[�^�j�I���j��Ԃ�
//	in:		�Ȃ�
//	Out:	D3DXQUATERNION = ��]�␳�l
//----------------------------------------------
inline D3DXQUATERNION CActiveFrame::GetQuat()
{
	return m_qtMotion;
}

//----------------------------------------------
//	Name:	GetVec
//	Func:	�ʒu�␳�l�i�x�N�g���j��Ԃ�
//	in:		�Ȃ�
//	Out:	D3DXVECTOR3 = �ʒu�␳�l
//----------------------------------------------
inline D3DXVECTOR3 CActiveFrame::GetVec()
{
	return m_vecMotion;
}

//----------------------------------------------------------
//	Name	: CActiveData
//	Func	: �ЂƂ̃A�j���[�V���������A���^�C���ɍX�V����
//----------------------------------------------------------
class CActiveData  
{
private:
	friend class CActiveMotion;

	CMeshData*			m_pMeshData;			// �Ή����郁�b�V���f�[�^
	CMotionData*		m_pMotionData;			// �Ή����郂�[�V�����f�[�^

	CActiveFrame*		m_pActiveFrame[32];		// �t���[���f�[�^
	int					m_nActiveFrameNum;		// �t���[���f�[�^��

	int					m_nMaxTime;				// �ő�t���[������
	int					m_nActiveTime;			// ���݃t���[������

public:

	HRESULT	CreateFrame(CMeshData* pMeshData,	// �t���[���f�[�^�̍쐬
			CMotionData* pMotionData);
	HRESULT	ComputMotion();						// ���ݎ��Ԃ���N�I�[�^�j�I�����Z�o
	HRESULT	Run();								// �A�j���[�V�����̍Đ�

	HRESULT Destroy();							// �S�I�u�W�F�N�g�̍폜

	/* �A�N�Z�X�֐� */
	int		GetMaxTime();						// �ő�t���[�����Ԃ�Ԃ�
	void	SetActiveTime(int nTime);			// ���݃t���[�����Ԃ̃Z�b�g

	CActiveData();
	virtual ~CActiveData();

};

//----------------------------------------------
//	Name:	GetMaxTime
//	Func:	�ő�t���[�����Ԃ�Ԃ�
//	in:		�Ȃ�
//	Out:	int = �ő�t���[������
//----------------------------------------------
inline int CActiveData::GetMaxTime()
{
	return m_nMaxTime;
};

//----------------------------------------------
//	Name:	SetActiveTime
//	Func:	���݃t���[�����Ԃ̃Z�b�g
//	in:		int nTime = �w��t���[������
//	Out:	�Ȃ�
//----------------------------------------------
inline void CActiveData::SetActiveTime(int nTime)
{
	m_nActiveTime = nTime;
};

//----------------------------------------------------------
//	Name	: CActiveMotion
//	Func	: �����̃��[�V�����𑍊Ǘ�����N���X
//----------------------------------------------------------
class CActiveMotion
{
private:
	CMeshData*			m_pMeshData;				// �Ή����郁�b�V���f�[�^
	D3DXMATRIX			m_matMotion[32];			// ���[�V�����}�g���N�X�z��
	D3DXMATRIX			m_matStock[32];				// �`�掞�p�}�g���N�X�z��
	int					m_nMeshFrameNum;			// ���b�V���t���[����

	CActiveData*		m_pActiveData[32];			// ���[�V�����f�[�^�z��|�C���^
	float				m_fBlendNum[32];			// �u�����h�W��
	int					m_nActiveDataNum;			// ���[�V�����f�[�^��

public:
	HRESULT	LoadMesh(CMeshData* pMeshData);			// ���b�V���f�[�^�̃Z�b�g
	HRESULT	LoadMotion(CMotionData* pMotionData);	// ���[�V�����f�[�^�쐬

	HRESULT	Render();								// �`�揈��
	HRESULT	UpDate();								// �`��p�}�g���N�X�X�V

	HRESULT	Destroy();								// �I������

	HRESULT	ChangeMotion(int nNum, float fChangeSpeed=0.1f);				// ���݂̃��[�V�����̕ύX
	HRESULT	ChangeMotion(int nNum1, int nNum2, float fChangeSpeed=0.1f);	// �w�胂�[�V�����������X�Ɏ���
	HRESULT	Play();															// ���܂��܂ȃf�[�^�̍X�V

	HRESULT	ComputMatrix();		// �u�����h�W���ɂ��⊮���������݂̃��[�V�����}�g���N�X�����߂�
	HRESULT	ComputAllMotion();	// �S�Ẵ��[�V�����t���[���̃��[�V�����f�[�^�̌v�Z

	/* �A�N�Z�X�֐� */
	D3DXMATRIX		GetMatMotion(int nFrame);				// �w��t���[���̃}�g���N�X�̎擾
	int				GetMeshFrameNum();						// ���b�V���t���[�����̎擾
	CActiveData*	GetMotion(int nMotion);					// �w�胂�[�V�����f�[�^�̎擾
	float			GetBlend(int nMotion);					// �w�胂�[�V�����̃u�����h�W���̎擾
	int				GetMotionNum();							// �S���[�V�������̎擾
	int				GetMaxTime(int nMotion);				// �w�胂�[�V�����̍ő�t���[�����̎擾

	void			SetMatMotion(D3DXMATRIX matMotion,int nFrame);	// �w��t���[���̃}�g���N�X�̃Z�b�g
	void			SetBlend(int nMotion, float fBlend);		// �w�胂�[�V�����̃u�����h�W���̃Z�b�g
	void			SetActiveTime(int nMotion, int nTime);		// �w�胂�[�V�����Ɍ��ݎ��Ԃ̃Z�b�g

	CActiveMotion();
	virtual ~CActiveMotion();

};
//------------------------------------------------------
//	Name:	GetMatMotion
//	Func:	�w��t���[���̃}�g���N�X�̎擾
//	in:		int	nFrame	= �w��t���[�� 
//	Out:	D3DXMATRIX	= �}�g���N�X
//------------------------------------------------------
inline D3DXMATRIX CActiveMotion::GetMatMotion(int nFrame)
{
	return m_matMotion[nFrame];
};

//------------------------------------------------------
//	Name:	GetMeshFrameNum
//	Func:	���b�V���t���[�����̎擾
//	in:		�Ȃ�
//	Out:	int = ���b�V���t���[����
//------------------------------------------------------
inline int CActiveMotion::GetMeshFrameNum()
{
	return m_nMeshFrameNum;
};

//------------------------------------------------------
//	Name:	GetMotion
//	Func:	�w�胂�[�V�����f�[�^�̎擾
//	in:		int	nMotion	= �w�胂�[�V���� 
//	Out:	CActiveData = ���[�V�����f�[�^
//------------------------------------------------------
inline CActiveData* CActiveMotion::GetMotion(int nMotion)
{
	return m_pActiveData[nMotion];
};

//------------------------------------------------------
//	Name:	GetMotionNum
//	Func:	���[�V�������̎擾
//	in:		�Ȃ�
//	Out:	int = ���[�V������
//------------------------------------------------------
inline int CActiveMotion::GetMotionNum()
{
	return m_nActiveDataNum;
};

//------------------------------------------------------
//	Name:	GetBlend
//	Func:	�w�胂�[�V�����̃u�����h�W���̎擾
//	in:		int nMotion	= �w�胂�[�V����
//	Out:	float		= �u�����h�W��
//------------------------------------------------------
inline float CActiveMotion::GetBlend(int nMotion)
{
	return m_fBlendNum[nMotion];
}

//------------------------------------------------------
//	Name:	GetMaxTime
//	Func:	�w�胂�[�V�����̍ő�t���[������Ԃ�
//	in:		int nMotion	= �w�胂�[�V����
//	Out:	int			= �ő�t���[����
//------------------------------------------------------
inline int CActiveMotion::GetMaxTime(int nMotion)
{
	return m_pActiveData[nMotion]->GetMaxTime();
}

//------------------------------------------------------
//	Name:	SetMatMotion
//	Func:	�w��t���[���̃}�g���N�X�̃Z�b�g
//	in:		D3DXMATRIX	matMotion
//			int			nFrame
//	Out:	�Ȃ�
//------------------------------------------------------
inline void CActiveMotion::SetMatMotion(D3DXMATRIX matMotion, int nFrame)
{
	m_matMotion[nFrame] = matMotion;
}

//------------------------------------------------------
//	Name:	SetBlend
//	Func:	�w�胂�[�V�����Ƀu�����h�W�����Z�b�g
//	in:		int		nMotion	= �w�胂�[�V����
//			float	fBlend	= �u�����h�W��
//	Out:	�Ȃ�
//------------------------------------------------------
inline void CActiveMotion::SetBlend(int nMotion, float fBlend)
{
	m_fBlendNum[nMotion]=fBlend;
}

//------------------------------------------------------
//	Name:	SetBlend
//	Func:	���݃t���[�����Ԃ̊i�[
//	in:		int		nMotion = �w�胂�[�V����
//			int		nTime	= �w�莞��
//	Out:	�Ȃ�
//------------------------------------------------------
inline void CActiveMotion::SetActiveTime(int nMotion, int nTime)
{
	m_pActiveData[nMotion]->SetActiveTime(nTime);
}

#endif // !defined(AFX_Active_H__2AA65FEF_1CB0_4E22_8246_689FB7A01849__INCLUDED_)
