//==========================================================
// 3DGraphicObj.h
// Auther : ���� ���V
// Data   : 2002/02/26
//==========================================================

#if !defined(AFX_GRAPHICOBJECT_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_)
#define AFX_3DGRAPHICOBJ_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "define.h"

//----------------------------------------------
//	Name:	C3DGraphicObj
//	Func:	�R�c�`��I�u�W�F�N�g�̊��N���X
//----------------------------------------------
class C3DGraphicObj  
{
protected:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3D�f�o�C�X
	D3DXMATRIX			m_matBase;		// �����p�}�g���N�X
	D3DXMATRIX			m_matStock;		// �`��p�}�g���N�X

public:
	virtual void FrameMove(){};							// ���t���[���̏���
	virtual void Render(){};							// �`�揈��
	virtual void UpDate(){m_matStock=m_matBase;};		// �`��p�}�g���N�X���X�V����

	/* �A�N�Z�X�֐�*/
	void	SetMatrix(D3DXMATRIX mat){m_matBase=mat;};	// �}�g���N�X�̃Z�b�g

	D3DXVECTOR3 GetPosBase();							// �}�g���N�X�̍��W���x�N�g���ŕԂ�
	D3DXVECTOR3 GetPosStock();							// �`��p�}�g���N�X�̒l���x�N�g���ŕԂ�
	D3DXMATRIX	GetMatBase(){return m_matBase;};		// �}�g���N�X��Ԃ�
	D3DXMATRIX	GetMatStock(){return m_matStock;};		// �`��p�}�g���N�X��Ԃ�

	D3DXMATRIX*	GetMatPointer(){return &m_matBase;};	// �}�g���N�X�̃|�C���^��Ԃ�

	C3DGraphicObj(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~C3DGraphicObj();
};

#endif // !defined(AFX_GRAPHICOBJECT_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_)
