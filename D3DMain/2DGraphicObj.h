//==========================================================
// 2DGraphicObj.h
// Auther : ���� ���V
// Data   : 2002/02/26
//==========================================================

#if !defined(AFX_GRAPHICOBJECT_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_)
#define AFX_2DGRAPHICOBJ_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_

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
//	Name:	2DGraphicObj
//	Func:	�Q�c�`��I�u�W�F�N�g�̊��N���X
//----------------------------------------------
class C2DGraphicObj  
{
protected:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3D�f�o�C�X

	D3DXVECTOR2			m_vecBase;		// �����p�Q�c�x�N�g��
	D3DXVECTOR2			m_vecStock;		// �`��p�Q�c�x�N�g��

	RECT				m_rectBase;		// �����p���N�g
	RECT				m_rectStock;	// �`��p���N�g

public:
	virtual void FrameMove(){};			// ���t���[���̏���
	virtual void Render(){};			// �`�揈��
	virtual void UpDate();				// �f�[�^�X�V

	/* �A�N�Z�X�֐�*/
	void	SetVec(D3DXVECTOR2 vec){m_vecBase=vec;};			// �x�N�g���̃Z�b�g
	void	SetRec(int left, int top, int right, int bottom);	// ���N�g�̃Z�b�g

	D3DXVECTOR2 GetVecBase(){return m_vecBase;};		// �����p�x�N�g����Ԃ�
	D3DXVECTOR2 GetVecStock(){return m_vecStock;};		// �`��p�x�N�g����Ԃ�

	RECT		GetRectBase(){return m_rectBase;};		// �����p���N�g��Ԃ�
	RECT		GetRectStock(){return m_rectStock;};	// �`��p���N�g��Ԃ�

	C2DGraphicObj(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~C2DGraphicObj();
};

//----------------------------------------------
//	Name:	SetRec
//	Func:	���N�g�̃Z�b�g
//	In:		int left	= ���[���W
//			int top		= ��[���W
//			int right	= �E�[���W
//			int bottom	= ���[���W
//	Out:	�Ȃ�
//----------------------------------------------
inline void C2DGraphicObj::SetRec(int left, int top, int right, int bottom)
{
	SetRect(&m_rectBase, left, top, right, bottom);
}

#endif // !defined(AFX_GRAPHICOBJECT_H__342DB640_2C5D_11D6_AE82_0000E22796BF__INCLUDED_)
