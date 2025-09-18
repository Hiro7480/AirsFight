//==========================================================
// 2DGraphicObj.cpp
// Auther : ���� ���V
// Data   : 2002/02/26
//==========================================================

#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CGraphicObjcet
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3D�f�o�C�X
//	Out:	�Ȃ�
//----------------------------------------------
C2DGraphicObj::C2DGraphicObj(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* D3D�f�o�C�X�̃Z�b�g */
	m_pd3dDevice = d3dDevice;

	/* �x�N�g���̏����� */
	m_vecBase *= 0;
	m_vecStock *= 0;

	/* ���N�g�̏����� */
	SetRect(&m_rectBase, 0,0,0,0);
	SetRect(&m_rectStock, 0,0,0,0);
}

//----------------------------------------------
//	Name:	~CGraphicObjcet
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
C2DGraphicObj::~C2DGraphicObj()
{

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�̍X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void C2DGraphicObj::UpDate()
{
	/* �x�N�g���̍X�V */
	m_vecStock = m_vecBase;

	/* ���N�g�̍X�V */
	m_rectStock = m_rectBase;
}