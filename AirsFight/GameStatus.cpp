//==========================================================
// GameStatus.cpp
// Auther : ���� ���V
// Data   : 2002/01/11
//==========================================================

#include "GameStatus.h"

//------------------------------------------------------
//	Name:	GameStatus
//	Func:	�R���X�g���N�^
//	in	:	LPDIRECT3DDEVICE8 d3dDevice = D3D�f�o�C�X
//	Out	:	�Ȃ�
//------------------------------------------------------
GameStatus::GameStatus(LPDIRECT3DDEVICE8 d3dDevice)
{
	m_pd3dDevice = d3dDevice;
}

//----------------------------------------------
//	Name:	~GameStatus
//	Func:	�f�X�g���N�^
//	in	:	�Ȃ�
//	Out	:	�Ȃ�
//----------------------------------------------
GameStatus::~GameStatus()
{

}