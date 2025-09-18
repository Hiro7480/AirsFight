//==========================================================
// StageObj.h
// Auther : ���� ���V
// Data   : 2002/04/16
//==========================================================

#if !defined(AFX_StageObj_H__9DD608E0_1C33_4378_95B2_1BD0186E0ECF__INCLUDED_)
#define AFX_StageObj_H__9DD608E0_1C33_4378_95B2_1BD0186E0ECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include <d3dx8.h>
#include "3DGraphicObj.h"
#include "MeshData.h"

//----------------------------------------------
//	Name:	CStageObj
//	Func:	�X�e�[�W�I�u�W�F�N�g�̊��N���X
//----------------------------------------------
class CStageObj:public C3DGraphicObj
{
private:
	CMeshObject*		m_pMeshObject;	// ���b�V���ւ̃|�C���^
	float				m_fLength;		// �o�E���f�B���O�X�t�B�A�̃T�C�Y

public:

	virtual	void FrameMove();			// ���t���[���̏���
	virtual void Render();				// ��ʕ`��

	/* �������֐� */
	void	LoadMesh(CMeshObject* pMesh);					// ���b�V���̃��[�h
	void	InitMatrix(D3DXVECTOR3 vecPos,					// �}�g���N�X�̏�����
			float fYaw, float fPitch, float fRoll);

	/* �A�N�Z�X�֐� */
	CMeshObject*	GetMesh(){return m_pMeshObject;};	// ���b�V����Ԃ�
	float			GetLength(){return m_fLength;};		// �I�u�W�F�N�g�T�C�Y��Ԃ�

	CStageObj(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CStageObj();
};

#endif // !defined(AFX_StageObj_H__9DD608E0_1C33_4378_95B2_1BD0186E0ECF__INCLUDED_)
