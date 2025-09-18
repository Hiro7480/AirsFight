//==========================================================
// BoostA.h
// Auther : ���� ���V
// Data   : 2002/03/09
//==========================================================

#if !defined(AFX_BOOSTA_H__CF380D3C_1AEB_439B_A24E_405494248D63__INCLUDED_)
#define AFX_BOOSTA_H__CF380D3C_1AEB_439B_A24E_405494248D63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	CBoostA
//	Func:	�u�[�X�^�[�G�t�F�N�gA
//			�_�b�V�����ɑ������獻�����ۂ����̂��o��
//----------------------------------------------
class CBoostA : public CEffect  
{
private:
	tagParticle m_Particle[10];
	void InitParticle();		// �p�[�e�B�N���̏������W�A�����ړ��l�Ȃǂ̐ݒ�

public:
	void FrameMove();			// ���t���[���̏���

	CBoostA(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CBoostA();
};

#endif // !defined(AFX_BOOSTA_H__CF380D3C_1AEB_439B_A24E_405494248D63__INCLUDED_)
