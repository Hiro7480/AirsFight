//==========================================================
// Stage.h
// Auther : ���� ���V
// Data   : 2002/01/14
//==========================================================

#if !defined(AFX_STAGE_H__7D0F984D_3093_434A_90B1_4101C9D48CF9__INCLUDED_)
#define AFX_STAGE_H__7D0F984D_3093_434A_90B1_4101C9D48CF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include <d3dx8.h>
#include "StageObj.h"
#include "BlockA.h"

//----------------------------------------------
//	Name:	CStage
//	Func:	�X�e�[�W�̃I�u�W�F�N�g�̊Ǘ�
//----------------------------------------------
class CStage
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3D�f�o�C�X
	char			m_cStageName[256];	// �X�e�[�W�̖��O

	CStageObj*		m_pBlock[32];		// �u���b�N�^�C�v
	int				m_nBlockNum;		// �u���b�N�^�C�v�̐�

	CStageObj*		m_pWall[32];		// �ǃ^�C�v
	int				m_nWallNum;			// �ǃ^�C�v�̐�

	CMeshObject*	m_pMeshObject[10];	// ���b�V��

public:
	void FrameMove();					// �I�u�W�F�N�g�̈ړ���
	void Render();						// ��ʕ`��
	void UpDate();						// �`��p�}�g���N�X�̍X�V

	/* �A�N�Z�X�֐� */
	CStageObj*		GetBlockObj(int n){return m_pBlock[n];};// �u���b�N�̃��b�V����Ԃ�
	CStageObj*		GetWallObj(int n){return m_pWall[n];};	// �ǂ̃��b�V����Ԃ�

	int				GetBlockNum(){return m_nBlockNum;};	// �u���b�N����Ԃ�
	int				GetWallNum(){return m_nWallNum;};	// �E�H�[������Ԃ�


	CStage(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CStage();
};

#endif // !defined(AFX_STAGE_H__7D0F984D_3093_434A_90B1_4101C9D48CF9__INCLUDED_)
