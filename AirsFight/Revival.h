//==========================================================
// Revival.h
// Auther : ���� ���V
// Data   : 2002/05/09
//==========================================================

#if !defined(AFX_REVIVAL_H__2978C598_EAEB_42A9_B308_96F0C2D99610__INCLUDED_)
#define AFX_REVIVAL_H__2978C598_EAEB_42A9_B308_96F0C2D99610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include "CompatiDX8.h"
#include "Effect.h"

//----------------------------------------------
//	Name:	CRevival
//	Func:	�����G�t�F�N�g
//			�������̃G�t�F�N�g
//----------------------------------------------
class CRevival : public CEffect  
{
private:
	tagParticle m_Particle[100];
	void InitParticle();		// �p�[�e�B�N���̏������W�A�����ړ��l�Ȃǂ̐ݒ�

public:
	void FrameMove();			// ���t���[���̏���

	CRevival(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase);
	virtual ~CRevival();
};

#endif // !defined(AFX_REVIVAL_H__2978C598_EAEB_42A9_B308_96F0C2D99610__INCLUDED_)
