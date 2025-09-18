//==========================================================
// GameStatus.h
// Auther : ���� ���V
// Data   : 2002/01/11
//==========================================================

#if !defined(AFX_GAMESTATUS_H__263F63A0_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_)
#define AFX_GAMESTATUS_H__263F63A0_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include "CompatiDX8.h"
#include <d3dx8.h>

//----------------------
//	�萔��`
//----------------------
/* ��ԕω����ʎq */
enum{
	NO_CHANGE,		// �ς��Ȃ�
	CHANGE_TITLE,	// �^�C�g���ֈڍs
	CHANGE_MENU,	// ���j���[�ֈڍs
	CHANGE_GAME,	// �Q�[���ֈڍs
	CHANGE_ENDING	// �G���f�B���O�ֈڍs
};

//----------------------------------------------
//	Name:	GameStatus
//	Func:	�Q�[���̏�Ԃ��Ǘ�������N���X
//----------------------------------------------
class GameStatus  
{
protected:
	LPDIRECT3DDEVICE8	m_pd3dDevice; 	// D3D�f�o�C�X

public:
	virtual int  FrameMove(){return 0;};
	virtual void Render(){};
	virtual void UpDate(){};

	GameStatus(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~GameStatus();
};

#endif // !defined(AFX_GAMESTATUS_H__263F63A0_06A4_11D6_A9B0_00B0D0ADB1AE__INCLUDED_)
