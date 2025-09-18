//==========================================================
// BoostB.h
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_BOOSTB_H__DA1C08DC_1EB1_42B6_8C5B_09255BD6EADA__INCLUDED_)
#define AFX_BOOSTB_H__DA1C08DC_1EB1_42B6_8C5B_09255BD6EADA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include "Effect.h"

//----------------------------------------------
//	Name:	CBoostA
//	Func:	�u�[�X�^�[�G�t�F�N�g�a
//			�W�����v���܂��͔�s���ɉ����ۂ�����
//----------------------------------------------
class CBoostB : public CEffect
{
private:
	tagParticle m_Particle[10];
	void InitParticle();		// �p�[�e�B�N���̏������W�A�����ړ��l�Ȃǂ̐ݒ�

public:
	void FrameMove();			// ���t���[���̏���

	CBoostB(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CBoostB();

};

#endif // !defined(AFX_BOOSTB_H__DA1C08DC_1EB1_42B6_8C5B_09255BD6EADA__INCLUDED_)
