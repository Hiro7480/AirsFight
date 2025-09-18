//==========================================================
// OrbitBul.h
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_ORBITBUL_H__3438B47D_2AF4_4A15_802C_D37C9BD5F4B9__INCLUDED_)
#define AFX_ORBITBUL_H__3438B47D_2AF4_4A15_802C_D37C9BD5F4B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	COrbitBul
//	Func:	�����G�t�F�N�gA 
//			�e���ǂ�G�ɓ���������
//----------------------------------------------
class COrbitBul : public CEffect  
{
private:
	tagParticle m_Particle[3];
	void InitParticle();		// �p�[�e�B�N���̏������W�A�����ړ��l�Ȃǂ̐ݒ�

public:
	void FrameMove();			// ���t���[���̏���

	COrbitBul(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~COrbitBul();
};
#endif // !defined(AFX_ORBITBUL_H__3438B47D_2AF4_4A15_802C_D37C9BD5F4B9__INCLUDED_)
