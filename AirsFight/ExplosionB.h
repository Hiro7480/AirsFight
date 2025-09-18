//==========================================================
// ExplosionB.h
// Auther : ���� ���V
// Data   : 2002/05/09
//==========================================================

#if !defined(AFX_EXPLOTIONB_H__FB55AF9D_7CC3_431C_859F_E631F67584CE__INCLUDED_)
#define AFX_EXPLOTIONB_H__FB55AF9D_7CC3_431C_859F_E631F67584CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	CExplositonB
//	Func:	�����G�t�F�N�gB
//			�e���L�����N�^�ɓ��������ꍇ
//----------------------------------------------
class CExplosionB : public CEffect  
{
private:
	tagParticle m_Particle[20];
	void InitParticle();		// �p�[�e�B�N���̏������W�A�����ړ��l�Ȃǂ̐ݒ�

public:
	void FrameMove();			// ���t���[���̏���

	CExplosionB(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CExplosionB();
};

#endif // !defined(AFX_EXPLOTIONB_H__FB55AF9D_7CC3_431C_859F_E631F67584CE__INCLUDED_)
