//==========================================================
// StageObj.cpp
// Auther : ���� ���V
// Data   : 2002/04/16
//==========================================================

#include "StageObj.h"

//----------------------------------------------
//	Name:	CStageObj
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3D�f�o�C�X
//	Out:	�Ȃ�
//----------------------------------------------
CStageObj::CStageObj(LPDIRECT3DDEVICE8 d3dDevice)
		  :C3DGraphicObj(d3dDevice)
{
	m_pMeshObject = NULL;
	m_fLength = 0;
}

//----------------------------------------------
//	Name:	~CStageObj
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CStageObj::~CStageObj()
{

}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CStageObj::FrameMove()
{

}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CStageObj::Render()
{
	/* ���b�V���̕`�� */
	m_pMeshObject->Render();
}

//--------------------------------------------------
//	Name:	InitMatrix
//	Func:	�}�g���N�X�̏�����
//	in:		D3DXVECTOR3	vecIn	= �I�u�W�F�N�g�̈ʒu
//			float		fYaw	= Yaw��]�p�x
//			float		fPitch	= Pitch��]�p�x
//			float		fRoll	= Roll��]�p�x
//	Out:	�Ȃ�
//--------------------------------------------------
void CStageObj::InitMatrix(D3DXVECTOR3 vecPos,
				float fYaw, float fPitch, float fRoll)
{
	D3DXMATRIX matTmp;

	/* �w�肵����]�p�ɉ�]������ */
	D3DXMatrixRotationYawPitchRoll(&matTmp, 
		D3DXToRadian(fYaw), D3DXToRadian(fPitch), D3DXToRadian(fRoll));

	/* �w�肵�����W�l�ɕ��s�ړ������� */
	matTmp._41 = vecPos.x;
	matTmp._42 = vecPos.y;
	matTmp._43 = vecPos.z;

	/* �}�g���N�X�̃Z�b�g */
	m_matBase = matTmp;
}

//--------------------------------------------------
//	Name:	LoadMesh
//	Func:	���b�V���̓ǂݍ���
//	in:		CMeshObjcet* pMesh	 = ���b�V���|�C���^
//			float		 fLength = �I�u�W�F�N�g�T�C�Y
//	Out:	�Ȃ�
//--------------------------------------------------
void CStageObj::LoadMesh(CMeshObject* pMesh)
{
	m_pMeshObject = pMesh;
	m_fLength = m_pMeshObject->GetLength();
}
