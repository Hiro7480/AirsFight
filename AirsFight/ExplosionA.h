//==========================================================
// ExplosionA.h
// Auther : ���� ���V
// Data   : 2002/03/09
//==========================================================

#if !defined(AFX_EXPLOSIONA_H__FAB780A5_11A4_48AF_9B0A_72DAC45FB3F2__INCLUDED_)
#define AFX_EXPLOSIONA_H__FAB780A5_11A4_48AF_9B0A_72DAC45FB3F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	CExplositonA
//	Func:	�����G�t�F�N�gA 
//			�Жʂɔ�������
//----------------------------------------------
class CExplosionA : public CEffect  
{
private:
	tagParticle m_Particle[20];
	void InitParticle();		// �p�[�e�B�N���̏������W�A�����ړ��l�Ȃǂ̐ݒ�

public:
	void FrameMove();			// ���t���[���̏���

	CExplosionA(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CExplosionA();
};

#endif // !defined(AFX_EXPLOSIONA_H__FAB780A5_11A4_48AF_9B0A_72DAC45FB3F2__INCLUDED_)
